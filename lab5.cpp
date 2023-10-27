#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_AUTHORS 100

struct SACH{
    char ten_sach[100];
    char tac_gia[50];
    char Nha_XB[50];
    int Nam_XB;
};

struct ThongKeTacGia{
    char tac_gia[50];
    int so_luong_sach;
};

struct NODE{
    SACH data;
    struct NODE *pNext;
};

struct LIST{
    NODE *pHead;
    NODE *pTail;
};

void List(struct LIST &l){
    l.pHead = NULL;
    l.pTail = NULL;
}

NODE *getNode(struct SACH sach){

    struct NODE *p = (struct NODE *)malloc(sizeof(struct NODE));
    if (p == NULL){
        printf("Khoi tao NODE khong thanh cong!");
        return NULL;
    }
    p->data = sach;
    p->pNext = NULL;
    return p; 
}

void addLast(struct LIST &l, struct NODE *p){
    if(l.pHead == NULL){
        l.pHead = l.pTail = p;
    } else{
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

void insertLast(struct LIST &l, struct SACH sach){
    NODE *p = getNode(sach);
    if(p == NULL){
        return;
    }
    addLast(l,p);
}

int NhapSach(struct SACH &sach){
    printf("\t\tNhap thong tin cho sach\t\t\n");
    printf("Nhap ten sach: ");
    fflush(stdin);
    fgets(sach.ten_sach, sizeof(sach.ten_sach), stdin);
    if (strcmp(sach.ten_sach, "") == 0) return 0;

    printf("Nhap ten tac gia: ");
    fflush(stdin);
    fgets(sach.tac_gia, sizeof(sach.tac_gia), stdin);

    printf("Nhap nha xuat ban: ");
    fflush(stdin);
    fgets(sach.Nha_XB, sizeof(sach.Nha_XB), stdin);

    printf("Nhap nam xuat ban: ");
    scanf("%d", &sach.Nam_XB);

    return 1;
}

void NhapDSSach(struct LIST &l){
    printf("\nBat dau nhap thong tin cua sach.Khong nhap ten sach de ket thuc. \n");
    struct SACH sach;
    int flag = NhapSach(sach);
    while(flag){
        insertLast(l,sach);
        flag = NhapSach(sach);
    }
    printf("\nKet thuc nhap danh sach!");
}

void SaveToFile(struct LIST &l, char *filename){
    FILE *f = fopen(filename, "a");
    if(f == NULL){
        printf("Khong the tao file.\n");
        return;
    }

    NODE *p = l.pHead;
    while(p != NULL){
        fprintf(f,"\n");
        fprintf(f, "\nTen Sach: %s\nTen Tac Gia: %s\nNha Xuat Ban: %s\nNam Xuat Ban: %d", p->data.ten_sach, p->data.tac_gia, p->data.Nha_XB, p->data.Nam_XB);
        p = p->pNext;
    }
    fclose(f);
    printf("\nLuu thanh cong!");
}

void SoLuongSachCua1TacGia(struct LIST &l, char tac_gia[], char *filename){
    FILE *f = fopen(filename,"r");
    if(f == NULL){
        printf("Tao file khong thanh congn\n");
        return;
    }
    //Doc tung sach tu tep va dem
    int cnt = 0;
    struct SACH sach;
    while(fscanf(f, "\nTen sach: %[^\n]\nTen tac gia: %[^\n]\nNXB: %[^\n]\nNam XB: %d", sach.ten_sach, sach.tac_gia, sach.Nha_XB, &sach.Nam_XB) != EOF){
        if(strcmp(sach.tac_gia,tac_gia) == 0){
            cnt++;
        }
    }
    fclose(f);
    printf("Tac gia %s co %d quyen sach trong danh sach.\n", tac_gia, cnt);

}

void DSSachTheoNamVaNhaXB(struct LIST &l, int namXB, char nhaXB[],char *filename){
    FILE *f = fopen(filename,"r");
    if(f == NULL){
        printf("Tao file khong thanh cong.\n");
        return;
    }
    //Doc tu tep va hien thi sach
    struct SACH sach;
    while(fscanf(f,"\nTen sach: %[^\n]\nTen tac gia: %[^\n]\nNXB: %[^\n]\nNam XB: %d", sach.ten_sach, sach.tac_gia, sach.Nha_XB, &sach.Nam_XB) != EOF){
        if(sach.Nam_XB == namXB && strcmp(sach.Nha_XB,nhaXB) == 0){
            printf("\nTen sach: %s\nTen tac gia: %s\n", sach.ten_sach, sach.tac_gia);
        }
    }
    fclose(f);
}


void XoaSach(struct LIST &l, char tac_gia[], char *filename, char *deleteFilename){
    FILE *f = fopen(filename,"r");
    if(f == NULL){
        printf("Tao file khong thanh cong.\n");
        return;
    }

    //mo tep tin tam
    FILE *tempFile = fopen("temp_QL_Sach.txt", "w");
    if(tempFile == NULL){
        printf("Khong the tao file tam thoi!\n");
        return;
    }

    //mo tep chua du lieu da xoa
    FILE *deleteFile = fopen(deleteFilename, "r");
    if(deleteFile == NULL){
        printf("Khong the mo file cho du lieu bi xoa.\n");
        fclose(f);
        fclose(tempFile);
        return;
    }

    struct SACH sach;
    //Doc va xu ly tu tep tin goc
    while(fscanf(f, "\nTen sach: %[^\n]\nTen tac gia: %[^\n]\nNXB: %[^\n]\nNam XB: %d", sach.ten_sach, sach.tac_gia, sach.Nha_XB, &sach.Nam_XB) != EOF){
        if(strcmp(sach.tac_gia, tac_gia) == 0){
            //luu du lieu bi xoa vao tep tin da xoa
            fprintf(deleteFile, "\nTen sach: %[^\n]\nTen tac gia: %[^\n]\nNXB: %[^\n]\nNam XB: %d", sach.ten_sach, sach.tac_gia, sach.Nha_XB, sach.Nam_XB); 
        } else{
            //Luu tru du lieu con lai vao tin tam kho
            fprintf(tempFile,"\nTen sach: %[^\n]\nTen tac gia: %[^\n]\nNXB: %[^\n]\nNam XB: %d", sach.ten_sach, sach.tac_gia, sach.Nha_XB, sach.Nam_XB);
        }
    }
    fclose(f);
    fclose(tempFile);
    fclose(deleteFile);
    
    remove(filename);
    rename("temp_quan_ly_sach.txt", filename);
}


void DocDanhSachSachTuFile(struct LIST &l,char *filename) {
    FILE *f = fopen(filename, "r");
    if (f== NULL) {
        printf("Khong the mo tao file.\n");
        return;
    }
    
    struct SACH sach;
    
    while (fscanf(f, "\nTen sach: %[^\n]\nTen tac gia: %[^\n]\nNXB: %[^\n]\nNam XB: %d", sach.ten_sach, sach.tac_gia, sach.Nha_XB, &sach.Nam_XB) != EOF) {
        insertLast(l, sach);
		printf("\nTen sach: %s\nTen tac gia: %s\nNXB: %s\nNam XB: %d\n", sach.ten_sach, sach.tac_gia, sach.Nha_XB, sach.Nam_XB);

    }

    fclose(f);
    printf("Doc du lieu tu file thanh cong!");
}

//Doc va hien thi so lieu thong ke
void ReadAndDisplayStatistics(char *countFilename) {
    FILE *thongKeFile = fopen(countFilename, "r");
    if (thongKeFile == NULL) {
        printf("Khong the mo tao file thong ke.\n");
        return;
    }

    char line[255];
    
    while (fgets(line, sizeof(line), thongKeFile) != NULL) {
        printf("%s", line);
    }

    fclose(thongKeFile);
}

void ThongKeSachTheoTacGia(struct LIST &l,char *filename,char *countFilename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong the mo tao file.\n");
        return;
    }

    FILE *thongKeFile = fopen(countFilename, "w");
    if (thongKeFile == NULL) {
        printf("Khong the tao file thong ke.\n");
        fclose(f);  // ÄĂ³ng tá»‡p gá»‘c
        return;
    }

    struct SACH sach;
    char authors[MAX_AUTHORS][50];
    int bookCount[MAX_AUTHORS] = {0};

    int authorCount = 0;

    while (fscanf(f, "\nTen sach: %[^\n]\nTen tac gia: %[^\n]\nNXB: %[^\n]\nNam XB: %d", sach.ten_sach, sach.tac_gia, sach.Nha_XB, &sach.Nam_XB) != EOF) {
        int authorIndex = -1;
        for (int i = 0; i < authorCount; i++) {
            if (strcmp(authors[i], sach.tac_gia) == 0) {
                authorIndex = i;
                break;
            }
        }

        if (authorIndex == -1) {
            strcpy(authors[authorCount], sach.tac_gia);
            authorIndex = authorCount;
            authorCount++;
        }

        bookCount[authorIndex]++;
    }

    for (int i = 0; i < authorCount; i++) {
        fprintf(thongKeFile, "Tac gia: %s, So luong sach: %d\n", authors[i], bookCount[i]);
    }

    fclose(f);
    fclose(thongKeFile);
}

main(){
	struct LIST l;
	List(l);
	bool check = true;
	while (check){
		printf("\n========MENU========");
		printf("\n1. Them danh sach sach");
		printf("\n2. So luong sach cua 1 tac gia");
		printf("\n3. Nhung quyen sach duoc phat hanh cua 1 NXB vao 1 nam");
		printf("\n4. Xoa tat ca sach cua 1 tac gia");
		printf("\n5. Thong ke so luong sach cua moi tac gia");
		printf("\n6. Doc du lieu tu file thong ke so luong sach");
		printf("\n7. Doc du lieu vao tep va dua vao danh sach");
		printf("\n0. Thoat");
		printf("\nVui long chon 1 chuc nang [1-7]. Nhap 0 de ket thuc: ");
		int chon;
		scanf("%d", &chon);
		switch (chon){
			case 1: 
				NhapDSSach(l);
				SaveToFile(l, "quan_ly_sach.txt");
				break;
			case 2: 
				char tac_gia[50];
				printf("Nhap ten tac gia: \n");
				fflush(stdin);
				gets(tac_gia);
				SoLuongSachCua1TacGia(l, tac_gia, "quan_ly_sach.txt");
				break;
			case 3: 
				int nam;
				char Nha_XB[255];
				printf("Nhap nha xuat ban can tim: \n");
				fflush(stdin);
				gets(Nha_XB);
				printf("Nhap nam xuat ban can tim: \n");
				scanf("%d", &nam);
				DSSachTheoNamVaNhaXB(l, nam, Nha_XB, "quan_ly_sach.txt");
				break;
			case 4: 
				char tac_gia1[50];
				printf("Nhap ten tac gia: \n");
				fflush(stdin);
				gets(tac_gia1);
				XoaSach(l, tac_gia1, "quan_ly_sach.txt", "sach_da_xoa.txt");
				break;
			case 5: 
				ThongKeSachTheoTacGia(l, "quan_ly_sach.txt", "thong_ke_sach_theo_tac_gia.txt");
				break;
			case 6: 
				ReadAndDisplayStatistics("thong_ke_sach_theo_tac_gia.txt");
				break;
			case 7: 
				DocDanhSachSachTuFile(l, "quan_ly_sach.txt");
                printf("Doc danh sach tu file thanh cong!\n");
				break;
			case 0: 
				printf("Tam biet!");
				check = false;
				break;
			default:
				printf("Nhap sai. Vui long nhap lai!\n");
				break;
		}

	}
}

