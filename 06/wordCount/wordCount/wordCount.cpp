// wordCount.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<string>
#include<map>
#include <cctype> //toupper/tolower
//#include <algorithm> //transform

using namespace std;

int countChar(FILE *inFile);//统计字符个数
int countWord(FILE *file);//统计单词个数
int countLine(FILE *file);//统计行数
int splitWord(FILE *file, string words[]);//分词
bool isWord(string s);
map<string, int> countEachWord(string words[], int segCount, int &wordCount);
void outputTop(map<string, int> word_map, int topNumber);


//int main(int argc, char *argv[])
int main()
{
	FILE *inFile;
	int res = 0;
	int segCount = 0;
	int wordCount = 0;
	int i = 0;
	string words[10000];
	map<string, int> my_map;

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
	segCount = splitWord(inFile, words);

	my_map = countEachWord(words, segCount, wordCount);
	for (i = 0; i <= segCount; i++)
		cout << words[i] << endl;
	cout << "words: " << wordCount << endl;

	rewind(inFile);
	res = countLine(inFile);
	cout << "lines: " << res << endl;

	outputTop(my_map, 10);

	system("pause");
    return 0;
}

int countChar(FILE *inFile)//统计字符个数
{
	int res = 0;
	char c;
	while ((c=fgetc(inFile))!=EOF) {
		if(c>=0 && c<=255)
			res++;
	}
	return res;
}

int countLine(FILE *file)//统计行数
{
	int res = 0;
	char c;
	while ((c = fgetc(file)) != EOF) {
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
	char last = ' ';
	while (last!=EOF) {
		c = fgetc(file);
		if (isDigit(c) && isBreak(last)) {//分隔符+数字
			while (true) {
				c = fgetc(file);
				if (c== EOF || isBreak(c)) {
					break;
				}
					
			}
		}
		else 
			if(isLetter(c) && isBreak(last)) {//分隔符+字母
					cur = 1;
					//str = "34";
					flag = true;
					while (true) {
						c = fgetc(file);
						if (flag && isLetter(c) && cur < 4) {
							//str += c;
							cur++;
						}
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
		last = c;
	}
	return res;
}

int splitWord(FILE *file, string words[])
{
	char c;
	string s = "";
	int i = 0;
	bool flag = false;
	while ((c = fgetc(file)) != EOF) {
		if (!isBreak(c)) {
			flag = true;
			s += tolower(c);
		}
		else 
			if(flag){
				words[i] = s;
				i++;
				s = "";
				flag = false;
			}
	}
	return i - 1;
}

bool isWord(string s)
{
	int i = 0;
	if (s.length() < 4)
		return false;
	else
		if (isLetter(s[0]) && isLetter(s[1]) && isLetter(s[2]) && isLetter(s[3]))
			return true;
		else
			return false;
}

map<string, int> countEachWord(string words[], int segCount, int &wordNumber)
{
	map<string, int> word_map;
	map<string, int>::iterator iter;
	int i = 0;
	int wordCount = 0;
	for (i = 0; i <= segCount; i++) {
		if (isWord(words[i])) {
			++word_map[words[i]];
		}
	}

	for (iter = word_map.begin(); iter != word_map.end(); iter++, wordCount++)

	wordNumber = wordCount;

	return word_map;
}

void outputTop(map<string, int> word_map, int topNumber)
{
	multimap<int, string, greater<int>> cnt;
	map<string, int>::iterator map_itr;
	multimap<int, string, greater<int>>::iterator multimap_itr;

	int i = 0;

	for (map_itr = word_map.begin(); map_itr != word_map.end(); map_itr++){
		cnt.insert(pair<int, string>(map_itr->second, map_itr->first));
	}

	for(i=0, multimap_itr = cnt.begin(); i<topNumber && multimap_itr != cnt.end(); multimap_itr++, i++){
		cout << multimap_itr->second << ": " << multimap_itr->first << endl;
	}
}