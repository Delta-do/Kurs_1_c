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

int cycle_input(int max_input)
{
	int k;

	do {
		fseek(stdin, 0, SEEK_END); //очищаем поток ввода
		puts("Введено некорректное значение");
		puts("Введите другое значение");
		printf("> ");
		scanf("%d", &k);
	} while (!(k >= 0 && k <= max_input));

	return k;
}

int screen_start()
{
	int k;

	fseek(stdin, 0, SEEK_END);
	system("cls"); //очищаем экран
	puts("Добро пожаловать!");
	puts("Это программа для расчёта функций: F1 и F2 ");
	puts("	сделана студенткой группы бИСТ-223 Смоленской Марией");
	puts("	по предмету \"Основы программирования и алгоритмизации\"");
	puts("Какую функцию вы хотите вычислить?");
	puts(" 1 - функция F1"); 
	puts(" 2 - функция F2");
	puts(" 0 - выход из программы");
	printf("> ");
	scanf("%d", &k);

	while (1)
	{
		switch (k)
		{
		case 0:
		{
			return 0;
		}
		case 1:
		{
			screen_F(1);
			return 0;
		}
		case 2:
		{
			screen_F(2);
			return 0;
		}

		default:
			k = cycle_input(2);
		}
	}
	return 0;
}

int screen_F(int n)
{
	int k;

	fseek(stdin, 0, SEEK_END);
	system("cls");
	printf("Расчёт функции F%d\n", n);
	puts("Каковы дальнейшие действия?");
	puts(" 1 - возврат к стартовому меню");
	puts(" 2 - задать значение");
	puts(" 3 - задать промежуток");
	puts(" 0 - выход из программы");
	printf("> ");
	scanf("%d", &k);

	while (1)
	{
		switch (k)
		{
		case 0:
		{
			return 0;
		}
		case 1:
		{
			screen_start();
			return 0;
		}
		case 2:
		{
			double x, y;
			puts("Введите значение x");
			printf("x = ");
			scanf("%lg", &x);

			if (n == 1) {

				if (x == 0)
				{
					do {
						fseek(stdin, 0, SEEK_END); //очищаем поток ввода
						puts("Значение x не из области допустимых значений");
						puts("Введите другое значение");
						printf("x = ");
						scanf("%lg", &x);
					} while (x == 0);
				}

				y = F1(x);
				printf("F1(%lg) = %.4lg\n", x, y);
			}

			if (n == 2)
			{
				y = F2(x);
				printf("F2(%lg) = %.4lg\n", x, y);
			}

			puts("Продолжить?");
			puts(" 1 - Да");
			puts(" 0 - Нет");
			printf("> ");
			scanf("%d", &k);
			if (k)
				screen_F(n);
			else
				return 0;

			return 0;
		}
		case 3:
		{
			puts("*Задание промежутка*");
			return 0;
		}

		default:
			k = cycle_input(3);
		}
	}

	return 0;
}


int main()
{
	
	setlocale(LC_ALL, "RUS");

	screen_start();
	
	return 0;
}