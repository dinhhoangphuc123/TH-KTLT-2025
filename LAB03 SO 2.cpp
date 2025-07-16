#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SinhVien {
    char mssv[500];
    char ten[100];
    float diem;
    struct SinhVien* tiep;
} SinhVien;
// Ham tao node moi
SinhVien* taoNode(char* mssv, char* ten, float diem) {
    SinhVien* sv = (SinhVien*)malloc(sizeof(SinhVien));
    strcpy(sv->mssv, mssv);
    strcpy(sv->ten, ten);
    sv->diem = diem;
    sv->tiep = NULL;
    return sv;
}

// Ham them sinh vien vao danh sach
void themSinhVien(SinhVien** dauDanhSach) {
    char mssv[10], ten[50];
    float diem;

    printf("Nhap MSSV: ");
    scanf("%s", mssv);
    printf("Nhap ten: ");
    scanf(" %[^\n]", ten);
    printf("Nhap diem: ");
    scanf("%f", &diem);

    SinhVien* sv = taoNode(mssv, ten, diem);
    sv->tiep = *dauDanhSach;
    *dauDanhSach = sv;
}

// Ham hien thi danh sach sinh vien
void hienThiDanhSach(SinhVien* dauDanhSach) {
    SinhVien* p = dauDanhSach;
    while (p != NULL) {
        printf("MSSV: %s, Ten: %s, Diem: %.2f\n", p->mssv, p->ten, p->diem);
        p = p->tiep;
    }
}

// Ham sao chep node
SinhVien* saoChepNode(SinhVien* sv) {
    return taoNode(sv->mssv, sv->ten, sv->diem);
}

// Ham tach danh sach thanh dat va khong dat
void tachDanhSach(SinhVien* dauDanhSach, SinhVien** danhSachDat, SinhVien** danhSachKhongDat) {
    while (dauDanhSach != NULL) {
        SinhVien* svMoi = saoChepNode(dauDanhSach);
        if (dauDanhSach->diem < 5.0) {
            svMoi->tiep = *danhSachKhongDat;
            *danhSachKhongDat = svMoi;
        } else {
            svMoi->tiep = *danhSachDat;
            *danhSachDat = svMoi;
        }
        dauDanhSach = dauDanhSach->tiep;
    }
}

// Ham ghi danh sach vao file
void ghiDanhSachRaFile(SinhVien* dauDanhSach, char* tenTep) {
    FILE* f = fopen(tenTep, "w");
    while (dauDanhSach != NULL) {
        fprintf(f, "%s,%s,%.2f\n", dauDanhSach->mssv, dauDanhSach->ten, dauDanhSach->diem);
        dauDanhSach = dauDanhSach->tiep;
    }
    fclose(f);
}

// Ham dem so sinh vien trong danh sach
int demSoLuong(SinhVien* dauDanhSach) {
    int dem = 0;
    while (dauDanhSach != NULL) {
        dem++;
        dauDanhSach = dauDanhSach->tiep;
    }
    return dem;
}

// Ham sap xep danh sach theo diem tang dan
void sapXepTheoDiem(SinhVien* dauDanhSach) {
    if (!dauDanhSach) return;
    for (SinhVien* p = dauDanhSach; p->tiep != NULL; p = p->tiep) {
        for (SinhVien* q = p->tiep; q != NULL; q = q->tiep) {
            if (p->diem > q->diem) {
                float tmp_diem = p->diem;
                p->diem = q->diem;
                q->diem = tmp_diem;

                char tmp_mssv[10], tmp_ten[50];
                strcpy(tmp_mssv, p->mssv);
                strcpy(tmp_ten, p->ten);
                strcpy(p->mssv, q->mssv);
                strcpy(p->ten, q->ten);
                strcpy(q->mssv, tmp_mssv);
                strcpy(q->ten, tmp_ten);
            }
        }
    }
}
int main() {
    SinhVien* danhSachGoc = NULL;
    SinhVien *danhSachDat = NULL, *danhSachKhongDat = NULL;

    int n;
    printf("Nhap so sinh vien: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("\nSinh vien thu %d:\n", i + 1);
        themSinhVien(&danhSachGoc);
    }

    printf("\nDanh sach GOC:\n");
    hienThiDanhSach(danhSachGoc);

    tachDanhSach(danhSachGoc, &danhSachDat, &danhSachKhongDat);

    printf("\nDanh sach KHONG DAT:\n");
    hienThiDanhSach(danhSachKhongDat);
    printf("\nDanh sach DAT:\n");
    hienThiDanhSach(danhSachDat);

    // Sap xep va ghi file
    sapXepTheoDiem(danhSachKhongDat);
    sapXepTheoDiem(danhSachDat);
    ghiDanhSachRaFile(danhSachKhongDat, "khongdat.txt");
    ghiDanhSachRaFile(danhSachDat, "dat.txt");

    // Tinh ti le
    int tong = demSoLuong(danhSachGoc);
    int soDat = demSoLuong(danhSachDat);
    int soKhongDat = demSoLuong(danhSachKhongDat);

    float tyLeDat = (float)soDat / tong * 100.0;
    float tyLeKhongDat = (float)soKhongDat / tong * 100.0;

    printf("\nTy le dat: %.2f%%\n", tyLeDat);
    printf("Ty le khong dat: %.2f%%\n", tyLeKhongDat);

    return 0;
}

