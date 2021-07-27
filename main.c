#include <stdio.h>
#include <stdlib.h>
#include "linked_list_disease.h"
#include "pet_prior_queue.h"
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

Queue antrian;
/* int bg, fg, delay, panjang;
int simbol[20] = {2,3,4,5,6,14,16,22,35,36,62,64,158,174,175,176,177,178,219};

void loading(int bg, int fg, int panjang, int delay, int simbol[20])
{
 int k, l;
	system("color F0");
   for (k=0; k<=panjang; k++)
   {
      //system("cls");  //digunakan untuk membersihkan layar pada compiler C, hampir sama dengan fungsi clrscr()
      gotoxy(55,1);printf("\n\tLOADING (PLEASE WAIT)\n\t");
      kecepatan(0.001);
	  for (l=0; l<k; l++)
       printf("%c", simbol[fg]);
      for (l=0; l<panjang-1; l++)
       printf("%c", simbol[bg]);
      Sleep(delay);
   }
}

void kecepatan(float seconds){
	clock_t endwait;
	endwait=clock()+seconds*CLOCKS_PER_SEC;
	while(clock()<endwait){};
}*/

void gotoxy(int x, int y) {
    /* Kursor untuk menunjuk pada titik (x,y) tertentu */

      COORD coord;
      coord.X = x;
      coord.Y = y;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void registrasi(Queue *Q){
	infotype data;
	char buffer[30] = {};
	int i=0,total;

	printf("==================== ROC'S VETERINARY CLINIC ====================\n");
    printf("||                     [NEW REGISTRARION]                      ||\n");
    printf("|| Please fill this form!                                      ||\n");
    printf("|| * Arrival            :                                      ||\n");
    printf("|| * Name               :                                      ||\n");
    printf("|| * Total of Diseases 	:                                      ||\n");
    printf("||                                                             ||\n");
	printf("|| Enter to Complete the Form!                                 ||\n");
	printf("=================================================================\n");
	gotoxy(26,3);scanf("%d", &data.waktu_datang);fflush(stdin);
	gotoxy(26,4);scanf("%s", buffer);fflush(stdin);
	gotoxy(26,5);scanf("%d", &total);fflush(stdin);

	data.nama = malloc(strlen(buffer));
	strcpy(data.nama, buffer);
	nextReg(&data, total);
	determinePriorityAndServiceTime(&data, data.penyakit.First);
	EnqueueNewPatient(Q, data);
	main();
}

void determinePriorityAndServiceTime(infotype *data, address_linked_list first){

    int severeCount, moderateCount, mildCount, totalTime;
    severeCount = moderateCount = mildCount = totalTime = 0;

    data->priority = 1;
    data->waktu_pelayaan = 0;

    while(first != NULL) {
        int severity = first->data_disease.severity;
        if(severity == MILD) {
            mildCount++;
            totalTime+=15;
        } else if(severity == MODERATE) {
            moderateCount++;
            totalTime+=30;
        } else if(severity == SEVERE) {
            severeCount++;
            totalTime+=45;
        }

        first = first->next;
    }

    (data->priority) += severeCount * 4;

    if(moderateCount >= 2) {
        (data->priority) += 3;
    } else if (moderateCount > 0) {
        (data->priority)++;
    }

    if(mildCount >= 3) {
        (data->priority) += 2;
    } else if (mildCount > 0) {
        (data->priority)++;
    }

    data->waktu_pelayaan = totalTime;
}

void nextReg(infotype *data, int total){
	LinkedList_Disease daftarPenyakit;
	infotype_disease penyakit;
	int pilihan,i;

	CreateNewDiseaseList(&daftarPenyakit);

	do{
		system("cls");
		system("color F0");
		printf("==================== ROC'S VETERINARY CLINIC ====================\n");
		printf("||                     [TYPE OF DISEASES]                      ||\n");
    	printf("|| Choose the diseases!                                        ||\n");
    	printf("|| 1. Skin Diseases         (R)                                ||\n");
    	printf("|| 2. Slight Injuries       (R)                                ||\n");
    	printf("|| 3. Sneeze                (R)                                ||\n");
    	printf("|| 4. Worming               (S)                                ||\n");
		printf("|| 5. Diarrhea              (S)                                ||\n");
    	printf("|| 6. Seriously Injured     (S)                                ||\n");
		printf("|| 7. Essophageal Disorders (B)                                ||\n");
    	printf("|| 8. Jaundice              (B)                                ||\n");
    	printf("|| 9. Virus                 (B)                                ||\n");
		printf("||                                                             ||\n");
		printf("|| Input your choice:                                          ||\n");
		printf("=================================================================\n");
		gotoxy(22,13);scanf("%d", &pilihan);fflush(stdin);

		penyakit.disease_name = pilihan-1;

		switch(pilihan){
            case 1 :
            case 2 :
            case 3 :
                penyakit.severity = MILD;
                i++;
				break;
            case 4 :
            case 5 :
            case 6 :
                penyakit.severity = MODERATE;
                i++;
				break;
            case 7 :
            case 8 :
            case 9 :
                penyakit.severity = SEVERE;
                i++;
                break;
            default :
                //SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),12);
                system("color F4");
                gotoxy(12,21);
                printf("Please choose the option on the menu!");
                getch();
                system("cls");
			break;
		}
		InsertNewDiseaseAtEnd(&daftarPenyakit, penyakit);
	}while(i != total);
	data->penyakit = daftarPenyakit;
}

void list(Queue Q){
	int pil;
	system("color F0");
	printf("=============================== ROC'S VETERINARY CLINIC ===============================\n");
	printf("||                                  [LIST OF QUEUE]                                  ||\n");
	if(IsQueueEmpty(Q)){
		do{
		system("color F0");
    	printf("||                                                                                   ||\n");
        printf("|| Sorry there isn't a Queue :(                                                      ||\n");
    	printf("|| Please make a Registration first!                                                 ||\n");
    	printf("||                                                                                   ||\n");
    	printf("|| Would you like to Register?                                                       ||\n");
    	printf("|| 1. Yes [Make a Registration]                                                      ||\n");
    	printf("|| 2. No  [Back to Menu]                                                             ||\n");
		printf("=======================================================================================\n");
    	gotoxy(31,6);scanf("%d", &pil);fflush(stdin);
    	switch(pil){
    		case 1:
    			system("cls");
				system("color F0");
				registrasi(&antrian);
    			break;
    		case 2:
    			main();
    			break;
    		default :
    			system("color F4");
				gotoxy(15,10);printf("Please choose the option on the menu!");getch();
				system("cls");
				break;
    		}
		}while(pil != "1" || pil != "2");
	}else{PrintQueue(Q);}
}

void call(Queue *Q){
	address_queue antrian,next;
	int pil;

	if(IsQueueEmpty(*Q)){
		do{
		system("color F0");
		printf("==================== ROC'S VETERINARY CLINIC ====================\n");
    	printf("||                        [CALL THE CAT]                       ||\n");
    	printf("||                                                             ||\n");
    	printf("|| Sorry there isn't a Queue :(                                ||\n");
    	printf("|| Please make a Registration first!                           ||\n");
    	printf("||                                                             ||\n");
    	printf("|| Would you like to Register?                                 ||\n");
    	printf("|| 1. Yes [Make a Registration]                                ||\n");
    	printf("|| 2. No  [Back to Menu]                                       ||\n");
    	printf("=================================================================\n");
    	gotoxy(31,6);scanf("%d", &pil);fflush(stdin);
    	switch(pil){
    		case 1:
    			system("cls");
				system("color F0");
				registrasi(Q);
    			break;
    		case 2:
    			main();
    			break;
    		default :
    			system("color F4");
				gotoxy(15,10);printf("Please choose the option on the menu!");getch();
				system("cls");
				break;
    		}
		}while(pil != "1" || pil != "2");
	}
	
	
	else{
		antrian = Q->Front;
		next = antrian->next;

		system("color F0");
	    printf("==================== ROC'S VETERINARY CLINIC ====================\n");
    	printf("||                        [CALL THE CAT]                       ||\n");
	    printf("||                                                             ||\n");
    	printf("|| Name                 : %-20s                 ||\n",Q->Front->data.nama);
	    printf("|| Start of Service     : %-13d                        ||\n",Q->Front->data.waktu_estimasi_mulai);
   		printf("|| End of Service       : %-14d                       ||\n",Q->Front->data.waktu_selesai);
    	printf("||                                                             ||\n");
    	if(next != NULL){
        	printf("|| Next Cat                                                    ||\n");
        	printf("|| Name                 : %-20s                 ||\n", next->data.nama);
        	printf("|| Start of Service     : %-13d                        ||\n", next->data.waktu_estimasi_mulai);
        	printf("||                                                             ||\n");
    	}
    	printf("|| Enter to Main Menu                                          ||\n");
    	printf("=================================================================\n");
    DequeuePatient(Q);
	}
}

int main()
{
	system("cls");
	int pilihan;
	if(IsQueueEmpty(antrian)){
		CreateNewQueue(&antrian);
	}

	do{
	system("cls");
	system("color F0");
    printf("=============== WELCOME TO ROC'S VETERINARY CLINIC ==============\n");
    printf("||                         [MAIN MENU]                         ||\n");
    printf("|| 1. New Registration                                         ||\n");
    printf("|| 2. List of Queue                                            ||\n");
    printf("|| 3. Call The Next Cat                                        ||\n");
    printf("|| 4. Exit                                                     ||\n");
    printf("||                                                             ||\n");
	printf("|| Input your choice:                                          ||\n");
	printf("=================================================================\n");
	gotoxy(22,7);scanf("%d", &pilihan);fflush(stdin);

	switch(pilihan){
		case 1 :
			system("cls");
			system("color F0");
			registrasi(&antrian);
			break;
		case 2 :
			system("cls");
			system("color F0");
			list (antrian);
			getch();
			break;
		case 3 :
			system("cls");
			system("color F0");
			call (&antrian);
			getch();
			break;
		case 4 :
			exit(0);
			break;
		default :
			//SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),12);
			system("color F4");
			gotoxy(15,9);printf("Please choose the option on the menu!");getch();
			break;
		}
	}while(pilihan != 4);

	return 0;
}
