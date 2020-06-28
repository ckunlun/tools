// runTime.cpp : 
// 从txt文件中读取压缩时间。
// 输入参数：压缩生产的txt文件
// 2020.6.23
// ckunlun 
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//从txt文档中读取时间
void readTime(string name);


int main(int argc, char* args[])
{
	if (argc != 2)
	{
		cout << "输入参数错误，输入参数示范：test.txt line" << endl;
	}
	else
	{
		string fileName = args[1];//读入输入的文件名

		readTime(fileName);

	}
	return 0;
}

void readTime(string name)
{
	ifstream txtFile(name, ios::in);
	if (!txtFile.is_open())
	{
		cout << "打开文件错误" << endl;
		return;
	}
	else
	{

		string text;//读取的包含时间的行
		int end = -1;
		while (getline(txtFile, text))
		{
			end = text.find("sec");//查找sec第一次出现的时间
			if (end != -1)
			{
				break;
			}
		}
		if (end == -1)
		{
			cout << "输入txt文件错误，无时间" << endl;
			return;
		}
		// 从字符串中分割出时间
		int start = text.find(":");//查找冒号第一次出现的位置
		
		string time = text.substr(start + 1, end - start - 1);
		double timeInt = atof(time.c_str());//string转float
		//cout << time << endl;
		cout << timeInt << endl;

	}

	txtFile.close();
}