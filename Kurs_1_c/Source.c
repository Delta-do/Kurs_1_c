#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <locale.h>
#include <math.h>

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

//поменять кодировку на юникод по всей программе
int print_F(int n)
{
	switch (n)
	{
	case 1:
	{
		puts("||                 cos(πx)                                   ||");
		puts("||        F1(x) = --------- + x * sin(πx)                    ||");
		puts("||                    x                                      ||");
		break;
	}
	case 2:
	{
		puts("||                  r                                        ||");
		puts("||                 |         3 + x                           ||");
		puts("||                 |   1 + --------- ,    x <= 0             ||");
		puts("||                 |        1 + x^2                          ||");
		puts("||                 |                                         ||");
		puts("||        F2(x) = k    1 + (1 - x)^2 ,    0 < x < 1          ||");
		puts("||                 |                                         ||");
		puts("||                 |       1 + x                             ||");
		puts("||                 |   -------------- ,   x >= 1             ||");
		puts("||                 |    1 + cos^2(x)                         ||");
		puts("||                  q                                        ||");
		break;
	}
	}
}

int tab_F(double x1, double x2, double step, int interval_type, int n)
{
	double (*pF) (double) = F1;

	if (n == 2)
	{
		pF = F2;
	}

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
	puts(" 2 - Задать промежуток для табуляции");
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
	puts(" 1 - Ввести данные для табуляции");
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
					return 0;
				case 2:
					screen_tab_F(n);
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