#include "../include/TimeUtil.h"
#include <string.h>

namespace TimeUtil
{
    TimeUser::TimeUser()
    {

    }

    TimeUser::~TimeUser()
    {

    }

    //================================

    Timer::Timer() : mUserPtr(NULL)
    {

    }

    Timer::~Timer()
    {

    }

    void Timer::attachUser( TimeUser* pUser )
    {
        mUserPtr = pUser;
    }

    void Timer::onRunTask()
    {
        while(1)
        {
            if (TASK_STATUS_STOP == taskStatus())
            {
                break;
            }

#ifdef WIN32
            Sleep(DEFAULT_TIME_PERIOD);
#elif defined(__linux__)

#endif

            if (NULL != mUserPtr)
            {
                mUserPtr->onTimerEvent();
            }
        }
    }

    void Timer::killTimer()
    {
        mUserPtr = NULL;

        stop();
    }

    void Timer::startTimer( int nTimePeriod )
    {
        mTimePeriod = nTimePeriod < 0 ? DEFAULT_TIME_PERIOD : nTimePeriod;

        //¿ªÆôÏß³Ì
        active();
    }

    void Timer::setTimerPeriod( int nTimePeriod )
    {
        mTimePeriod = nTimePeriod < 0 ? DEFAULT_TIME_PERIOD : nTimePeriod;
    }

    int Timer::timerPeriod() const
    {
        return mTimePeriod;
    }

}
