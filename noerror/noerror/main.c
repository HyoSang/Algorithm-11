#include "redblack.h"
#include <time.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct moive//7�� ������, 3�� 3���� �󿵽ð� �ǹ��մϴ�.
{
	char name[20];
	int startHour[7][3];
	RBNode ** mv[7][3];
}MV;

void generateSeat(RBNode** (movie)[3]) //�¼� �������� �Լ��Դϴ�.
{
	int i, j, k;
	int randArray[300];
	for (i = 0; i < 3; i++)
	{
		movie[i] = (RBNode**)malloc(sizeof(RBNode*));
		(*movie[i]) = NULL;
		for (j = 0; j < 300; j++)
		{
			randArray[j] = 0;
		}
		j = 1;
		
		while (j <= 210)
		{
			k = rand() % 300;
			if (randArray[k] == 0)
			{
				randArray[k] = 1;
				j++;
			}
		}
		
		for (j = 1; j <= 300; j++)
		{
			if(randArray[j]==1)Insert(movie[i], Create(j));
		}
	}
}

void print(RBNode ** (movie)[3], int mNum)//�¼� ����ϴ� �Լ��Դϴ�. mNum���� �ð��븦 �Է��Ͻø� �˴ϴ�.
{
	int i, j;
	printf("  ");
	for (j = 0; j < 30; j++)
	{
		printf("%2d", j + 1);
		if (j == 6 || j == 22)printf("  ");
	}
	printf("\n");
	for (i = 0; i < 10; i++)
	{
		printf("%c ", 'A' + i);
		for (j = i * 30 + 1; j <= (i + 1) * 30; j++)
		{
			if (Search(*movie[mNum], j)!= NULL)printf("��");
			else printf("��");
			if (j == i * 30 + 7 || j == i * 30 + 23)printf("  ");
		}
		printf("\n");
	}
}

void printReservation(RBNode ** (movie)[3], int mNum, int seatnum)	// ���� �� ���� �¼��� ��, ���� ��� �Ŀ��� �ٸ� ����ϴ� �Լ�
{
	int i, j;
	printf("  ");
	for (j = 0; j < 30; j++)
	{
		printf("%2d", j + 1);
		if (j == 6 || j == 22)printf("  ");
	}
	printf("\n");
	for (i = 0; i < 10; i++)
	{
		printf("%c ", 'A' + i);
		for (j = i * 30 + 1; j <= (i + 1) * 30; j++)
		{
			if (j == seatnum) {
				if (Search(*movie[mNum], j) == NULL) printf("��");
				else printf("��");
			}
			else if (Search(*movie[mNum], j) != NULL)	printf("��");
			else printf("��");

			if (j == i * 30 + 7 || j == i * 30 + 23)printf("  ");
		}
		printf("\n");
	}
}

