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
	timer = time(NULL);			//1900년 1월 1일 0시 0분 0초부터 시작하여 현재까지의 초 
	t = localtime(&timer); 		// 포맷팅을 위해 구조체에 넣음  
	
	while(true)
	{
		do
		{
			printf("권종을 선택하세요.\n1.  종합이용권(롯데월드 + 민속박물관)\n2.  파크이용권(롯데월드)\n");
			scanf("%d", &ticketChoice);
		} while(!(ticketChoice == 1 || ticketChoice== 2)); 
		
		do
		{
			printf("\n이용시간을 선택하세요.\n1.  1Day\n2.  After4(오후 4시부터 입장)\n");
			scanf("%d", &ticketTime); 
		} while(!(ticketTime == 1 || ticketTime == 2));
		
		printf("\n생년월일을 입력하세요. 예) 20220316 \n");
		scanf("%d", &personalNumber);
		
		printf("\n몇 개를 주문하시겠습니까?\n");
		scanf("%d", &ticketAmount); 
		 
		do
		{
			printf("\n우대사항을 선택하세요.\n1.  없음(나이 우대는 자동 처리)\n2.  장애인\n3.  국가유공자\n4.  휴가장병\n5.  임산부\n6.  다둥이 행복카드\n");
			scanf("%d", &specialOffer);
		} while(!(specialOffer == 1 || specialOffer == 2 || specialOffer == 3 || specialOffer == 4 || specialOffer == 5 || specialOffer == 6));
		
	// 오늘 날짜를  생년월일 형식으로 바꾸기 
		todayDate = (t -> tm_year + 1900) * 10000 + (t -> tm_mon + 1) * 100 + t -> tm_mday; 	// *10000, *100 > 0을 뒤에 붙여 3월9일이 아닌 0309의 형태로 나오게 한다. 
	
	//만 나이 계산
		age = (todayDate - personalNumber)/10000; 
	
	// 연령대별 분류에 따른 기본 티켓값 
		// 0 ~ 12개월 미만 
			if(age < MIN_BABY)
			{
				basicFee = 0;
			}
		
		// 12개월 이상 ~ 36개월 미만
			if(age >= MIN_BABY && age < MIN_CHILD && ticketAmount > 10)		// 단체 입장인 경우에만 입장료 있음(단체 기준은 임의로 10명 초과로 정함) 
			{
				basicFee = FEE_BABY;
			}
			else if(age >= MIN_BABY && age < MIN_CHILD && ticketAmount <= 10)	// 단체 입장이 아닌 경우 무료 입장 
			{
				basicFee = 0;
			}	
			
		// 36개월 이상 ~ 만 12세, 만 65세 이상 
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
			
		// 만 13세 이상 ~ 만 18세	
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
		
		// 만 19세 이상 ~ 만 64세	
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
			
	//티켓 최종가격 계산				
	// 우대조건 1. 나이 계산	
		if(specialOffer == 1)
		{
			totalFee = basicFee * ticketAmount;
		}
	// 우대조건 2. 	장애인 - 종합이용권, 파크이용권 50% + 동반 1인까지 
		if(specialOffer == 2)
		{
			if(ticketAmount == 1)
			{
				totalFee = basicFee * DISCOUNT_RATE_DISABLED;
			}
			if(ticketAmount == 2)
			{
				totalFee = basicFee * DISCOUNT_RATE_DISABLED * 2;
			}	
			else
			{
				totalFee = (basicFee * DISCOUNT_RATE_DISABLED * 2) + (basicFee * (ticketAmount - 2));
			}	
		}
	// 우대조건 3. 국가유공자 - 종합이용권, 파크이용권 50% + 동반 1인까지	
		if(specialOffer == 3)
		{
			if(ticketAmount == 1)
			{
				totalFee = basicFee * DISCOUNT_RATE_MERIT;
			}
			if(ticketAmount == 2)
			{
				totalFee = basicFee * DISCOUNT_RATE_MERIT * 2;
			}
			else
			{
				totalFee = (basicFee * DISCOUNT_RATE_MERIT * 2) + (basicFee * (ticketAmount -2));
			}
		}
	// 우대조건 4. 휴가장병 - 종합이용권 49% + 동반 1인까지	
		if(specialOffer == 4 && ticketChoice == 1)
		{
			if(ticketAmount == 1)
			{
				totalFee = basicFee * DISCOUNT_RATE_SOLDIER; 
			}
			if(ticketAmount == 2)
			{
				totalFee = basicFee * DISCOUNT_RATE_SOLDIER * 2;
			}
			else
			{
				totalFee = (basicFee * DISCOUNT_RATE_SOLDIER * 2) + (basicFee * (ticketAmount -2));
			}
		}
	// 우대조건 5. 임산부 - 종합이용권 50% + 본인만	
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
	// 우대조건 6. 다둥이 행복카드 - 종합이용권  30% + 카드에 명기된 가족에 한함	
		if(specialOffer == 6 && ticketChoice == 1)
		{
			totalFee = basicFee * DISCOUNT_RATE_FAMILY * ticketAmount;
		}

	// 티켓 최종 가격 출력 (무료인 경우 '무료 입장입니다')	
		if(totalFee == 0)
		{
			printf("\n무료 입장입니다.\n");
		}
		else
		{
		printf("\n가격은 %d 원 입니다.\n감사합니다.\n", totalFee);
		}
		
	// 티켓 구매 계속 진행 여부 확인	
		do
		{
			printf("\n티켓을 계속 구매 하시겠습니까?\n1.  티켓 구매\n2.  종료\n");
			scanf("%d", &againProcess);
		} while (!(againProcess == 1 || againProcess == 2));
		
		if(againProcess == 2)
		{
			printf("\n티켓 구매를 종료합니다.  감사합니다.\n");
			break; 
		}
		
	
	printf("\n");	// 가독성을 위해 한 줄 띄우기	
		
	}	
	
	return 0;	
}
	
 
  
