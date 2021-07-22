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
	EnqueueNewPatient(Q, data);
}

void nextReg(infotype *data, int total){
	//kalau salah mending gimana?
	//1. Kasih peringatan klo salah masukin hrus dri awal lgi
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
			gotoxy(12,15);printf("Please choose the option on the menu!");getch();
	        system("cls");
	        nextReg(data, total);
			break;
		} InsertNewDiseaseAtEnd(&daftarPenyakit, penyakit);
		i++;		
	}while(i != total);
	data->penyakit = daftarPenyakit;
}

void list(Queue Q){
	system("color F0"); 
	printf("==================== ROC'S VETERINARY CLINIC ====================\n");
	printf("||                       [LIST OF QUEUE]                       ||\n");
	PrintQueue(Q);
	printf("|| Enter to Main Menu                                          ||\n");  
	printf("=================================================================\n");
}

void call(Queue Q){
	address_queue antrian,next;
	
	antrian = Q.Front;
	next = antrian->next;
	
	system("color F0"); 
		printf("==================== ROC'S VETERINARY CLINIC ====================\n");
		printf("||                        [CALL THE CAT]                       ||\n");
    	printf("|| Choose the diseases!                                        ||\n");
    	printf("|| Name                 : %-20s                 ||\n",Q.Front->data.nama);
    	printf("|| Start of Service     : %-13d                        ||\n",Q.Front->data.waktu_estimasi_mulai);
    	printf("|| End of Service       : %-14d                       ||\n",Q.Front->data.waktu_selesai);
    	printf("||                                                             ||\n"); 
    	if(next != NULL){
		printf("|| Next Cat                                                    ||\n");
    	printf("|| Name                 : %-20s                 ||\n", next->data.nama);
		printf("|| Start of Service     : %-13d                        ||\n", next->data.waktu_estimasi_mulai);
    	printf("||                                                             ||\n");}
		printf("|| Enter to Main Menu                                          ||\n");  
		printf("=================================================================\n");
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
			call (antrian);
			getch();
			break;
		case 4 :
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
