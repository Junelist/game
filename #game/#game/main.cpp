#include <graphics.h>

char board_data[3][3] =
{
	{'-', '-', '-'},
	{'-', '-', '-'},
	{'-', '-', '-'},
};
char currentPlayer = 'O';

//检查是否有玩家赢了
bool CheckWin(char c);

//检查是否平局
bool CheckDraw();

//绘制棋盘网格
void DrawBoard();

//绘制棋子
void DrawPiece();

//绘制提示信息
void DrawTipText();


int main()
{
	initgraph(600, 600);

	bool running = true;

	ExMessage mag;

	BeginBatchDraw();

	while (running)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&mag))
		{
			if (mag.message == WM_LBUTTONDOWN)
			{
				int x = mag.x / 200;
				int y = mag.y / 200;

				if (board_data[y][x] == '-')
				{
					board_data[y][x] = currentPlayer;
					currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
				}
			}

			cleardevice();

			DrawBoard();
			DrawPiece();
			DrawTipText();

			FlushBatchDraw();

			if (CheckWin('X'))
			{
				MessageBox(GetHWnd(), _T("x 玩家获胜)"), _T("游戏结束"), MB_OK);
				running = false;
			}
			else if (CheckWin('O'))
			{
				MessageBox(GetHWnd(), _T("O 玩家获胜)"), _T("游戏结束"), MB_OK);
				running = false;
			}
			else if (CheckDraw())
			{
				MessageBox(GetHWnd(), _T("平局"), _T("游戏结束"), MB_OK);
				running = false;
			}

			if (!running)
				break;
		}
		DWORD end_time = GetTickCount();
		if (end_time - start_time < 1000 / 60)
			Sleep(1000 / 60 - (end_time - start_time));
	}
	EndBatchDraw();

	return 0;
}

bool CheckWin(char c)
{
	if (board_data[0][0] == c && board_data[0][1] == c && board_data[0][2] == c)
		return true;
	if (board_data[1][0] == c && board_data[1][1] == c && board_data[1][2] == c)
		return true;
	if (board_data[2][0] == c && board_data[2][1] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][0] == c && board_data[1][0] == c && board_data[2][0] == c)
		return true;
	if (board_data[0][1] == c && board_data[1][1] == c && board_data[2][1] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][2] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][0] == c && board_data[1][1] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][1] == c && board_data[2][0] == c)
		return true;

	return false;
}

bool CheckDraw()
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (board_data[y][x] == '-')
				return false;
		}
	}
	return true;
}

void DrawBoard()
{
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
}

void DrawPiece()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			switch (board_data[i][j])
			{
			case 'O':
			{
				circle(100 + j * 200, 100 + i * 200, 100);
				break;
			}
			case 'X':
			{
				line(0 + j * 200, 0 + i * 200, 200 + j * 200, 200 + i * 200);
				line(200 + j * 200, 0 + i * 200, 0 + j * 200, 200 + i * 200);
				break;
			}
			case '-':
			{
				break;
			}
			}
		}
	}
}

void DrawTipText()
{
	static TCHAR str[64];
	_stprintf_s(str, _T("当前棋子: %c"), currentPlayer);

	settextcolor(RGB(255, 175, 45));
	outtextxy(0, 0, str);
}