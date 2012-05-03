# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./src/components/exposure
# Target is a library:  

INSTALLS += target
target.path = /lib/

macx {
    CONFIG += staticlib warn_on
}

HEADERS += tupexposuresheet.h \
           tupexposureheader.h \
           tupexposuretable.h \
           tupscenetabwidget.h

SOURCES += tupexposuresheet.cpp \
           tupexposureheader.cpp \ 
           tupexposuretable.cpp \
           tupscenetabwidget.cpp
*:!macx{
    CONFIG += dll warn_on
}

TEMPLATE = lib
TARGET = exposure

FRAMEWORK_DIR = "../../framework"
include($$FRAMEWORK_DIR/framework.pri)
include(../components_config.pri)
