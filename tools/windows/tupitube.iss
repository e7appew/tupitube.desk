[Setup]
AppName=TupiTube Desk
AppVersion=0.2.10
AppPublisher=MaeFloresta
AppPublisherURL=https://www.maefloresta.com/
DefaultDirName={pf}\TupiTube
DefaultGroupName=TupiTube
OutputDir=c:\devel\installer
ChangesEnvironment=yes
ChangesAssociations=yes
; Uncomment this line for 64bit installer
; ArchitecturesInstallIn64BitMode=x64

[Dirs]
Name: "{app}\bin"
Name: "{app}\bin\platforms"
Name: "{app}\bin\imageformats"
Name: "{app}\bin\mediaservice"
Name: "{app}\bin\audio"
Name: "{app}\data"
Name: "{app}\data\html"
Name: "{app}\data\html\css"
Name: "{app}\data\html\examples"
Name: "{app}\data\html\images"
Name: "{app}\data\html\pages"
Name: "{app}\data\palettes"
Name: "{app}\data\storyboard"
Name: "{app}\data\themes"
Name: "{app}\data\themes\default"
Name: "{app}\data\themes\defaul\config"
Name: "{app}\data\themes\default\cursors"
Name: "{app}\data\themes\default\icons"
Name: "{app}\data\themes\default\images"
Name: "{app}\data\themes\dark"
Name: "{app}\data\themes\dark\config"
Name: "{app}\data\themes\dark\cursors"
Name: "{app}\data\themes\dark\icons"
Name: "{app}\data\themes\dark\images"
Name: "{app}\data\translations"
Name: "{app}\data\xml"
Name: "{app}\data\xml\en"
Name: "{app}\data\xml\es"
Name: "{app}\data\xml\fr"
Name: "{app}\data\xml\pt"
Name: "{app}\plugins"
Name: "{app}\lib"
Name: "{app}\lib\qt5"
Name: "{app}\lib\libav"

[Files]
Source: "bin\*"; DestDir: "{app}\bin"
Source: "bin\platforms\*"; DestDir: "{app}\bin\platforms"
Source: "bin\imageformats\*"; DestDir: "{app}\bin\imageformats"
Source: "bin\mediaservice\*"; DestDir: "{app}\bin\mediaservice"
Source: "bin\audio\*"; DestDir: "{app}\bin\audio"
Source: "data\html\css\*"; DestDir: "{app}\data\html\css"
Source: "data\html\examples\*"; DestDir: "{app}\data\html\examples"
Source: "data\html\images\*"; DestDir: "{app}\data\html\images"
Source: "data\html\pages\*"; DestDir: "{app}\data\html\pages"
Source: "data\palettes\*"; DestDir: "{app}\data\palettes"
Source: "data\storyboard\*"; DestDir: "{app}\data\storyboard"
Source: "data\themes\default\config\*"; DestDir: "{app}\data\themes\default\config"
Source: "data\themes\default\cursors\*"; DestDir: "{app}\data\themes\default\cursors"
Source: "data\themes\default\icons\*"; DestDir: "{app}\data\themes\default\icons"
Source: "data\themes\default\images\*"; DestDir: "{app}\data\themes\default\images"
Source: "data\themes\dark\config\*"; DestDir: "{app}\data\themes\dark\config"
Source: "data\themes\dark\cursors\*"; DestDir: "{app}\data\themes\dark\cursors"
Source: "data\themes\dark\icons\*"; DestDir: "{app}\data\themes\dark\icons"
Source: "data\themes\dark\images\*"; DestDir: "{app}\data\themes\dark\images"
Source: "data\translations\*"; DestDir: "{app}\data\translations"
Source: "data\xml\en\*"; DestDir: "{app}\data\xml\en"
Source: "data\xml\es\*"; DestDir: "{app}\data\xml\es"
Source: "data\xml\fr\*"; DestDir: "{app}\data\xml\fr"
Source: "data\xml\pt\*"; DestDir: "{app}\data\xml\pt"
Source: "plugins\*"; DestDir: "{app}\plugins"
Source: "lib\*"; DestDir: "{app}\lib"
Source: "lib\qt5\*"; DestDir: "{app}\lib\qt5"
Source: "lib\libav\*"; DestDir: "{app}\lib\libav"

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: string; ValueName: "TUPITUBE_HOME"; ValueData: "{app}"; Flags: uninsdeletevalue
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: string; ValueName: "TUPITUBE_SHARE"; ValueData: "{app}\data"; Flags: uninsdeletevalue
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: string; ValueName: "TUPITUBE_PLUGIN"; ValueData: "{app}\plugins"; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".tup"; ValueType: string; ValueName: ""; ValueData: "TupiTubeDesk"; Flags: uninsdeletevalue 
Root: HKCR; Subkey: "TupiTubeDesk"; ValueType: string; ValueName: ""; ValueData: "TupiTube Desk"; Flags: uninsdeletekey
Root: HKCR; Subkey: "TupiTubeDesk\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\bin\tupitube.ico,0"; Flags: uninsdeletekey
Root: HKCR; Subkey: "TupiTubeDesk\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\TupiTube.vbs"" ""%1"""; Flags: uninsdeletekey

[Icons]
Name: "{group}\TupiTube Desk"; Filename: "{app}\bin\TupiTube.vbs"; IconFilename: "{app}\bin\tupitube.ico"
Name: "{commondesktop}\TupiTube Desk"; Filename: "{app}\bin\TupiTube.vbs"; IconFilename: "{app}\bin\tupitube.ico"; Comment: "2D Animation Tool"
