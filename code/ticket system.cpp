#include <stdio.h>
#include <time.h>

// �⺻ ���� ����

 //������ ����
 	const int FEE_BABY = 15000;
	const int FEE_ADULT_BOTH_1DAY = 59000, FEE_TEEN_BOTH_1DAY = 52000, FEE_CHILD_BOTH_1DAY = 47000;
	const int FEE_ADULT_BOTH_AFTER4 = 48000, FEE_TEEN_BOTH_AFTER4 = 42000, FEE_CHILD_BOTH_AFTER4 = 36000;
	const int FEE_ADULT_PARK_1DAY = 56000, FEE_TEEN_PARK_1DAY = 50000, FEE_CHILD_PARK_1DAY = 46000;
	const int FEE_ADULT_PARK_AFTER4 = 45000, FEE_TEEN_PARK_AFTER4 = 40000, FEE_CHILD_PARK_AFTER4 = 35000; 
	
 //���̿� ���� ����
	const int MIN_BABY = 1; 
	const int MIN_CHILD = 3, MAX_CHILD = 12;
	const int MIN_TEEN = 13, MAX_TEEN = 18;
	const int MIN_ADULT = 19, MAX_ADULT = 64;	

 //������
	const float DISCOUNT_RATE_DISABLED = 0.5;
	const float DISCOUNT_RATE_MERIT = 0.5; 
	const float DISCOUNT_RATE_SOLDIER = 0.51;
	const float DISCOUNT_RATE_PREGNANT = 0.5;
	const float DISCOUNT_RATE_FAMILY = 0.7;
 
 //��Ÿ	
	int ticketChoice, ticketTime, personalNumber, ticketAmount, specialOffer, againProcess;			 
	int id, gender, century, birthYearFull, birthYear, birthMonth, birthDate, gap, age;					// �� ���� ��� 
	int basicFee, totalFee, finalFee;
	int ticketChoiceArr[100]={0}, ticketTimeArr[100]={0}, ageArr[100]={0}, ticketAmountArr[100]={0}, totalFeeArr[100]={0}, specialOfferArr[100]={0};	// �ֹ� ���� ���� 
	int position;	// �迭���� Ȱ�� 
	int continueBuying;
	 
