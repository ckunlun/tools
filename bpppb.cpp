// bpppb.cpp : 计算原始图像和恢复图像bpppb=总字节数*8/宽/高/谱段数
//			 输入示例：coding.bin size
// 时间：2020.6.22
// 作者：ckunlun
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//函数功能：计算bpppb函数
//输入参数：
//压缩码流 输入图像尺寸
void bpppb(string coding, long long size);

int main(int argc, char* args[])
{

	if (argc != 3)
	{
		cout << "输入参数错误，输入示例：coding.bin size";
	}
	else
	{
		string codingName = args[1];  //解压后的恢复图像
		long long size = atoi(args[2]);   //输入图像尺寸，计算方法：宽*高*通道数

		bpppb(codingName, size);

		//cout << oriImage << "   " << reImage << "   " << depth << "   " << size << "   " << endl;
	}

	return 0;

}

void bpppb(string coding, long long size)
{
	long double length = 0.0;  //码流文件的位数。
	long double imgSize = (double)size;
	double bpppb = 0.0;


	//读入恢复图像
	ifstream codingFile(coding, ios::in | ios::binary);
	if (!codingFile.is_open())
	{
		cout << "打开文件失败" << endl;
		return;
	}
	else
	{
		codingFile.seekg(0, ios::end);
		streampos ps = codingFile.tellg(); //获取文件指针的位置
		//cout << ps << endl;

		length = (double)ps;
		bpppb = length * 8.0 / imgSize;
		cout << bpppb << endl;
	}

	codingFile.close();


}