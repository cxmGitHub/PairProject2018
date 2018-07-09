// wordCount.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<stdio.h>

using namespace std;

int countChar(FILE *inFile);//统计字符个数
int countWord(FILE *file);//统计单词个数
int countLine(FILE *file);//统计行数

//int main(int argc, char *argv[])
int main()
{
	FILE *inFile;
	int res = 0;
	//fopen_s(&inFile, argv[1], "r");
	fopen_s(&inFile, "E:/晓梅的文档/北航做中学培训/PairProject2018/06/temp.txt", "r");
	if (inFile == NULL) {
		cout << "error" << endl;
		system("pause");
		return 0;
	}

	res = countChar(inFile);
	cout << "characters: " << res << endl;

	rewind(inFile);

	res = countLine(inFile);
	cout << "lines: " << res << endl;

	rewind(inFile);

	res = countWord(inFile);
	cout << "words: " << res << endl;

	system("pause");
    return 0;
}

int countChar(FILE *inFile)//统计字符个数
{
	int res = 0;
	char c;
	//fscanf_s(inFile, "%c", &c, sizeof(char));
	//cout << c;
	while (fscanf_s(inFile, "%c", &c, sizeof(char)) !=EOF) {
		if(c>=0 && c<=255)
			res++;
		//fscanf_s(inFile, "%c", &c, sizeof(char));
	}
	return res;
}

int countLine(FILE *file)//统计行数
{
	int res = 0;
	char c;
	while (fscanf_s(file, "%c", &c, sizeof(char)) != EOF) {
		//cout << c;
		if (c=='\n')
			res++;
	}
	return res;
}

bool isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}

bool isLetter(char c)
{
	if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
		return true;
	else
		return false;
}

bool isBreak(char c)
{
	if (!isDigit(c) && !isLetter(c))
		return true;
	else
		return false;
}

int countWord(FILE *file)//统计单词个数
{
	int res = 0;
	int cur = 0;
	bool flag = true;

	char c;
	//fscanf_s(file, "%c", &c, sizeof(char));
	char last = ' ';
	while (last!=EOF) {
		//fscanf_s(file, "%c", &c, sizeof(char));
		c = fgetc(file);
		if (isDigit(c) && isBreak(last)) {//分隔符+数字
			//cout << "分隔符+数字:" << c;
			while (true) {
				//fscanf_s(file, "%c", &c, sizeof(char));
				//cout << c;
				c = fgetc(file);
				if (c== EOF || isBreak(c)) {
					//cout << "break" << endl;
					break;
				}
					
			}
		}
		else {
			if (isBreak(c) && isBreak(last)) {//分隔符+分隔符
				/*
				while (true) {
					fscanf_s(file, "%c", &c, sizeof(char));
					if (!isBreak(c))
						break;
				}
				*/
			}
			else
				if(isLetter(c) && isBreak(last)) {//分隔符+字母
					cur = 1;
					flag = true;
					while (true) {
						//fscanf_s(file, "%c", &c, sizeof(char));
						c = fgetc(file);
						if (flag && isLetter(c) && cur < 4)
							cur++;
						else
							if (flag && cur == 4) {
								flag = false;
								res++;
							}
							else
								if (flag && !isLetter(c))
									flag = false;

						if (c==EOF || isBreak(c))
							break;
					}
				}
			}
		last = c;
	}
	return res;
}