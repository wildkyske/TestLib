#-------------------------------------------------
#
# Project created by QtCreator 2014-12-21T10:30:46
#
#-------------------------------------------------

QT       -= core gui

TARGET = Utility
TEMPLATE = lib

DEFINES +=UTILITY_EXPORTS
DEFINES +=UNICODE
DEFINES +=_GLIBCXX_USE_WCHAR_T
DEFINES += LINUX

INCLUDEPATH += ./include
OBJECTS_DIR = ../../obj/Utility
DESTDIR = ../../App/linux

#CONFIG += staticlib
CONFIG += warn_off

SOURCES +=    src/XMouseKeyboard.cpp \
    src/AutoRegisterObjectManager.cpp \
    src/CloneObject.cpp \
    src/CodeConvert.cpp \
    src/DebugObject.cpp \
    src/DllLoader.cpp \
    src/DllLoadObserver.cpp \
    src/DllManager.cpp \
    src/DllManager_Implement.cpp \
    src/FileDirControl.cpp \
    src/GlobalKeyGenerator.cpp \
    src/Graph.cpp \
    src/MapPoint.cpp \
    src/MathUtilBase.cpp \
    src/MessageIDGenerator.cpp \
    src/MutexLock.cpp \
    src/Random.cpp \
    src/RandomNumber.cpp \
    src/ReflectObject.cpp \
    src/ReflectObject_Implement.cpp \
    src/RGBA.cpp \
    src/Subject.cpp \
    src/Timer.cpp \
    src/UniqueIDGenerator.cpp \
    src/XEncoder.cpp \
    src/StlUtil.cpp \
    src/Telegram.cpp \
    src/CodeConvertNet.cpp \
    src/XUnitTestBase.cpp

HEADERS +=  utility_global.h \
    include/AutoImplement.h \
    include/AutoRegisterObject.h \
    include/AutoRegisterObjectManager.h \
    include/AutoRegisterProxy.h \
    include/base_constant.h \
    include/CloneObject.h \
    include/CodeConvert.h \
    include/CommandSimulate.h \
    include/DebugObject.h \
    include/DllLoader.h \
    include/DllLoadObserver.h \
    include/DllManager.h \
    include/DllManager_Implement.h \
    include/EventDef.h \
    include/excepts.h \
    include/FileDirControl.h \
    include/GlobalKeyGenerator.h \
    include/Graph.h \
    include/Guard.h \
    include/KeyObjectManager.h \
    include/KeyPointerManager.h \
    include/KeyValue.h \
    include/MapPoint.h \
    include/MathUtilBase.h \
    include/md5.h \
    include/MemoryManager.h \
    include/MessageIDGenerator.h \
    include/MutexLock.h \
    include/obj.h \
    include/ObserverBase.h \
    include/PropertyMacro.h \
    include/Random.h \
    include/RandomNumber.h \
    include/ReflectObject.h \
    include/ReflectObject_Implement.h \
    include/RGBA.h \
    include/Singleton.h \
    include/SmartPtr.h \
    include/State.h \
    include/StateMachine.h \
    include/Subject.h \
    include/Timer \
    include/typedefs.h \
    include/UniqueIDGenerator.h \
    include/UsefulStlEx.h \
    include/utility_common.h \
    include/UtilityExport.h \
    include/XEncoder.h \
    include/XMouseKeyboard.h \
    include/StlUtil.h \
    include/Telegram.h \
    include/XUnitTestBase.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
