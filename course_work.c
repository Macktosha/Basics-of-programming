#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define YES 1
#define NO 0
#define WORD_SIZE 18
#define MAX 512




  struct ticket {
	  //необходимые данные для составления базы данных
	char plane[WORD_SIZE];
	char company[WORD_SIZE];
	char departure[WORD_SIZE];
	char arrival[WORD_SIZE];

	int  transfer;
	int date_day;
	int date_month;
	int date_year;

	float dep_time;
	float arr_time;
	int price;
}new_tik[MAX];

//Прототипы функций
void show_base();     //вывод базы данных
int line_counter();   //счетчик строк
void create_ticket(); //создать билет
void find_price();    //определить лучшую цену
void delete_ticket(); //удалить билет
void editing_menu();  //меню выбора редактирования
int find_free();      //поиск свободной ячейки массива структуры
void sorting_menu();  //меню подбора
void find_transfer(); //определить самую короткую пересадку
void clearize();      //очистить базу данных
void put_to_file();   //печать в файл
void edit_exact_ticket();
void recover_base();
/// // // //

char ch2 = (char)16;

void main_menu()//главное меню программы
{
	
	 int menu = 0;
	printf("\t\t\t\t\tMenu\n   Choose the option:\n");
	printf("\t\t\t%c1 - Create database\\Add data\n",ch2);
	printf("\t\t\t%c2 - Open database\n",ch2);
	printf("\t\t\t%c3 - Editing of database\n",ch2);
	printf("\t\t\t%c4 - Sorting\n",ch2);
	printf("\t\t\t\t0 -> Exit\n");
	scanf_s("%d", &menu);
	
	switch (menu)
	{
	case 1:
		system("cls");
		create_ticket();
		break;
	case 2: 
		system("cls");
		show_base();
		main_menu();
		break;
	case 3: 
		system("cls");
		editing_menu();
		break;
	case 4:
		system("cls");
		sorting_menu();

		break;
	case 0: system("exit");
		break;

	default: system("exit");
		break;
	}
}

void sorting_menu()//меню для работы с сортировками/поиском
{
	 int tosort = 0;
	printf("\t\tHow would you like to sort?\n");
	printf("\t1 - Price\n\t2 - Shortest transfer\n");
	printf("\t\t0 -> To main menu\n");
	scanf_s("%d", &tosort);
	switch (tosort)
	{
	case 1: 
		find_price();
		break;
	case 2:
	   find_transfer();
		break;
	case 0: main_menu();
		break;
	default: system("exit");
		break;
	}
}

void editing_menu()//меню для работы над данными
{
	printf("\t\tHow would you like to edit data?\n");
	printf("\t1 - Add ticket\n\t2 - Delete ticket\n\t3 - Edit exact ticket\n\t4 - Clearize database\n");
	printf("\t\t0 -> To main menu\n");
	 int choice = 0;
	scanf_s("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("The ticket will be added to the end of the list\n");
		create_ticket();
		break;
	case 2: 
		show_base();
		printf("\n");
		delete_ticket();
		break;
	case 4: 
		printf("Would you like to clear all data??? 1-Yes 0-No\n");
		int choice2 = 0;
		scanf_s("%d", &choice2);
		system("cls");
		if (choice2) {
			clearize();
			break;
		}
		else {
			main_menu(); break;
		}
	case 3: 
		edit_exact_ticket();
		break;
	case 0: main_menu();
		break;
	default:printf("Error");
		main_menu();
		break;
	}
}

void heading() //заголовок таблицы
{
	printf("\n");
	for (int i = 1; i <= 156; i++)
		printf("=");
	printf("\n");
	printf("|   #|     Company      |       Plane      |              Departure -> Arrival              |     Date     |  Dept.time/Arr.time |    Price    |  Transfer | \n");
	for (int i = 1; i <= 156; i++)
		printf("=");
	
}


