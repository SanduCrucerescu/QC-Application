QT       += core gui sql printsupport widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adding.cpp \
    cart.cpp \
    main.cpp \
    mainwin.cpp \
    mainwindow.cpp \
    modify.cpp

HEADERS += \
    adding.h \
    cart.h \
    mainwin.h \
    mainwindow.h \
    modify.h

FORMS += \
    adding.ui \
    cart.ui \
    mainwin.ui \
    mainwindow.ui \
    modify.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
