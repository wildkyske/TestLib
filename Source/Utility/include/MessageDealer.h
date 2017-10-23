#pragma once
#ifndef MESSAGE_DEALER_H
#define MESSAGE_DEALER_H
/*
	filename	: 	MessageDealer.h
	created		:	2013/03/17  12:22
	author		:	LiKuan
	desc		:	消息处理器，需要处理消息的继承此类
	note		:	
	copyright @ xcahr studio. e-mail:530754393@qq.com
*/
#include "Telegram.h"
#include "UtilityExport.h"

/*
	ClassName:	MessageDealer
	Brief:		消息处理者，可以收发消息
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
    	Brief:    	发送消息
    	Returns:   	void
    	Date:		2013/03/17 - Author:LiKuan
    	Parameter: 	MessageDealer * other,  消息接收者
    	Parameter: 	int msg, 消息类型
    	Parameter: 	void * extra, 附加消息
    	Parameter: 	double nDealyTime, 延迟发送
    */
    void sendMessage(MessageDealer* other, int msg, void* extra = NULL, double nDealyTime = 0.0);

    void sendMessage(const Telegram& telegram);

    void postMessage(const Telegram& telegram);

    /*
    	Method:    	handleMessage [Access:virtual public ]
    	Brief:    	处理消息
    	Returns:   	bool, 返回true，消息被处理不继续往下送
    	Date:		2013/03/17 - Author:LiKuan
    	Parameter: 	const Telegram & telgram, 消息正文
    */
    virtual bool handleMessage(const Telegram& telgram) = 0;

    int id() const;
protected:
    int mID;
};
#endif
