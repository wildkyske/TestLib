#pragma once
#ifndef EVENT_DEF_H
#define EVENT_DEF_H

#include "UtilityExport.h"
#include "typedefs.h"
#include "XMouseKeyboard.h"

/*
@. 主要用来处理鼠标键盘等信息.
*/
class /*UTILITY_EXPORT*/ EventArgument
{
public:
    //事件类型
    enum
    {
        EVT_TYPE_NONE = 0,
        //鼠标
        EVT_TYPE_PUSH = 1<<0,
        EVT_TYPE_CLICK = EVT_TYPE_PUSH,
        EVT_TYPE_RELEASE = 1<<1,
        EVT_TYPE_DBLCLICK = 1<<2,
        EVT_TYPE_DRAG = 1<<3,
        EVT_TYPE_MOVE = 1<<4,
        //键盘
        EVT_TYPE_KEYDOWN = 1<<5,
        EVT_TYPE_KEYUP = 1<<6,
        //
        EVT_TYPE_FRAME = 1<<7,
        EVT_TYPE_QUIT = 1<<15,
        EVT_TYPE_USER = 1<<16,
    };

    enum{
        MOUSE_BUTTON_LEFT = 1<<0,
        MOUSE_BUTTON_MIDDLE = 1<<1,
        MOUSE_BUTTON_RIGHT = 1<<2,
    };
public:
    EventArgument(){}
    ~EventArgument(){}

public:
    int mEvtType;
    int mEvtCode;
    XMouseKeyboard::KEY mKey;//键盘
    XMouseKeyboard::MOUSE mMouseButton;//鼠标
    int mMouseX;
    int mMouseY;
    double mX;
    double mY;
    double mZ;
};

#endif
