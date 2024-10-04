QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    info.cpp \
    main.cpp \
    mainwindow.cpp \
    signup.cpp \
    taskcreator.cpp \
    updatet.cpp \
    updateuser.cpp \
    user.cpp

HEADERS += \
    admin.h \
    info.h \
    mainwindow.h \
    signup.h \
    taskcreator.h \
    updatet.h \
    updateuser.h \
    user.h

FORMS += \
    admin.ui \
    info.ui \
    mainwindow.ui \
    signup.ui \
    taskcreator.ui \
    updatet.ui \
    updateuser.ui \
    user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    projects.db \
    projects.db \
    projects.txt \
    timeline.db \
    users.db
