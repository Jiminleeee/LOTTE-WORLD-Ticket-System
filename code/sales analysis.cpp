#include <stdio.h>

// report.csv ����  
	const int MAX = 100;
	int count = 0;
	int year[MAX], month[MAX], date[MAX], ticketChoiceArr[MAX], ticketTimeArr[MAX], ageArr[MAX], ticketAmountArr[MAX], totalFeeArr[MAX], specialOfferArr[MAX]={0};	

// ������ �Ǹ� ��Ȳ 	
	int ticketTimeList[MAX]={0}, age1DayList[MAX]={0}, ageAfter4List[MAX]={0}, totalFeeList[MAX]={0};

// ���ں� �Ǹ� ��Ȳ 
	int specialOfferList[MAX]={0},  totalFeeDayList[MAX][MAX]={0};
	int day,datePosition;


//���� ���� �ҷ�����
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
	printf("�⵵  ��  ��   ����  �ð�  ����  ����    ����  �������\n");
	for(int index = 0; index < count; index++)
	{
		printf("%d%4d%4d%5d%6d%7d%5d%10d%6d\n", year[index], month[index], date[index], ticketChoiceArr[index], ticketTimeArr[index], 
													ageArr[index], ticketAmountArr[index], totalFeeArr[index], specialOfferArr[index]);
	}
	printf("------------------------------------------------------------------------------------------------\n\n");
}

// ������ �Ǹ� ��Ȳ - 1Day�� ��
void ticketTimeOutput1Day()
{
	for(int index = 0; index < count; index++)
	{ //1Day �϶�  
		if(ticketTimeArr[index] == 1)
		{
			ticketTimeList[0] += ticketAmountArr[index];
		//���̿� ���� 1Day �Ǹ� ��Ȳ �ľ� 
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
		// 1Day ����	
			totalFeeList[0] += totalFeeArr[index];
		}
	}
} 

//������ �Ǹ� ��Ȳ - After4�� ��
void ticketTimeOutputAfter4()
{
	for(int index = 0; index < count; index++)
	{	
		if(ticketTimeArr[index] == 2)
		{
			ticketTimeList[1] += ticketAmountArr[index];
		//���̿� ���� After4 �Ǹ� ��Ȳ �ľ� 
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
		//After4 ����	
			totalFeeList[1] += totalFeeArr[index];
		}
	}		
}

// ������ �Ǹ� ��Ȳ ��� ���
void ticketTimeOutputResult()
{
	printf("1Day �� %d��\n", ticketTimeList[0]);
	printf("���̺� %d��, ��� %d��, û�ҳ� %d��, � %d��, ���� %d��\n", age1DayList[0], age1DayList[1], age1DayList[2], age1DayList[3], age1DayList[4]); 
	printf("1Day ���� : %d��\n\n", totalFeeList[0]);
	printf("After4 �� %d��\n", ticketTimeList[1]);
	printf("���̺� %d��, ��� %d��, û�ҳ� %d��, � %d��, ���� %d��\n", ageAfter4List[0], ageAfter4List[1], ageAfter4List[2], ageAfter4List[3], ageAfter4List[4]); 
	printf("After4 ���� : %d��\n", totalFeeList[1]);
} 

//������ ���� ���� ���
void ticketTimeOutputFile()
{
	FILE * filePointer1 = fopen("Ticketdata.csv", "w");
	
	fprintf(filePointer1, "����,�ְ���,�߰���\n");
	fprintf(filePointer1, "���̺�, %d,%d\n", age1DayList[0], ageAfter4List[0]);
	fprintf(filePointer1, "���, %d,%d\n", age1DayList[1], ageAfter4List[1]);
	fprintf(filePointer1, "û�ҳ�, %d,%d\n", age1DayList[2], ageAfter4List[2]);
	fprintf(filePointer1, "�, %d,%d\n", age1DayList[3], ageAfter4List[3]);
	fprintf(filePointer1, "����, %d,%d\n", age1DayList[4], ageAfter4List[4]);
	fprintf(filePointer1, "�հ�, %d,%d\n", ticketTimeList[0], ticketTimeList[1]);
	fprintf(filePointer1, "����, %d,%d\n", totalFeeList[0], totalFeeList[1]);
	
	fclose(filePointer1);
}

// ������ ���� ��Ȳ ����
void ticketTimeOutput()
{
	ticketTimeOutput1Day();
	ticketTimeOutputAfter4();
	ticketTimeOutputResult();
	ticketTimeOutputFile();
} 

