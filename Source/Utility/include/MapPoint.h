#pragma once
#ifndef MapPoint_h__
#define MapPoint_h__

#include "UtilityExport.h"

/*
	ClassName:	CMapPoint
	Brief:		ͨ�õ�ͼ�����
	Author:		Administrator
	Date:		2013/10/31
*/
class UTILITY_EXPORT CMapPoint
{
public:
    enum
    {
        MAP_POINT_XYZ = 0x1,    //xyz����
        MAP_POINT_GEO = 0x2,    //��������
        MAP_POINT_SCREEN = 0x4, //��Ļ����
        MAP_POINT_MAP = 0x8,    //��ͼ���꣬ͨ������Ϸ��ͼ���
        MAP_POINT_INDEX = 0x10, //��������
    };
public:
    CMapPoint(void);
    ~CMapPoint(void);

    // @Brief ʹĳ������������Ч [10/31/2013 Administrator]
    void validType(int nMask);

    // @Brief ʹĳ����������ʧЧ [10/31/2013 Administrator]
    void invalidType(int nMask);

    // @Brief �����Ƿ���Ч [10/31/2013 Administrator]
    bool isTypeValid(int nMask) const;

public:
    // @Brief ����xyz���� [10/31/2013 Administrator]
    void setXYZ(double _x, double _y, double _z);

    // @Brief ��ȡxyz���� [10/31/2013 Administrator]
    bool getXYZ(double& _x, double& _y, double& _z) const;

    // @Brief ���þ�γ�� [10/31/2013 Administrator]
    void setLonLatAlt(double lon, double lat, double alt) ;

    // @Brief ��ȡ��γ�� [10/31/2013 Administrator]
    bool getLonLatAlt(double& lon, double& lat, double& alt) const;

    // @Brief ������Ļ���� [10/31/2013 Administrator]
    void setScreenCoord(int _sx, int _sy);

    // @Brief ��ȡ��Ļ���� [10/31/2013 Administrator]
    bool getScreenCoord(int& _sx, int& _sy) const;

    // @Brief ���õ�ͼ���� [10/31/2013 Administrator]
    void setMapCoord(double mx, double my, double mz);

    // @Brief ��ȡ��ͼ���� [10/31/2013 Administrator]
    bool getMapCoord(double& mx, double& my, double& mz) const;

    // @Brief ������������ [10/31/2013 Administrator]
    void setIndex(int idx);

    // @Brief ��ȡ�������� [10/31/2013 Administrator]
    bool getIndex(int& idx) const;

public:
    int mTypeMask;  //��������

    double x, y, z; //xyz����

    double longitude, latitude, altitude;   //��γ��

    int sx, sy; //��Ļ����

    double mapx, mapy, mapz;    //��ͼ���꣬ͨ��Ϊ����

    int index;                  //��������
};
#endif // MapPoint_h__
