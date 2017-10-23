#pragma once

#include "typedefs.h"
#include "UsefulStlEx.h"
#include "KeyPointerManager.h"

/*
	@. brief �����������

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

        //����true�ɹ�������falseʧ��.
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
        //�������
        int mCmdCode;

        //�������
        std::vector<tstring> mCmdParam;

        //��������
        tstring mCmdDesc;
    };
}