// ���ں� ���� ��Ȳ 
void dailyOutput()
{
	FILE * filePointer2 = fopen("Dailydata.csv", "w");
 	fprintf(filePointer2,"��,��,��, �� ����\n");
	
	for(int index = 0; index < count; index++)
	{
	
		day = date[index];
		if(index == 0)
		{
			totalFeeDayList[datePosition][0] = day;						//datePosition = 0 > (0,0)�� ��¥�� �ϳ� ���´� 
			totalFeeDayList[datePosition][1] += totalFeeArr[index];		// (0,1)�� ����� �Ѿ��� ���� ���� ��� 
		}
		else if(date[index] == date[index-1])							// ��¥�� ������ �Ͱ� ������ (0,1)�� ����� �Ѿ��� �ѹ� �� ���Ѵ� 
		{
			totalFeeDayList[datePosition][1] += totalFeeArr[index];
		}
		else
		{
			datePosition++;												// �� ���� ��쿡�� (1,0)�� ���ο� ��¥ 
			totalFeeDayList[datePosition][0] = day;						
			totalFeeDayList[datePosition][1] += totalFeeArr[index];		// (1,1) > �� ���� ����� �Ѿ� 
		}
		if(date[index] == date[index+1])
		{																// ��¥�� ������ �� ������ ��� x > �ٸ� ��츸 ��� 
			continue;
		}
		else
		{
		
			printf("%d�� %02d�� %02d�� : �� ����  %6d��\n", year[index], month[index], date[index], totalFeeDayList[datePosition][1]);		
		}
		
		fprintf(filePointer2, "%d,%d,%d,%d\n", year[index], month[index], date[index], totalFeeDayList[datePosition][1]);
		
	}	
	fclose(filePointer2);
} 

// ���� �Ǹ���Ȳ 
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

// ���� �Ǹ� ��Ȳ ��� ���
void specialOfferOutputResult()
{
	printf("�� �Ǹ� Ƽ�� �� 	:  	%3d��\n", specialOfferList[0]);
	printf("��� ����       	:  	%3d��\n", specialOfferList[1]); 
	printf("�����          	:  	%3d��\n",specialOfferList[2]);
	printf("����������      	:  	%3d��\n", specialOfferList[3]); 
	printf("�ް� �庴       	:  	%3d��\n", specialOfferList[4]); 
	printf("�ӻ��          	:  	%3d��\n", specialOfferList[5]); 
	printf("�ٵ��� �ູī�� 	:	%3d��\n",specialOfferList[6]);
}

// ���� �Ǹ� ��Ȳ ���� ���
void specialOfferOutputFile()
{
	FILE * filePointer3 = fopen("special offer.csv", "w");

	fprintf(filePointer3, "����, ����\n");
	fprintf(filePointer3,"������, %d\n", specialOfferList[1]); 
	fprintf(filePointer3,"�����, %d\n", specialOfferList[2]);
	fprintf(filePointer3,"����������, %d\n", specialOfferList[3]);
	fprintf(filePointer3,"�ް� �庴, %d\n", specialOfferList[4]);
	fprintf(filePointer3,"�ӻ��, %d\n", specialOfferList[5]);
	fprintf(filePointer3,"�ٵ��� �ູī��, %d\n", specialOfferList[6]);     
	fprintf(filePointer3,"�հ�, %d\n", specialOfferList[0]); 

	fclose(filePointer3);
}

// ���� �Ǹ� ��Ȳ ����
void specialOfferOutput() 
{
	specialOfferOutputCalculation();
	specialOfferOutputResult();
	specialOfferOutputFile();
}


int main()
{
	reportFileOutput();
	
//������ �Ǹ� ��Ȳ
	printf("\n===============������ �Ǹ� ��Ȳ=============================\n");
	
	ticketTimeOutput();

	printf("-------------------------------------------------------------------\n\n\n");

 
//���ں� ���� ��Ȳ
	printf("=============���ں� ���� ��Ȳ ===============\n");
 	
 	dailyOutput();
	
	printf("--------------------------------------------------------\n\n\n");
	
	
// ���� �Ǹ� ��Ȳ
	printf("\n=========== ���� �Ǹ� ��Ȳ ===============\n");
	
	specialOfferOutput();
	
	printf("------------------------------------------------\n\n\n");


	return 0;

} 
