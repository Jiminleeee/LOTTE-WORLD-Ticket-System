#include <stdio.h>
#include <time.h>

// 기본 변수 정의

 //권종별 가격
 	const int FEE_BABY = 15000;
	const int FEE_ADULT_BOTH_1DAY = 59000, FEE_TEEN_BOTH_1DAY = 52000, FEE_CHILD_BOTH_1DAY = 47000;
	const int FEE_ADULT_BOTH_AFTER4 = 48000, FEE_TEEN_BOTH_AFTER4 = 42000, FEE_CHILD_BOTH_AFTER4 = 36000;
	const int FEE_ADULT_PARK_1DAY = 56000, FEE_TEEN_PARK_1DAY = 50000, FEE_CHILD_PARK_1DAY = 46000;
	const int FEE_ADULT_PARK_AFTER4 = 45000, FEE_TEEN_PARK_AFTER4 = 40000, FEE_CHILD_PARK_AFTER4 = 35000; 
	
 //나이에 따른 범위
	const int MIN_BABY = 1; 
	const int MIN_CHILD = 3, MAX_CHILD = 12;
	const int MIN_TEEN = 13, MAX_TEEN = 18;
	const int MIN_ADULT = 19, MAX_ADULT = 64;	

 //할인율
	const float DISCOUNT_RATE_DISABLED = 0.5;
	const float DISCOUNT_RATE_MERIT = 0.5; 
	const float DISCOUNT_RATE_SOLDIER = 0.51;
	const float DISCOUNT_RATE_PREGNANT = 0.5;
	const float DISCOUNT_RATE_FAMILY = 0.7;
 
 //기타	
	int ticketChoice, ticketTime, personalNumber, ticketAmount, specialOffer, againProcess;			 
	int id, gender, century, birthYearFull, birthYear, birthMonth, birthDate, gap, age;					// 만 나이 계산 
	int basicFee, totalFee, finalFee;
	int ticketChoiceArr[100]={0}, ticketTimeArr[100]={0}, ageArr[100]={0}, ticketAmountArr[100]={0}, totalFeeArr[100]={0}, specialOfferArr[100]={0};	// 주문 내역 저장 
	int count;	// 배열에서 활용 
	int continueBuying;