void create_ticket() //новый билет
{
	int slot = 0;
	 int transf_indicator = 0; //1-есть пересадка 0-нет
	
	slot = find_free();//находим свободное место в массиве 
	
	 getchar();
	 //авиакомпания
	 printf("Enter the company:  \n");							
	 gets(new_tik[slot].company);


	//самолет
	 printf("\nEnter the plane:  \n");
	 gets(new_tik[slot].plane);


	 //вылет->прилет 
	 printf("Enter departure:  \n");
	 gets(new_tik[slot].departure);
	 printf("Enter destination:  \n");
	 gets(new_tik[slot].arrival);
	 
	 //дата вылета
	 printf("Enter date of departure(format dd.mm.year): \n");
	 scanf_s("%d.%d.%d", &new_tik[slot].date_day, &new_tik[slot].date_month, &new_tik[slot].date_year);

			

		 getchar();
		 //время вылета/прилета
	 printf("\nDeparture time (format 00.00) :  \n");
	 scanf_s("%f", &new_tik[slot].dep_time);
	 getchar();
	printf("\nArrival time (format 00.00) :  \n");
	//getchar();
	 scanf_s("%f", &new_tik[slot].arr_time);



	 //цена 
	 getchar();
	 printf("\nEnter the price of the ticket\n");
	 scanf_s("%d", &new_tik[slot].price);
	 



	 //пересадка? если да, то сколько; нет - идем дальше
	 printf("Flight with a transfer? 1 - Yes   0 - No:  ");
	 scanf_s("%d", &transf_indicator);
	 switch (transf_indicator)
	 {
	 case 0: new_tik[slot].transfer = NO;
		
		 break;
	 case 1:  printf("Enter the duration of transfer in minutes:  ");

		 scanf_s("%d", &new_tik[slot].transfer);
		 break;
		
	 }

	 put_to_file();

	 system("cls");
	 show_base();
	 printf("\n\t\t");
	 main_menu();
}

int find_free()//функция, которая ищет свободное место для добавления 
{
	register int t;
	for (t = 0; new_tik[t].company[0] && t < MAX; t++);
	if (t == MAX) return -1;
	return t;
}

void show_base() //вывести базу данных
{
	heading();
	printf("\n");
	int k = line_counter();
	int sb = 0;
	while (sb != k) {
		printf("|%4d| %16s | %16s | %22s->%22s |   %2d.%2d.%d | %9.2f/%9.2f | %11d | %9d |\n", sb + 1, new_tik[sb].company, new_tik[sb].plane, new_tik[sb].departure,
			new_tik[sb].arrival, new_tik[sb].date_day, new_tik[sb].date_month, new_tik[sb].date_year, new_tik[sb].dep_time, new_tik[sb].arr_time, new_tik[sb].price, new_tik[sb].transfer);

		sb++;
	}

}



int line_counter()//счетчик строк в базе
{
	int lines_amnt = 0;
	FILE* file1 = fopen("data.txt", "r");
	rewind(file1);
	while (!feof(file1)) {
		if (fgetc(file1) == '\n')
			lines_amnt++;
	
}
	
	return lines_amnt;
	
	fclose(file1);
}

void delete_ticket()//удаление билета(строки)
{
	int to_del = 0;
	int lines_cnt = line_counter();
	printf("\t\tWhich line would you like to delete?\n");
	scanf_s("%d", &to_del);
	
		for (int i = to_del-1; i < lines_cnt ; i++) {
			
			new_tik[i] = new_tik[i + 1];
			memset(&new_tik[i+1], 0, sizeof(new_tik[i+1]));
			
		}
	

	put_to_file();
	recover_base();


	main_menu();
}


