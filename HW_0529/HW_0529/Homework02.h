#pragma once

struct Card
{
	std::string Shape;	// 카드 모양
	int Number;			// 카드 넘버

	Card();
	Card(int InShape, int InNumber);

	void PrintCard();
};

struct Deck
{
	std::vector<Card> Cards;	// 덱


	Deck();

	void Initialize();
};

struct HandCards
{
	std::vector<Card> Cards;	// 손패
	int Score;					// 점수

	HandCards();
	void DrawCard(Deck& Deck);
	int CalcScore();
};

void Homework02_Run();
void PrintHandCard(HandCards& PlayerCards, HandCards& DealerCards, int Option = 0);
void InitializeCards(Deck& InDeck, HandCards& PlayerCards, HandCards& DealerCards);
void PlayerTurn(Deck& Deck, HandCards& PlayerCards, HandCards& DealerCards);
void DealerTurn(Deck& Deck, HandCards& PlayerCards, HandCards& DealerCards);
void CalcResult(Deck& Deck, HandCards& PlayerCards, HandCards& DealerCards);