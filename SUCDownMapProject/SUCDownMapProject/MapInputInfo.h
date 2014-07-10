#pragma once
class MapInputInfo
{
public:
	MapInputInfo(void);
	~MapInputInfo(void);
	Pos2D  left_top_degree;// 左上经纬度
	Pos2D  right_down_degree;//右下经纬度
	string  imageFormart;//图片格式  png,jpg
	string  mapSererUrl;// 服务器url
	int minLevel;// 最小层
	int maxLevel;// 最大层
	string defaultFilePath; // 文件存储路径
	int  threadNum;// 线程数
};

