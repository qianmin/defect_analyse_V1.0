QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 手动添加工程包含（include）目录：
INCLUDEPATH+= C:\software\opencv\opencv4151\opencv\build\include
INCLUDEPATH+= C:\software\opencv\opencv4151\opencv\build\include\opencv 	// 可不添加
INCLUDEPATH+= C:\software\opencv\opencv4151\opencv\build\include\opencv2	// 可不添加

# 手动添加工程库（lib）目录：
LIBS += -LC:/software/opencv/opencv4151/opencv/build/x64/vc15/lib/ -lopencv_world451d
#(d表示debug，release慢一点就不会报错）

RESOURCES += \
    tset1.qrc
