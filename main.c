#include <stdio.h>
#include <string.h>

#include "disease.h"
#include "pet_prior_queue.h"

Queue antrian;

void registrasi(Queue *Q){
	/*
	* @author : Syelvie Ira Ratna Mulia
	* @deskription : modul pengisian data(nama, waktu datang dan total penyakit) yang dibutuhkan registrasi
	*/
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

	if(total < 1 || total > 9) {
        system("color F4");
        gotoxy(12,21);
        printf("Total disease has minimun of 1 and maximun of 9 !");
        getch();
        system("cls");
        system("color F0");
        registrasi(Q);
	} else {
	    data.nama = malloc(strlen(buffer));
	    data.totalDisease = total;
        strcpy(data.nama, buffer);
        nextReg(&data);
        determinePriorityAndServiceTime(&data, data.penyakit);
        EnqueueNewPatient(Q, data);
        main();
	}
}

void nextReg(infotype *data){
	/*
	* @author : Syelvie Ira Ratna Mulia
	* @deskription : modul pengisian data (jenis jenis penyakit) yang dibutuhkan registrasi
	*/
	memset(data->penyakit, -1, sizeof(infotype_disease) * 9);
	infotype_disease penyakit;
	int pilihan, i = 0;

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
		printf("|| Input disease %d :                                           ||\n", i + 1);
		printf("=================================================================\n");
		gotoxy(25,13);scanf("%d", &pilihan);fflush(stdin);

		if(CheckIfDiseaseAlreadyExist(data->penyakit, data->totalDisease, pilihan - 1)){
            system("color F4");
            gotoxy(12,15);
            printf("You have already input that disease !");
            getch();
            system("cls");
            continue;
		}

		penyakit.disease_name = pilihan-1;

		switch(pilihan){
            case 1 :
            case 2 :
            case 3 :
                penyakit.severity = MILD;
                data->penyakit[i] = penyakit;
                i++;
				break;
            case 4 :
            case 5 :
            case 6 :
                penyakit.severity = MODERATE;
                data->penyakit[i] = penyakit;
                i++;
				break;
            case 7 :
            case 8 :
            case 9 :
                penyakit.severity = SEVERE;
                data->penyakit[i] = penyakit;
                i++;
                break;
            default :
                //SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),12);
                system("color F4");
                gotoxy(12,15);
                printf("Please choose the option on the menu!");
                getch();
                system("cls");
			break;
		}
	} while(i < data->totalDisease);
}

void list(Queue Q){
	/*
	* @author : Syelvie Ira Ratna Mulia
	* @deskription : Menampilkan list antrian
	*/
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
	/*
	* @author : Syelvie Ira Ratna Mulia
	* @deskription : modul yang menampilkan pemanggilan kucing yang dipanggil
	*/

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

int main(){
	/*
	* @author : Syelvie Ira Ratna Mulia
	* @deskription : modul main menu
	*/

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
