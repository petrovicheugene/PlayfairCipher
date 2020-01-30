QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#PRO VARS

#Application version
VER_MAJ=1
VER_MIN=0
VER_PAT=0

PRODUCT_SHORT_NAME="PlayfairCipher"
PRODUCT_FILE_BASE_NAME="playfaircipher"
QMAKE_TARGET_PRODUCT="Playfair Cipher"
QMAKE_TARGET_DESCRIPTION="Playfair cipher"
QMAKE_TARGET_COMPANY="Petrovich"
QMAKE_TARGET_COPYRIGHT="Copyright © $${QMAKE_TARGET_COMPANY} Ltd. 2020. All rights reserved."
COMPANY_URL=www.tpu.ru
PROJECT_ROOT_PATH = $${PWD}/

win32: OS_SUFFIX = win32
linux-g++: OS_SUFFIX = linux

CONFIG += c++11
CONFIG += c++14
#CONFIG += c++17
#preserve src directory structure in build directory
#CONFIG += object_parallel_to_source

#CONFIG -= debug_and_release
#CONFIG -= debug_and_release_target

VERSION=$${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d

} else {
    BUILD_FLAG = release
}

#Define the preprocessor macro to get the application version in the application.
DEFINES += APP_DISPLAY_NAME=\"\\\"$${QMAKE_TARGET_PRODUCT}\\\"\"
DEFINES += APP_PRODUCT=\"\\\"$${PRODUCT_SHORT_NAME}\\\"\"
DEFINES += APP_VERSION=\"\\\"$${VERSION}.$${VER_RELEASE}\\\"\"
DEFINES += APP_COMPANY=\"\\\"$${QMAKE_TARGET_COMPANY}\\\"\"
DEFINES += APP_COMPANY_URL=\"\\\"$${COMPANY_URL}\\\"\"
DEFINES += APP_COPYRIGHT=\"\\\"$${QMAKE_TARGET_COPYRIGHT}\\\"\"
DEFINES += APP_ICON=\"\\\"$${RC_ICONS}\\\"\"

#DEBUG SETTINGS
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
#by default defined: in Debug mode QT_DEBUG, in Release mode QT_NO_DEBUG

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



SOURCES += \
    ControlPanel.cpp \
    PlayfairCipher.cpp \
    ZTranslatorManager.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    ControlPanel.h \
    MainWindow.h \
    PlayfairCipher.h \
    ZTranslatorManager.h

TRANSLATIONS += \
    PlayfairCipher_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
