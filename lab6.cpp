// lab6.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream> //��� cin, cout
using namespace std; //��� cin, cout

struct Phone //�������
{
	char firm[64]; // �����
	char country[64];// ������ �������������
	double price; // ����
};

struct List // ������
{
	Phone phone; // ��� ����
	List *pNext; // ����������� ��������� �������
};

// ������� ���������� �������� � ������ ������
void addFirst(List *& pF, // ��������� �� ������ ������
	List* p) // ��������� �� ����������� �������
{
	p->pNext = pF;
	pF = p;
}
// �������� �������� �� ������ ������
List * delFirst(List *&pF) // ������� ���������� ��������� �� ��������� �������
{
	if (pF == 0) return 0;
	List *p = pF;
	pF = pF->pNext;
	return p;

}
// ���������� �������� ����� ��������
bool add(List *&pF, List * pZad, List *p)
{
	// ������� ���������� true ��� ���������� ���������� � false � ������ ������
	if (pZad == pF) // ������� ����� ������
	{
		p->pNext = pF;
		pF = p;
		return true;
	}

	List *pPred = pF; // ��������� �� ���������� ������� ����� pZad
	while (pPred->pNext != pZad && pPred->pNext)
		pPred = pPred->pNext;
	if (pPred->pNext == 0) return false; // �������� pZad ��� � ������
	p->pNext = pZad;
	pPred->pNext = p;
	return true;
}
// �������� ������ �������� p �� ������
List * del(List*& pF, List *p) // ������� ���������� ��������� �� ��������� �������
{
	if (pF == 0) return 0;
	if (pF == p) // ������� ������ �������
	{
		pF = pF->pNext;
		return p;
	}
	else
	{
		List *pPred = pF; // ��������� �� ���������� ������� ����� p
		while (pPred->pNext != p && pPred->pNext)
			pPred = pPred->pNext;
		if (pPred->pNext == 0) return 0; // �������� p ��� � ������
		pPred->pNext = p->pNext;
		return p;
	}
	while (delFirst(pF)); // ������� ������
}

int main(int argc, char* argv[])
{
	List *pF = 0; // ������ ����
	List *p;
	// ���� ������
	char Ch; // ���������� ��� ����� ������� ����������� �����
	do
	{

		p = (List *)malloc(sizeof(List)); // �������� ������ ��� �������
		printf("Firma: ");
		cin >> p->phone.firm;
		printf("Country: ");
		cin >> p->phone.country;
		printf("Price: ");
		cin >> p->phone.price;
		addFirst(pF, p); // ��������� ������� � ������ ������
		printf("For continue press Y or y else any key! ");
		cin >> Ch;
	} while (Ch == 'Y' || Ch == 'y');
	// ����� �����
	for (List *pi = pF; pi; pi = pi->pNext) // �������� ������
		printf("\n\n %s %s price=%.2f", pi->phone.firm, pi->phone.country, pi->phone.price);

	// ���������� ������
	for (List *pi = pF; pi->pNext;)
	{
		// ���� ����������� ������� � ������
		double min = pi->phone.price;
		List *pmin = pi;
		for (List *pj = pi->pNext; pj; pj = pj->pNext)
		if (pj->phone.price<min)
		{
			min = pj->phone.price;
			pmin = pj;
		}
		if (pi != pmin) // ����������� ������� ������ ������, �� ����� ����� pi
		{
			del(pF, pmin);
			add(pF, pi, pmin);
		}
		else pi = pi->pNext;
	}
	// ������ ������ ����� ����������
	printf("\n\nSrting:");
	for (List *pi = pF; pi; pi = pi->pNext) // �������� ������
		printf("\n%s %s price=%.2f", pi->phone.firm, pi->phone.country, pi->phone.price);
	system("pause"); // ������������� ���������, ���� ������� ����� �������
	return 0;
}