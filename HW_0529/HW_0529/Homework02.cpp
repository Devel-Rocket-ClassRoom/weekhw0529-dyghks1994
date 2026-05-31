#include <random>
#include <iostream>
#include <vector>
#include "Homework02.h"

using namespace std;

/// <summary>
///  블랙잭
/// 게임 목표
///		두 카드의 합이 21에 가깝게 만들되, 21을 넘지 않는 것이 목표
///		21을 초과하면(버스트, Bust)  즉시 패배
///		배팅은 없음
/// 카드의 값
///		2~10: 카드 숫자 그대로 점수.
///		J(잭), Q(퀸), K(킹) : 각각 10점.
///		A(에이스) : 1점 또는 11점(유리한 쪽으로 자동 선택).
///	게임 진행 절차
///		초기 배분
///			딜러와 플레이어 모두 2장씩 카드를 받음.
///			플레이어의 카드는 두 장 모두 공개.
///			딜러는 한 장은 공개(오픈 카드), 한 장은 비공개(홀 카드).
///		플레이어 턴
///			플레이어가 먼저 행동.
///			선택지:
///				Hit(히트) : 카드를 한 장 더 받음.
///				Stand(스탠드) : 더 이상 카드를 받지 않고 멈춤.
///			플레이어가 21을 초과하면(버스트) 즉시 패배.
///		딜러 턴
///			플레이어가 스탠드를 하면 딜러 차례.
///			딜러는 자신의 카드 합이 17 이상이 될 때까지 계속 히트(카드 받기)해야 함.
///			A가 포함된 "소프트 17"(A + 6 = 7 또는 17)도 멈춤.
///			17 이상이면 멈추고, 21을 넘으면 딜러 패배.
/// 승패 판정
///		버스트가 아닌 경우, 점수 비교.
///			플레이어가 21에 더 가까우면 승리.
///			동점이면 무승부(Push).
///			딜러가 더 가까우면 패배.
///		블랙잭: 처음 받은 두 장이 A + 10(또는 J, Q, K)이면 블랙잭.일반적으로 블랙잭이 단순 21점보다 우선함.
/// Homework02_Run(); 함수로 실행 가능해야 함.
/// </summary>
void Homework02_Run()
{
	int Round = 1;

	// 덱 생성
	Deck GameDeck;

	// 손패 생성
	HandCards PlayerHands;
	HandCards DealerHands;

	while (true)
	{
		system("cls");
		printf("[블랙잭] Round %d\n\n", Round);

		// 손패 초기화
		InitializeCards(GameDeck, PlayerHands, DealerHands);

		PrintHandCard(PlayerHands, DealerHands, 1);	// 딜러 턴 전까지, 딜러카드 1장만 출력되게 함.

		/// 플레이어 턴
		PlayerTurn(GameDeck, PlayerHands, DealerHands);

		/// 딜러 턴
		DealerTurn(GameDeck, PlayerHands, DealerHands);

		/// 승패판정(점수 계산)
		CalcResult(GameDeck, PlayerHands, DealerHands);


		// 게임 라운드 +1
		Round++;

		int ReGame = 0;
		printf("재시작 = 1 / 종료는 2 입력 하세요.");
		cin >> ReGame;

		if (ReGame == 2)
		{
			printf("블랙잭을 종료 합니다.\n\n");
			break;
		}

	}
	
	
}

Card::Card()
	: Shape("")
	, Number(0)
{

}

Card::Card(int InShape, int InNumber)
	: Shape("")
	, Number(0)
{
	this->Number = InNumber;

	switch (InShape)
	{
		case 1:
		{
			this->Shape = "♠";
			break;
		}

		case 2:
		{
			this->Shape = "♥";
			break;
		}

		case 3:
		{
			this->Shape = "◆";
			break;
		}

		case 4:
		{
			this->Shape = "♣";
			break;
		}
	}
}

void Card::PrintCard()
{
	switch (this->Number)
	{
	case 1:
	{
		printf("%s%c ", this->Shape.c_str(), 'A');
		break;
	}

	case 11:
	{
		printf("%s%c ", this->Shape.c_str(), 'J');
		break;
	}

	case 12:
	{
		printf("%s%c ", this->Shape.c_str(), 'Q');
		break;
	}

	case 13:
	{
		printf("%s%c ", this->Shape.c_str(), 'K');
		break;
	}

	default:
	{
		printf("%s%d ", this->Shape.c_str(), this->Number);
		break;
	}
	}
}

HandCards::HandCards()
	: Score(0)
{
	Cards.reserve(10);	// 10장 만큼 공간 예약
}

void HandCards::DrawCard(Deck& Deck)
{
	Cards.push_back(Deck.Cards.back());		// 덱의 맨 뒤 카드를 패에 추가
	Deck.Cards.pop_back();					// 빼낸 카드 제거
}

/// <summary>
/// 현재 카드패의 점수 계산
/// </summary>
int HandCards::CalcScore()
{
	this->Score = 0;	// 점수 초기화
	int AceCount = 0;	// 현재 패의 A 개수

	for (vector<Card>::iterator iter = Cards.begin(); iter != Cards.end(); iter++)
	{
		// A는 우선 11 더하고 최종적으로 버스트 된 경우 10 차감
		if (iter->Number == 1)
		{
			this->Score += 11;
			AceCount++;
		}

		// J, Q, K -> 10으로 계산
		else if (iter->Number >= 11 && iter->Number <= 13)
		{
			this->Score += 10;
		}

		// 2 ~ 10 은 각 숫자만큼 증가
		else
		{
			this->Score += iter->Number;
		}
	}

	// 버스트 된 경우
	// A 개수만큼 10점씩 차감
	while (this->Score > 21 && AceCount > 0)
	{
		this->Score -= 10;
		AceCount--;
	}

	return this->Score;
}

