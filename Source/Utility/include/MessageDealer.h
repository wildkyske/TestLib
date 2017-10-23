#pragma once
#ifndef MESSAGE_DEALER_H
#define MESSAGE_DEALER_H
/*
	filename	: 	MessageDealer.h
	created		:	2013/03/17  12:22
	author		:	LiKuan
	desc		:	��Ϣ����������Ҫ������Ϣ�ļ̳д���
	note		:	
	copyright @ xcahr studio. e-mail:530754393@qq.com
*/
#include "Telegram.h"
#include "UtilityExport.h"

/*
	ClassName:	MessageDealer
	Brief:		��Ϣ�����ߣ������շ���Ϣ
	Author:		LiKuan
	Date:		2013/03/17
*/
class UTILITY_EXPORT MessageDealer
{
public:
    MessageDealer();
    virtual ~MessageDealer();

    /*
    	Method:    	sendMessage [Access:public ]
    	Brief:    	������Ϣ
    	Returns:   	void
    	Date:		2013/03/17 - Author:LiKuan
    	Parameter: 	MessageDealer * other,  ��Ϣ������
    	Parameter: 	int msg, ��Ϣ����
    	Parameter: 	void * extra, ������Ϣ
    	Parameter: 	double nDealyTime, �ӳٷ���
    */
    void sendMessage(MessageDealer* other, int msg, void* extra = NULL, double nDealyTime = 0.0);

    void sendMessage(const Telegram& telegram);

    void postMessage(const Telegram& telegram);

    /*
    	Method:    	handleMessage [Access:virtual public ]
    	Brief:    	������Ϣ
    	Returns:   	bool, ����true����Ϣ����������������
    	Date:		2013/03/17 - Author:LiKuan
    	Parameter: 	const Telegram & telgram, ��Ϣ����
    */
    virtual bool handleMessage(const Telegram& telgram) = 0;

    int id() const;
protected:
    int mID;
};
#endif
