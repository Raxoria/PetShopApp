#include <stdio.h>
#include <stdlib.h>
#include "linked_list_disease.h"
#include "pet_prior_queue.h"
#include <string.h>
#include <windows.h>

Queue antrian;

void gotoxy(int x, int y) {
    /* Kursor untuk menunjuk pada titik (x,y) tertentu */

      COORD coord;
      coord.X = x;
      coord.Y = y;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void registrasi(Queue *Q){
	//catatan reg : mau dibikin 2 modul? atau gimana? biar gotoxynya jalan. Trus klo misalnya total dijadiin struct gimana?
	//cara masukin enum, data penyakitnya gimana?
	infotype data;
	char buffer[30] = {};
	int i=0,total,pilihan;
	
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
	EnqueueNewPatient(Q, data);
}

void nextReg(infotype *data, int total){
	LinkedList_Disease daftarPenyakit;
	infotype_disease penyakit;
	
	CreateNewDiseaseList(&daftarPenyakit);
	
	do{
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
			penyakit.severity = 1;
			break;
		case 4 :
		case 5 :
		case 6 :
			penyakit.severity = 2;
			break;
		case 7 :
		case 8 :
		case 9 :
			penyakit.severity = 3;
			break;
		default :
			//SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),12); 
			system("color F4");
			gotoxy(12,21);printf("Please choose the option on the menu!");getch();
	        system("cls");
			break;
		} InsertNewDiseaseAtEnd(&daftarPenyakit, penyakit);
		i++;		
	}while(i != total);
}

void list(Queue Q){
	system("color F0"); 
	PrintQueue(Q);
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
			getch();
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
			break;
		case 4 :
			break;
		default :
			//SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),12); 
			system("color F4");
			gotoxy(24,9);printf("Please choose the option on the menu!");getch();
			break;
		}
	}while(pilihan != 4);
	
	return 0;
}