void find_price() //подобро маршрута с наименьшей стоимостью
{
	 int min = 99999;
	 int N = line_counter();
     int p = 0;

	 char* fl_from=(char*)malloc(20 * sizeof(char));     
	 
	 fl_from[19] = '\0';
	 char *fl_to = (char*)malloc(20 * sizeof(char));     

	 fl_to[19] = '\0';

	 printf("Enter data to find the cheapest ticket\n Enter departure: ");
	 getchar();
	 gets(fl_from);
	 printf("\nEnter arrival: ");
	 gets(fl_to);
	 //ищем совпадение и минимальную цену
	 for (int i = 0; i < N; i++) {
			 if (((strcmp(fl_from, new_tik[i].departure)) == 0) && ((strcmp(fl_to, new_tik[i].arrival)) == 0)&&(new_tik[i].price<min)) {
				 p = i;
				 min = new_tik[i].price;
			 }
			 else if ((((strcmp(fl_from, new_tik[i].departure)) != 0) && ((strcmp(fl_to, new_tik[i].arrival)) != 0)))
				 printf("There is no such ticket in data base or input is incorrect\n");
		 
	 }
	 system("cls");
	 printf("\n\tThe cheapest ticket from <%s> to <%s> costs: %d \n", fl_from, fl_to,min);
	 printf("\t\tINFO:\n");
	 printf("Company: %s\nPlane:%s\nDeparture: %2.2f\tArrival: %2.2f\nOn date: %d.%d.%d\n", new_tik[p].company, new_tik[p].plane, new_tik[p].dep_time,
		 new_tik[p].arr_time, new_tik[p].date_day, new_tik[p].date_month, new_tik[p].date_year);

	 if (new_tik[p].transfer == 0)
		 printf("Transfer: NO\n\n");
	 else
		 printf("Transfer: %d min.\n\n", new_tik[p].transfer);
	 
	 free(fl_to);
	 free(fl_from);
	 sorting_menu();
}

void find_transfer()
{
	int min = 9999;
	int N = line_counter();
	int t = 0;
	char* from = (char*)malloc(20 * sizeof(char)); from[19] = '\0';
	char* destin = (char*)malloc(20 * sizeof(char)); destin[19] = '\0';
	printf("Enter data to find the ticket with shortest transfer \n Enter departure: ");
	getchar();
	gets(from);
	printf("\nEnter arrival: ");
	gets(destin);
	//ищем совпадение и ищем минимальную пересадку
	for (int i = 0; i < N; i++) {
		if (((strcmp(from, new_tik[i].departure)) == 0) && ((strcmp(destin, new_tik[i].arrival)) == 0) && (new_tik[i].transfer < min)) {
			t = i;
			min = new_tik[i].transfer;
		}
		else if ((((strcmp(from, new_tik[i].departure)) != 0) && ((strcmp(destin, new_tik[i].arrival)) != 0)))
			printf("There is no such ticket in data base or input is incorrect\n");
	}


	system("cls");
	if (min == 0) {
		printf("\n\tThe ticket from <%s> to <%s> without transfer is available\n\t\tINFO:\n", from, destin);
		printf("Company: %s\nPlane:%s\nDeparture: %2.2f\tArrival: %2.2f\nOn date: %d.%d.%d\nPrice: %d\n\n", new_tik[t].company, new_tik[t].plane, new_tik[t].dep_time,
			new_tik[t].arr_time, new_tik[t].date_day, new_tik[t].date_month, new_tik[t].date_year, new_tik[t].price);
	}

	else {
		printf("\n\tThe ticket from <%s> to <%s> with the shortest transfer duration <%d min.>\n\t\tINFO:\n", from, destin, min);
		printf("Company: %s\nPlane:%s\nDeparture: %2.2f\tArrival: %2.2f\nOn date: %d.%d.%d\nPrice: %d\n\n", new_tik[t].company, new_tik[t].plane, new_tik[t].dep_time,
			new_tik[t].arr_time, new_tik[t].date_day, new_tik[t].date_month, new_tik[t].date_year, new_tik[t].price);
	}
	free(from);
	free(destin);
	sorting_menu();
}

void clearize() { //функция для быстрой очистки базы данных
	FILE* file1 = fopen("data.txt", "w+");
	fclose(file1);
	main_menu();
}