int main()
{	
 // ���� ��¥ ���ϱ�  
	time_t timer;
	struct tm * t;
	timer = time(NULL);			//1900�� 1�� 1�� 0�� 0�� 0�ʺ��� �����Ͽ� ��������� �� 
	t = localtime(&timer); 		// �������� ���� ����ü�� ����  

	
	while(true)
	{ 
	 do		//Ƽ�� ���� ���� 
	 {
	
	 
		do
		{
			printf("������ �����ϼ���.\n");
			printf("1.  �����̿��(�Ե����� + �μӹڹ���)\n");
			printf("2.  ��ũ�̿��(�Ե�����)\n");
			scanf("%d", &ticketChoice);
		} while(!(ticketChoice == 1 || ticketChoice== 2)); 
		
		do
		{
			printf("\n�̿�ð��� �����ϼ���.\n");
			printf("1.  1Day\n");
			printf("2.  After4(���� 4�ú��� ����)\n");
			scanf("%d", &ticketTime); 
		} while(!(ticketTime == 1 || ticketTime == 2));
		
		printf("\n�ֹε�� ��ȣ�� �Է��ϼ���. ��) 940907-2 \n");
		scanf("%d-%d", &id, &gender);
		
		printf("\n�� ���� �ֹ��Ͻðڽ��ϱ�?\n");
		scanf("%d", &ticketAmount); 
		 
		do
		{
			printf("\n�������� �����ϼ���.\n");
			printf("1.  ����(���� ���� �ڵ� ó��)\n");
			printf("2.  �����(����1�α���, �����̿��/��ũ�̿�� 50%% ���)\n");
			printf("3.  ����������(����1�α���, �����̿��/��ũ�̿�� 50%% ���)\n");
			printf("4.  �ް��庴(����1�α���, �����̿�� 49%% ���)\n");
			printf("5.  �ӻ��(�ӻ�� ����, �����̿�� 50%% ���)\n");
			printf("6.  �ٵ��� �ູī��(�ٵ��� �ູī�� ȸ�� ����(ī�忡 ���� ������ ����), �����̿�� 30%% ���)\n");
			scanf("%d", &specialOffer);
		} while(!(specialOffer == 1 || specialOffer == 2 || specialOffer == 3 || specialOffer == 4 || specialOffer == 5 || specialOffer == 6));
		
	
	//�� ���� ���
		birthYear = id / 10000;					//�ڷ����� int�� 981216 > 98.1216 > 98
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
	
	//����⵵ - ����⵵ 
		gap = (t -> tm_year +1900) - birthYearFull;		// ���� �⵵���� ����⵵�� ����  // tm_year : 1900�� ���� ������ �� �������� ��Ÿ�� 
	
		if(birthMonth >= (t -> tm_mon+1) && birthDate >= (t -> tm_mday))	// tm_mon : 0 ~ 11 > +1�� �ؾ� �� // tm_mday : 1 ~ 31 > �״�� ���  
		{
			age = gap;								// ������ �������� ���� �⵵���� ����⵵�� ����ŭ�� �� ����
		}
		else
		{
			age = gap - 1;							// ������ ������ �ʾ����� ���� �⵵���� ����⵵�� �� �Ϳ� -1�� �ؾ� �� ���� 
		}
	
	// ���ɴ뺰 �з��� ���� �⺻ Ƽ�ϰ� 
		// 0 ~ 12���� �̸� 
		if(age < MIN_BABY)
		{
			basicFee = 0;
		}
		
		// 12���� �̻� ~ 36���� �̸�
		if(age >= MIN_BABY && age < MIN_CHILD && ticketAmount > 10)		// ��ü ������ ��쿡�� ����� ����(��ü ������ ���Ƿ� 10�� �ʰ��� ����) 
		{
			basicFee = FEE_BABY;
		}
		else if(age >= MIN_BABY && age < MIN_CHILD && ticketAmount <= 10)	// ��ü ������ �ƴ� ��� ���� ���� 
		{
			basicFee = 0;
		}	
			
		// 36���� �̻� ~ �� 12��, �� 65�� �̻� 
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
		// �� 13�� �̻� ~ �� 18��	
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
		
		// �� 19�� �̻� ~ �� 64��	
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
			
	//Ƽ�� �������� ���				
		// ������� 1. ���� ���	
		if(specialOffer == 1)
		{
			totalFee = basicFee * ticketAmount;
		}
		
	// ������� 2. 	����� - �����̿��, ��ũ�̿�� 50% + ���� 1�α��� 
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
		
	// ������� 3. ���������� - �����̿��, ��ũ�̿�� 50% + ���� 1�α���	
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
		
	// ������� 4. �ް��庴 - �����̿�� 49% + ���� 1�α���	
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
		
	// ������� 5. �ӻ�� - �����̿�� 50% + ���θ�	
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
		
	// ������� 6. �ٵ��� �ູī�� - �����̿��  30% + ī�忡 ���� ������ ����	
		if(specialOffer == 6 && ticketChoice == 1)
		{
			totalFee = basicFee * DISCOUNT_RATE_FAMILY * ticketAmount;
		}

	// Ƽ�� ���� ���� ��� (������ ��� '���� �����Դϴ�')	
		if(totalFee == 0)
		{
			printf("\n���� �����Դϴ�.\n");
		}
		else
		{
			printf("\n������ %d �� �Դϴ�.\n�����մϴ�.\n", totalFee);
		}
		
	// Ƽ�� ���� ���� ���� (�迭) 
		ticketChoiceArr[position] = ticketChoice;
		ticketTimeArr[position] = ticketTime;
		ageArr[position] = age;
		ticketAmountArr[position] = ticketAmount;
		totalFeeArr[position] = totalFee;
		specialOfferArr[position] = specialOffer;
		position++;
		
	// Ƽ�� ���� ������ ���� �ݾ� 
	finalFee += totalFee;
		
	// Ƽ�� ���� ��� ���� ���� Ȯ��	
		
		printf("\nƼ���� ��� ���� �Ͻðڽ��ϱ�?\n1.  Ƽ�� ����\n2.  ����\n");
		scanf("%d", &againProcess);
	 
	 } while (againProcess == 1);		// 1. Ƽ�� ���� ���ý� Ƽ�� ���� ���� �ٽ� ���� 
		
		
		
		printf("\nƼ�� ���Ÿ� �����մϴ�.  �����մϴ�.\n");
		
	
	//���� ���� �����	
		FILE * filePointer = fopen("report.csv","a");
	
	
	// Ƽ�� ���� ������ ��� 
		printf("\n====================== �Ե����� ======================\n");
		printf("   ����     �ð�    ����     ����     �ݾ�       �������\n\n");
		for(int index = 0; index < position; index++)
		{//���� ���� ��� 
			fprintf(filePointer, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",t-> tm_year + 1900, t-> tm_mon + 1, t -> tm_mday,
																ticketChoiceArr[index], ticketTimeArr[index], ageArr[index], 
																ticketAmountArr[index], totalFeeArr[index], specialOfferArr[index]);	
		// ����� ����	
			switch(ticketChoiceArr[index])
			{
				case 1:
					printf("�����̿��  ");
					break; 
				case 2:
					printf("��ũ�̿��  ");
					break;
			}
		// ����� �ð�	
			switch(ticketTimeArr[index])
			{
				case 1: 
					printf("1Day    ");
					break;
				case 2:
					printf("After4  ");
					break; 
			}
		// ���� ����	
			if(ageArr[index] < 3)
			{
				printf("���̺�  ");
			}
			else if(ageArr[index] < 12)
			{
				printf("���  ");
			}
			else if(ageArr[index] < 18)
			{
				printf("û�ҳ�  ");
			}
			else if(ageArr[index] < 65) 
			{
				printf("�    ");
			}
			else
			{
				printf("����    ");
			}				
		// Ƽ�� ����
			printf("%3d   ", ticketAmountArr[index]);	
		// �� �ݾ�
			printf("%8d��   ", totalFeeArr[index]);
		// ������� 
			switch(specialOfferArr[index])
			{
				case 1:
					printf("������� ����\n");
					break;
				case 2:
					printf("����� ���\n");
					break;
				case 3:
					printf("���������� ���\n");
					break;
				case 4:
					printf("�ް��庴 ���\n");
					break;
				case 5:
					printf("�ӻ�� ���\n");
					break;
				case 6:
					printf("�ٵ��� �ູī�� ���\n");
					break;
			}
	
		}
		printf("\n\n����� �Ѿ��� %d�� �Դϴ�.\n", finalFee);
		printf("=======================================================");
		
	
		 
		// ���ο� Ƽ�� ���� or ���α׷� ���� 
		printf("\n\n��� �߱��Ͻðڽ��ϱ�?\n");
		printf("1. ���ο� �ֹ�\n2. ���α׷�  ����\n");	
		scanf("%d", &continueBuying);
		
		//���ο� ���� ����� ���� ���� �ʱ�ȭ 
		position = 0;	
		finalFee = 0;
	
		
		if(continueBuying == 1)
		{	
			continue;
		}
			
			
		break;	
		
    	printf("\n");	//������ ���� �� �� ���� 
	}

	return 0;	
}
	
 
  
