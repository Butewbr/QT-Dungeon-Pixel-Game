QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attack.cpp \
    boneattack.cpp \
    burger.cpp \
    carbunis.cpp \
    chest.cpp \
    choosecharacter.cpp \
    commands.cpp \
    demon.cpp \
    entrance.cpp \
    fireball.cpp \
    game.cpp \
    ground.cpp \
    healthpoints.cpp \
    hitbox.cpp \
    main.cpp \
    mainwindow.cpp \
    meteor.cpp \
    obiunam.cpp \
    skeleton.cpp \
    slash3d.cpp \
    slime.cpp \
    specialattack.cpp

HEADERS += \
    attack.h \
    boneattack.h \
    burger.h \
    carbunis.h \
    chest.h \
    choosecharacter.h \
    commands.h \
    demon.h \
    entrance.h \
    fireball.h \
    game.h \
    ground.h \
    healthpoints.h \
    hitbox.h \
    mainwindow.h \
    meteor.h \
    obiunam.h \
    skeleton.h \
    slash3d.h \
    slime.h \
    specialattack.h

FORMS += \
    choosecharacter.ui \
    commands.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
