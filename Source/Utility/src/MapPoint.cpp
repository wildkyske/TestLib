#include "../include/MapPoint.h"

CMapPoint::CMapPoint(void)
    :mTypeMask(MAP_POINT_XYZ)
{
}

CMapPoint::~CMapPoint(void)
{
}

void CMapPoint::validType( int nMask )
{
    if (!isTypeValid(nMask))
    {
        mTypeMask = mTypeMask | nMask;
    }
}

void CMapPoint::invalidType( int nMask )
{
    if (isTypeValid(nMask))
    {
        mTypeMask = mTypeMask & (~nMask);
    }
}

bool CMapPoint::isTypeValid( int nMask ) const
{
    return (mTypeMask & nMask) != 0;
}

void CMapPoint::setXYZ( double _x, double _y, double _z )
{
    x = _x;
    y = _y;
    z = _z;

    validType(MAP_POINT_XYZ);
}

bool CMapPoint::getXYZ( double& _x, double& _y, double& _z ) const
{
    if (!isTypeValid(MAP_POINT_XYZ))
    {
        return false;
    }

    _x = x;
    _y = y;
    _z = z;

    return true;
}

void CMapPoint::setLonLatAlt( double lon, double lat, double alt )
{
    longitude = lon;
    latitude = lat;
    altitude = alt;

    validType(MAP_POINT_GEO);
}

bool CMapPoint::getLonLatAlt( double& lon, double& lat, double& alt ) const
{
    if (!isTypeValid(MAP_POINT_GEO))
    {
        return false;
    }
    lon = longitude;
    lat = latitude;
    alt = altitude;

    return true;
}

void CMapPoint::setScreenCoord( int _sx, int _sy )
{
    sx = _sx;
    sy = _sy;

    validType(MAP_POINT_SCREEN);
}

bool CMapPoint::getScreenCoord( int& _sx, int& _sy ) const
{
    if (!isTypeValid(MAP_POINT_SCREEN))
    {
        return false;
    }

    _sx = sx;
    _sy = sy;

    return true;
}

void CMapPoint::setMapCoord( double mx, double my, double mz )
{
    mapx = mx;
    mapy = my;
    mapz = mz;
    
    validType(MAP_POINT_MAP);
}

bool CMapPoint::getMapCoord( double& mx, double& my, double& mz ) const
{
    if (!isTypeValid(MAP_POINT_MAP))
    {
        return false;
    }

    mx = mapx;
    my = mapy;
    mz = mapz;

    return true;
}

void CMapPoint::setIndex( int idx )
{
    index = idx;

    validType(MAP_POINT_INDEX);
}

bool CMapPoint::getIndex( int& idx ) const
{
    if (!isTypeValid(MAP_POINT_INDEX))
    {
        return false;
    }

    idx = index;
    
    return true;
}
