#include "pch.h"
#include <iostream>

void Test(bool &_f, int depth, int N, int** _size, char*** _block, int mapR, int mapC, char** map);
void Put(int posR, int posC, int blockR, int  blockC, char** block, char** map)
{
	for (int i = 0; i < blockR; i++)
		for (int j = 0; j < blockC; j++)
			if (block[i][j] == 'O')
				map[posR + i][posC + j] = 'O';
}

void BlockTest(bool &_f, int depth, int N, int posR, int posC, int** _size, char*** _block, int mapR, int mapC, char** map)
{
	for (int k = 0; k < _size[depth][1]; k++)
		for (int l = 0; l < _size[depth][0]; l++)
			if (_block[depth][k][l] == 'O' & map[posR + k][posC + l] == 'O')
				return;
	Put(posR, posC, _size[depth][1], _size[depth][0], _block[depth], map);
	Test(_f, depth + 1, N, _size, _block, mapR, mapC, map);
}

void Test(bool &_f, int depth, int N, int** _size, char*** _block, int mapR, int mapC, char** map)
{
	if (depth == N)
	{
		for (int i = 0; i < mapR; i++)
			for (int j = 0; j < mapC; j++)
				if (map[i][j] == '-')
					return;
		std::cout << "Yes" << std::endl;
		_f = true;
		return;
	}
	char** temp = new char*[mapR];
	for (int posR = 0; posR < mapR - _size[depth][1] + 1; posR++)
		for (int posC = 0; posC < mapC - _size[depth][0] + 1; posC++)
		{
			for (int i = 0; i < mapR; i++)
			{
				temp[i] = new char[mapC];
				for (int j = 0; j < mapC; j++)
					temp[i][j] = map[i][j];
			}
			BlockTest(_f, depth, N, posR, posC, _size, _block, mapR, mapC, temp);
		}
}

int main()
{
	int N;
	std::cin >> N;
	int** size = new int*[N];
	char*** block = new char**[N];

	for (int i = 0; i < N; i++)
	{
		size[i] = new int[2];
		std::cin >> size[i][0] >> size[i][1];
		block[i] = new char*[size[i][1]];

		for (int j = 0; j < size[i][1]; j++)
		{
			block[i][j] = new char[size[i][0]];
			for (int k = 0; k < size[i][0]; k++)
				std::cin >> block[i][j][k];
		}
	}

	int M;
	std::cin >> M;
	int** mapSize = new int*[M];
	char*** maps = new char**[M];

	for (int i = 0; i < M; i++)
	{
		mapSize[i] = new int[2];
		std::cin >> mapSize[i][0] >> mapSize[i][1];
		maps[i] = new char*[mapSize[i][1]];

		for (int j = 0; j < mapSize[i][1]; j++)
		{
			maps[i][j] = new char[mapSize[i][0]];
			for (int k = 0; k < mapSize[i][0]; k++)
				std::cin >> maps[i][j][k];
		}
	}

	bool flag;
	for (int m = 0; m < M; m++)
	{
		flag = false;
		Test(flag, 0, N, size, block, mapSize[m][1], mapSize[m][0], maps[m]);
		if (!flag)
			std::cout << "No" << std::endl;
	}
	return 0;
}