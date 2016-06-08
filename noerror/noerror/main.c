#include "redblack.h"
#include <time.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct moive//7은 일주일, 3은 3번의 상영시간 의미합니다.
{
	char name[20];
	int startHour[7][3];
	RBNode ** mv[7][3];
}MV;

void generateSeat(RBNode** (movie)[3]) //좌석 랜덤생성 함수입니다.
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

void print(RBNode ** (movie)[3], int mNum)//좌석 출력하는 함수입니다. mNum에는 시간대를 입력하시면 됩니다.
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
			if (Search(*movie[mNum], j)!= NULL)printf("■");
			else printf("□");
			if (j == i * 30 + 7 || j == i * 30 + 23)printf("  ");
		}
		printf("\n");
	}
}

void printReservation(RBNode ** (movie)[3], int mNum, int seatnum)	// 예약 후 에는 좌석에 ★, 예약 취소 후에는 ☆를 출력하는 함수
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
				if (Search(*movie[mNum], j) == NULL) printf("☆");
				else printf("★");
			}
			else if (Search(*movie[mNum], j) != NULL)	printf("■");
			else printf("□");

			if (j == i * 30 + 7 || j == i * 30 + 23)printf("  ");
		}
		printf("\n");
	}
}

void getCTime(int * year, int * month, int * day) //오늘 시간 구하는 함수입니다.
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
	strcpy(movie[0]->name, "아가씨");
	strcpy(movie[1]->name, "엑스맨:아포칼립스");
	strcpy(movie[2]->name, "곡성");
	strcpy(movie[3]->name, "미 비포 유");
	strcpy(movie[4]->name, "앵그리버드 더 무비");//네이버 틀어서 떠있는 영화 입력했는데 아무거나 입력하시면 됩니다.
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
		printf("        영화 예매 시스템\n");
		printf("오늘의 날짜는 %d년 %d월 %d일입니다.\n", year, month, day);
		printf("     원하는 기능을 입력하세요.\n(1. 영화확인 2.영화 예매 및 현황 3.종료)\n");
		printf("->");
		scanf_s("%d", &i);
		if (i == 1)
		{
			while (1)
			{
				fflush(stdin);
				system("cls");
				printf("        영화 예매 시스템\n");
				printf("오늘의 날짜는 %d년 %d월 %d일입니다.\n", year, month, day);
				printf("날짜를 입력하세요 \n오늘부터 일주일의 일정을 확인 가능합니다. \nex)6월 6일");
				printf("->");
				scanf_s("%d월 %d일", &i, &j);
				printf("입력하신 날짜가 %d월 %d일이 맞습니까?(yes:1/no:0)\n", i, j);
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
				printf("        영화 예매 시스템\n");
				printf("오늘의 날짜는 %d년 %d월 %d일입니다.\n", year, month, day);
				printf("%d월 %d일 상영하는 영화 목록과 시간표입니다.\n", i, j);
				printf("┏━━┳━━━━━━━━━━┳━━━━━━━━┳━━━━━━━━┳━━━━━━━━┓\n");
				printf("┃번호┃         제목       ┃     시간 1     ┃     시간 2     ┃     시간 3     ┃\n");
				printf("┣━━╋━━━━━━━━━━╋━━━━━━━━╋━━━━━━━━╋━━━━━━━━┫\n");

				for (d = 0; d < 5; d++)
				{
					printf("┃%3d ┃%20s┃      %2d:00     ┃      %2d:00     ┃      %2d:00     ┃\n", d + 1, movie[d]->name, movie[d]->startHour[k][0], movie[d]->startHour[k][1], movie[d]->startHour[k][2]);
					if (d == 4) printf("┗━━┻━━━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┛\n");
					else printf("┣━━╋━━━━━━━━━━╋━━━━━━━━╋━━━━━━━━╋━━━━━━━━┫\n");
				}
				printf("원하시는 기능을 선택하세요(1. 현재 좌석 확인, 2.처음으로 돌아가기)\n");
				printf("->");
				scanf_s("%d", &q);
				if (q == 1)
				{
						printf("원하는 영화의 번호와 상영시간을 입력하세요\n(ex : 1번 영화의 상영시간 2 = 1,2)\n");
						printf("->");
						scanf_s("%d,%d", &q, &d);
						if (q < 1 || q>5)continue;
						if (d < 1 || d>3)continue;
						printf("%s의 %d:00 시간대의 좌석이 맞습니까?(yes:1/no:0)\n", movie[q - 1]->name, movie[q - 1]->startHour[k][d - 1]);
						printf("->");
						scanf_s("%d", &t);
						if (t == 1)
						{
							system("cls");
							printf("        영화 예매 시스템\n");
							printf("오늘의 날짜는 %d년 %d월 %d일입니다.\n", year, month, day);
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
			while (1)						// 위 좌석 확인하는 거 이용해서 했습니다.
			{
				fflush(stdin);
				system("cls");
				printf("        영화 예매 시스템\n");
				printf("오늘의 날짜는 %d년 %d월 %d일입니다.\n", year, month, day);
				printf("날짜를 입력하세요 \n오늘부터 일주일의 영화를 예매 가능합니다. \nex)6월 6일\n");
				printf("->");
				scanf_s("%d월 %d일", &i, &j);
				printf("입력하신 날짜가 %d월 %d일이 맞습니까?(yes:1/no:0)\n", i, j);
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
				printf("        영화 예매 시스템\n");
				printf("오늘의 날짜는 %d년 %d월 %d일입니다.\n", year, month, day);
				printf("%d월 %d일 상영하는 영화 목록과 시간표입니다.\n", i, j);
				printf("┏━━┳━━━━━━━━━━┳━━━━━━━━┳━━━━━━━━┳━━━━━━━━┓\n");
				printf("┃번호┃         제목       ┃     시간 1     ┃     시간 2     ┃     시간 3     ┃\n");
				printf("┣━━╋━━━━━━━━━━╋━━━━━━━━╋━━━━━━━━╋━━━━━━━━┫\n");

				for (d = 0; d < 5; d++)
				{
					printf("┃%3d ┃%20s┃      %2d:00     ┃      %2d:00     ┃      %2d:00     ┃\n", d + 1, movie[d]->name, movie[d]->startHour[k][0], movie[d]->startHour[k][1], movie[d]->startHour[k][2]);
					if (d == 4) printf("┗━━┻━━━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┛\n");
					else printf("┣━━╋━━━━━━━━━━╋━━━━━━━━╋━━━━━━━━╋━━━━━━━━┫\n");
				}
				printf("원하시는 기능을 선택하세요(1. 영화 예매 하기, 2. 영화 예매 취소하기 3.처음으로 돌아가기)\n");
				printf("->");
				scanf_s("%d", &q);
				if (q == 1)
				{
					printf("원하는 영화의 번호와 상영시간을 입력하세요\n(ex : 1번 영화의 상영시간 2 = 1,2)\n");
					printf("->");
					scanf_s("%d,%d", &q, &d);
					if (q < 1 || q>5)continue;
					if (d < 1 || d>3)continue;
					printf("%s의 %d:00 시간대가 맞습니까?(yes:1/no:0)\n", movie[q - 1]->name, movie[q - 1]->startHour[k][d - 1]);
					printf("->");
					scanf_s("%d", &t);
					if (t == 1)
					{
						while (1) {
							fflush(stdin);
							system("cls");
							printf("        영화 예매 시스템\n");
							printf("오늘의 날짜는 %d년 %d월 %d일입니다.\n", year, month, day);
							printf("\n\t\t%s의 %d:00 시간대의 예매 현황\n\n", movie[q - 1]->name, movie[q - 1]->startHour[k][d - 1]);
							print(movie[q - 1]->mv[k], d - 1);
							printf("예매하시겠습니까?(yes:1/no:0)\n->");
							scanf("%d", &t);
							if (t == 1) {
								printf("원하는 좌석의 위치를 입력하세요\n(ex : C열의 15번째 좌석 = C,15)\n->");
								getchar();
								scanf("%c,%d", &row, &column);
								if (row < 'A' || row > 'J')continue;
								if (column < 1 || column > 30)continue;
								printf("좌석 위치가 %c%d이 맞습니까?(yes:1/no:0)", row, column);
								scanf("%d", &t);
								if (t == 1) {
									seatnum = ((row - 65) * 30) + column;								// 입력받은 좌석 위치를 node의 data형으로 바꿔줌
									if (Search(*(movie[q - 1]->mv[k][d - 1]), seatnum) == NULL) {
										Insert(movie[q - 1]->mv[k][d - 1], Create(seatnum));
										printReservation(movie[q - 1]->mv[k], d - 1, seatnum);
										printf("예약되었습니다.\n");
										Print_Property(*(movie[q - 1]->mv[k][d - 1]));
										system("pause");
									}
									else {
										printf("이미 예약된 자리 입니다.\n"); system("pause"); continue;
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
					printf("예매 취소를 원하는 영화의 번호와 상영시간을 입력하세요\n(ex : 1번 영화의 상영시간 2 = 1,2)\n");	// 예매와 거의 똑같습니다.
					printf("->");
					scanf_s("%d,%d", &q, &d);
					if (q < 1 || q>5)continue;
					if (d < 1 || d>3)continue;
					printf("%s의 %d:00 시간대가 맞습니까?(yes:1/no:0)\n", movie[q - 1]->name, movie[q - 1]->startHour[k][d - 1]);
					printf("->");
					scanf_s("%d", &t);
					if (t == 1)
					{
						while (1) {
							fflush(stdin);
							system("cls");
							printf("        영화 예매 시스템\n");
							printf("오늘의 날짜는 %d년 %d월 %d일입니다.\n", year, month, day);
							printf("\n\t\t%s의 %d:00 시간대의 예매 현황\n\n", movie[q - 1]->name, movie[q - 1]->startHour[k][d - 1]);
							print(movie[q - 1]->mv[k], d - 1);
							printf("예매 취소하시겠습니까?(yes:1/no:0)\n->");
							scanf("%d", &t);
							if (t == 1) {
								printf("취소를 원하는 좌석의 위치를 입력하세요\n(ex : C열의 15번째 좌석 = C,15)\n->");
								getchar();
								scanf("%c,%d", &row, &column);
								if (row < 'A' || row > 'J')continue;
								if (column < 1 || column > 30)continue;
								printf("좌석 위치가 %c%d이 맞습니까?(yes:1/no:0)", row, column);
								scanf("%d", &t);
								if (t == 1) {
									seatnum = ((row - 65) * 30) + column;
									if (Search(*(movie[q - 1]->mv[k][d - 1]), seatnum) != NULL) {
										Delete(movie[q - 1]->mv[k][d - 1], seatnum);
										printReservation(movie[q - 1]->mv[k], d - 1, seatnum);
										printf("취소되었습니다.\n");
										Print_Property(*(movie[q - 1]->mv[k][d - 1]));
										system("pause");
									}
									else {
										printf("예약된 자리가 아닙니다.\n"); system("pause"); continue;
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

