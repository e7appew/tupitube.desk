# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./src/plugins/tools/texttool
# Target is a library:  

INSTALLS += target 
target.path = /plugins/ 
KDEV_QTVER = 4 
CONFIG += plugin 
include(../../../../tupiglobal.pri)
TEMPLATE = lib 
HEADERS += texttool.h \
           textconfigurator.h 
SOURCES += texttool.cpp \
           textconfigurator.cpp 

FRAMEWORK_DIR = "../../../framework"
include($$FRAMEWORK_DIR/framework.pri)

include(../tools_config.pri)