void PrintHandCard(HandCards& PlayerCards, HandCards& DealerCards, int Option)
{
	printf("--------------------------------------\n\n");

	// 플레이어 카드 출력
	printf("플레이어 카드 = ");
	for (std::vector<Card>::iterator iter = PlayerCards.Cards.begin(); iter != PlayerCards.Cards.end(); iter++)
	{
		iter->PrintCard();		
	}

	// 딜러 카드 출력 
	printf("\n");
	printf("딜러 카드 = ");

	for (std::vector<Card>::iterator iter = DealerCards.Cards.begin(); iter != DealerCards.Cards.end(); iter++)
	{
		iter->PrintCard();

		// 옵션 값 있으면 1장 출력하고 바로 중단
		if (Option)
		{
			break;
		}
	}
	printf("\n");
	
	printf("--------------------------------------\n\n");

}



void InitializeCards(Deck& InDeck, HandCards& PlayerCards, HandCards& DealerCards)
{
	// 덱 초기화
	InDeck.Initialize();

	// 손패 초기화
	PlayerCards.Cards.clear();
	DealerCards.Cards.clear();

	// 플레이어 2장 드로우
	PlayerCards.DrawCard(InDeck);
	PlayerCards.DrawCard(InDeck);

	// 딜러 2장 드로우
	DealerCards.DrawCard(InDeck);
	DealerCards.DrawCard(InDeck);
}

void PlayerTurn(Deck& Deck, HandCards& PlayerCards, HandCards& DealerCards)
{
	// Hit 선택시 계속 드로우
	int curPlayerScore = PlayerCards.CalcScore();
	while (true)
	{
		int PlayerInput = 0;
		printf("1. Hit   ,    2.Stand  =  ");
		cin >> PlayerInput;

		// Stand 입력시 드로우 종료
		if (PlayerInput == 2)
		{
			printf("플레이어가 Stand 합니다.\n\n");
			break;
		}


		// 추가 드로우 후 점수 재계산
		PlayerCards.DrawCard(Deck);
		curPlayerScore = PlayerCards.CalcScore();

		// 버스트면 패배
		if (curPlayerScore > 21)
		{
			PrintHandCard(PlayerCards, DealerCards);
			printf("플레이어 점수 = %d로 버스트 되었습니다! \n", curPlayerScore);

			// 즉시 종료
			return;
		}

		// 옵션값으로 딜러카드 1장만 출력되도록 함.
		PrintHandCard(PlayerCards, DealerCards, 1);
	}
}

void DealerTurn(Deck& Deck, HandCards& PlayerCards, HandCards& DealerCards)
{
	int curDealerScore = DealerCards.CalcScore();

	// 딜러 점수가 17이상이 될 때까지 Hit
	while (curDealerScore < 17)
	{
		printf("딜러가 Hit 합니다.\n");

		DealerCards.DrawCard(Deck);					// 추가 드로우
		curDealerScore = DealerCards.CalcScore();	// 점수 재계산
		//PrintHandCard(PlayerCards, DealerCards);	// 카드패 출력

		if (curDealerScore > 21)
		{
			printf("딜러 점수 = %d로 버스트 되었습니다! \n", curDealerScore);
			return ;
		}

	}

	printf("\n");
	printf("딜러가 Stand 합니다.\n");

	return;
}

void CalcResult(Deck& Deck, HandCards& PlayerCards, HandCards& DealerCards)
{
	int curPlayerScore = PlayerCards.CalcScore();
	int curDealerScore = DealerCards.CalcScore();

	/// 전체 카드패 출력
	PrintHandCard(PlayerCards, DealerCards);

	if (curPlayerScore > curDealerScore)
	{
		printf("최종 점수 플레이어(%d)점  vs  딜러(%d)점 으로 플레이어의 승리!\n\n", curPlayerScore, curDealerScore);
	}

	else if (curPlayerScore < curDealerScore)
	{
		printf("최종 점수 플레이어(%d)점  vs  딜러(%d)점 으로 딜러 승리!\n\n", curPlayerScore, curDealerScore);
	}

	/// 점수가 같은 경우 패의 카드수 비교
	else
	{
		// 플레이어 카드 수가 적을 때
		if (PlayerCards.Cards.size() < DealerCards.Cards.size())
		{
			printf("최종 점수 플레이어(%d)점  vs  딜러(%d)점 으로 플레이어의 승리!\n\n", curPlayerScore, curDealerScore);

		}

		// 딜러 카드 수가 적을 때
		else if (PlayerCards.Cards.size() > DealerCards.Cards.size())
		{
			printf("최종 점수 플레이어(%d)점  vs  딜러(%d)점 으로 딜러 승리!\n\n", curPlayerScore, curDealerScore);
		}

		// 점수도 같고 카드 수도 같으면
		else
		{
			printf("최종 점수 플레이어(%d)점  vs  딜러(%d)점 으로 무승부!\n\n", curPlayerScore, curDealerScore);
		}
	}
}

Deck::Deck()
{
	Cards.reserve(52);
	
	Initialize();
}

void Deck::Initialize()
{
	Cards.clear();

	for (int CardShape = 1; CardShape <= 4; CardShape++)
	{
		for (int CardNum = 1; CardNum <= 13; CardNum++)
		{
			this->Cards.push_back(Card(CardShape, CardNum));
		}
	}
	
	// 덱 셔플
	int Size = Cards.size();
	for (int i = Size - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		Card Temp = Cards[i];
		Cards[i] = Cards[j];
		Cards[j] = Temp;
	}
}