//함수 정의
//오늘 날짜 구하기 
void todayDate()
{
	time_t timer;
	struct tm * t;
	timer = time(NULL);			//1900년 1월 1일 0시 0분 0초부터 시작하여 현재까지의 초 
	t = localtime(&timer); 		// 포맷팅을 위해 구조체에 넣음 
}
// 티켓 권종 선택 
void selectTicket()
{
	do
		{
			printf("권종을 선택하세요.\n");
			printf("1.  종합이용권(롯데월드 + 민속박물관)\n");
			printf("2.  파크이용권(롯데월드)\n");
			scanf("%d", &ticketChoice);
		} while(!(ticketChoice == 1 || ticketChoice== 2)); 
	
}
// 입장 시간 선택 
void selectTime()
{
	do
		{
			printf("\n이용시간을 선택하세요.\n");
			printf("1.  1Day\n");
			printf("2.  After4(오후 4시부터 입장)\n");
			scanf("%d", &ticketTime); 
		} while(!(ticketTime == 1 || ticketTime == 2));
}
// 주민등록번호 입력 
void inputId()
{
	printf("\n주민등록 번호를 입력하세요. 예) 940907-2 \n");
	scanf("%d-%d", &id, &gender);		
}	 
// 티켓 매수 선택 
void howManyTicket()
{
	printf("\n몇 개를 주문하시겠습니까?\n");
	scanf("%d", &ticketAmount); 	
}
// 우대조건 선택 
void selectOffer()
{
	do
		{
			printf("\n우대사항을 선택하세요.\n");
			printf("1.  없음(나이 우대는 자동 처리)\n");
			printf("2.  장애인(동반1인까지, 종합이용권/파크이용권 50%% 우대)\n");
			printf("3.  국가유공자(동반1인까지, 종합이용권/파크이용권 50%% 우대)\n");
			printf("4.  휴가장병(동반1인까지, 종합이용권 49%% 우대)\n");
			printf("5.  임산부(임산부 본인, 종합이용권 50%% 우대)\n");
			printf("6.  다둥이 행복카드(다둥이 행복카드 회원 본인(카드에 명기된 가족에 한함), 종합이용권 30%% 우대)\n");
			scanf("%d", &specialOffer);
		} while(!(specialOffer == 1 || specialOffer == 2 || specialOffer == 3 || specialOffer == 4 || specialOffer == 5 || specialOffer == 6));
}
// 만 나이 계산 
void americanAge()
{
	//오늘 날짜 구하기 
	time_t timer;
	struct tm * t;
	timer = time(NULL);			//1900년 1월 1일 0시 0분 0초부터 시작하여 현재까지의 초 
	t = localtime(&timer); 		// 포맷팅을 위해 구조체에 넣음 
	
	birthYear = id / 10000;					//자료형이 int라서 981216 > 98.1216 > 98
	birthMonth = (id % 10000) / 100; 		// 981216 > 1216 > 12.16 > 12
	birthDate = id % 100;					// 981216 > 9812.16 > 16
	
	switch(gender)
	{					
		case 1: case 2:
			century = 1900;								  
			birthYearFull = birthYear + century;
			break;
			 
		case 3: case 4:
			century = 2000;								
			birthYearFull = birthYear + century;
			break;
				
		default:
		break;	
	}
	
	//현재년도 - 출생년도 
	gap = (t -> tm_year +1900) - birthYearFull;		// 현재 년도에서 출생년도를 뺀다  // tm_year : 1900년 이후 지금이 몇 년인지를 나타냄 
	
	if(birthMonth >= (t -> tm_mon+1) && birthDate >= (t -> tm_mday))	// tm_mon : 0 ~ 11 > +1을 해야 함 // tm_mday : 1 ~ 31 > 그대로 사용  
	{
		age = gap;								// 생일이 지났으면 현재 년도에서 출생년도를 뺀만큼이 만 나이
	}
	else
	{
		age = gap - 1;							// 생일이 지나지 않았으면 현재 년도에서 출생년도를 뺀 것에 -1을 해야 만 나이 
	}	
}
// 베이비 무료 입장 
void freeBabyBasicFee() 
{
	if(age < MIN_BABY)
		{
			basicFee = 0;
		}
}
// 베이비 유료 입장 (단체인 경우) 
void babyBasicFee()
{
	if(age >= MIN_BABY && age < MIN_CHILD && ticketAmount > 10)		// 단체 입장인 경우에만 입장료 있음(단체 기준은 임의로 10명 초과로 정함) 
		{
			basicFee = FEE_BABY;
		}
		else if(age >= MIN_BABY && age < MIN_CHILD && ticketAmount <= 10)	// 단체 입장이 아닌 경우 무료 입장 
		{
			basicFee = 0;
		}	
}
// 어린이 및 노인 기본 입장료 
void childBasicFee()
{
	if(age >= MIN_CHILD && age <= MAX_CHILD || age > MAX_ADULT)
		{
			if(ticketChoice == 1)	 
				{
					if(ticketTime == 1)
					{
						basicFee = FEE_CHILD_BOTH_1DAY; 	
					}
					else if(ticketTime == 2)
					{
						basicFee = FEE_CHILD_BOTH_AFTER4;
					}
				}
			if(ticketChoice == 2)
				{
					if(ticketTime == 1)
					{
						basicFee = FEE_CHILD_PARK_1DAY;
					}
					else if(ticketTime == 2)
					{
						basicFee = FEE_CHILD_PARK_AFTER4;
					}
				}
		} 				
}
// 청소년 기본 입장료 
void teenBasicFee()
{
	if(age >= MIN_TEEN && age <= MAX_TEEN)
	{
		if(ticketChoice == 1)
		{
			if (ticketTime == 1)
			{
				basicFee = FEE_TEEN_BOTH_1DAY; 	
			}
			else if(ticketTime == 2)
			{
				basicFee = FEE_TEEN_BOTH_AFTER4;
			}
		}
		if(ticketChoice == 2)
		{ 
			if(ticketTime == 1)
			{
				basicFee = FEE_TEEN_PARK_1DAY;
			}
			else if(ticketTime == 2)
			{
				basicFee = FEE_TEEN_PARK_AFTER4;
			}
		}
	}
}
// 성인 기본 입장료 
void adultBasicFee()
{
	if(age >= MIN_ADULT && age <= MAX_ADULT)
	{
		if(ticketChoice == 1)
		{
			if(ticketTime == 1)
			{
				basicFee = FEE_ADULT_BOTH_1DAY; 	
			}
			else if(ticketTime == 2)
			{
				basicFee = FEE_ADULT_BOTH_AFTER4;
			}
		}
		if(ticketChoice == 2)
		{
			if(ticketTime == 1)
			{
				basicFee = FEE_ADULT_PARK_1DAY;
			}
			else if(ticketTime == 2)
			{
				basicFee = FEE_ADULT_PARK_AFTER4;
			}
		}
	}	
}
// 우대조건 1. 없음 (나이) 
void specialOfferAge()
{
	if(specialOffer == 1)
	{
		totalFee = basicFee * ticketAmount;
	}
}
// 우대조건 2. 장애인 
void specialOfferDisabled()
{
	if(specialOffer == 2)
	{
		if(ticketAmount == 1)
		{
			totalFee = basicFee * DISCOUNT_RATE_DISABLED;
		}
		else if(ticketAmount == 2)
		{
			totalFee = basicFee * DISCOUNT_RATE_DISABLED * 2;
		}	
		else
		{
			totalFee = (basicFee * DISCOUNT_RATE_DISABLED * 2) + (basicFee * (ticketAmount - 2));
		}	
	}
}
// 우대조건 3. 국가 유공자 
void specialOfferMerit()
{
	if(specialOffer == 3)
	{
		if(ticketAmount == 1)
		{
			totalFee = basicFee * DISCOUNT_RATE_MERIT;
		}
		else if(ticketAmount == 2)
		{
			totalFee = basicFee * DISCOUNT_RATE_MERIT * 2;
		}
		else
		{
			totalFee = (basicFee * DISCOUNT_RATE_MERIT * 2) + (basicFee * (ticketAmount -2));
		}
	}
}
// 우대조건 4. 휴가 장병 
void specialOfferSoldier()
{
	if(specialOffer == 4 && ticketChoice == 1)
	{
		if(ticketAmount == 1)
		{
			totalFee = basicFee * DISCOUNT_RATE_SOLDIER; 
		}
		else if(ticketAmount == 2)
		{
			totalFee = basicFee * DISCOUNT_RATE_SOLDIER * 2;
		}
		else
		{
			totalFee = (basicFee * DISCOUNT_RATE_SOLDIER * 2) + (basicFee * (ticketAmount -2));
		}
	}
}
// 우대조건 5. 임산부 
void specialOfferPregnant()
{
	if(specialOffer == 5 && ticketChoice == 1)
	{
		if(ticketAmount == 1) 
		{
			totalFee = basicFee * DISCOUNT_RATE_PREGNANT;
		}
		else
		{
			totalFee = (basicFee * DISCOUNT_RATE_PREGNANT) + (basicFee * (ticketAmount-1));
		}
	} 
}
// 우대조건 6. 다둥이 행복카드 
void specialOfferFamily()
{
	if(specialOffer == 6 && ticketChoice == 1)
	{
		totalFee = basicFee * DISCOUNT_RATE_FAMILY * ticketAmount;
	}
}
// 합산 티켓 가격 
void totalTicketFee()
{
	if(totalFee == 0)
	{
		printf("\n무료 입장입니다.\n");
	}
	else
	{
		printf("\n가격은 %d 원 입니다.\n감사합니다.\n", totalFee);
	}
	
	// 티켓 구매 내역의 최종 금액 
	finalFee += totalFee;
}
// 영수증 및 파일 출력 
void receiptAndFile()
{
	// 매출 파일 만들기 
	FILE * filePointer = fopen("report.csv","a");
	printf("\n====================== 롯데월드 ======================\n");
	printf("   권종     시간    연령     수량     가격       우대조건\n\n");
	for(int index = 0; index < count; index++)
	{//매출 파일 출력 
		time_t timer;
		struct tm * t;
		timer = time(NULL);			//1900년 1월 1일 0시 0분 0초부터 시작하여 현재까지의 초 
		t = localtime(&timer); 		// 포맷팅을 위해 구조체에 넣음 
		
		fprintf(filePointer, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",t-> tm_year + 1900, t-> tm_mon + 1, t -> tm_mday,
																ticketChoiceArr[index], ticketTimeArr[index], ageArr[index], 
																ticketAmountArr[index], totalFeeArr[index], specialOfferArr[index]);	
	// 입장권 종류	
		switch(ticketChoiceArr[index])
		{
			case 1:
				printf("종합이용권  ");
				break; 
			case 2:
				printf("파크이용권  ");
				break;
		}
	// 입장권 시간	
		switch(ticketTimeArr[index])
		{
			case 1: 
				printf("1Day    ");
				break;
			case 2:
				printf("After4  ");
				break; 
		}
	// 나이 구분	
		if(ageArr[index] < 3)
		{
			printf("베이비  ");
		}
		else if(ageArr[index] < 13)
		{
			printf("어린이  ");
		}
		else if(ageArr[index] < 19)
		{
			printf("청소년  ");
		}
		else if(ageArr[index] < 65) 
		{
			printf("어른    ");
		}
		else
		{
			printf("노인    ");
		}				
	// 티켓 수량
		printf("%3d   ", ticketAmountArr[index]);	
	// 총 가격 
		printf("%8d원   ", totalFeeArr[index]);
	// 우대조건 
		switch(specialOfferArr[index])
		{
			case 1:
				printf("우대조건 없음\n");
				break;
			case 2:
				printf("장애인 우대\n");
				break;
			case 3:
				printf("국가유공자 우대\n");
				break;
			case 4:
				printf("휴가장병 우대\n");
				break;
			case 5:
				printf("임산부 우대\n");
				break;
			case 6:
				printf("다둥이 행복카드 우대\n");
				break;
		}
	
	}
	printf("\n\n입장료 총액은 %d원 입니다.\n", finalFee);
	printf("=======================================================");
}
// 티켓 주문 선택  
void ticketOrderChoice()
{
	 
	selectTicket();		// 티켓 종류 선택
	
	selectTime();		// 입장 시간 선택	

	inputId();			// 주민등록번호 입력 
		
	howManyTicket();	// 티켓 매수 
	
	selectOffer();		// 우대조건 선택 
} 
// 나이 계산 및 나이에 따른 티켓 기본 가격 
void ageCalculation()
{
	americanAge();		//만 나이 계산
	
	// 연령대별 분류에 따른 기본 티켓값 
	freeBabyBasicFee();		// 0 ~ 12개월 미만 
	
	babyBasicFee();			// 12개월 이상 ~ 36개월 미만
		
	childBasicFee();		// 36개월 이상 ~ 만 12세, 만 65세 이상 
	
	teenBasicFee();			// 만 13세 이상 ~ 만 18세	
	
	adultBasicFee();		// 만 19세 이상 ~ 만 64세
}
// 우대 조건에 따른 티켓 가격 계산 
void specialOfferCalculation()
{
	specialOfferAge();		// 우대조건 1. 나이 계산
	
	specialOfferDisabled();	// 우대조건 2. 	장애인
			
	specialOfferMerit();	// 우대조건 3. 국가유공자
		
	specialOfferSoldier();	// 우대조건 4. 휴가장병
	
	specialOfferPregnant();	// 우대조건 5. 임산부 
		
	specialOfferFamily();	// 우대조건 6. 다둥이 행복카드 
}

