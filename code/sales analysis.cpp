#include <stdio.h>

// report.csv 파일  
	const int MAX = 100;
	int count = 0;
	int year[MAX], month[MAX], date[MAX], ticketChoiceArr[MAX], ticketTimeArr[MAX], ageArr[MAX], ticketAmountArr[MAX], totalFeeArr[MAX], specialOfferArr[MAX]={0};	

// 권종별 판매 현황 	
	int ticketTimeList[MAX]={0}, age1DayList[MAX]={0}, ageAfter4List[MAX]={0}, totalFeeList[MAX]={0};

// 일자별 판매 현황 
	int specialOfferList[MAX]={0},  totalFeeDayList[MAX][MAX]={0};
	int day,datePosition;


//매출 파일 불러오기
void reportFileOutput()
{
	FILE * fp = fopen("report.csv","r");
	while(fscanf (fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d", &year[count], &month[count], &date[count], &ticketChoiceArr[count], &ticketTimeArr[count], 
													&ageArr[count], &ticketAmountArr[count], &totalFeeArr[count], &specialOfferArr[count]) != -1)
	{
		count++;
	}
	fclose(fp);
	
	printf("============================================ report.csv ======================================\n");
	printf("년도  월  일   권종  시간  연령  수량    가격  우대조건\n");
	for(int index = 0; index < count; index++)
	{
		printf("%d%4d%4d%5d%6d%7d%5d%10d%6d\n", year[index], month[index], date[index], ticketChoiceArr[index], ticketTimeArr[index], 
													ageArr[index], ticketAmountArr[index], totalFeeArr[index], specialOfferArr[index]);
	}
	printf("------------------------------------------------------------------------------------------------\n\n");
}

// 권종별 판매 현황 - 1Day일 때
void ticketTimeOutput1Day()
{
	for(int index = 0; index < count; index++)
	{ //1Day 일때  
		if(ticketTimeArr[index] == 1)
		{
			ticketTimeList[0] += ticketAmountArr[index];
		//나이에 따른 1Day 판매 현황 파악 
			if(ageArr[index] < 3)
			{
				age1DayList[0] += ticketTimeList[0];
			}
			else if(ageArr[index] < 13)
			{
				age1DayList[1] += ticketTimeList[0];
			}
			else if(ageArr[index] < 19)
			{
				age1DayList[2] += ticketTimeList[0];
			}
			else if(ageArr[index] < 65)
			{
				age1DayList[3] += ticketTimeList[0];
			}
			else if(ageArr[index] >= 65)
			{
				age1DayList[4] += ticketTimeList[0];
			}
		// 1Day 매출	
			totalFeeList[0] += totalFeeArr[index];
		}
	}
} 

//권종별 판매 현황 - After4일 때
void ticketTimeOutputAfter4()
{
	for(int index = 0; index < count; index++)
	{	
		if(ticketTimeArr[index] == 2)
		{
			ticketTimeList[1] += ticketAmountArr[index];
		//나이에 따른 After4 판매 현황 파악 
			if(ageArr[index] < 3)
			{
				ageAfter4List[0] += ticketTimeList[1];
			}
			else if(ageArr[index] < 13)
			{
				ageAfter4List[1] += ticketTimeList[1];
			}
			else if(ageArr[index] < 19)
			{
				ageAfter4List[2] += ticketTimeList[1];
			}
			else if(ageArr[index] < 65)
			{
				ageAfter4List[3] += ticketTimeList[1];
			}
			else if(ageArr[index] >= 65)
			{
				ageAfter4List[4] += ticketTimeList[1];
			}
		//After4 매출	
			totalFeeList[1] += totalFeeArr[index];
		}
	}		
}

// 권종별 판매 현황 결과 출력
void ticketTimeOutputResult()
{
	printf("1Day 총 %d매\n", ticketTimeList[0]);
	printf("베이비 %d매, 어린이 %d매, 청소년 %d매, 어른 %d매, 노인 %d매\n", age1DayList[0], age1DayList[1], age1DayList[2], age1DayList[3], age1DayList[4]); 
	printf("1Day 매출 : %d원\n\n", totalFeeList[0]);
	printf("After4 총 %d매\n", ticketTimeList[1]);
	printf("베이비 %d매, 어린이 %d매, 청소년 %d매, 어른 %d매, 노인 %d매\n", ageAfter4List[0], ageAfter4List[1], ageAfter4List[2], ageAfter4List[3], ageAfter4List[4]); 
	printf("After4 매출 : %d원\n", totalFeeList[1]);
} 

//권종별 매출 파일 출력
void ticketTimeOutputFile()
{
	FILE * filePointer1 = fopen("Ticketdata.csv", "w");
	
	fprintf(filePointer1, "구분,주간권,야간권\n");
	fprintf(filePointer1, "베이비, %d,%d\n", age1DayList[0], ageAfter4List[0]);
	fprintf(filePointer1, "어린이, %d,%d\n", age1DayList[1], ageAfter4List[1]);
	fprintf(filePointer1, "청소년, %d,%d\n", age1DayList[2], ageAfter4List[2]);
	fprintf(filePointer1, "어른, %d,%d\n", age1DayList[3], ageAfter4List[3]);
	fprintf(filePointer1, "노인, %d,%d\n", age1DayList[4], ageAfter4List[4]);
	fprintf(filePointer1, "합계, %d,%d\n", ticketTimeList[0], ticketTimeList[1]);
	fprintf(filePointer1, "매출, %d,%d\n", totalFeeList[0], totalFeeList[1]);
	
	fclose(filePointer1);
}

