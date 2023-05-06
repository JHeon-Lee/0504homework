#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define BET 500

typedef enum
{
	ZEROPLUS,
	ONEPLUS,
	TWOPLUS,
	THREEPLUS,
	FOURPLUS,
	FIVEPLUS,
	SIXPLUS,
	SEVENPLUS,
	EIGHTPLUS,
	NINEPLUS,
	FOURSIX,
	FOURTEN,
	ONETEN,
	ONENINE,
	ONEFOUR,
	ONETWO,
	ONEPAIR,
	TWOPAIR,
	THREEPAIR,
	FOURPAIR,
	FIVEPAIR,
	SIXPAIR,
	SEVENPAIR,
	EIGHTPAIR,
	NINEPAIR,
	TENPAIR,
	ONETHREESPECIAL,
	ONEEIGHTSPECIAL,
	THREEEIGHTSPECIAL
}Combinations;

typedef struct
{
	int number;
	bool special;
}Card;

typedef struct
{
	char name[100];
	int money;
	Card card1;
	Card card2;
	Combinations combine;
}Player;

void InitCards(Card* cards);
void Shuffle(Card* cards);
Combinations Combination(Card card1, Card card2);
void ShowResult(Player* player, int index);

int main()
{
	srand((unsigned int)time(NULL));
	rand();
	int isContinue = 1;
	int CurrentGame = 1;

	while (1)
	{
		system("cls");

		Card cards[20];
		int playerNum = 0;

		printf("���� ����\n");
		printf("�÷��̾� ���� ���Ͻÿ�. (�������) : ");
		scanf_s("%d", &playerNum);

		Player* player = (Player*)malloc(sizeof(Player) * playerNum);
	
		for (int i = 0; i < playerNum; i++)
		{
			char buffer[100] = { 0 };

			printf("%d��° �÷��̾��� �̸��� ���Ͻÿ�. (���� 100��, �ѱ� 50�� �̳�) : ", i + 1);
			scanf_s(" %s", buffer, sizeof(buffer));
			strcpy_s(player[i].name, 100, buffer);

			player[i].money = 10000;
		}

		while (1)
		{
			InitCards(cards);
			Shuffle(cards);

			for (int i = 0; i < playerNum; i++)
			{
				player[i].card1.number = cards[i].number;
				player[i].card1.special = cards[i].special;
				player[i].card2.number = cards[i + 10].number;
				player[i].card2.special = cards[i + 10].special;

				player[i].combine = Combination(player[i].card1, player[i].card2);
			}

			Combinations max = ZEROPLUS;
			for (int i = 0; i < playerNum; i++)
			{
				if (max < player[i].combine)
					max = player[i].combine;
			}

			int prize = 0;
			int winner = 0;
			for (int i = 0; i < playerNum; i++)
			{
				if (max != player[i].combine)
				{
					player[i].money -= BET;
					prize += BET;
				}
				if (max == player[i].combine)
				{
					winner++;
				}
			}

			for (int i = 0; i < playerNum; i++)
			{
				if (max == player[i].combine)
				{
					player[i].money += prize / winner;
				}
			}

			ShowResult(player, playerNum);

			printf("0. ���� 1. ��� : ");
			scanf_s("%d", &CurrentGame);
			if (CurrentGame == 0)
			{
				free(player);
				player = NULL;

				break;
			}
		}
		printf("0. ���� ���� 1. �� ���� : ");
		scanf_s("%d", &isContinue);
		if (isContinue == 0)
			break;
	}

	return 0;
}

void InitCards(Card* cards)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cards[i + j * 10].number = i + 1;
			if((i == 0 || i == 2 || i == 7) && j == 1)
				cards[i + j * 10].special = 1;
			else
				cards[i + j * 10].special = 0;
		}
	}
}

void Shuffle(Card* cards)
{
	for (int i = 0; i < 250; i++)
	{
		int src = rand() % 20;
		int dest = rand() % 20;

		Card temp = cards[src];
		cards[src] = cards[dest];
		cards[dest] = temp;
	}
}

