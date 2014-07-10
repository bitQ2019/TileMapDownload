#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"DataStuct.h"
using namespace std;
using namespace ds::Reti;
class mapALG
{
public:
	mapALG(void);
	~mapALG(void);
public:
	Bounds  earthBounds;
	int preDefineParameters(int tileWidth, int tileHeight, const vector<int > & lodLevel, const vector<double > & lodResolution, double tileOriginLon, double tileOriginLat, const string & tileType, int tileBuffer);
	vector<ImageInfo >  getImage(double map_left, double map_right, double map_bottom, double map_top, double resolution, const wstring & img_url, const wstring & img_path);
	
private:
	Point centerPoint;
	rectTile tileInfo;
	vector<Lod> vecLod;
	string  tileType;
	int  tileBuffer;
	rectTile  positionOfLeftBottom2ViewSize;
};

