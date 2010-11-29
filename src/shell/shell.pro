# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./src/shell
# Target is an application:  ../../bin/tupi.bin

INSTALLS += tupidata \
            launcher \
            desktop \
            icons \
            tupiman \
            target 

target.path = /bin/ 

launcher.target = ../../launcher/tupi
launcher.commands = cp ../../launcher/tupi $(INSTALL_ROOT)/bin
launcher.path = /bin/

tupiman.target = ../components/help/help/man/tupi.1
tupiman.commands = cp ../components/help/help/man/tupi.1 $(INSTALL_ROOT)/man1
tupiman.path = /man1/

desktop.target = ../../launcher/tupi.desktop
desktop.commands = cp ../../launcher/tupi.desktop $(INSTALL_ROOT)/applications
desktop.path = /applications/

icons.target = ../../launcher/icons/tupi.png
icons.commands = cp ../../launcher/icons/tupi.png $(INSTALL_ROOT)/pixmaps
icons.path = /pixmaps/

tupidata.target = data
tupidata.commands = cp -r data/* $(INSTALL_ROOT)/data
tupidata.path = /data/ 

TRANSLATIONS += data/translations/tupi_es.ts \
                data/translations/tupi_ca.ts \
                data/translations/tupi_ru.ts
HEADERS += ktmainwindow.h \
           ktstatusbar.h \
           ktnewproject.h \
           ktsplash.h \
           ktcrashhandler.h \
           ktcrashwidget.h \
           ktapplication.h \
           configwizard.h \
           ktlocalprojectmanagerhandler.h
SOURCES += main.cpp \
           ktmainwindow.cpp \
           ktstatusbar.cpp \
           ktnewproject.cpp \
           ktsplash.cpp \
           ktcrashhandler.cpp \
           ktcrashwidget.cpp \
           ktapplication.cpp \
           configwizard.cpp \
           ktmainwindow_gui.cpp \
           ktlocalprojectmanagerhandler.cpp

FRAMEWORK_DIR = "../framework"
include($$FRAMEWORK_DIR/framework.pri)

include(shell_config.pri)
include(../../tupiglobal.pri)
TARGET = ../../bin/tupi.bin
TEMPLATE = app
linux-g{
    TARGETDEPS += ../../src/libtupi/libtupi.so \
  ../../src/libui/libui.a \
  ../../src/store/libtupistore.so \
  ../../src/components/pen/libpen.a \
  ../../src/components/kinas/libkinas.a \
  ../../src/components/help/libhelp.a \
  ../../src/components/import/libimport.a \
  ../../src/components/export/libexport.a \
  ../../src/components/exposure/libexposure.a \
  ../../src/components/timeline/libtimeline.a \
  ../../src/components/library/liblibrary.a \
  ../../src/components/colorpalette/libcolorpalette.a \
  ../../src/components/scenes/libscenes.a \
  ../../src/components/twitter/libtwitter.a
}

