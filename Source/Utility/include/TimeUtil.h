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
    	Brief:		定时器
    	Author:		Administrator
    	Date:		2013/04/11
    */
    class UTILITY_EXPORT Timer : public XTask
    {
    public:
        enum{DEFAULT_TIME_PERIOD = 1000};//一个最短时间间隔
    public:
        Timer();
        virtual ~Timer();

        /*
        	Method:    	attachUser [Access:public ]
        	Brief:    	附加一个用户
        	Returns:   	void
        	Date:		2013/04/11 - Author:Administrator
        	Parameter: 	TimeUser * pUser
        */
        void attachUser(TimeUser* pUser);

        /*
        	Method:    	setTimer [Access:public ]
        	Brief:    	设置定时器
        	Returns:   	void
        	Date:		2013/04/11 - Author:Administrator
        	Parameter: 	int nTimePeriod
        */
        void startTimer(int nTimePeriod = -1);

        /*
        	Method:    	killTimer [Access:public ]
        	Brief:    	杀死定时器
        	Returns:   	void
        	Date:		2013/04/11 - Author:Administrator
        */
        void killTimer();

        /*
        	Method:    	setTimerPeriod [Access:public ]
        	Brief:    	设置时间周期
        	Returns:   	void
        	Date:		2013/04/11 - Author:Administrator
        	Parameter: 	int nTimePeriod
        */
        void setTimerPeriod(int nTimePeriod = -1);

        /*
        	Method:    	timerPeriod [Access:public ]
        	Brief:    	定时器间隔
        	Returns:   	int
        	Date:		2013/04/11 - Author:Administrator
        */
        int timerPeriod() const;
    protected:
        /*
        	Method:    	onRunTask [Access:virtual protected ]
        	Brief:    	线程
        	Returns:   	void
        	Date:		2013/04/11 - Author:Administrator
        */
        virtual void onRunTask();
    protected:
        TimeUser* mUserPtr;//用户

        int mTimePeriod;//周期
    };
}

#endif