// 권종별 매출 현황 종합
void ticketTimeOutput()
{
	ticketTimeOutput1Day();
	ticketTimeOutputAfter4();
	ticketTimeOutputResult();
	ticketTimeOutputFile();
} 

// 일자별 매출 현황 
void dailyOutput()
{
	FILE * filePointer2 = fopen("Dailydata.csv", "w");
 	fprintf(filePointer2,"년,월,일, 총 매출\n");
	
	for(int index = 0; index < count; index++)
	{
	
		day = date[index];
		if(index == 0)
		{
			totalFeeDayList[datePosition][0] = day;						//datePosition = 0 > (0,0)에 날짜를 하나 놓는다 
			totalFeeDayList[datePosition][1] += totalFeeArr[index];		// (0,1)에 입장권 총액을 더한 값을 출력 
		}
		else if(date[index] == date[index-1])							// 날짜가 이전의 것과 같으면 (0,1)에 입장권 총액을 한번 더 더한다 
		{
			totalFeeDayList[datePosition][1] += totalFeeArr[index];
		}
		else
		{
			datePosition++;												// 그 외의 경우에는 (1,0)에 새로운 날짜 
			totalFeeDayList[datePosition][0] = day;						
			totalFeeDayList[datePosition][1] += totalFeeArr[index];		// (1,1) > 그 날의 입장권 총액 
		}
		if(date[index] == date[index+1])
		{																// 날짜가 다음날 과 같으면 출력 x > 다른 경우만 출력 
			continue;
		}
		else
		{
		
			printf("%d년 %02d월 %02d일 : 총 매출  %6d원\n", year[index], month[index], date[index], totalFeeDayList[datePosition][1]);		
		}
		
		fprintf(filePointer2, "%d,%d,%d,%d\n", year[index], month[index], date[index], totalFeeDayList[datePosition][1]);
		
	}	
	fclose(filePointer2);
} 

// 우대권 판매현황 
void specialOfferOutputCalculation()
{
	for(int index = 0; index < count; index++)
	{
		specialOfferList[0] += ticketAmountArr[index];
		
		if(specialOfferArr[index] == 1)
		{
			specialOfferList[1] += ticketAmountArr[index];
		}
		else if(specialOfferArr[index] == 2)
		{
			specialOfferList[2] += ticketAmountArr[index];
		}
		else if(specialOfferArr[index] == 3)
		{
			specialOfferList[3] += ticketAmountArr[index];
		}
		else if(specialOfferArr[index] == 4)
		{
			specialOfferList[4] += ticketAmountArr[index];
		}
		else if(specialOfferArr[index] == 5)
		{
			specialOfferList[5] += ticketAmountArr[index];
		}
		else if(specialOfferArr[index] == 6)
		{
			specialOfferList[6] += ticketAmountArr[index];
		}
	}
}

// 우대권 판매 현황 결과 출력
void specialOfferOutputResult()
{
	printf("총 판매 티켓 수 	:  	%3d매\n", specialOfferList[0]);
	printf("우대 없음       	:  	%3d매\n", specialOfferList[1]); 
	printf("장애인          	:  	%3d매\n",specialOfferList[2]);
	printf("국가유공자      	:  	%3d매\n", specialOfferList[3]); 
	printf("휴가 장병       	:  	%3d매\n", specialOfferList[4]); 
	printf("임산부          	:  	%3d매\n", specialOfferList[5]); 
	printf("다둥이 행복카드 	:	%3d매\n",specialOfferList[6]);
}

// 우대권 판매 현황 파일 출력
void specialOfferOutputFile()
{
	FILE * filePointer3 = fopen("special offer.csv", "w");

	fprintf(filePointer3, "구분, 우대권\n");
	fprintf(filePointer3,"우대없음, %d\n", specialOfferList[1]); 
	fprintf(filePointer3,"장애인, %d\n", specialOfferList[2]);
	fprintf(filePointer3,"국가유공자, %d\n", specialOfferList[3]);
	fprintf(filePointer3,"휴가 장병, %d\n", specialOfferList[4]);
	fprintf(filePointer3,"임산부, %d\n", specialOfferList[5]);
	fprintf(filePointer3,"다둥이 행복카드, %d\n", specialOfferList[6]);     
	fprintf(filePointer3,"합계, %d\n", specialOfferList[0]); 

	fclose(filePointer3);
}

// 우대권 판매 현황 종합
void specialOfferOutput() 
{
	specialOfferOutputCalculation();
	specialOfferOutputResult();
	specialOfferOutputFile();
}


int main()
{
	reportFileOutput();
	
//권종별 판매 현황
	printf("\n===============권종별 판매 현황=============================\n");
	
	ticketTimeOutput();

	printf("-------------------------------------------------------------------\n\n\n");

 
//일자별 매출 현황
	printf("=============일자별 매출 현황 ===============\n");
 	
 	dailyOutput();
	
	printf("--------------------------------------------------------\n\n\n");
	
	
// 우대권 판매 현황
	printf("\n=========== 우대권 판매 현황 ===============\n");
	
	specialOfferOutput();
	
	printf("------------------------------------------------\n\n\n");


	return 0;

} 
