#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
	char name[255];
	char code[10];
	int QTY;
};

struct Bon {
	char name[100];
	int stockAwal;
	char code[10];
	int QTY;
};

Product stock[30];
Bon sold[5];
Bon history[30];
int amount;
int type;

void cekStock() {
	int i = 0;
	FILE *cek = fopen("stock.txt", "r");
	while(!feof(cek)) {
		fscanf(cek, "%[^#]#%[^#]#%d\n", stock[i].name, stock[i].code, &stock[i].QTY);
		i++;
	}
	type = i;
	fclose(cek);
}

void listProduct() {
	system("@cls||clear");
	printf("\n\t\tOur Market Product\n");
	printf(" ________________________________________________________________\n");
	printf("|No.|%-25s   |\t%-7s |\t%-8s |\n", "Name", "Code", "QTY");
	printf("|___|____________________________|______________|________________|\n");
	for(int i = 0; i < type; i++) {
		printf("|%-2d.|%-25s   |\t%-7s |\t%-4d Pcs |\n", i + 1, stock[i].name, stock[i].code, stock[i].QTY);
	}
	printf("|___|____________________________|______________|________________|\n");
	puts("\tTekan Tombol Apa Saja Untuk Kembali Ke Main Menu");
	getchar();
	system("@cls||clear");
}

void updateStock() {
	FILE *update = fopen("stock.txt", "w");
	for(int i = 0; i < type; i++) {
		fprintf(update, "%s#%s#%d", stock[i].name, stock[i].code, stock[i].QTY);
		if(i < type - 1) {
			fprintf(update, "\n");
		}
	}
	fclose(update);
}

void buyItem() {
	system("@cls||clear");
	char buy[100];
	int PCS;
	printf("\n\t\tMARKET\n");
	printf("\tMasukkan Nama / Kode Produk       : ");
	scanf(" %[^\n]", buy);
	printf("\tMasukkan Jumlah Yang Ingin Dibeli : ");
	scanf(" %d", &PCS);
	for(int i = 0; i < type; i++) {
		if(i <= type - 1 && strcasecmp(buy, stock[i].name) == 0 || strcasecmp(buy, stock[i].code) == 0) {
			if(stock[i].QTY >= PCS) {
				stock[i].QTY -= PCS;
				printf("\tPembelian Berhasil\n");
				strcpy(sold[amount].code, stock[i].code);
				strcpy(sold[amount].name, stock[i].name);
				sold[amount].QTY = PCS;
				sold[amount].stockAwal = stock[i].QTY + PCS;
				amount++;
				updateStock();
			} else {
				printf("\tBarang Tersisa %d Pcs\n", stock[i].QTY);
			}
		}
	}
	puts("\tTekan Tombol Apa Saja Untuk Kembali Ke Main Menu");
	getchar();
	system("@cls||clear");
}

void printStruct() {
	system("@cls||clear");
	FILE *backUp = fopen("jualan@.sky", "ab");
	for(int i = 0; i < amount; i++) {
		fwrite(&sold[i], sizeof(Bon), 1, backUp);
	}
	fclose(backUp);
	printf("\n\t\tMARKET\n");
	printf("\tUpload Berhasil\n");
	puts("\tTekan Tombol Apa Saja Untuk Kembali Ke Main Menu");
	getchar();
	system("@cls||clear");
}

void readHistory() {
	system("@cls||clear");
	FILE *backUp = fopen("jualan@.sky", "rb");
	for(int i = 0; i < amount; i++) {
		fread(&history[i], sizeof(Bon), 1, backUp);
	}
	printf("\n\t\tMARKET\n");
	for(int i = 0; i < amount; i++) {
		printf("%s (%s) sejumlah %d\n", sold[i].name, sold[i].code, sold[i].QTY);
	}
	fclose(backUp);
	puts("\tTekan Tombol Apa Saja Untuk Kembali Ke Main Menu");
	getchar();
	system("@cls||clear");
}

void exit() {
	system("@cls||clear");
	printf("\n\t\tMARKET\n");
	for(int i = 0; i < amount; i++) {
		printf("\t%s terbeli sebanyak %d dari stock awal %d\n", sold[i].name, sold[i].QTY, sold[i].stockAwal);
	}
	for(int i = 0; i < type; i++) {
		printf("\n\t%s tersisa %d Pcs\n", stock[i].name, stock[i].QTY);
	}
	puts("\n\tTekan Tombol Apa Saja Untuk Keluar aplikasi");
	getchar();
	system("@cls||clear");
}

void mainMenu() {
	printf("\n\t\tMARKET\n");
	puts("  1. Lihat List Barang");
	puts("  2. Masukkan Data Pembelian");
	puts("  3. Tulis Data Pembelian");
	puts("  4. Baca Data Pembelian");
	puts("  5. Keluar");
	printf("  Masukkan Pilihan >>");
	while(1) {
		int choice = -1;
		scanf("%d", &choice);
		getchar();
		if(choice == 1) {
			listProduct();
			mainMenu();
			break;
		} else if(choice == 2) {
			buyItem();
			mainMenu();
			break;
		} else if(choice == 3) {
			printStruct();
			mainMenu();
			break;
		} else if(choice == 4) {
			readHistory();
			mainMenu();
			break;
		} else if(choice == 5) {
			exit();
			break;
		}
	}
}

int main() {
	cekStock();
	FILE *cek = fopen("stock.txt", "r");
	if(!cek) {
		return 1;
	} else {
		mainMenu();
	}	
}