void put_to_file()//печать содержимого массива структур в файл
{
	FILE* file1 = fopen("data.txt", "w+");
	int fin = find_free();
	for (int j = 0; j != fin; j++) {
		fprintf(file1, "%s\t%s\t%s\t%s\t%d\t%d\t%d\t%2.2f\t%2.2f\t%d\t%d\n", new_tik[j].company, new_tik[j].plane, new_tik[j].departure,new_tik[j].arrival,
		 new_tik[j].date_day, new_tik[j].date_month, new_tik[j].date_year,new_tik[j].dep_time,new_tik[j].arr_time, new_tik[j].price, new_tik[j].transfer);
	}
	fclose(file1);
} 

void edit_exact_ticket()//редактирование определенных полей
{
L1:
	show_base();
	int select1 = 0;
	int select2 = 0;
	
	printf("\n\nChoose the ticket to edit: ");
	scanf_s("%d", &select1);
EDIT:
	printf("\n\t\tWhat would you like to edit?\n\t1 - Company\n\t2 - Plane\n\t3 - Departure\n\t4 - Arrival\n\t5 - Date of departure\n\t6 - Depart. time\n\t7 - Arrival time\n\t8 - Price\n\t9 - Transfer\n\t10 - Choose another ticket\n\t\t0 - Main menu\n");
	scanf_s("%d", &select2);
	printf("\n");
	switch (select2)
	{
	case 1: 
		getchar();
		printf("Enter new company:\n");
		gets(new_tik[select1 - 1].company);
		printf("\nDone!");
		goto EDIT;
		break;
	case 2: 
		getchar();
		printf("Enter new plane:\n");
		gets(new_tik[select1 - 1].plane);
		printf("\nDone!");
		goto EDIT;
		break;
	case 3: 
		getchar();
		printf("Enter new departure:\n");
		gets(new_tik[select1 - 1].departure);
		printf("\nDone!");
		goto EDIT;
		break;
	case 4: 
		getchar();
		printf("Enter new destination:\n");
		gets(new_tik[select1 - 1].arrival);
		printf("\nDone!");
		goto EDIT;
		break;
	case 5:
		printf("Enter new date(format dd.mm.yyyy):\n");
		scanf_s("%d.%d.%d", &new_tik[select1-1].date_day, &new_tik[select1 - 1].date_month, &new_tik[select1 -1].date_year);
		printf("\nDone!");
		goto EDIT;
		break;
	case 6: 
		printf("\nEnter new departure time (format 00.00) :  \n");
		scanf_s("%f", &new_tik[select1-1].dep_time);
		printf("\nDone!");
		goto EDIT;
		break;
	case 7:
		printf("\nEnter new arrival time (format 00.00) :  \n");
		scanf_s("%f", &new_tik[select1 - 1].arr_time);
		printf("\nDone!");
		goto EDIT;
		break;
	case 8: 
		printf("\nEnter new price of the ticket\n");
		scanf_s("%d", &new_tik[select1-1].price);
		printf("\nDone!");
		goto EDIT;
		break;
	case 9: 
		printf("Enter new duration of a transfer(if there is no tranfer, please, enter 0)");
		scanf_s("%d", &new_tik[select1 - 1].transfer);
		printf("\nDone!");
		goto EDIT;
		break;
	case 10:
		system("cls");
		goto L1; 
		break;
	case 0:
		system("cls");
		main_menu();
		break;
	
	}
	put_to_file();
	recover_base();
}

void recover_base()//функция которая восстанавливает массив структур из файла 
{
	FILE* file1 = fopen("data.txt", "r+");
	int cnt = line_counter();
	int rec = 0;

	while(rec!=cnt) {
	
		fscanf(file1, "%s\t%s\t%s\t%s\t%d\t%d\t%d\t%f\t%f\t%d\t%d\n", &new_tik[rec].company, &new_tik[rec].plane, &new_tik[rec].departure,
			&new_tik[rec].arrival, &new_tik[rec].date_day, &new_tik[rec].date_month, &new_tik[rec].date_year, &new_tik[rec].dep_time, &new_tik[rec].arr_time, &new_tik[rec].price,&new_tik[rec].transfer);
		
		rec++;
	
	}
	
	
	
	fclose(file1);
}


int main()
{
	recover_base();
	main_menu();
	return 0;
}


