#pragma once
#ifndef SUDOKU_CREATE_H
#define SUDOKU_CREATE_H
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#define InputFilePath "output.txt"
using namespace std;
class Sudoku
{
public:
	bool lex_next_perm(int Array[], int n);//寻找下一字典序排列
	int SudokuCreate(int num, char* FilePath);


private:
	void interchange(int Array[], int i, int j);
	void reverse(int Array[], int i, int j);
	bool output(int row23, int row46, int row79,char *FilePath);
	int SudoArray[9] = {1,2,3,4,5,6,7,8,9};
	int SudoMap[9][9];
	int RowOrder13[2][3] = { {0,1,2}, {0,2,1} };
	int RowOrder46[6][3] = { {3,4,5},{3,5,4},{4,3,5},{4,5,3},{5,3,4},{5,4,3} };
	int RowOrder79[6][3] = { {6,7,8},{6,8,7},{7,6,8},{7,8,6},{8,6,7},{8,7,6} };
};
	


int Sudoku::SudokuCreate(int num, char *FilePath)
{
	
	int MoveLeft[8] = { 3,6,1,4,7,2,5,8 };
	int number = 0;
	bool flag = true;
	while(flag)
	{
		memcpy(SudoMap[0], SudoArray, sizeof(SudoArray));
		for (int j = 0; j < 8; j++)
			for (int k = 0; k < 9; k++)
				SudoMap[j + 1][k] = SudoMap[0][(k + MoveLeft[j]) % 9];
		for (int row23 = 0; row23 < 2; row23++)
			for (int row46 = 0; row46 < 6; row46++)
				for (int row79 = 0; row79 < 6; row79++)
				{
					bool  FlagOutput= output(row23, row46, row79, FilePath);
					if (FlagOutput)
					{
						number++;
						if (number == num)
						{
							return 0;
						}
					}
				}
		flag = lex_next_perm(SudoArray + 1, 8);
	}
	return 0;
}
bool Sudoku::output(int row23, int row46, int row79, char* FilePath)
{
	int RowOrder[9];
	memcpy(RowOrder, RowOrder13[row23], sizeof(RowOrder13[0]));
	memcpy(RowOrder + 3, RowOrder46[row46], sizeof(RowOrder46[row46]));
	memcpy(RowOrder + 6, RowOrder79[row79], sizeof(RowOrder79[row79]));
	ofstream InputFile(InputFilePath, ios::out);//文件不存在则创建，若文件已存在则清空原内容
	if (!InputFile)
	{
		printf("Open file failed!\n");
		return false;
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			InputFile << SudoMap[RowOrder[i]][j] << " ";
		InputFile << endl;
	}
	
	return true;

}
void Sudoku::interchange(int Array[], int i, int j)
{
	int temp = Array[j];
	Array[j] = Array[i];
	Array[i] = temp;
}
void Sudoku::reverse(int Array[], int i, int j)
{
	int lim = i + (j - i) / 2;
	for (int k = i; k < lim; k++)
	{
		interchange(Array, k, j - k + i);
	}
}
bool Sudoku::lex_next_perm(int Array[], int n)
{
	if (n > 0)
	{
		int j;
		for (j = n - 2; j >= 0; j--)
		{
			if (Array[j] < Array[j + 1])
				break;
		}

		if (j == -1)//说明现在是最后一个序列，没有下一个序列了
		{
			reverse(Array, 0, n - 1);
			return false;
		}
		else
		{
			int l;
			for (l = n - 1; l > j; l--)
			{
				if (Array[l] > Array[j])
					break;
			}
			interchange(Array, j, l);
			reverse(Array, j + 1, n - 1);
			return true;
		}
	}
	return false;
}


#endif
