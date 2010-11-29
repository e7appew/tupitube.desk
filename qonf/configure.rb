# encoding: utf-8

require 'qonf/test'
require 'qonf/config'
require 'qonf/info'
require 'qonf/qonfexception'
require 'qonf/makefile'

module RQonf

class Configure
    attr_reader :qmake, :statusFile
    
    def initialize(args)
        @statusFile = Dir.getwd+"/configure.status"
        
        @tests = []
        @testsDir = Dir.getwd
        
        @options = {}
        parseArgs(args)
        
        @qmake = QMake.new
        
        setPath()       
        Makefile::setArgs(@options)
 
    end

    def hasArgument?(arg)
        @options.has_key?(arg)
    end

    def argumentValue(arg)
        @options[arg].to_s
    end
    
    def setTestDir(dir)
        @testsDir = dir
    end
    
        def verifyQtVersion(minqtversion)
                Info.info << "Checking for Qt >= " << minqtversion << "... "

                if @qmake.findQMake(minqtversion, true)
                        print "[ \033[92mOK\033[0m ]\n"
                else
                        print "[FAILED]\n"
                        raise QonfException.new("Invalid Qt version.\n   Please, upgrade to #{minqtversion} or higher (Visit: http://www.trolltech.com)")
                end
        end

    def createTests
        @tests.clear
        findTest(@testsDir)
    end
    
    def runTests(config, debug)
        @tests.each { |test|
            if not test.run(config, debug) and not test.optional
                raise QonfException.new("Required")
            end
        }
    end
    
    def createMakefiles
        Info.info << "Creating makefiles..." << $endl
        @qmake.run("", true)
        
        Info.info << "Updating makefiles and source code..." << $endl
        
        @makefiles = Makefile::findMakefiles(Dir.getwd)
        
        @makefiles.each { |makefile|
                           Makefile::override(makefile)
        }
    end
    
    private
    def parseArgs(args)
        optc = 0
        last_opt = ""
        while args.size > optc
            arg = args[optc].strip
            
            if arg =~ /^--([\w-]*)={0,1}([\W\w]*)/
                opt = $1.strip
                val = $2.strip

                @options[opt] = val
                
                last_opt = opt
            elsif arg =~ /^-(\w)/
                @options[$1.strip] = nil
                last_opt = $1.strip
            else
                # arg is an arg for option
                if not last_opt.to_s.empty? and @options[last_opt].to_s.empty?
                    @options[last_opt] = arg
                else
                    raise "Invalid option: #{arg}"
                end
            end
        
            optc += 1
        end
    end
    
    def findTest(path)
        if $DEBUG
            Info.warn << "Searching qonfs in: " << path << $endl
        end
        Dir.foreach(path) { |f|
            
            file = "#{path}/#{f}"

            if File.stat(file).directory?
                if not f =~ /^\./
                    findTest(file)
                end
            elsif file =~ /.qonf$/
                @tests << Test.new(file, @qmake)
            end
        }
    end

   private
    def setPath()
        if @options['prefix'].nil? then
           @options['prefix'] = "/usr/local/tupi"
        end
        if @options['bindir'].nil? then
           @options['bindir'] = @options['prefix'] + "/bin" 
        end
        if @options['libdir'].nil? then
           @options['libdir'] = @options['prefix'] + "/lib" 
        end
        if @options['includedir'].nil? then
           @options['includedir'] = @options['prefix'] + "/include" 
        end
        if @options['sharedir'].nil? then
           @options['sharedir'] = @options['prefix'] + "/share"
        end

        launcher_prefix = @options['prefix'] 
        launcher_sharedir = @options['sharedir']
        launcher_libdir = @options['libdir']
        launcher_includedir = @options['includedir']
        launcher_bindir = @options['bindir']

        if @options['debian-build'].nil? then
           @options['debian-build'] = "/usr"
        else
           @options['debian-build'] = @options['prefix']
           launcher_prefix = "/usr" 
           launcher_sharedir = "/usr/share/tupi" 
           launcher_libdir = "/usr/lib" 
           launcher_includedir = "/usr/include"
           launcher_bindir = "/usr/bin" 
        end

        newfile = "#!/bin/bash\n\n"
        newfile += "export TUPI_HOME=\"" + launcher_prefix + "\"\n"
        newfile += "export TUPI_SHARE=\"" + launcher_sharedir + "\"\n"
        newfile += "export TUPI_LIB=\"" + launcher_libdir + "\"\n"
        newfile += "export TUPI_PLUGIN=\"" + launcher_libdir + "/plugins\"\n"
        newfile += "export TUPI_INCLUDE=\"" + launcher_includedir + "\"\n"
        newfile += "export TUPI_BIN=\"" + launcher_bindir + "\"\n\n"
        newfile += "export LD_LIBRARY_PATH=\"\$\{TUPI_LIB\}:\$\{TUPI_PLUGIN\}:$LD_LIBRARY_PATH\"\n\n"
        newfile += "exec ${TUPI_BIN}/tupi.bin $*"

        launcher = File.open("launcher/tupi", "w") { |f|
                   f << newfile
        }

        newfile = "[Desktop Entry]\n"
        newfile += "Encoding=UTF-8\n"
        newfile += "Name=Tupi: Magic 2D\n"
        newfile += "Name[es]=Tupí: Magia 2D\n"
        newfile += "Name[pt]=Tupí: Magia 2D\n"
        newfile += "Name[ru]=Tupi: Magic 2D\n"
        newfile += "Exec=" + launcher_bindir + "/tupi\n"
        newfile += "Icon=tupi.png\n"
        newfile += "Type=Application\n"
        newfile += "MimeType=application/tup;application/ntup;\n"
        newfile += "Categories=Application;Graphics;2DGraphics;RasterGraphics;\n"
        newfile += "Comment=2D Animation Toolkit\n"
        newfile += "Comment[es]=Herramienta para Animación 2D\n"
        newfile += "Comment[pt]=Ferramenta de animação 2D\n"
        newfile += "Comment[ru]=Создание двухмерной векторной анимации\n"
        newfile += "Terminal=false\n"

        launcher = File.open("launcher/tupi.desktop", "w") { |f|
                   f << newfile
        }

        newmakefile = ""
        File.open("src/components/help/help/css/tupi.ini", "r") { |f|
                  lines = f.readlines
                  index = 0
                  while index < lines.size
                        line = lines[index]
                        if line.include? "TUPI_SHARE" then
                           newmakefile += "#{line.gsub(/\$\(TUPI_SHARE\)/, launcher_sharedir)}"
                        else
                           newmakefile += line
                        end
                        
                        index += 1
                  end
        }

        File.open("src/components/help/help/css/tupi.css", "w") { |f|
             f << newmakefile
        }

    end
end
end # module

if __FILE__ == $0
    begin
        conf = RQonf::Configure.new()
        
        conf.verifyQtVersion("4.5.0")
        conf.createTests
        conf.createConfig("config.pri")
    rescue QonfException => err
        Info.error << "Configure failed. error was: #{err.message}\n"
    rescue => err
        Info.error << "General failure: #{err.message}\n" << err.backtrace
    end
end

