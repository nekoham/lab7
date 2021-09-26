#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<thread>

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 4);
	printf(" <-0-> ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 0);
	printf("^");
}
void draw_star(int x, int y)
{
	gotoxy(x, y);
	setcolor(7, 0);
	printf("*");
}
void draw_score(int x, int y, int score)
{
	gotoxy(x, y);
	setcolor(7, 0);
	printf("Score : %d", score);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void clear_background(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf("        ");

}
void clear_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}
char cursor(int x, int y) 
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
struct bullet
{
	int alive = 0; //status
	int x = 0, y = 0; //position
};
int main()
{
	char ch = '.';
	int x = 38, y = 20, direction = 0, star_count = 20, score = 0;
	srand(time(NULL));
	rand();
	bullet bullets[5];
	setcursor(0);
	draw_ship(x, y);

	for (int i = 0; i < 20; i++)
	{
		draw_star(rand() % 60 + 9, rand() % 4 + 1);
	}

	do {
		draw_score(71, 0, score);

		if (star_count < 20)
		{
			draw_star(rand() % 60 + 9, rand() % 4 + 1);
			star_count += 1;
		}
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 's') { direction = 1; }
			if (ch == 'a') { direction = 2; }
			if (ch == 'd') { direction = 3; }
			if (ch == ' ')
			{
				for (int i = 0; i < 5; i++)
				{
					if (bullets[i].alive == 0) {
						bullets[i].alive = 1;
						bullets[i].x = x + 3;
						bullets[i].y = y - 1;
						break;
					}
				}
				fflush(stdin);
			}
		}
		if (direction == 1)
		{
			draw_ship(x, y);
		}
		else if (direction == 2 && x > 0)
		{
			clear_background(x, y);
			draw_ship(--x, y);
		}
		else if (direction == 3 && x < 73)
		{
			clear_background(x, y);
			draw_ship(++x, y);
		}
		for (int i = 0; i < 5; i++)
		{
			if (bullets[i].alive == 1)
			{
				clear_bullet(bullets[i].x, bullets[i].y);
				if (bullets[i].y > 0)
				{
					if (cursor(bullets[i].x, bullets[i].y - 1) == '*')
					{
						clear_bullet(bullets[i].x, bullets[i].y - 1);
						bullets[i].alive = 0;
						std::thread q(Beep, 700, 100);
						q.detach();
						star_count -= 1;
						score += 1;
					}
					else
					{
						draw_bullet(bullets[i].x, --bullets[i].y);
					}
				}
				else
				{
					bullets[i].alive = 0;
				}
			}
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}

