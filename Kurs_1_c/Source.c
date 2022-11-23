#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <io.h> //_setmode
#include <fcntl.h> //_O_U16TEXT
#include <windows.h>
#include <locale.h>
#include <math.h>

#define SCREENW 60 //размеры поля вывода в символах
#define SCREENH 40

double F1(double x)
{
	double y;
	y = cos(M_PI * x) / x + x * sin(M_PI * x);
	return y;
}

double F2(double x)
{
	double y;
	if (x <= 0)				// x <= 0
		y = 1 + ((3 + x) / (1 + pow(x, 2)));
	else
		if (x > 0 && x < 1) // 0 < x < 1
			y = pow(1 + pow(1 - x, 2), 0.5);
		else				// x >= 1
			y = (1 + x) / (1 + pow(cos(x), 2));
	return y;
}

int print_F(int n)
{
	int d = _setmode(_fileno(stdout), _O_U16TEXT); //меняем кодировку на юникод
	//wprintf(L"%d\n", d);

	switch (n)
	{
	case 1:
	{
		wprintf(L"||                 cos(πx)                                   ||\n");
		wprintf(L"||        F1(x) = --------- + x * sin(πx)                    ||\n");
		wprintf(L"||                    x                                      ||\n");
		break;
	}
	case 2:
	{
		wprintf(L"||                 「                                        ||\n");
		wprintf(L"||                 |         3 + x                           ||\n");
		wprintf(L"||                 |   1 + --------- ,    x <= 0             ||\n");
		wprintf(L"||                 |        1 + x²                           ||\n");
		wprintf(L"||                 |                                         ||\n");
		wprintf(L"||        F2(x) = <    1 + (1 - x)² ,     0 < x < 1          ||\n");
		wprintf(L"||                 |                                         ||\n");
		wprintf(L"||                 |       1 + x                             ||\n");
		wprintf(L"||                 |   -------------- ,   x >= 1             ||\n");
		wprintf(L"||                 |    1 + cos²(x)                          ||\n");
		wprintf(L"||                 L                                         ||\n");
		break;
	}
	}

	d = _setmode(_fileno(stdout), d); //меняем кодировку обратно

	return 0;
}

int tab_F(double x1, double x2, double step, int interval_type, int n)
{
	double (*pF) (double) = F1;

	if (n == 2)
		pF = F2;

	switch (interval_type)
	{
	case 1:
		x1 += step;
		break;
	case 2:
		break;
	case 3:
		x1 += step;
		x2 += step;
		break;
	case 4:
		x2 += step;
		break;
	}

	puts("======================");
	printf("||   x   |   F%d(x)  ||\n", n);
	puts("||------------------||");

	for (double x = x1; x < x2; x += step)
	{
		if (n == 1 && x == 0)
		{
			printf("|| %5.1lf |     -    ||\n", x);
		}
		else
		{
			printf("|| %5.1lf | %8.2lf ||\n", x, pF(x));
		}
	}

	puts("======================");

	return 0;
}

int draw_F(double x1, double x2, int interval_type, int n)
{
	char screen[SCREENW][SCREENH];
	double x, y[SCREENW];
	double ymin = 0, ymax = 0;
	double hx, hy;
	int i, j;
	int xz, yz;

	double (*pF) (double) = F1;

	if (n == 2) pF = F2;

	hx = (x2 - x1) / (SCREENW - 1);

	switch (interval_type)
	{
	case 1:
		x1 += hx;
		break;
	case 2:
		break;
	case 3:
		x1 += hx;
		x2 += hx;
		break;
	case 4:
		x2 += hx;
		break;
	}

	for (i = 0, x = x1; i < SCREENW; ++i, x += hx) 
	{
		if (n == 1 && x == 0) //учитываем область допустимых значений
			y[i] = pF(x + 0.1);
		else
			y[i] = pF(x); //расчет значений функции для каждой точки поля вывода графика

		if (y[i] < ymin) ymin = y[i];
		if (y[i] > ymax) ymax = y[i];
	}

	hy = (ymax - ymin) / (SCREENH - 1);
	yz = (int)floor(ymax / hy + 0.5);
	xz = (int)floor((0. - x1) / hx + 0.5);

	//построение осей и заполнение массива отображения пробелами

	for (j = 0; j < SCREENH; ++j)
		for (i = 0; i < SCREENW; ++i)
		{
			if (j == yz && i == xz) screen[i][j] = '+';
			else if (j == yz) screen[i][j] = '-';
			else if (i == xz) screen[i][j] = '|';
			else screen[i][j] = ' ';
		}

	//определение положения значения функции на поле вывода

	for (i = 0; i < SCREENW; ++i) 
	{
		j = (int)floor((ymax - y[i]) / hy + 0.5);
		screen[i][j] = '*';
	}

	//печать массива символов

	for (j = 0; j < SCREENH; ++j) 
	{
		for (i = 0; i < SCREENW; ++i)  putchar(screen[i][j]);
		putchar('\n');
	}

	return 0;
}

int cycle_input(int max_input)
{
	int v;

	do {
		fseek(stdin, 0, SEEK_END); //очищаем поток ввода
		puts("Введено некорректное значение");
		puts("Введите другое значение");
		printf("> ");
		scanf("%d", &v);
	} while (!(v >= 0 && v <= max_input));

	return v;
}

