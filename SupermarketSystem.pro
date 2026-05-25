QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databasemanager.cpp \
    inventory_widget.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    member_widget.cpp \
    report_widget.cpp \
    saleswidget.cpp

HEADERS += \
    databasemanager.h \
    inventory_widget.h \
    logindialog.h \
    mainwindow.h \
    member_widget.h \
    report_widget.h \
    saleswidget.h

FORMS += \
    logindialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