Combinations Combination(Card card1, Card card2)
{
	if (card1.special == true && card2.special == true)
	{
		if (
			((card1.number == 3 && card2.number == 8) ||
				(card1.number == 8 && card2.number == 3))
			)
			return THREEEIGHTSPECIAL;

		else if (
			((card1.number == 1 && card2.number == 3) ||
				(card1.number == 3 && card2.number == 1))
			)
			return ONETHREESPECIAL;

		else if (
			((card1.number == 1 && card2.number == 8) ||
				(card1.number == 8 && card2.number == 1))
			)
			return ONEEIGHTSPECIAL;
	}

	else if (card1.number == card2.number)
	{
		if (card1.number == 10)
			return TENPAIR;

		else if (card1.number == 9)
			return NINEPAIR;

		else if (card1.number == 8)
			return EIGHTPAIR;

		else if (card1.number == 7)
			return SEVENPAIR;

		else if (card1.number == 6)
			return SIXPAIR;

		else if (card1.number == 5)
			return FIVEPAIR;

		else if (card1.number == 4)
			return FOURPAIR;

		else if (card1.number == 3)
			return THREEPAIR;

		else if (card1.number == 2)
			return TWOPAIR;

		else if (card1.number == 1)
			return ONEPAIR;
	}
	else
	{
		if (
			(card1.number == 1 && card2.number == 2) ||
			(card1.number == 2 && card2.number == 1)
			)
			return ONETWO;

		else if (
			(card1.number == 1 && card2.number == 4) ||
			(card1.number == 4 && card2.number == 1)
			)
			return ONEFOUR;

		else if (
			(card1.number == 1 && card2.number == 9) ||
			(card1.number == 9 && card2.number == 1)
			)
			return ONENINE;

		else if (
			(card1.number == 1 && card2.number == 10) ||
			(card1.number == 10 && card2.number == 1)
			)
			return ONETEN;

		else if (
			(card1.number == 4 && card2.number == 10) ||
			(card1.number == 10 && card2.number == 4)
			)
			return FOURTEN;

		else if (
			(card1.number == 4 && card2.number == 6) ||
			(card1.number == 6 && card2.number == 4)
			)
			return FOURSIX;

		else if (
			((card1.number + card2.number) % 10 == 9)
			)
			return NINEPLUS;

		else if (
			((card1.number + card2.number) % 10 == 8)
			)
			return EIGHTPLUS;

		else if (
			((card1.number + card2.number) % 10 == 7)
			)
			return SEVENPLUS;

		else if (
			((card1.number + card2.number) % 10 == 6)
			)
			return SIXPLUS;

		else if (
			((card1.number + card2.number) % 10 == 5)
			)
			return FIVEPLUS;

		else if (
			((card1.number + card2.number) % 10 == 4)
			)
			return FOURPLUS;

		else if (
			((card1.number + card2.number) % 10 == 3)
			)
			return THREEPLUS;

		else if (
			((card1.number + card2.number) % 10 == 2)
			)
			return TWOPLUS;

		else if (
			((card1.number + card2.number) % 10 == 1)
			)
			return ONEPLUS;

		else 
			return ZEROPLUS;
	}
}

void ShowResult(Player* player, int index)
{
	printf("\n�̸�\t\t�����ݾ�\tī��1\tī��2\t��1\t��2\t����\n");

	for (int i = 0; i < index; i++)
	{
		printf("%s\t\t%d\t\t%d\t%d\t", player[i].name, player[i].money, player[i].card1.number, player[i].card2.number);
		
		switch (player[i].card1.special)
		{
		case false:
			printf("X \t");
			break;
		case true:
			printf("��\t");
			break;
		}

		switch (player[i].card2.special)
		{
		case false:
			printf("X \t");
			break;
		case true:
			printf("��\t");
			break;
		}

		switch (player[i].combine)
		{
		case ZEROPLUS:
			printf("����\n");
			break;
		case ONEPLUS:
			printf("�Ѳ�\n");
			break;
		case TWOPLUS:
			printf("�β�\n");
			break;
		case THREEPLUS:
			printf("����\n");
			break;
		case FOURPLUS:
			printf("�ײ�\n");
			break;
		case FIVEPLUS:
			printf("�ټ���\n");
			break;
		case SIXPLUS:
			printf("������\n");
			break;
		case SEVENPLUS:
			printf("�ϰ���\n");
			break;
		case EIGHTPLUS:
			printf("������\n");
			break;
		case NINEPLUS:
			printf("����\n");
			break;
		case FOURSIX:
			printf("����\n");
			break;
		case FOURTEN:
			printf("���\n");
			break;
		case ONETEN:
			printf("���\n");
			break;
		case ONENINE:
			printf("����\n");
			break;
		case ONEFOUR:
			printf("����\n");
			break;
		case ONETWO:
			printf("�˸�\n");
			break;
		case ONEPAIR:
			printf("�涯\n");
			break;
		case TWOPAIR:
			printf("�̶�\n");
			break;
		case THREEPAIR:
			printf("�ﶯ\n");
			break;
		case FOURPAIR:
			printf("�綯\n");
			break;
		case FIVEPAIR:
			printf("����\n");
			break;
		case SIXPAIR:
			printf("����\n");
			break;
		case SEVENPAIR:
			printf("ĥ��\n");
			break;
		case EIGHTPAIR:
			printf("�ȶ�\n");
			break;
		case NINEPAIR:
			printf("����\n");
			break;
		case TENPAIR:
			printf("�嶯\n");
			break;
		case ONETHREESPECIAL:
			printf("�ϻﱤ��\n");
			break;
		case ONEEIGHTSPECIAL:
			printf("���ȱ���\n");
			break;
		case THREEEIGHTSPECIAL:
			printf("���ȱ���\n");
			break;
		}
	}
}