int screen_start(int do_delete)
{
	int v;

	fseek(stdin, 0, SEEK_END);
	if (do_delete)
		system("cls");
	
	puts("===============================================================");
	puts("||                    Добро пожаловать!                      ||");
	puts("||         Это программа для расчёта функций F1 и F2         ||");
	puts("||-----------------------------------------------------------||");
	print_F(1);
	puts("||-----------------------------------------------------------||");
	print_F(2);
	puts("===============================================================");
	puts("Какую функцию вы хотите вычислить?");
	puts(" 1 - Функция F1"); 
	puts(" 2 - Функция F2");
	puts(" 0 - выход из программы");
	printf("> ");
	scanf("%d", &v);

	while (1)
	{
		switch (v)
		{
		case 1:
			screen_F(1);
			return 0;
		case 2:
			screen_F(2);
			return 0;
		case 0:
			return 0;

		default:
			v = cycle_input(2);
		}
	}
	return 0;
}

int screen_F(int n)
{
	int v;

	fseek(stdin, 0, SEEK_END);
	system("cls");
	puts("===============================================================");
	printf("||                   Расчёт функции F%d                       ||\n", n);
	puts("||-----------------------------------------------------------||");
	print_F(n);
	puts("===============================================================");
	puts("Каковы дальнейшие действия?");
	puts(" 1 - Задать единичное значение");
	puts(" 2 - Задать промежуток для табуляции и построения графика");
	puts(" 3 - вернуться в главное меню");
	puts(" 0 - выйти из программы");
	printf("> ");
	scanf("%d", &v);

	while (1)
	{
		switch (v)
		{
		case 1:
		{
			double x;
			double y = 0;
			puts("Введите значение x");
			printf("x = ");
			scanf("%lg", &x);

			if (n == 1) {

				if (x == 0)
				{
					do {
						fseek(stdin, 0, SEEK_END);
						puts("Значение x не из области допустимых значений");
						puts("Введите другое значение");
						printf("x = ");
						scanf("%lg", &x);
					} while (x == 0);
				}

				y = F1(x);
			}

			if (n == 2)
			{
				y = F2(x);
			}

			printf("F%d(%lg) = %.4lg\n", n, x, y);

			printf("Продолжить работу с функцией F%d?\n", n);
			puts(" 1 - Да");
			puts(" 0 - Нет");
			printf("> ");
			scanf("%d", &v);
			if (v)
				screen_F(n);
			else
				screen_start(1);

			return 0;
		}
		case 2:
			screen_tab_F(n);
			return 0;
		case 3:
			screen_start(1);
			return 0;
		case 0:
			return 0;

		default:
			v = cycle_input(3);
		}
	}

	return 0;
}

int screen_tab_F(int n)
{
	int v, t;
	double x1, x2, h;

	fseek(stdin, 0, SEEK_END);
	system("cls");
	puts("===============================================================");
	printf("||               Табулирование функции F%d                    ||\n", n);
	puts("||-----------------------------------------------------------||");
	print_F(n);
	puts("===============================================================");
	puts("Каковы дальнейшие действия?");
	puts(" 1 - Ввести данные для табуляции и построения графика");
	puts(" 2 - вернуться к расчёту функции");
	puts(" 3 - вернуться в главное меню");
	puts(" 0 - выйти из программы");
	printf("> ");
	scanf("%d", &v);

	while (1)
	{
		switch (v)
		{
		case 1:
		{
			puts("Выберите вид промежутка");
			puts(" 1 - Интервал      (x1, x2)");
			puts(" 2 - Полуинтервал  [x1, x2)");
			puts(" 3 - Полуинтервал  (x1, x2]");
			puts(" 4 - Отрезок       [x1, x2]");
			printf("> ");
			scanf("%d", &t);

			puts("Введите границы промежутка");
			printf("x1 = ");
			scanf("%lg", &x1);
			printf("x2 = ");
			scanf("%lg", &x2);

			while (!(x1 < x2))
			{
				fseek(stdin, 0, SEEK_END);
				puts("Введены некорректные значения: x1 должен быть меньше x2");
				puts("Введите другие значения");
				printf("x1 = ");
				scanf("%lg", &x1);
				printf("x2 = ");
				scanf("%lg", &x2);
			}

			puts("Введите шаг табуляции");
			printf("h = ");
			scanf("%lg", &h);

			tab_F(x1, x2, h, t, n);

			puts("Каковы дальнейшие действия?");
			puts(" 1 - Построить график по значениям табуляции");
			puts(" 2 - выполнить ещё одно табулирование функции");
			puts(" 3 - вернуться к расчёту функции");
			puts(" 4 - вернуться в главное меню");
			puts(" 0 - выйти из программы");
			printf("> ");
			scanf("%d", &v);

			while (1)
			{
				switch (v)
				{
				case 1:
					draw_F(x1, x2, t, n);

					printf("Продолжить табулирование функции F%d?\n", n);
					puts(" 1 - Да");
					puts(" 0 - Нет");
					printf("> ");
					scanf("%d", &v);
					if (v)
						screen_tab_F(n);
					else
						screen_start(1);
					return 0;
				case 2:
					screen_tab_F(n);
					return 0;
				case 3:
					screen_F(n);
					return 0;
				case 4:
					screen_start(1);
					return 0;
				case 0:
					return 0;

				default:
					v = cycle_input(4);
				}
			}

			return 0;
		}
		case 2:
			screen_F(n);
			return 0;
		case 3:
			screen_start(1);
			return 0;
		case 0:
			return 0;

		default:
			v = cycle_input(3);
		}
	}

	return 0;
}

//поменять размер окна по умолчанию
int main()
{
	setlocale(LC_ALL, "RUS");

	puts("===============================================================");
	puts("||                    Курсовая работа                        ||");
	puts("||   по предмету \"Основы программирования и алгоритмизации\"  ||");
	puts("||     Выполнил студент группы бИСТ-223 Смоленская М.А.      ||");
	puts("===============================================================");
	puts("");

	screen_start(0);
	
	return 0;
}