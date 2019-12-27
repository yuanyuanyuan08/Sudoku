﻿// Sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "Sudoku_create.h"

int main(int argc, char *argv[])
{
	if (argc != 3)//生成数独终局和求解数独终局的命令行参数都是3个，若输入不为3个则为不合法输入
	{
		printf("Input Error!\n");
		return 0;
	}
	if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-C") == 0)//参数"-c"或"-C"表示要生成终局
	{
		Sudoku Sudo;
		double Num;
		if ((Num = atoi(argv[2])) == 0|| Num != (int)Num)//若输入的不是数独终局数量则输入不合法
		{
			printf("Input Error!\n");
			return 0;
		}
		//SudokuCreate(Num, FilePath);//生成终局到指定文件
		Sudo.SudokuCreate(Num,InputFilePath);
	}
	else if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "-S") == 0)//参数"-s"或"-S"表示要求解终局
	{
		char* OutFile = argv[2];
		ifstream file(InputFilePath);
		if (!file)
		{
			printf("Please generate sudoku first!\n");
			return 0;
		}
		//SudokuAnswer(FilePath,OutFile);
	}

    
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
