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
	const float DISCOUNT_RATE_DISABLED = 0.5, DISCOUNT_RATE_DISABLED_WITH = 0.5;
	const float DISCOUNT_RATE_MERIT = 0.5, DISCOUNT_RATE_MERIT_WITH = 0.5; 
	const float DISCOUNT_RATE_SOLDIER = 0.51, DISCOUNT_RATE_SOLDIER_WITH = 0.51;
	const float DISCOUNT_RATE_PREGNANT = 0.5;
	const float DISCOUNT_RATE_FAMILY = 0.7;
	
	int ticketChoice, ticketTime, personalNumber, ticketAmount, specialOffer, totalFee, againProcess;
	int todayDate, age, basicFee;
	 
int main()
{	
 // 오늘 날짜 구하기 
	time_t timer;
	struct tm * t;
	timer = time(NULL);		//1970년 1월 1일 0시 0분 0초부터 시작하여 현재까지의 초 
	t = localtime(&timer); 	// 포맷팅을 위해 구조체에 넣음  
	
	while(true)
	{
		printf("권종을 선택하세요.\n1.  종합이용권\n2.  파크이용권\n");
		scanf("%d", &ticketChoice);
	
		printf("\n이용시간을 선택하세요.\n1.  1Day\n2.  After4\n");
		scanf("%d", &ticketTime); 
		
		printf("\n생년월일을 입력하세요. 예) 20220316 \n");
		scanf("%d", &personalNumber);
		
		
		
	// 오늘 날짜를  생년월일 형식으로 바꾸기 
		todayDate = (t -> tm_year + 1900) * 10000 + (t -> tm_mon + 1) * 100 + t -> tm_mday; 	// *10000, *100 > 0을 뒤에 붙여 3월9일이 아닌 0309의 형태로 나오게 한다. 
	
	
	//만 나이 계산
		age = (todayDate - personalNumber)/10000; 
	
	
	// 연령대별 분류에 따른 기본 티켓값 
		// 0 ~ 36개월 미만 
			if(age < MIN_CHILD)
			{
				basicFee = 0;
			}
			
		// 36개월 이상 ~ 만 12세, 만 65세 이상 
			if(age >= MIN_CHILD && age <= MAX_CHILD || age > MAX_ADULT)
			{
				if(ticketChoice == 1 && ticketTime == 1)
				{
					basicFee = FEE_CHILD_BOTH_1DAY; 	
				}
				
				if(ticketChoice == 1 && ticketTime == 2)
				{
					basicFee = FEE_CHILD_BOTH_AFTER4;
				}
				
				if(ticketChoice == 2 && ticketTime == 1)
				{
					basicFee = FEE_CHILD_PARK_1DAY;
				}
				
				if(ticketChoice == 2 && ticketTime == 2)
				{
					basicFee = FEE_CHILD_PARK_AFTER4;
				}
			} 	
			
		// 만 13세 이상 ~ 만 18세	
			if(age >= MIN_TEEN && age <= MAX_TEEN)
			{
				if(ticketChoice == 1 && ticketTime == 1)
				{
					basicFee = FEE_TEEN_BOTH_1DAY; 	
				}
				
				if(ticketChoice == 1 && ticketTime == 2)
				{
					basicFee = FEE_TEEN_BOTH_AFTER4;
				}
				
				if(ticketChoice == 2 && ticketTime == 1)
				{
					basicFee = FEE_TEEN_PARK_1DAY;
				}
				
				if(ticketChoice == 2 && ticketTime == 2)
				{
					basicFee = FEE_TEEN_PARK_AFTER4;
				}
			} 	
		
		// 만 19세 이상 ~ 만 64세	
			if(age >= MIN_ADULT && age <= MAX_ADULT)
			{
				if(ticketChoice == 1 && ticketTime == 1)
				{
					basicFee = FEE_ADULT_BOTH_1DAY; 	
				}
				
				if(ticketChoice == 1 && ticketTime == 2)
				{
					basicFee = FEE_ADULT_BOTH_AFTER4;
				}
				
				if(ticketChoice == 2 && ticketTime == 1)
				{
					basicFee = FEE_ADULT_PARK_1DAY;
				}
				
				if(ticketChoice == 2 && ticketTime == 2)
				{
					basicFee = FEE_ADULT_PARK_AFTER4;
				}
			} 	
		
		printf("\n몇 개를 주문하시겠습니까?  (최대 주문량 10개)\n");
		scanf("%d", &ticketAmount); 
		 
		printf("\n우대사항을 선택하세요.\n1.  없음(나이 우대는 자동 처리)\n2.  장애인\n3.  국가유공자\n4.  휴가장병\n5.  임산부\n6.  다둥이 행복카드\n");
		scanf("%d", &specialOffer);
		
	// 동반1인 조건 제외한 우대가격
		
		if(specialOffer == 2)
		{
			basicFee *= DISCOUNT_RATE_DISABLED;
		}
		else if(specialOffer == 3)
		{
			basicFee *= DISCOUNT_RATE_MERIT;
		}
		else if(specialOffer == 4 && ticketChoice == 1)
		{
			basicFee *= DISCOUNT_RATE_SOLDIER; 
		}
		else if(specialOffer == 5 && ticketChoice == 1)
		{
			basicFee *= DISCOUNT_RATE_PREGNANT;
		} 
		else if(specialOffer == 6 && ticketChoice == 1)
		{
			basicFee *= DISCOUNT_RATE_FAMILY;
		}

	// 개수에 따른 요금 계산 
		
		totalFee = basicFee * ticketAmount;	
		
		printf("\n가격은 %d 원 입니다.\n감사합니다.\n", totalFee);
		
		printf("\n계속 발권하시겠습니까?\n1.  티켓 발권\n2.  종료\n");
		scanf("%d", &againProcess);
		if(againProcess == 2)
		{
			printf("\n티켓 발권을 종료합니다.  감사합니다.\n");
			break; 
		}
		
		
	}	
	
	return 0;	
}
	
 
  
