#ifndef RGBA_h__
#define RGBA_h__

#include "UtilityExport.h"

/*
	ClassName:	XRGBA
	Brief:		rgba颜色
	Author:		kyske
	Date:		2013/12/08
*/
class UTILITY_EXPORT XRGBA
{
public:
    XRGBA(int nColor = 0);
    
    XRGBA(int r, int g, int b, int a);
    
    XRGBA(float r, float g, float b, float a);
    
    XRGBA(double r, double g, double b, double a);

    virtual ~XRGBA();

    operator int() const;

    XRGBA& operator=(int rgba);

    void setArgbColor(int argb);

    void setRgbaColor(int rgba);

    // @Brief 返回0xaabbggrr格式的颜色 [12/8/2013 kyske]
    int rgba() const;

    // @Brief 返回0xaarrggbb格式的颜色 [12/8/2013 kyske]
    int argb() const;

    unsigned char red() const;

    unsigned char green() const;

    unsigned char blue() const;

    unsigned char alpha() const;

    float redF() const;

    float greenF() const;

    float blueF() const;

    float alphaF() const;

    void setRed(unsigned char r);

    void setGreen(unsigned char g);

    void setBlue(unsigned char b);

    void setAlpha(unsigned char a);

    void setRedF(float r);

    void setGreenF(float g);

    void setBlueF(float b);

    void setAlphaF(float a);

public:

    union
    {
        int _color;
        struct  
        {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };
    };

};
#endif // RGBA_h__
