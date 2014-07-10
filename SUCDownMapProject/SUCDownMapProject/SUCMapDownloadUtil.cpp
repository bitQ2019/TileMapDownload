#include "StdAfx.h"
#include "SUCMapDownloadUtil.h"
#include <process.h>
#include "lock.h"
CCS::CCriticalSection threadFlag_Critical_Section;
int * threadFlag;

SUCMapDownloadUtil::SUCMapDownloadUtil(void)
{
	inputInfo = NULL;
	threadFlag = NULL;
}


SUCMapDownloadUtil::~SUCMapDownloadUtil(void)
{
	delete threadFlag;
	threadFlag == NULL;
}
void SUCMapDownloadUtil::setMapInputInfo(const MapInputInfo * info)
{
	this->inputInfo = info;
}

int SUCMapDownloadUtil::caculateTilex(const double &longitude ,const int &zoom )
{
	int tilex = (int )(longitude+180)/((360)/pow((double)2,zoom));

	return tilex;
}
int SUCMapDownloadUtil::caculateTiley(const double &latitude ,const int &zoom )
{
	/*if (latitude < 0)
	{
		latitude  =180 + latitude;
	}
	else
	{
		latitude =  latitude - 180;
	}*/
	// 如果误差较大，进行墨卡托转换
	// 现在没有墨卡托转换
	int tiley  = (int)(90-latitude)/((360)/pow((double)2,(int)zoom));
	//

	return tiley;
}

void SUCMapDownloadUtil::DownLoadMapFromServer(const MapInputInfo * info)
{
	this -> setMapInputInfo ( info );

	threadFlag = new int[info->threadNum];
	memset(threadFlag , 0 ,sizeof(int)*info->threadNum);
 	if(!this ->creatDir(info->defaultFilePath))
	{
		//创建失败
	};// 创建根目录 e:zjemap
	

	for( int level = info->minLevel;level< info->maxLevel+1;level++ )
	{
		char tempChar[20];
		sprintf(tempChar, "%d", level);
		string tempDirString = info ->defaultFilePath+"\\"+tempChar;
		if(!this->creatDir(tempDirString))
		{
			// 创建失败
		}
		int minTileX = this->caculateTilex( info->left_top_degree.d0 ,level );
		int maxTileY = this->caculateTiley( info->left_top_degree.d1 ,level );
		int maxTileX = this->caculateTilex( info->right_down_degree.d0 ,level );
		int minTileY = this->caculateTiley( info->right_down_degree.d1 , level);

		for(int tileY = 22003 ; tileY <maxTileY+1 ; tileY++ )
		{
			char tempChar2[20];
			sprintf(tempChar2, "%d", tileY);
			string tempDirString2 = tempDirString +"\\" +tempChar2;
			if(!this->creatDir(tempDirString2))
			{
				// 创建失败
			}
			this->downLoadImgHorizontal( level , tileY , minTileX , maxTileX , tempDirString2 );
		}
	}
	while(!isDownLoadComplete())
	{
		Sleep(1000);
	}


}
void SUCMapDownloadUtil::downLoadImgHorizontal (const int &level ,const int &verticalNum ,const int &minTileX ,const int &maxTileX ,string dirName) 
{
	try
	{

	for(int i = minTileX ; i < maxTileX+ 1 ; i++)
	{
		DownFileInfo *downFileInfo = new DownFileInfo;
		if(downFileInfo == NULL)
			return;

		downFileInfo->downloadUrl = inputInfo->mapSererUrl+formUrlPostfix(level,verticalNum,i);

		char tempChar [20];
		sprintf(tempChar , "%d",i);

		downFileInfo->fileName =dirName+"\\" + tempChar +"." +inputInfo->imageFormart;

		while(!isAnyThreadFree())
		{
			// 等待
			Sleep(10);
		}
		
		downFileInfo->threadNo = freeThreadFlag;
		//多线程
		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0,&SUCMapDownloadUtil::ThreadProc, downFileInfo, NULL, NULL);

		if(hThread == NULL)
		{
			delete downFileInfo;
			// 创建线程失败  写日志
			cout<<"create thread fail" << endl;
		}


	}
	}
	catch(...)
	{
		cout<<"error happen"<<endl;
	}
}

bool SUCMapDownloadUtil::creatDir(string dirName)
{
	LPCWSTR strFolder = stringToLPCWSTR(dirName);
	do
	{

		//if(!PathFileExists(strFolder))//文件夹不存在则创建
		{
			if (CreateDirectory(strFolder,NULL))
			{
				// 记录日志

				break;
			};
			return false;
			//记录日志
		}

	} while(0);

	return true;
}

string SUCMapDownloadUtil::formUrlPostfix(const int &level,const int & y ,const int &x)
{
	char tempChar [50];
	sprintf(tempChar,"%d/%d/%d",level,y,x);

	return tempChar;
}
string SUCMapDownloadUtil::intToString(const int & intValue)
{
	char tempChar [50];
	sprintf(tempChar,"%d",intValue);
	return tempChar;
}
bool SUCMapDownloadUtil::isAnyThreadFree( void  )
{
	bool flag = false;
	threadFlag_Critical_Section.Enter();
	for( int i = 0; i <inputInfo->threadNum ; i++ )
	{ 
		if (threadFlag[i] ==0)
		{
			freeThreadFlag = i;
			threadFlag[i]= 1;
			flag  = true; 
			break;
		}
	}
	threadFlag_Critical_Section.Leave();
	return flag;
}
unsigned _stdcall SUCMapDownloadUtil::ThreadProc(void* param)
{
	DownFileInfo *downFileInfo  = (DownFileInfo *)param;
		
	HRESULT hr = URLDownloadToFile(0,stringToLPCWSTR(downFileInfo->downloadUrl), stringToLPCWSTR(downFileInfo->fileName), 0,NULL);
	if(hr == S_OK)
	{
			// 成功  写日志
	}
		else
	{
			// 失败  写日志
	}
	
	threadFlag_Critical_Section.Enter();

	cout <<downFileInfo->threadNo <<"\t" <<downFileInfo->fileName<<endl;
	threadFlag[downFileInfo->threadNo] = 0;

	threadFlag_Critical_Section.Leave();
	
	delete downFileInfo;
	downFileInfo = NULL;
	 ///_endthreadex( 0 );
    return 0;

}
bool SUCMapDownloadUtil::isDownLoadComplete( void )
{
	bool flag = true;
	threadFlag_Critical_Section.Enter();
	for(int i = 0; i< inputInfo->threadNum; i++ )
	{
		if( threadFlag[i] == 1 )
		{
			flag = false;
		}
	}
	threadFlag_Critical_Section.Leave();
	return flag;
}