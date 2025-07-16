#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct MonAn {
    char ten[50];
    float gia;
    struct MonAn *next;
} MonAn;
typedef struct DonHang {
    char ten[50];
    int soLuong;
    float tongTien;
    struct DonHang *next;
} DonHang;
typedef struct BanAn {
    int soBan;
    DonHang *donHang;
} BanAn;
MonAn *thucDon = NULL;
BanAn **danhSachBan = NULL;
void khoiTaoBanAn() {
    danhSachBan = (BanAn **)malloc(5 * sizeof(BanAn *));
    for (int i = 0; i < 5; i++) {
        danhSachBan[i] = (BanAn *)malloc(sizeof(BanAn));
        danhSachBan[i]->soBan = i + 1;
        danhSachBan[i]->donHang = NULL;
    }
}
void themMonAn() {
    MonAn *monMoi = (MonAn *)malloc(sizeof(MonAn));
    if (!monMoi) {
        printf("Khong du bo nho!\n");
        return;
    }

    printf("Nhap ten mon an: ");
    scanf(" %[^\n]", monMoi->ten);
    printf("Nhap gia mon an: ");
    scanf("%f", &monMoi->gia);
    monMoi->next = NULL;

    if (thucDon == NULL) {
        thucDon = monMoi;
    } else {
        MonAn *temp = thucDon;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = monMoi;
    }

    printf("Mon an da duoc them vao thuc don!\n");
}

void inThucDon() {
    if (thucDon == NULL) {
        printf("Thuc don trong!\n");
        return;
    }

    printf("\nThuc don:\n");
    MonAn *temp = thucDon;
    while (temp != NULL) {
        printf("%-30s %10.2f\n", temp->ten, temp->gia);
        temp = temp->next;
    }
}

void datMonAn(int soBan) {
    if (soBan < 1 || soBan > 5) {
        printf("So ban khong hop le! Vui long chon tu 1 den 5.\n");
        return;
    }

    char tenMonAn[50];
    int soLuong;
    MonAn *timMonAn = thucDon;

    printf("Nhap ten mon an: ");
    scanf(" %[^\n]", tenMonAn);
    printf("Nhap so luong: ");
    scanf("%d", &soLuong);

    while (timMonAn != NULL && strcmp(timMonAn->ten, tenMonAn) != 0) {
        timMonAn = timMonAn->next;
    }

    if (timMonAn == NULL) {
        printf("Mon an khong co trong thuc don!\n");
        return;
    }

    DonHang *donMoi = (DonHang *)malloc(sizeof(DonHang));
    strcpy(donMoi->ten, tenMonAn);
    donMoi->soLuong = soLuong;
    donMoi->tongTien = timMonAn->gia * soLuong;
    donMoi->next = NULL;

    BanAn *ban = danhSachBan[soBan - 1];
    if (ban->donHang == NULL) {
        ban->donHang = donMoi;
    } else {
        DonHang *temp = ban->donHang;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = donMoi;
    }

    printf("Da dat mon thanh cong cho ban %d!\n", soBan);
}

void xemDonHang(int soBan) {
    if (soBan < 1 || soBan > 5) {
        printf("So ban khong hop le! Vui long chon tu 1 den 5.\n");
        return;
    }

    DonHang *temp = danhSachBan[soBan - 1]->donHang;
    if (temp == NULL) {
        printf("Ban %d chua co don hang!\n", soBan);
        return;
    }

    printf("\nDon hang cua ban %d:\n", soBan);
    float tongTien = 0;
    while (temp != NULL) {
        printf("%-30s %5d %10.2f\n", temp->ten, temp->soLuong, temp->tongTien);
        tongTien += temp->tongTien;
        temp = temp->next;
    }
    printf("Tong tien: %.2f\n", tongTien);
}

void giaiPhongBoNho() {
    while (thucDon != NULL) {
        MonAn *temp = thucDon;
        thucDon = thucDon->next;
        free(temp);
    }

    for (int i = 0; i < 5; i++) {
        while (danhSachBan[i]->donHang != NULL) {
            DonHang *temp = danhSachBan[i]->donHang;
            danhSachBan[i]->donHang = danhSachBan[i]->donHang->next;
            free(temp);
        }
        free(danhSachBan[i]);
    }

    free(danhSachBan);
}

int main() {
    khoiTaoBanAn();
    int luaChon, soBan;

    while (1) {
        printf("\n===== Quan Ly Quan An =====\n");
        printf("1. Them mon an vao thuc don\n");
        printf("2. Xem thuc don\n");
        printf("3. Dat mon an cho ban\n");
        printf("4. Xem don hang cua ban\n");
        printf("5. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &luaChon);

        if (luaChon == 1) {
            themMonAn();
        } else if (luaChon == 2) {
            inThucDon();
        } else if (luaChon == 3) {
            printf("Nhap so ban (1-5): ");
            scanf("%d", &soBan);
            datMonAn(soBan);
        } else if (luaChon == 4) {
            printf("Nhap so ban (1-5): ");
            scanf("%d", &soBan);
            xemDonHang(soBan);
        } else if (luaChon == 5) {
            printf("Thoat chuong trinh.\n");
            giaiPhongBoNho();
            break;
        } else {
            printf("Lua chon khong hop le! Vui long nhap so tu 1 den 5.\n");
        }
    }

    return 0;
}
