#pragma once
#include "MapInputInfo.h"
using namespace std;
typedef struct
{
	string downloadUrl;

	string fileName;

	int  threadNo;

} DownFileInfo;



class SUCMapDownloadUtil
{
public:
	SUCMapDownloadUtil(void);
	~SUCMapDownloadUtil(void);
	void DownLoadMapFromServer(const MapInputInfo *info );
	void setMapInputInfo(const MapInputInfo *info);
	static unsigned _stdcall	ThreadProc(void* param);// œ¬‘ÿœﬂ≥Ã
private:
	int caculateTiley(const double &latitude ,const int &zoom );
	int caculateTilex(const double &longitude ,const int &zoom );
	void downLoadImgHorizontal (const int &level ,const int &verticalNum ,const int &minTileX ,const int &maxTileX ,string dirName) ;
	bool creatDir(string dirName);
	string SUCMapDownloadUtil::formUrlPostfix(const int &level,const int & y ,const int &x);
	string intToString(const int & intValue);
	void downLoadFile(void *downInfo);
    bool isAnyThreadFree( void );
	bool isDownLoadComplete( void );
	
private:
	const MapInputInfo *inputInfo;
	
	int   freeThreadFlag;
};



