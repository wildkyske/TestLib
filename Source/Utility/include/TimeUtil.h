#pragma once
#ifndef TIME_UTIL_H
#define TIME_UTIL_H

#include "XTask.h"

namespace TimeUtil
{
    class UTILITY_EXPORT TimeUser
    {
    public:
        TimeUser();
        virtual ~TimeUser();

        virtual void onTimerEvent() = 0;
    };

    /*
    	ClassName:	Timer
    	Brief:		��ʱ��
    	Author:		Administrator
    	Date:		2013/04/11
    */
    class UTILITY_EXPORT Timer : public XTask
    {
    public:
        enum{DEFAULT_TIME_PERIOD = 1000};//һ�����ʱ����
    public:
        Timer();
        virtual ~Timer();

        /*
        	Method:    	attachUser [Access:public ]
        	Brief:    	����һ���û�
        	Returns:   	void
        	Date:		2013/04/11 - Author:Administrator
        	Parameter: 	TimeUser * pUser
        */
        void attachUser(TimeUser* pUser);

        /*
        	Method:    	setTimer [Access:public ]
        	Brief:    	���ö�ʱ��
        	Returns:   	void
        	Date:		2013/04/11 - Author:Administrator
        	Parameter: 	int nTimePeriod
        */
        void startTimer(int nTimePeriod = -1);

        /*
        	Method:    	killTimer [Access:public ]
        	Brief:    	ɱ����ʱ��
        	Returns:   	void
        	Date:		2013/04/11 - Author:Administrator
        */
        void killTimer();

        /*
        	Method:    	setTimerPeriod [Access:public ]
        	Brief:    	����ʱ������
        	Returns:   	void
        	Date:		2013/04/11 - Author:Administrator
        	Parameter: 	int nTimePeriod
        */
        void setTimerPeriod(int nTimePeriod = -1);

        /*
        	Method:    	timerPeriod [Access:public ]
        	Brief:    	��ʱ�����
        	Returns:   	int
        	Date:		2013/04/11 - Author:Administrator
        */
        int timerPeriod() const;
    protected:
        /*
        	Method:    	onRunTask [Access:virtual protected ]
        	Brief:    	�߳�
        	Returns:   	void
        	Date:		2013/04/11 - Author:Administrator
        */
        virtual void onRunTask();
    protected:
        TimeUser* mUserPtr;//�û�

        int mTimePeriod;//����
    };
}

#endif
