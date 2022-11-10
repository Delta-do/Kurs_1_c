#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

int F1()
{
	puts("*����� ����� 1 �������*");
	return 0;
}

int F2()
{
	puts("*����� ����� 2 �������*");
	return 0;
}

int cycle_input(int max_input)
{
	int k;

	do {
		fseek(stdin, 0, SEEK_END);
		puts("������� ������������ ��������");
		puts("������� ������ ��������");
		scanf("%d", &k);
	} while (!(k >= 0 && k <= max_input));

	return k;
}

int screen_start()
{
	int k;

	system("cls");
	puts("����� ����������!");
	puts("��� ��������� ��� ������� �������: F1 � F2 ");
	puts("	������� ���������� ������ ����-223 ���������� ������");
	puts("	�� �������� \"������ ���������������� � ��������������\"");
	puts("����� ������� �� ������ ���������?");
	puts(" 1 - ������� F1"); 
	puts(" 2 - ������� F2");
	puts(" 0 - ����� �� ���������");
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
	puts("������ ������� F1");
	puts("������ ���������� ��������?");
	puts(" 1 - ������� �� ���������� ����");
	puts(" 2 - ������ ��������");
	puts(" 3 - ������ ����������");
	puts(" 0 - ����� �� ���������");
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
			puts("*������� ��������*");
			return 0;
		}
		case 3:
		{
			puts("*������� ����������*");
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