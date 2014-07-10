// SUCDownMapProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SUCMapDownloadUtil.h"

#pragma comment(lib, "urlmon.lib")
//using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	
	// 可以配置输入信息
	MapInputInfo * mapInfo = new MapInputInfo;
	if (mapInfo == NULL)
		return 0;
	// 下载工具类
	SUCMapDownloadUtil * mapUtil  = new SUCMapDownloadUtil;
	if (mapUtil == NULL)
		return 0;
	/*mapUtil->setMapInputInfo( mapInfo );*/
	std::cout << "download start"<< endl;
	mapUtil->DownLoadMapFromServer( mapInfo ) ;
	
	delete mapInfo;
	mapInfo = NULL;
	delete mapUtil;
	mapUtil = NULL;

	std::cout << "download complete"<< endl;
	system("pause");
    return 0;
}