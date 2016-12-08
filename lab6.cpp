// lab6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream> //для cin, cout
using namespace std; //для cin, cout

struct Phone //Телефон
{
	char firm[64]; // Фирма
	char country[64];// Страна производитель
	double price; // Цена
};

struct List // Список
{
	Phone phone; // Инф поле
	List *pNext; // Указательна следующий элемент
};

// Функция добавления элемента в начало списка
void addFirst(List *& pF, // Указатель на начало списка
	List* p) // Указатель на добавляемый элемент
{
	p->pNext = pF;
	pF = p;
}
// Удаление элемента из начала списка
List * delFirst(List *&pF) // Функция возвращает указатель на удаляемый элемент
{
	if (pF == 0) return 0;
	List *p = pF;
	pF = pF->pNext;
	return p;

}
// Добавление элемента перед заданным
bool add(List *&pF, List * pZad, List *p)
{
	// Функция возвращает true при нормальном завершении и false в случае ошибки
	if (pZad == pF) // Элемент будет первым
	{
		p->pNext = pF;
		pF = p;
		return true;
	}

	List *pPred = pF; // Указатель на предыдущий элемент перед pZad
	while (pPred->pNext != pZad && pPred->pNext)
		pPred = pPred->pNext;
	if (pPred->pNext == 0) return false; // Элемента pZad нет в списке
	p->pNext = pZad;
	pPred->pNext = p;
	return true;
}
// Удаление любого элемента p из списка
List * del(List*& pF, List *p) // Функция возвращает указатель на удаленный элемент
{
	if (pF == 0) return 0;
	if (pF == p) // Удаляем первый элемент
	{
		pF = pF->pNext;
		return p;
	}
	else
	{
		List *pPred = pF; // Указатель на предыдущий элемент перед p
		while (pPred->pNext != p && pPred->pNext)
			pPred = pPred->pNext;
		if (pPred->pNext == 0) return 0; // Элемента p нет в списке
		pPred->pNext = p->pNext;
		return p;
	}
	while (delFirst(pF)); // Очистка списка
}

int main(int argc, char* argv[])
{
	List *pF = 0; // Список пуст
	List *p;
	// Ввод списка
	char Ch; // Переменная для ввода условия продолжения ввода
	do
	{

		p = (List *)malloc(sizeof(List)); // Выделяем память под элемент
		printf("Firma: ");
		cin >> p->phone.firm;
		printf("Country: ");
		cin >> p->phone.country;
		printf("Price: ");
		cin >> p->phone.price;
		addFirst(pF, p); // Добавляем элемент в начало списка
		printf("For continue press Y or y else any key! ");
		cin >> Ch;
	} while (Ch == 'Y' || Ch == 'y');
	// Вывод спика
	for (List *pi = pF; pi; pi = pi->pNext) // Просмотр списка
		printf("\n\n %s %s price=%.2f", pi->phone.firm, pi->phone.country, pi->phone.price);

	// Сортировка списка
	for (List *pi = pF; pi->pNext;)
	{
		// Ищем минимальный элемент в списке
		double min = pi->phone.price;
		List *pmin = pi;
		for (List *pj = pi->pNext; pj; pj = pj->pNext)
		if (pj->phone.price<min)
		{
			min = pj->phone.price;
			pmin = pj;
		}
		if (pi != pmin) // Минимальный элемент делаем первым, он будет перед pi
		{
			del(pF, pmin);
			add(pF, pi, pmin);
		}
		else pi = pi->pNext;
	}
	// Печать списка после сортировки
	printf("\n\nSrting:");
	for (List *pi = pF; pi; pi = pi->pNext) // Просмотр списка
		printf("\n%s %s price=%.2f", pi->phone.firm, pi->phone.country, pi->phone.price);
	system("pause"); // Останавливаем программу, ждем нажатия любой клавиши
	return 0;
}