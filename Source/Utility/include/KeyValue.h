#ifndef KeyValue_h__
#define KeyValue_h__

#include <map>

template <typename TKey, typename TValue>
class KeyValue
{
public:
    KeyValue();
    virtual ~KeyValue();

    /*
    	Method:    	getValue [Access:public ]
    	Brief:    	获取值
    	Returns:   	bool
    	Date:		2013/04/30 - Author:kyske
    	Parameter: 	const TKey & val
    	Parameter: 	TValue & nValue
    */
    bool getValue(const TKey& val, TValue& nValue) const;

    /*
    	Method:    	setValue [Access:public ]
    	Brief:    	设置值
    	Returns:   	void
    	Date:		2013/04/30 - Author:kyske
    	Parameter: 	const TKey & nkey
    	Parameter: 	const TValue & nValue
    */
    void setValue(const TKey& nkey, const TValue& nValue);

    /*
    	Method:    	clear [Access:public ]
    	Brief:    	清楚
    	Returns:   	void
    	Date:		2013/04/30 - Author:kyske
    */
    void clear();
protected:
    std::map<TKey, TValue> mContent;
};

template <typename TKey, typename TValue>
KeyValue<TKey, TValue>::KeyValue()
{

}

template <typename TKey, typename TValue>
KeyValue<TKey, TValue>::~KeyValue()
{

}

template <typename TKey, typename TValue>
bool KeyValue<TKey, TValue>::getValue( const TKey& nkey, TValue& nValue ) const
{
    typename std::map<TKey, TValue>::iterator it = mContent.find(nkey);
    if (it == mContent.end())
    {
        return false;
    }

    nValue = it->second;
    return true;
}

template <typename TKey, typename TValue>
void KeyValue<TKey, TValue>::setValue( const TKey& nkey, const TValue& nValue )
{
    typename std::map<TKey, TValue>::iterator it = mContent.find(nkey);
    if (it == mContent.end())
    {
        mContent.insert(std::make_pair(nkey, nValue));
        return;
    }

    it->second = nValue;
}

template <typename TKey, typename TValue>
void KeyValue<TKey, TValue>::clear()
{
    mContent.clear();
}

#endif // KeyValue_h__
