#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define BET 500	// 베팅액 고정

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
}Combinations;	// 족보

typedef struct
{
	int number;
	bool special;
}Card; // 카드 구조체

typedef struct
{
	char name[100];
	int money;
	Card card1;
	Card card2;
	Combinations combine;
}Player; // 플레이어 구조체

void InitCards(Card* cards); // 카드 생성
void Shuffle(Card* cards); // 카드 셔플
Combinations Combination(Card card1, Card card2); // 족보 계산
void ShowResult(Player* player, int index); // 결과 출력

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

		printf("섯다 게임\n");
		printf("플레이어 수를 정하시오. (열명까지) : "); // 20장의 카드를 2장씩 사용하므로 10명이 최대
		scanf_s("%d", &playerNum);

		Player* player = (Player*)malloc(sizeof(Player) * playerNum); // 입력한 플레이어 수 만큼 동적할당으로 player 생성
	
		for (int i = 0; i < playerNum; i++) // 플레이어 이름 입력
		{
			char buffer[100] = { 0 };

			printf("%d번째 플레이어의 이름을 정하시오. (영문 100자, 한글 50자 이내) : ", i + 1);
			scanf_s(" %s", buffer, sizeof(buffer));
			strcpy_s(player[i].name, 100, buffer);

			player[i].money = 10000;
		}

		while (1)
		{
			InitCards(cards);
			Shuffle(cards);

			for (int i = 0; i < playerNum; i++) // 플레이어 카드 돌리기
			{
				player[i].card1.number = cards[i].number;
				player[i].card1.special = cards[i].special;
				player[i].card2.number = cards[i + 10].number;
				player[i].card2.special = cards[i + 10].special;

				player[i].combine = Combination(player[i].card1, player[i].card2);
			}

			Combinations max = ZEROPLUS;
			for (int i = 0; i < playerNum; i++) // 가장 높은 족보 찾기
			{
				if (max < player[i].combine)
					max = player[i].combine;
			}

			int prize = 0;
			int winner = 0;
			for (int i = 0; i < playerNum; i++) // 가장 높은 족보보다 낮으면 베팅액만큼 잃고, 잃은 금액은 상금에 쌓는다
												// 그리고 가장 높은족보 들고있는 사람수 카운트
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

			for (int i = 0; i < playerNum; i++) // 가장 높은 족보들고있는 사람에게 상금 / 중복인원 만큼 상금 분배
			{
				if (max == player[i].combine)
				{
					player[i].money += prize / winner;
				}
			}

			ShowResult(player, playerNum); // 결과 출력

			printf("0. 스톱 1. 계속 : ");
			scanf_s("%d", &CurrentGame);
			if (CurrentGame == 0)
			{
				free(player);
				player = NULL;

				break;
			}
		}
		printf("0. 게임 종료 1. 새 게임 : ");
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
	printf("\n이름\t\t보유금액\t카드1\t카드2\t광1\t광2\t족보\n");

	for (int i = 0; i < index; i++)
	{
		printf("%s\t\t%d\t\t%d\t%d\t", player[i].name, player[i].money, player[i].card1.number, player[i].card2.number);
		
		switch (player[i].card1.special)
		{
		case false:
			printf("X \t");
			break;
		case true:
			printf("광\t");
			break;
		}

		switch (player[i].card2.special)
		{
		case false:
			printf("X \t");
			break;
		case true:
			printf("광\t");
			break;
		}

		switch (player[i].combine)
		{
		case ZEROPLUS:
			printf("망통\n");
			break;
		case ONEPLUS:
			printf("한끗\n");
			break;
		case TWOPLUS:
			printf("두끗\n");
			break;
		case THREEPLUS:
			printf("세끗\n");
			break;
		case FOURPLUS:
			printf("네끗\n");
			break;
		case FIVEPLUS:
			printf("다섯끗\n");
			break;
		case SIXPLUS:
			printf("여섯끗\n");
			break;
		case SEVENPLUS:
			printf("일곱끗\n");
			break;
		case EIGHTPLUS:
			printf("여덟끗\n");
			break;
		case NINEPLUS:
			printf("갑오\n");
			break;
		case FOURSIX:
			printf("세륙\n");
			break;
		case FOURTEN:
			printf("장사\n");
			break;
		case ONETEN:
			printf("장삥\n");
			break;
		case ONENINE:
			printf("구삥\n");
			break;
		case ONEFOUR:
			printf("독사\n");
			break;
		case ONETWO:
			printf("알리\n");
			break;
		case ONEPAIR:
			printf("삥땡\n");
			break;
		case TWOPAIR:
			printf("이땡\n");
			break;
		case THREEPAIR:
			printf("삼땡\n");
			break;
		case FOURPAIR:
			printf("사땡\n");
			break;
		case FIVEPAIR:
			printf("오땡\n");
			break;
		case SIXPAIR:
			printf("육땡\n");
			break;
		case SEVENPAIR:
			printf("칠땡\n");
			break;
		case EIGHTPAIR:
			printf("팔땡\n");
			break;
		case NINEPAIR:
			printf("구땡\n");
			break;
		case TENPAIR:
			printf("장땡\n");
			break;
		case ONETHREESPECIAL:
			printf("일삼광땡\n");
			break;
		case ONEEIGHTSPECIAL:
			printf("일팔광땡\n");
			break;
		case THREEEIGHTSPECIAL:
			printf("삼팔광땡\n");
			break;
		}
	}
}
