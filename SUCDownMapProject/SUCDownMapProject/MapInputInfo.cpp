#include "StdAfx.h"
#include "MapInputInfo.h"


MapInputInfo::MapInputInfo(void)
{
	this->imageFormart = "png";
	this->mapSererUrl = BASE_SERVICE_URL;
	this->left_top_degree = Pos2D( 117.55337,26.69868);
	this->right_down_degree = Pos2D( 122.95991, 31.608534);
	this->minLevel = 17;
	this->maxLevel = 17;
	this->defaultFilePath = "D:\\zjemap";
	this->threadNum = 20;
}


MapInputInfo::~MapInputInfo(void)
{

}
