#pragma once
#ifndef SUDOKU_CREATE_H
#define SUDOKU_CREATE_H
#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#define InputFilePath "./BIN/output.txt"
#define PuzzleFilePath "./BIN/puzzle.txt"
using namespace std;
class Sudoku
{
public:
	bool lex_next_perm(int Array[], int n);//寻找下一字典序排列
	int SudokuCreate(int num);
	int SudokuPuzzleGenerate();
	int SolvePuzzle(char* AnswerFilePath);

private:
	void BackTrack(int pos,ofstream &AnswerFile);
	void RandomSpace(int (*Array)[9],ofstream &PuzzleFile);
	void interchange(int Array[], int i, int j);
	void reverse(int Array[], int i, int j);
	bool IsPlace(int pos);
	bool output(int row23, int row46, int row79,ofstream &FilePath);
	int SudoArray[9] = {1,2,3,4,5,6,7,8,9};
	int SudoMap[9][9];
	int RowOrder13[2][3] = { {0,1,2}, {0,2,1} };
	int RowOrder46[6][3] = { {3,4,5},{3,5,4},{4,3,5},{4,5,3},{5,3,4},{5,4,3} };
	int RowOrder79[6][3] = { {6,7,8},{6,8,7},{7,6,8},{7,8,6},{8,6,7},{8,7,6} };
};
	


int Sudoku::SudokuCreate(int num)
{
	
	int MoveLeft[8] = { 3,6,1,4,7,2,5,8 };
	int number = 0;
	bool flag = true;
	ofstream InputFile;
	InputFile.open(InputFilePath, ios::out);//文件不存在则创建，若文件已存在则清空原内容
	if (!InputFile)
	{
		printf("Open file failed!\n");
		return false;
	}
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
					bool  FlagOutput= output(row23, row46, row79, InputFile);
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
	InputFile.close();
	return 0;
}
bool Sudoku::output(int row23, int row46, int row79, ofstream &File)
{
	int RowOrder[9];
	memcpy(RowOrder, RowOrder13[row23], sizeof(RowOrder13[row23]));
	memcpy(RowOrder + 3, RowOrder46[row46], sizeof(RowOrder46[row46]));
	memcpy(RowOrder + 6, RowOrder79[row79], sizeof(RowOrder79[row79]));

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			File << SudoMap[RowOrder[i]][j] << " ";
		File << endl;
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

int Sudoku::SudokuPuzzleGenerate()
{
	ifstream SudokuFile(InputFilePath);
	ofstream SudokuPuzzle(PuzzleFilePath);
	string str;
	int line[3][9];
	int count = 0;
	if (SudokuFile.fail()||SudokuPuzzle.fail())
	{
		printf("Open File Error!\n");
		return -1;
	}
	while (getline(SudokuFile,str))
	{
		for (int i = 0,j = 0; i < 18; i++)
		{
			if (str[i] == ' ' || str[i] == '\n' ||str[i] == '0')
				continue;
			line[count][j] = str[i] - '0';
			j++;

		}
		count++;
		if (count == 3)
		{
			RandomSpace(line, SudokuPuzzle);
			count = 0;
		}
	}
	SudokuFile.close();
	SudokuPuzzle.close();
	return 0;
}
void Sudoku::RandomSpace(int(*Array)[9], ofstream& PuzzleFile)
{
	int SpaceNum = 0, BoxNumber = 0;
	int row, column;
	for (BoxNumber = 0; BoxNumber < 3; BoxNumber++)//三行矩阵包括三个宫，每个宫中都安排4个空格，总共36个空格
	{
		for (SpaceNum = 0; SpaceNum < 4;)
		{
			int pos = rand() % 8;//生成0~8之间的随机数
			row = pos / 3;
			column = pos % 3 + BoxNumber * 3;
			if (!Array[row][column])//若该位置已经是0，则说明生成了重复的位置，需要重新生成
				continue;
			Array[row][column] = 0;
			SpaceNum++;
		}

	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			PuzzleFile << Array[i][j] << " ";
		}
		PuzzleFile << endl;
	}
}

int Sudoku::SolvePuzzle(char* AnswerFilePath)
{
	string str;
	stringstream buf;
	int count = 0,row = 0;
	ofstream AnswerFile(AnswerFilePath);
	ifstream PuzzleFile(PuzzleFilePath);
	if (PuzzleFile.fail()||AnswerFile.fail())
	{
		printf("Please generate sudoku first!\n");
		return 0;
	}
	buf << PuzzleFile.rdbuf();
	str = buf.str();
	
	for (string::iterator iter = str.begin(); iter != str.end(); iter++)
	{
		if (*iter == ' ' || *iter == '\n')
			continue;
		SudoMap[row][count] = *iter - '0';
		count++;
		if (count == 9)
		{
			row++;
			count = 0;
			if (row == 9)
			{
				BackTrack(0,AnswerFile);
				
				row = 0;
			}
		}
	}
	PuzzleFile.close();
	AnswerFile.close();
	return 0;
}
void Sudoku::BackTrack(int pos, ofstream& AnswerFile)
{
	if (pos == 81)
	{
		output(0, 0, 0, AnswerFile);
		return;
	}
	int row = pos / 9;
	int column = pos % 9;
	if (SudoMap[row][column] == 0)
	{
		for (int i = 1; i <= 9; i++)
		{
			SudoMap[row][column] = i;
			if (IsPlace(pos))
				BackTrack(pos + 1, AnswerFile);
		}
		
	}
	else
		BackTrack(pos + 1,AnswerFile);

}
bool Sudoku::IsPlace(int pos)
{
	int row = pos / 9;
	int column = pos % 9;
	for (int i = 0; i < 9; i++)
	{
		if (i == column)
			continue;
		if (SudoMap[row][i] == SudoMap[row][column] )
			return false;
	}
	for (int i = 0; i < 9; i++)
	{
		if (i == row)
			continue;
		if (SudoMap[i][column] == SudoMap[row][column])
			return false;
	}
	int BoxRow = row / 3 * 3;
	int BoxColumn = column / 3 * 3;
	for (int i = BoxRow; i < BoxRow + 3; i++)
	{
		for (int j = BoxColumn; j < BoxColumn + 3; j++)
		{
			if (i == row && j == column) continue;
			if (SudoMap[i][j] == SudoMap[row][column])
				return false;
		}
	}
	return true;
}
#endif