void getCTime(int * year, int * month, int * day) //���� �ð� ���ϴ� �Լ��Դϴ�.
{
	int i;
	time_t t;
	time(&t);
	char cmon[4] = "", buf[50], cday[3] = "", cyear[5] = "";
	ctime_s(buf, sizeof(buf), &t);
	for (i = 0; i < 3; i++)
	{
		cmon[i] = buf[i + 4];
	}
	for (i = 0; i < 2; i++)
	{
		cday[i] = buf[i + 8];
	}
	for (i = 0; i < 4; i++)
	{
		cyear[i] = buf[i + 20];
	}
	if (strcmp(cmon, "Jan") == 0)
	{
		*month = 1;
	}
	else if (strcmp(cmon, "Feb") == 0)
	{
		*month = 2;
	}
	else if (strcmp(cmon, "Mar") == 0)
	{
		*month = 3;
	}
	else if (strcmp(cmon, "Apr") == 0)
	{
		*month = 4;
	}
	else if (strcmp(cmon, "May") == 0)
	{
		*month = 5;
	}
	else if (strcmp(cmon, "Jun") == 0)
	{
		*month = 6;
	}
	else if (strcmp(cmon, "Jul") == 0)
	{
		*month = 7;
	}
	else if (strcmp(cmon, "Aug") == 0)
	{
		*month = 8;
	}
	else if (strcmp(cmon, "Sep") == 0)
	{
		*month = 9;
	}
	else if (strcmp(cmon, "Oct") == 0)
	{
		*month = 10;
	}
	else if (strcmp(cmon, "Nov") == 0)
	{
		*month = 11;
	}
	else if (strcmp(cmon, "Dec") == 0)
	{
		*month = 12;
	}

	*year = (cyear[0] - '0') * 1000 + (cyear[1] - '0') * 100 + (cyear[2] - '0') * 10 + (cyear[3] - '0');
	if (cday[0] == 32)*day = cday[1] - '0';
	else *day = (cday[0] - '0') * 10 + cday[1] - '0';
}
int main(void)
{
	
	int i, j, k, d, q, t, year, month, day, seatnum, column; char row;
	int randArray[5];
	MV * movie[5];
	for (i = 0; i < 5; i++)
	{
		movie[i] = (MV*)malloc(sizeof(MV));
	}
	strcpy(movie[0]->name, "�ư���");
	strcpy(movie[1]->name, "������:����Į����");
	strcpy(movie[2]->name, "�");
	strcpy(movie[3]->name, "�� ���� ��");
	strcpy(movie[4]->name, "�ޱ׸����� �� ����");//���̹� Ʋ� ���ִ� ��ȭ �Է��ߴµ� �ƹ��ų� �Է��Ͻø� �˴ϴ�.
	srand(time(NULL));
	for (i = 0; i < 7; i++)
	{
		
		for (j = 0; j < 5; j++)
		{
			generateSeat(movie[j]->mv[i]);
			randArray[j] = 0;
		}
		j = 0;
		while(j<5)
		{
			
			k = rand() % 5;
			if ( k== 0 && randArray[0] == 0)
			{
				movie[j]->startHour[i][0] = 8;
				movie[j]->startHour[i][1] = 12;
				movie[j]->startHour[i][2] = 16;
				randArray[0] = 1;
				j++;
			}
			else if (k == 1 && randArray[1] == 0)
			{
				movie[j]->startHour[i][0] = 11;
				movie[j]->startHour[i][1] = 14;
				movie[j]->startHour[i][2] = 17;
				randArray[1] = 1;
				j++;
			}
			else if (k == 2 && randArray[2] == 0)
			{
				movie[j]->startHour[i][0] = 7;
				movie[j]->startHour[i][1] = 13;
				movie[j]->startHour[i][2] = 18;
				randArray[2] = 1;
				j++;
			}
			else if (k == 3 && randArray[3] == 0)
			{
				movie[j]->startHour[i][0] = 15;
				movie[j]->startHour[i][1] = 19;
				movie[j]->startHour[i][2] = 22;
				randArray[3] = 1;
				j++;
			}
			else if (k == 4 && randArray[4] == 0)
			{
				movie[j]->startHour[i][0] = 9;
				movie[j]->startHour[i][1] = 20;
				movie[j]->startHour[i][2] = 24;
				randArray[4] = 1;
				j++;
			}
		}
		
	}
	getCTime(&year, &month, &day);
	while (1)
	{
		fflush(stdin);
		system("cls");
		printf("        ��ȭ ���� �ý���\n");
		printf("������ ��¥�� %d�� %d�� %d���Դϴ�.\n", year, month, day);
		printf("     ���ϴ� ����� �Է��ϼ���.\n(1. ��ȭȮ�� 2.��ȭ ���� �� ��Ȳ 3.����)\n");
		printf("->");
		scanf_s("%d", &i);
		if (i == 1)
		{
			while (1)
			{
				fflush(stdin);
				system("cls");
				printf("        ��ȭ ���� �ý���\n");
				printf("������ ��¥�� %d�� %d�� %d���Դϴ�.\n", year, month, day);
				printf("��¥�� �Է��ϼ��� \n���ú��� �������� ������ Ȯ�� �����մϴ�. \nex)6�� 6��");
				printf("->");
				scanf_s("%d�� %d��", &i, &j);
				printf("�Է��Ͻ� ��¥�� %d�� %d���� �½��ϱ�?(yes:1/no:0)\n", i, j);
				printf("->");
				scanf_s("%d", &k);
				if (k == 1)
				{
					if (i == month)
					{
						if (j - day >= 0 && j - day < 7)
						{
							k = j - day;
							break;
						}
					}
					else if (i - 1 == month)
					{
						if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
						{
							if (31 - day + j < 7)
							{
								k = 31 - day;
								break;
							}

						}
						else if (i == 2)
						{
							if (year % 4 == 0)
							{
								if (29 - day + j < 7)
								{
									k = 31 - day;
									break;
								}
							}
							else
							{
								if (28 - day + j < 7)
								{
									k = 31 - day;
									break;
								}
							}
						}
						else
						{
							if (30 - day + j < 7)
							{
								k = 31 - day;
								break;
							}
						}
						continue;
					}
					continue;
				}
				else if (k == 0)
				{
					continue;
				}
				else
				{
					continue;
				}
			}
			while (1)
			{
				fflush(stdin);
				system("cls");
				printf("        ��ȭ ���� �ý���\n");
				printf("������ ��¥�� %d�� %d�� %d���Դϴ�.\n", year, month, day);
				printf("%d�� %d�� ���ϴ� ��ȭ ��ϰ� �ð�ǥ�Դϴ�.\n", i, j);
				printf("������������������������������������������������������������������������������������\n");
				printf("����ȣ��         ����       ��     �ð� 1     ��     �ð� 2     ��     �ð� 3     ��\n");
				printf("������������������������������������������������������������������������������������\n");

				for (d = 0; d < 5; d++)
				{
					printf("��%3d ��%20s��      %2d:00     ��      %2d:00     ��      %2d:00     ��\n", d + 1, movie[d]->name, movie[d]->startHour[k][0], movie[d]->startHour[k][1], movie[d]->startHour[k][2]);
					if (d == 4) printf("������������������������������������������������������������������������������������\n");
					else printf("������������������������������������������������������������������������������������\n");
				}
				printf("���Ͻô� ����� �����ϼ���(1. ���� �¼� Ȯ��, 2.ó������ ���ư���)\n");
				printf("->");
				scanf_s("%d", &q);
				if (q == 1)
				{
						printf("���ϴ� ��ȭ�� ��ȣ�� �󿵽ð��� �Է��ϼ���\n(ex : 1�� ��ȭ�� �󿵽ð� 2 = 1,2)\n");
						printf("->");
						scanf_s("%d,%d", &q, &d);
						if (q < 1 || q>5)continue;
						if (d < 1 || d>3)continue;
						printf("%s�� %d:00 �ð����� �¼��� �½��ϱ�?(yes:1/no:0)\n", movie[q - 1]->name, movie[q - 1]->startHour[k][d - 1]);
						printf("->");
						scanf_s("%d", &t);
						if (t == 1)
						{
							system("cls");
							printf("        ��ȭ ���� �ý���\n");
							printf("������ ��¥�� %d�� %d�� %d���Դϴ�.\n", year, month, day);
							print(movie[q - 1]->mv[k], d - 1);
							system("pause");
							break;
						}
						else continue;

					
				}
				else if (q == 2)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			
		}
		else if(i == 2)
		{
			while (1)						// �� �¼� Ȯ���ϴ� �� �̿��ؼ� �߽��ϴ�.
			{
				fflush(stdin);
				system("cls");
				printf("        ��ȭ ���� �ý���\n");
				printf("������ ��¥�� %d�� %d�� %d���Դϴ�.\n", year, month, day);
				printf("��¥�� �Է��ϼ��� \n���ú��� �������� ��ȭ�� ���� �����մϴ�. \nex)6�� 6��\n");
				printf("->");
				scanf_s("%d�� %d��", &i, &j);
				printf("�Է��Ͻ� ��¥�� %d�� %d���� �½��ϱ�?(yes:1/no:0)\n", i, j);
				printf("->");
				scanf_s("%d", &k);
				if (k == 1)
				{
					if (i == month)
					{
						if (j - day >= 0 && j - day < 7)
						{
							k = j - day;
							break;
						}
					}
					else if (i - 1 == month)
					{
						if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
						{
							if (31 - day + j < 7)
							{
								k = 31 - day;
								break;
							}

						}
						else if (i == 2)
						{
							if (year % 4 == 0)
							{
								if (29 - day + j < 7)
								{
									k = 31 - day;
									break;
								}
							}
							else
							{
								if (28 - day + j < 7)
								{
									k = 31 - day;
									break;
								}
							}
						}
						else
						{
							if (30 - day + j < 7)
							{
								k = 31 - day;
								break;
							}
						}
						continue;
					}
					continue;
				}
				else if (k == 0)
				{
					continue;
				}
				else
				{
					continue;
				}
			}
			while (1)
			{
				fflush(stdin);
				system("cls");
				printf("        ��ȭ ���� �ý���\n");
				printf("������ ��¥�� %d�� %d�� %d���Դϴ�.\n", year, month, day);
				printf("%d�� %d�� ���ϴ� ��ȭ ��ϰ� �ð�ǥ�Դϴ�.\n", i, j);
				printf("������������������������������������������������������������������������������������\n");
				printf("����ȣ��         ����       ��     �ð� 1     ��     �ð� 2     ��     �ð� 3     ��\n");
				printf("������������������������������������������������������������������������������������\n");

				for (d = 0; d < 5; d++)
				{
					printf("��%3d ��%20s��      %2d:00     ��      %2d:00     ��      %2d:00     ��\n", d + 1, movie[d]->name, movie[d]->startHour[k][0], movie[d]->startHour[k][1], movie[d]->startHour[k][2]);
					if (d == 4) printf("������������������������������������������������������������������������������������\n");
					else printf("������������������������������������������������������������������������������������\n");
				}
				printf("���Ͻô� ����� �����ϼ���(1. ��ȭ ���� �ϱ�, 2. ��ȭ ���� ����ϱ� 3.ó������ ���ư���)\n");
				printf("->");
				scanf_s("%d", &q);
				if (q == 1)
				{
					printf("���ϴ� ��ȭ�� ��ȣ�� �󿵽ð��� �Է��ϼ���\n(ex : 1�� ��ȭ�� �󿵽ð� 2 = 1,2)\n");
					printf("->");
					scanf_s("%d,%d", &q, &d);
					if (q < 1 || q>5)continue;
					if (d < 1 || d>3)continue;
					printf("%s�� %d:00 �ð��밡 �½��ϱ�?(yes:1/no:0)\n", movie[q - 1]->name, movie[q - 1]->startHour[k][d - 1]);
					printf("->");
					scanf_s("%d", &t);
					if (t == 1)
					{
						while (1) {
							fflush(stdin);
							system("cls");
							printf("        ��ȭ ���� �ý���\n");
							printf("������ ��¥�� %d�� %d�� %d���Դϴ�.\n", year, month, day);
							printf("\n\t\t%s�� %d:00 �ð����� ���� ��Ȳ\n\n", movie[q - 1]->name, movie[q - 1]->startHour[k][d - 1]);
							print(movie[q - 1]->mv[k], d - 1);
							printf("�����Ͻðڽ��ϱ�?(yes:1/no:0)\n->");
							scanf("%d", &t);
							if (t == 1) {
								printf("���ϴ� �¼��� ��ġ�� �Է��ϼ���\n(ex : C���� 15��° �¼� = C,15)\n->");
								getchar();
								scanf("%c,%d", &row, &column);
								if (row < 'A' || row > 'J')continue;
								if (column < 1 || column > 30)continue;
								printf("�¼� ��ġ�� %c%d�� �½��ϱ�?(yes:1/no:0)", row, column);
								scanf("%d", &t);
								if (t == 1) {
									seatnum = ((row - 65) * 30) + column;								// �Է¹��� �¼� ��ġ�� node�� data������ �ٲ���
									if (Search(*(movie[q - 1]->mv[k][d - 1]), seatnum) == NULL) {
										Insert(movie[q - 1]->mv[k][d - 1], Create(seatnum));
										printReservation(movie[q - 1]->mv[k], d - 1, seatnum);
										printf("����Ǿ����ϴ�.\n");
										Print_Property(*(movie[q - 1]->mv[k][d - 1]));
										system("pause");
									}
									else {
										printf("�̹� ����� �ڸ� �Դϴ�.\n"); system("pause"); continue;
									}

								}
								break;
							}
							break;
						}
						break;
					}
					else continue;
				}
				else if (q == 2) {
					printf("���� ��Ҹ� ���ϴ� ��ȭ�� ��ȣ�� �󿵽ð��� �Է��ϼ���\n(ex : 1�� ��ȭ�� �󿵽ð� 2 = 1,2)\n");	// ���ſ� ���� �Ȱ����ϴ�.
					printf("->");
					scanf_s("%d,%d", &q, &d);
					if (q < 1 || q>5)continue;
					if (d < 1 || d>3)continue;
					printf("%s�� %d:00 �ð��밡 �½��ϱ�?(yes:1/no:0)\n", movie[q - 1]->name, movie[q - 1]->startHour[k][d - 1]);
					printf("->");
					scanf_s("%d", &t);
					if (t == 1)
					{
						while (1) {
							fflush(stdin);
							system("cls");
							printf("        ��ȭ ���� �ý���\n");
							printf("������ ��¥�� %d�� %d�� %d���Դϴ�.\n", year, month, day);
							printf("\n\t\t%s�� %d:00 �ð����� ���� ��Ȳ\n\n", movie[q - 1]->name, movie[q - 1]->startHour[k][d - 1]);
							print(movie[q - 1]->mv[k], d - 1);
							printf("���� ����Ͻðڽ��ϱ�?(yes:1/no:0)\n->");
							scanf("%d", &t);
							if (t == 1) {
								printf("��Ҹ� ���ϴ� �¼��� ��ġ�� �Է��ϼ���\n(ex : C���� 15��° �¼� = C,15)\n->");
								getchar();
								scanf("%c,%d", &row, &column);
								if (row < 'A' || row > 'J')continue;
								if (column < 1 || column > 30)continue;
								printf("�¼� ��ġ�� %c%d�� �½��ϱ�?(yes:1/no:0)", row, column);
								scanf("%d", &t);
								if (t == 1) {
									seatnum = ((row - 65) * 30) + column;
									if (Search(*(movie[q - 1]->mv[k][d - 1]), seatnum) != NULL) {
										Delete(movie[q - 1]->mv[k][d - 1], seatnum);
										printReservation(movie[q - 1]->mv[k], d - 1, seatnum);
										printf("��ҵǾ����ϴ�.\n");
										Print_Property(*(movie[q - 1]->mv[k][d - 1]));
										system("pause");
									}
									else {
										printf("����� �ڸ��� �ƴմϴ�.\n"); system("pause"); continue;
									}
								}
								break;
							}
							break;
						}
						break;
					}
					else continue;
				}
				else if (q == 3)
				{
					break;
				}
				else
				{
					continue;
				}
			}
		}
		else if (i == 3)
		{
			break;
		}
		else
		{
			continue;
		}


	}
	
	
	
	

}

