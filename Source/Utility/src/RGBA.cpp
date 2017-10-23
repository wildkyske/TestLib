#include "../include/RGBA.h"
#include "../include/MathUtilBase.h"
using namespace MathUtil;

//============================================

XRGBA::XRGBA( int nColor /*= 0*/ ) 
    : _color(nColor)
{

}

XRGBA::XRGBA( int r, int g, int b, int a )
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

XRGBA::XRGBA( float r, float g, float b, float a )
{
    this->r = (int)(r * float(0xff));
    this->g = (int)(g * float(0xff));
    this->b = (int)(b * float(0xff));
    this->a = (int)(a * float(0xff));
}

XRGBA::XRGBA( double r, double g, double b, double a )
{
    double r0 = r*double(0xff);
    this->r = int(r0);
    this->g = int(g*double(0xff));
    this->b = int(b*double(0xff));
    this->a = int(a*double(0xff));
}

XRGBA::~XRGBA()
{

}

XRGBA::operator int() const
{
    return _color;
}

int XRGBA::rgba() const
{
    return _color;
}

int XRGBA::argb() const
{
    int col = _color;
    char* pCol = (char*)&col;
    byteswap(pCol[0], pCol[2]);
    return col;
}

unsigned char XRGBA::red() const
{
    return r;
}

unsigned char XRGBA::green() const
{
    return g;
}

unsigned char XRGBA::blue() const
{
    return b;
}

unsigned char XRGBA::alpha() const
{
    return a;
}

float XRGBA::redF() const
{
    return r/float(0xff);
}

float XRGBA::greenF() const
{
    return  g/float(0xff);
}

float XRGBA::blueF() const
{
    return b/float(0xff);
}

float XRGBA::alphaF() const
{
    return a/float(0xff);
}

void XRGBA::setRed( unsigned char r )
{
    this->r = r;
}

void XRGBA::setGreen( unsigned char g )
{
    this->g = g;
}

void XRGBA::setBlue( unsigned char b )
{
    this->b = b;
}

void XRGBA::setAlpha( unsigned char a )
{
    this->a = a;
}

void XRGBA::setRedF( float r )
{
    this->r = r/float(0xff);
}

void XRGBA::setGreenF( float g )
{
    this->g = g/float(0xff);
}

void XRGBA::setBlueF( float b )
{
    this->b = b/float(0xff);
}

void XRGBA::setAlphaF( float a )
{
    this->a = a/float(0xff);
}

XRGBA& XRGBA::operator=( int rgba )
{
    this->_color = rgba;
    return *this;
}

void XRGBA::setArgbColor( int argb )
{
    this->_color = argb;
    byteswap(this->r, this->b);
}

void XRGBA::setRgbaColor( int rgba )
{
    this->_color = rgba;
}
