// snr.cpp : 计算原始图像和恢复图像snr
//			 输入示例：ori.yuv re.yuv depth size
// 时间：2020.6.22
// 作者：ckunlun
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

//函数功能：计算snr函数
//输入参数：
//原始图像名 恢复图像名 图像比特深度 输入图像尺寸
void snr(string ori, string re, int depth, long long size);

int main(int argc, char *args[])
{
    
	if (argc != 5)
	{
		cout << "输入参数错误，输入示例：ori.yuv re.yuv depth size";
	}
	else
	{
		string oriImage = args[1]; //待压缩原始图像
		string reImage = args[2];  //解压后的恢复图像
		int depth = atoi(args[3]);  //输入图像的比特深度
		long long size = atoi(args[4]);   //输入图像尺寸，计算方法：宽*高*通道数
		
		snr(oriImage, reImage, depth, size);

		//cout << oriImage << "   " << reImage << "   " << depth << "   " << size << "   " << endl;
	}
	
	return 0;
	
}

void snr(string ori, string re, int depth, long long size)
{
	long long length = size * depth /  8;  //输入图像的字节数。

    unsigned char* oriImg = new unsigned char[length];//读取初始图像的数组
	unsigned char* reImg = new unsigned char[length];
	unsigned int* oriImgInt = NULL; //数据存储到int数组
	unsigned int* reImgInt = NULL;
	long double ex = 0.0;  //原始图像的能量。
	long double en = 0.0; //原始图像和恢复图像误差的能量。
	double snr = 0.0;

	if (depth != 8)
	{
		oriImgInt = new unsigned int[length / 2];
		reImgInt = new unsigned int[length / 2];
		memset(oriImgInt, 0, length / 2);
		memset(reImgInt, 0, length / 2);
	}
	else
	{
		oriImgInt = new unsigned int[length]; //数据存储到int数组
		reImgInt = new unsigned int[length];
		memset(oriImgInt, 0, length);
		memset(reImgInt, 0, length);
	}
	


	// 数组初始化
	memset(oriImg, 0, length);
	memset(reImg, 0, length);


	//读入原始图像
	FILE* fp;
	fp = fopen(ori.c_str(), "rb");
	fread(reImg, 1, length, fp);
	fclose(fp);
	fp = fopen(re.c_str(), "rb");
	fread(oriImg, 1, length, fp);
	fclose(fp);
	
	if (depth != 8)
	{
		for (int i = 1; i < length; i += 2)
		{
			oriImg[i] = (oriImg[i]) & ((1 << (depth - 8)) - 1);	//保证高位数据空位为0
			oriImgInt[i / 2] = (unsigned int)(((oriImg[i]) << 8) + (oriImg[i - 1]));
			ex += oriImgInt[i / 2] * oriImgInt[i / 2];
			

		}
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			oriImgInt[i] = (unsigned int)(oriImg[i]);
			ex += (oriImgInt[i] * oriImgInt[i]);
			
		}
	}

	


	if (depth != 8)
	{
		for (int i = 1; i < length; i += 2)
		{
			reImg[i] = (reImg[i]) & ((1 << (depth - 8)) - 1);	//保证高位数据空位为0
			reImgInt[i / 2] = (unsigned int)(((reImg[i]) << 8) + (reImg[i - 1]));
			en += (oriImgInt[i / 2] - reImgInt[i / 2]) * (oriImgInt[i / 2] - reImgInt[i / 2]);
		}
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			reImgInt[i] = (unsigned int)(reImg[i]);
			en += ((oriImgInt[i] - reImgInt[i]) * (oriImgInt[i] - reImgInt[i]));
		}
	}
	if (en == 0)
	{
		snr = 999;//无损
	}
	else
	{
		snr = 10 * log10(double(ex / en));
	}
	

	//cout << ex << "  " << en << endl;
	cout << snr << endl;


	delete[] oriImg;
	delete[] reImg;
	delete[] oriImgInt;
	delete[] reImgInt;
}