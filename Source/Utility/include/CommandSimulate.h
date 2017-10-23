#pragma once

#include "typedefs.h"
#include "UsefulStlEx.h"
#include "KeyPointerManager.h"

/*
	@. brief 仿真命令管理

    @. namespace CmdSimulate

	@. author Administrator . 2/19/2013 .
*/

namespace CmdSimulate
{
    class ICommand;

    class CommandManager : public KeyPointerManager<const tstring, ICommand>
    {
    public:
        static CommandManager* getInstancePtr()
        {
            static CommandManager _instance;
            return &_instance;
        }

        bool registerCommand(ICommand* pCmd)
        {
            if (NULL ==pCmd)
            {
                return false;
            }

            if (!pCmd->isValid())
            {
                return false;
            }

            return insertObject(pCmd->mCmdParam[0], pCmd);
        }

    };

    class ICommand
    {
    public:

        ICommand(const tstring& cmdTxt)
        {
            fill(cmdTxt);

            CommandManager::getInstancePtr()->registerCommand(this);
        }

        //返回true成功，返回false失败.
        bool run()
        {
            if (!isValid())
            {
                return false;
            }

            return onRun();
        }

        ~ICommand(){}

        void fill(const tstring& cmdTxt, int nCmdCode = -1, const tstring& cmdDesc = _TX(""))
        {
            mCmdDesc = cmdDesc;
            mCmdCode = nCmdCode;
            mCmdParam = stlu::SplitC(cmdTxt, _TX(" "));
        }

        bool isValid() const
        {
            if (mCmdParam.size() < 1)
            {
                return false;
            }

            for (int i = 0; i < mCmdParam.size(); ++i)
            {
                if (mCmdParam[i].length() <= 0)
                {
                    return false;
                }
            }

            return true;
        }
    protected:
        virtual bool onRun() = 0;

    protected:
        //命令代码
        int mCmdCode;

        //命令参数
        std::vector<tstring> mCmdParam;

        //命令描述
        tstring mCmdDesc;
    };
}
