#pragma once
#ifndef MapPoint_h__
#define MapPoint_h__

#include "UtilityExport.h"

/*
	ClassName:	CMapPoint
	Brief:		通用地图坐标点
	Author:		Administrator
	Date:		2013/10/31
*/
class UTILITY_EXPORT CMapPoint
{
public:
    enum
    {
        MAP_POINT_XYZ = 0x1,    //xyz坐标
        MAP_POINT_GEO = 0x2,    //地理坐标
        MAP_POINT_SCREEN = 0x4, //屏幕坐标
        MAP_POINT_MAP = 0x8,    //地图坐标，通常和游戏地图相关
        MAP_POINT_INDEX = 0x10, //索引坐标
    };
public:
    CMapPoint(void);
    ~CMapPoint(void);

    // @Brief 使某种坐标类型生效 [10/31/2013 Administrator]
    void validType(int nMask);

    // @Brief 使某种坐标类型失效 [10/31/2013 Administrator]
    void invalidType(int nMask);

    // @Brief 类型是否有效 [10/31/2013 Administrator]
    bool isTypeValid(int nMask) const;

public:
    // @Brief 设置xyz坐标 [10/31/2013 Administrator]
    void setXYZ(double _x, double _y, double _z);

    // @Brief 获取xyz坐标 [10/31/2013 Administrator]
    bool getXYZ(double& _x, double& _y, double& _z) const;

    // @Brief 设置经纬高 [10/31/2013 Administrator]
    void setLonLatAlt(double lon, double lat, double alt) ;

    // @Brief 获取经纬高 [10/31/2013 Administrator]
    bool getLonLatAlt(double& lon, double& lat, double& alt) const;

    // @Brief 设置屏幕坐标 [10/31/2013 Administrator]
    void setScreenCoord(int _sx, int _sy);

    // @Brief 获取屏幕坐标 [10/31/2013 Administrator]
    bool getScreenCoord(int& _sx, int& _sy) const;

    // @Brief 设置地图坐标 [10/31/2013 Administrator]
    void setMapCoord(double mx, double my, double mz);

    // @Brief 获取地图坐标 [10/31/2013 Administrator]
    bool getMapCoord(double& mx, double& my, double& mz) const;

    // @Brief 设置索引坐标 [10/31/2013 Administrator]
    void setIndex(int idx);

    // @Brief 获取索引坐标 [10/31/2013 Administrator]
    bool getIndex(int& idx) const;

public:
    int mTypeMask;  //类型掩码

    double x, y, z; //xyz坐标

    double longitude, latitude, altitude;   //经纬高

    int sx, sy; //屏幕坐标

    double mapx, mapy, mapz;    //地图坐标，通常为整数

    int index;                  //索引坐标
};
#endif // MapPoint_h__
