#include <iostream>
#include <vector>
#include "stdafx.h"
#define BASE_SERVICE_URL "http://ditu.zj.cn//services/tilecache/zjemap/"
#define M_PI       3.14159265358979323846
#define MAX_LENGTH  20037508.3427892
#define MAX_LAT    85.05112877980659

#define ARRAY_SIZE(array) (sizeof(array)/sizeof((array)[0]))


using namespace std;
struct Pos2D
{
	double d0, d1;

public:
	Pos2D(){}
	Pos2D(double x, double y) : d0(x), d1(y){}
	Pos2D(const Pos2D &right) : d0(right.d0), d1(right.d1){}

	bool operator == (const Pos2D &right) const
	{	return d0 == right.d0 && d1 == right.d1;	}
	//this < does not mean 'less', it only provides some sortability which is useful for
	//associative containers such as set, map, etc.
	bool operator < (const Pos2D &right) const
	{	return d0 < right.d0 || d0 == right.d0 && d1 < right.d1;	}
	bool operator != (const Pos2D &right) const
	{	return !(*this == right);	}

	Pos2D & operator = (const Pos2D &right)
	{
		d0 = right.d0; d1 = right.d1 ;
		return *this;
	}

};

struct Rect2D
{
	Pos2D left_low;
	Pos2D right_top;

public:
	Rect2D(double left, double bottom, double right, double top)
	{
		left_low.d0 = left;
		left_low.d1 = bottom;
		right_top.d0 = right;
		right_top.d1 = top;
	}

	Rect2D(Pos2D left_low, Pos2D right_top)
	{
		this->left_low = left_low;
		this->right_top = right_top;
	}

	Rect2D(){};
};

namespace mc
{

	typedef struct 
	{
		double scole;
		int level;
		double resolution;
	} mapLods;

	typedef vector < mapLods > MapLodsArray;

	const MapLodsArray baseMyLoadsArray ( void )
	{
		MapLodsArray myArray ;

		mapLods lods0;
		lods0.level = 0;
		lods0.scole = 590995197.1416692;
		lods0.resolution = 1.40625;
		myArray.push_back( lods0 );

		mapLods lods1;
		lods1.level = 1;
		lods1.scole = 295497598.5708346;
		lods1.resolution = 0.703125;
		myArray.push_back( lods1 );

		mapLods lods2;
		lods2.level = 2;
		lods2.scole = 147748799.2854173;
		lods2.resolution =  0.3515625;
		myArray.push_back( lods2 );

		mapLods lods3;
		lods3.level = 3;
		lods3.scole = 73874399.64270864;
		lods3.resolution = 0.17578125;
		myArray.push_back( lods3 );

		mapLods lods4;
		lods4.level = 4;
		lods4.scole = 36937199.82135432;
		lods4.resolution = 0.087890625;
		myArray.push_back( lods4 );

		mapLods lods5;
		lods5.level = 5;
		lods5.scole = 18468599.91067716;
		lods5.resolution = 0.0439453125;
		myArray.push_back( lods5 );

		mapLods lods6;
		lods6.level = 6;
		lods6.scole = 9234299.95533858;
		lods6.resolution = 0.02197265625;
		myArray.push_back( lods6 );

		mapLods lods7;
		lods7.level = 7;
		lods7.scole = 4617149.97766929;
		lods7.resolution = 0.010986328125;
		myArray.push_back( lods7 );

		mapLods lods8;
		lods8.level = 8;
		lods8.scole = 2308574.988834645;
		lods8.resolution = 0.0054931640625;
		myArray.push_back( lods8 );

		mapLods lods9;
		lods9.level = 9;
		lods9.scole = 1154287.4944173226;
		lods9.resolution = 0.00274658203125;
		myArray.push_back( lods9 );

		mapLods lods10;
		lods10.level = 10;
		lods10.scole = 577143.7472086613;
		lods10.resolution = 0.001373291015625;
		myArray.push_back( lods10 );

		mapLods lods11;
		lods11.level = 11;
		lods11.scole = 288571.87360433064;
		lods11.resolution = 0.0006866455078125;
		myArray.push_back( lods11 );

		mapLods lods12;
		lods12.level = 12;
		lods12.scole = 144285.93680216532;
		lods12.resolution = 0.00034332275390625;
		myArray.push_back( lods12 );

		mapLods lods13;
		lods13.level = 13;
		lods13.scole = 72142.96840108266;
		lods13.resolution = 0.000171661376953125;
		myArray.push_back( lods13 );

		mapLods lods14;
		lods14.level = 14;
		lods14.scole = 36071.48420054133;
		lods14.resolution = 0.0000858306884765625;
		myArray.push_back( lods14 );

		mapLods lods15;
		lods15.level = 15;
		lods15.scole = 18035.742100270665;
		lods15.resolution = 0.00004291534423828125;
		myArray.push_back( lods15 );

		mapLods lods16;
		lods16.level = 16;
		lods16.scole = 9017.871050135333;
		lods16.resolution = 0.000021457672119140625;
		myArray.push_back( lods16 );

		mapLods lods17;
		lods17.level = 17;
		lods17.scole = 4508.935525067666;
		lods17.resolution = 0.000010728836059570312;
		myArray.push_back( lods17 );
		return myArray;
	}



}

LPCWSTR stringToLPCWSTR(std::string orig);