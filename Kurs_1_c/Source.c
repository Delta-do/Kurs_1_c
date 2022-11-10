#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

int F1()
{
	puts("*Здесь будет 1 функция*");
	return 0;
}

int F2()
{
	puts("*Здесь будет 2 функция*");
	return 0;
}

int cycle_input(int max_input)
{
	int k;

	do {
		fseek(stdin, 0, SEEK_END);
		puts("Введено некорректное значение");
		puts("Введите другое значение");
		scanf("%d", &k);
	} while (!(k >= 0 && k <= max_input));

	return k;
}

int screen_start()
{
	int k;

	system("cls");
	puts("Добро пожаловать!");
	puts("Это программа для расчёта функций: F1 и F2 ");
	puts("	сделана студенткой группы бИСТ-223 Смоленской Марией");
	puts("	по предмету \"Основы программирования и алгоритмизации\"");
	puts("Какую функцию вы хотите вычислить?");
	puts(" 1 - функция F1"); 
	puts(" 2 - функция F2");
	puts(" 0 - выход из программы");
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
			screen_F1();
			return 0;
		}
		case 2:
		{
			F2();
			return 0;
		}

		default:
			k = cycle_input(2);
		}
	}
	return 0;
}

int screen_F1()
{
	int k;

	system("cls");
	puts("Расчёт функции F1");
	puts("Каковы дальнейшие действия?");
	puts(" 1 - возврат на предыдущее окно");
	puts(" 2 - задать значение");
	puts(" 3 - задать промежуток");
	puts(" 0 - выход из программы");
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
			puts("*Задание значения*");
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