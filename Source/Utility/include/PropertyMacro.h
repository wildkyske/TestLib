#ifndef PropertyMacro_h__
#define PropertyMacro_h__

#define REGISTER_PROPERTY(dataType, dataName) protected: \
    dataType m##dataName;\
    public:\
    const dataType& get##dataName() const{\
        return m##dataName;}\
    dataType& get##dataName() {\
        return m##dataName;}\
    void set##dataName(const dataType& val){\
        m##dataName = val;}

#endif // PropertyMacro_h__
