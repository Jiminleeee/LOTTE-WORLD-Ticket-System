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
	const float DISCOUNT_RATE_DISABLED = 0.5, DISCOUNT_RATE_DISABLED_WITH = 0.5;
	const float DISCOUNT_RATE_MERIT = 0.5, DISCOUNT_RATE_MERIT_WITH = 0.5; 
	const float DISCOUNT_RATE_SOLDIER = 0.51, DISCOUNT_RATE_SOLDIER_WITH = 0.51;
	const float DISCOUNT_RATE_PREGNANT = 0.5;
	const float DISCOUNT_RATE_FAMILY = 0.7;
	
	int ticketChoice, ticketTime, personalNumber, ticketAmount, specialOffer, totalFee, againProcess;
	int todayDate, age, basicFee;
	 
int main()
{	
 // ���� ��¥ ���ϱ� 
	time_t timer;
	struct tm * t;
	timer = time(NULL);		//1970�� 1�� 1�� 0�� 0�� 0�ʺ��� �����Ͽ� ��������� �� 
	t = localtime(&timer); 	// �������� ���� ����ü�� ����  
	
	while(true)
	{
		printf("������ �����ϼ���.\n1.  �����̿��\n2.  ��ũ�̿��\n");
		scanf("%d", &ticketChoice);
	
		printf("\n�̿�ð��� �����ϼ���.\n1.  1Day\n2.  After4\n");
		scanf("%d", &ticketTime); 
		
		printf("\n��������� �Է��ϼ���. ��) 20220316 \n");
		scanf("%d", &personalNumber);
		
		
		
	// ���� ��¥��  ������� �������� �ٲٱ� 
		todayDate = (t -> tm_year + 1900) * 10000 + (t -> tm_mon + 1) * 100 + t -> tm_mday; 	// *10000, *100 > 0�� �ڿ� �ٿ� 3��9���� �ƴ� 0309�� ���·� ������ �Ѵ�. 
	
	
	//�� ���� ���
		age = (todayDate - personalNumber)/10000; 
	
	
	// ���ɴ뺰 �з��� ���� �⺻ Ƽ�ϰ� 
		// 0 ~ 36���� �̸� 
			if(age < MIN_CHILD)
			{
				basicFee = 0;
			}
			
		// 36���� �̻� ~ �� 12��, �� 65�� �̻� 
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
			
		// �� 13�� �̻� ~ �� 18��	
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
		
		// �� 19�� �̻� ~ �� 64��	
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
		
		printf("\n�� ���� �ֹ��Ͻðڽ��ϱ�?  (�ִ� �ֹ��� 10��)\n");
		scanf("%d", &ticketAmount); 
		 
		printf("\n�������� �����ϼ���.\n1.  ����(���� ���� �ڵ� ó��)\n2.  �����\n3.  ����������\n4.  �ް��庴\n5.  �ӻ��\n6.  �ٵ��� �ູī��\n");
		scanf("%d", &specialOffer);
		
	// ����1�� ���� ������ ��밡��
		
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

	// ������ ���� ��� ��� 
		
		totalFee = basicFee * ticketAmount;	
		
		printf("\n������ %d �� �Դϴ�.\n�����մϴ�.\n", totalFee);
		
		printf("\n��� �߱��Ͻðڽ��ϱ�?\n1.  Ƽ�� �߱�\n2.  ����\n");
		scanf("%d", &againProcess);
		if(againProcess == 2)
		{
			printf("\nƼ�� �߱��� �����մϴ�.  �����մϴ�.\n");
			break; 
		}
		
		
	}	
	
	return 0;	
}
	
 
  
