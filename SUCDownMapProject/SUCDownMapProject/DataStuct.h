#pragma once
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

namespace  DataStruct
{\
	namespace Reti
	{
		#define M_PI       3.14159265358979323846


struct ImageInfo
{

	int left;
	int top;
	std::string name;

public:

	ImageInfo()
	{

	}

};
struct Point
{
	Point ()
	{

	}
	Point(int a,int b):x( a),y( b)
	{

	}
	Point( Point &p ):x(p.x),y(p.y){}

	bool operator ==(const Point &right) const
	{
		return this->x==right.x&& this->y==right.y;
	}

	bool operator !=(const Point &right) const
	{
		return !(this->x==right.x&&this->y==right.y);
	}

	Point & operator =(const Point &right) 
	{
		this->x=right.x;
		this->y=right.y;
		return * this;
	}

	Point & operator +(const Point &right)
	{
		this->x=this->x+right.x;
		this->y=this->y+right.y;
		return *this;
	}

	Point & operator -(const Point &right)
	{
		this->x=this->x-right.x;
		this->y=this->y-right.y;
		return *this;
	}
	double x;
	double y;

	Point & operator * (const Point &right)
	{

		this->x=this->x*right.x;
		this->y=this->y*right.y;
	}


};
struct Bounds
{
	Point rightTop;
	Point leftBottom;
public :
	Bounds(void )
	{
		rightTop.x=-20037508.3427892 ;
		rightTop.y=-20037508.3427892 ;
		leftBottom.x=20037508.3427892 ;
		leftBottom.y=20037508.3427892 ;
	}
};
struct Lod
{
	int  level;//   0--17 越大块数越少
	int  resolution;
	//Bounds viewBounds;
};
struct rectTile
{
	int width;
	int height;
};

std::string ws2s(const std::wstring& ws)
{
    std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
    setlocale(LC_ALL, "chs");
    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = 2 * ws.size() + 1;
    char *_Dest = new char[_Dsize];
    memset(_Dest,0,_Dsize);
    wcstombs(_Dest,_Source,_Dsize);
    std::string result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

std::wstring s2ws(const std::string& s)
{
    setlocale(LC_ALL, "chs"); 
    const char* _Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, "C");
    return result;
}

string NumToString(int num)
{
	char temp[30];

	itoa(num,temp,10);

	return string(temp);
}

void  changeLongitudeAndLatitudeIntoPoint(Point &center )
{
	center.x=center.x/180*(20037508.3427892);
	center.y=center.y*(M_PI)/180;//转换到弧度
	
	center.y=0.5 * log((1 + sin(center.y)) / (1 -sin(center.y)));//墨卡托转换
	center.y=center.y*180/(2*85.05112877980659)/M_PI;
	center.y=(1-center.y-0.5)/0.5*20037508.3427892;
}
}

}