int main()
{		
	while(true)
	{ 
	 do		//티켓 구매 과정 
	 {
	// 티켓 주문 선택
	 	ticketOrderChoice();
		 	 
	// 나이 계산 및 나이에 따른 티켓 기본 가격 	
		ageCalculation();		
			
	// 우대 조건에 따른 티켓 가격 계산				
		specialOfferCalculation();		 
		
	// 티켓 합산 가격
		totalTicketFee();		 
		
	// 티켓 구매 내역 저장 (배열) 
		ticketChoiceArr[count] = ticketChoice;
		ticketTimeArr[count] = ticketTime;
		ageArr[count] = age;
		ticketAmountArr[count] = ticketAmount;
		totalFeeArr[count] = totalFee;
		specialOfferArr[count] = specialOffer;
		count++;
		
	// 티켓 구매 계속 진행 여부 확인	
		printf("\n티켓을 계속 구매 하시겠습니까?\n1.  티켓 구매\n2.  종료\n");
		scanf("%d", &againProcess);
	 
	 } while (againProcess == 1);		// 1. 티켓 구매 선택시 티켓 구매 과정 다시 진행 
		
	printf("\n티켓 구매를 종료합니다.  감사합니다.\n");		//2. 종료 선택 시 티켓 구매 종료 
		
	// 티켓 구매 영수증 및 파일로 출력 
		receiptAndFile();
	
	// 새로운 티켓 구매 or 프로그램 종료 
		printf("\n\n계속 발권하시겠습니까?\n");
		printf("1. 새로운 주문\n2. 프로그램  종료\n");	
		scanf("%d", &continueBuying);
		
	//새로운 구매 진행시 기존 정보 초기화 
		count = 0;	
		finalFee = 0;
	
		if(continueBuying == 1)		// 1. 새로운 주문 선택시 티켓 구매 과정 처음부터 진행 
		{	
			continue;
		}
			
		break;		// 2. 종료 선택시 티켓 구매 종료 
		
    printf("\n");	//가독성 위해 한 줄 띄어쓰기 
	
	}

	return 0;	
}
	
 
  
