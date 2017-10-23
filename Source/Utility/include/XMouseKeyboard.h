#pragma once

#include "UtilityExport.h"

/*
    @. �����ṩ���������ͼ��̰�����Ϣ����һЩת�빤�����Լ�֧�ֶ�ƽ̨.
*/
class UTILITY_EXPORT XMouseKeyboard
{
public:
    typedef enum stKEY
    {
        KEY_A = 0x32,
        KEY_B = 0x33,
        KEY_C = 0x34,
    }KEY;

    typedef enum stMOUSE
    {
        MOUSE_LEFT_BUTTON,
        MOUSE_MIDDLE_BUTTON,
        MOUSE_RIGHT_BUTTON,
    }MOUSE;

    typedef enum stKEY_STATE
    {
        KEY_ST_UP,
        KEY_ST_DOWN,
    }KEY_STATE;

    typedef enum stMOUSE_STATE
    {
        MOUSE_ST_CLICK,
        MOUSE_ST_PRESS,
        MOUSE_ST_RELEASE,
    }MOUSE_STATE;
public:
    XMouseKeyboard(void);
    ~XMouseKeyboard(void);

    static bool isKeyDown(int nKey);

    static bool isKeyUp(int nKey);
};
