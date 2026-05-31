#include <iostream>
#include <string>
#include "Homework01_Run.h"

using namespace std;

void Homework01_Run()
{
	/// 입력 받을 변수
	int Years = 0;	// 년
	int Months = 0;	// 월
	int Days = 0;	// 일

	int ResultDays = 0;	// 변환한 총 일수

	printf("1. 요일 구하기\n");
	printf(" - 1년 1월 1일(월요일)을 기준으로 입력한 날짜까지 며칠이 지났는지 계산한 후, 7로 나눈 나머지로 요일을 구하기.\n");
	printf("년, 월, 일을 입력하세요.(공백으로 구분 = ");

	cin >> Years >> Months >> Days;

	CalcDayOfWeek(Years, Months, Days);
}

void CalcDayOfWeek(const int Years, const int Months, const int Days)
{
	/// 입력받은 년, 월, 일을 총 일수로 변환해서 합산
	// 년도 변환
	int dY = YearsToDays(Years);

	// 월 변환
	int dM = MonthsToDays(Months, IsLeapYear(Years));
	//printf("dY = %d / dM = %d / d = %d\n", dY, dM, Days);

	// 총 일수 합산
	int TotalDays = dY + dM + Days;
	//printf("총 일수 => %d \n", TotalDays);

	std::string DaysOfWeek[] = {"월요일", "화요일", "수요일", "목요일", "금요일", "토요일", "일요일"};
	int idx = (TotalDays - 1) % 7;
	printf("[%d년, %d월, %d일]은 (%s)입니다.\n\n", Years, Months, Days, DaysOfWeek[idx].c_str());
}


int YearsToDays(const int Years)
{
	int Result = 0;
	int LeapYearCount = 0;	// 윤년 개수

	for(int i = 1; i < Years; i++)
	{
		// 윤년이면 카운트 1 증가
		if (IsLeapYear(i))
		{
			LeapYearCount++;
		}
	}

	Result = (Years - 1) * 365 + LeapYearCount;

	return Result;
}

int MonthsToDays(const int Months, const bool isLeapYear)
{
	int Result = 0;
	 
	for (int i = 1; i < Months; i++)
	{
		switch (i)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
			{
				Result += 31;
				break;
			}

			case 4:
			case 6:
			case 9:
			case 11:
			{
				Result += 30;
				break;
			}

			case 2:
			{
				// 윤년인 경우 29일, 평년인 경우 28일로 계산
				(isLeapYear) ? Result += 29 : Result += 28;
				break;
			}

			default:
			{
				printf("ERROR \n\n");
				break;
			}
		}
	}

	return Result;
}

bool IsLeapYear(const int Year)
{
	return (Year % 4 == 0) && (Year % 100 != 0) || ((Year % 400 == 0));
}

