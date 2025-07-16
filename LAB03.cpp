//Bai tap: Quan ly Quan an voi Dat mon theo Ban
//Viet mot chuong trinh C de quan ly quan an voi cac tinh nang sau:
//Nguoi dung co the them ten va gia cua mon an vao thuc don.
//Thuc don toi da co the chua 100 mon an.
//In ra danh sach cac mon an trong thuc don theo dinh dang bang voi cot ten mon an va gia.
//Quan an co toi da 5 ban.
//Nguoi dung co the chon mot ban cu the (tu 1 den 5) va dat mon an cho ban do.
//Nguoi dung co the nhap ten mon an va so luong mon an can dat.
//Neu mon an khong co trong thuc don, thong bao loi se duoc hien thi.
//Khi hoan thanh dat mon, in ra tong so tien cua cac mon an da dat cho ban do.
//In ra danh sach cac mon an da dat va tong so tien cua ban duoc chon.
//Thoat khoi chuong trinh quan ly quan an.
//Menu chinh:
//Them mon an vao thuc don
//Xem thuc don
//Dat mon an cho ban
//Xem don hang cua ban
//Thoat
//Yeu cau:
//Su dung cau truc struct de dinh nghia mon an va don hang.
//Su dung mang de luu tru thuc don va don hang cua tung ban.
//Su dung vong lap va cau dieu kien de thuc hien cac chuc nang.
#include<stdio.h>
#include<string.h>
#define MAXMON 100
#define MAXBAN 5
#define MAXDAT 100
typedef struct {
    char tenmon[50];
    int gia;
} MonAn;
typedef struct {
    char tenmon[50];
    int soluong;
} DatMon;
typedef struct {
    DatMon danhsachdat[MAXDAT];
    int somon;
} DonHang;
MonAn menu[MAXMON];
int somonmenu = 0;
DonHang ban[MAXBAN];
void themmon() {
    if (somonmenu >= MAXMON) {
        printf("Menu da day!\n");
        return;
    }
    printf("Nhap ten mon: ");
    scanf(" %[^\n]", menu[somonmenu].tenmon);
    printf("Nhap gia: ");
    scanf("%d", &menu[somonmenu].gia);
    somonmenu++;
    printf("Da them mon thanh cong!\n");
}
void inmenu() {
    printf("\n********************* MENU*********************\n");
    printf("%-30s | %-10s\n", "Ten mon", "Gia");
    for (int i = 0; i < somonmenu; i++) {
        printf("%-30s | %-10d\n", menu[i].tenmon, menu[i].gia);
    }
}
int timmon(char ten[]) {
    for (int i = 0; i < somonmenu; i++) {
        if (strcmp(menu[i].tenmon, ten) == 0) {
            return i;
        }
    }
    return -1;
}
void datmon() {
    int soban;
    printf("Nhap so ban (1 - %d): ", MAXBAN);
    scanf("%d", &soban);
    if (soban < 1 || soban > MAXBAN) {
        printf("So ban khong hop le!\n");
        return;
    }
    int chon = 1;
    while (chon) {
        char tenmon[50];
        int soluong;
        printf("Nhap ten mon muon dat: ");
        scanf(" %[^\n]", tenmon);
        int vitri = timmon(tenmon);
        if (vitri == -1) {
            printf("Mon an khong co trong menu!\n");
        } else {
            printf("Nhap so luong: ");
            scanf("%d", &soluong);
            DonHang *d = &ban[soban - 1];
            int da_co = 0;
            for (int i = 0; i < d->somon; i++) {
                if (strcmp(d->danhsachdat[i].tenmon, tenmon) == 0) {
                    d->danhsachdat[i].soluong += soluong;
                    da_co = 1;
                    break;
                }
            }
            if (!da_co) {
                strcpy(d->danhsachdat[d->somon].tenmon, tenmon);
                d->danhsachdat[d->somon].soluong = soluong;
                d->somon++;
            }
            printf("Da dat mon thanh cong!\n");
        }
        printf("Ban co muon dat tiep? (1: Co, 0: Khong): ");
        scanf("%d", &chon);
    }
}
void xemdonhang() {
    int soban;
    printf("Nhap so ban muon xem (1 - %d): ", MAXBAN);
    scanf("%d", &soban);
    if (soban < 1 || soban > MAXBAN) {
        printf("So ban khong hop le!\n");
        return;
    }
    DonHang *d = &ban[soban - 1];
    if (d->somon == 0) {
        printf("Ban chua dat mon nao.\n");
        return;
    }
    int tongtien = 0;
    printf("\n--- DON HANG BAN %d ---\n", soban);
    printf("%-30s | %-10s | %-10s\n", "Ten mon", "So luong", "Thanh tien");
    for (int i = 0; i < d->somon; i++) {
        int vitri = timmon(d->danhsachdat[i].tenmon);
        int tien = d->danhsachdat[i].soluong * menu[vitri].gia;
        printf("%-30s | %-10d | %-10d\n", d->danhsachdat[i].tenmon, d->danhsachdat[i].soluong, tien);
        tongtien += tien;
    }
    printf("Tong tien: %d\n", tongtien);
}
int main() {
    int chon;
    do {
        printf("\n*********************QUAN LY QUAN AN*********************\n");
        printf("1. Them mon an vao menu\n");
        printf("2. Xem menu\n");
        printf("3. Dat mon an cho ban\n");
        printf("4. Xem don hang cua ban\n");
        printf("5. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &chon);
        switch (chon) {
            case 1: 
		themmon(); break;
            case 2: 
		inmenu(); break;
            case 3:
		datmon(); break;
            case 4: 
		xemdonhang(); break;
            case 5: 
		printf("Ban da thoat khoi chuong trinh!\n"); break;
            default: 
		printf("Lua chon khong hop le!\n");
        }
    } while (chon != 5);
    return 0;
}

