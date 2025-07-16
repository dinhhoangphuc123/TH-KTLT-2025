#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Khai bao cau truc SinhVien
typedef struct SinhVien {
    char mssv[100];
    char hoTen[100];
    float diem;
    struct SinhVien* next;
} SinhVien;

// Ham them sinh vien vao danh sach theo thu tu MSSV
void ThemSinhVien(SinhVien** dau) {
    SinhVien* svMoi = (SinhVien*)malloc(sizeof(SinhVien));
    printf("Nhap MSSV: ");
    getchar();
    fgets(svMoi->mssv, sizeof(svMoi->mssv), stdin);
    svMoi->mssv[strcspn(svMoi->mssv, "\n")] = 0;
    
    printf("Nhap ho ten: ");
    fgets(svMoi->hoTen, sizeof(svMoi->hoTen), stdin);
    svMoi->hoTen[strcspn(svMoi->hoTen, "\n")] = 0;
    
    printf("Nhap diem: ");
    scanf("%f", &svMoi->diem);
    getchar();
    svMoi->next = NULL;

    // Chen vao danh sach theo thu tu MSSV
    if (*dau == NULL || strcmp(svMoi->mssv, (*dau)->mssv) < 0) {
        svMoi->next = *dau;
        *dau = svMoi;
    } else {
        SinhVien* p = *dau;
        while (p->next != NULL && strcmp(p->next->mssv, svMoi->mssv) < 0) {
            p = p->next;
        }
        svMoi->next = p->next;
        p->next = svMoi;
    }
}

// Hien thi danh sach sinh vien
void HienThiDanhSach(SinhVien* dau) {
    printf("\nDanh sach sinh vien:\n");
    while (dau != NULL) {
        printf("MSSV: %s, Ho ten: %s, Diem: %.2f\n", dau->mssv, dau->hoTen, dau->diem);
        dau = dau->next;
    }
}

// Tim sinh vien theo MSSV
SinhVien* TimTheoMssv(SinhVien* dau, char mssv[]) {
    while (dau != NULL) {
        if (strcmp(dau->mssv, mssv) == 0) return dau;
        dau = dau->next;
    }
    return NULL;
}

// Xoa sinh vien theo MSSV
void XoaTheoMssv(SinhVien** dau, char mssv[]) {
    SinhVien* p = *dau;
    SinhVien* truoc = NULL;
    while (p != NULL && strcmp(p->mssv, mssv) != 0) {
        truoc = p;
        p = p->next;
    }
    if (p == NULL) {
        printf("Khong tim thay MSSV de xoa\n");
        return;
    }
    if (truoc == NULL) *dau = p->next;
    else truoc->next = p->next;
    free(p);
    printf("Da xoa sinh vien co MSSV %s\n", mssv);
}

// Tim sinh vien co diem cao nhat
void TimDiemCaoNhat(SinhVien* dau) {
    if (dau == NULL) {
        printf("Danh sach rong\n");
        return;
    }
    float max = dau->diem;
    SinhVien* p = dau;
    while (p != NULL) {
        if (p->diem > max) max = p->diem;
        p = p->next;
    }
    printf("Sinh vien co diem cao nhat:\n");
    p = dau;
    while (p != NULL) {
        if (p->diem == max)
            printf("MSSV: %s, Ho ten: %s, Diem: %.2f\n", p->mssv, p->hoTen, p->diem);
        p = p->next;
    }
}

// Cap nhat thong tin sinh vien theo MSSV
void CapNhatSinhVien(SinhVien* dau, char mssv[]) {
    SinhVien* sv = TimTheoMssv(dau, mssv);
    if (sv == NULL) {
        printf("Khong tim thay sinh vien\n");
        return;
    }
    printf("Nhap ho ten moi: ");
    char hoTenMoi[100];
    fgets(hoTenMoi, sizeof(hoTenMoi), stdin);
    hoTenMoi[strcspn(hoTenMoi, "\n")] = 0;
    if (strlen(hoTenMoi) > 0) strcpy(sv->hoTen, hoTenMoi);

    printf("Nhap diem moi (-1 neu khong thay doi): ");
    float diemMoi;
    scanf("%f", &diemMoi);
    getchar();
    if (diemMoi >= 0) sv->diem = diemMoi;
}

// Tim sinh vien trong khoang diem
void TimTheoKhoangDiem(SinhVien* dau, float min, float max) {
    printf("Sinh vien trong khoang diem %.2f - %.2f:\n", min, max);
    while (dau != NULL) {
        if (dau->diem >= min && dau->diem <= max)
            printf("MSSV: %s, Ho ten: %s, Diem: %.2f\n", dau->mssv, dau->hoTen, dau->diem);
        dau = dau->next;
    }
}

// Ghi danh sach sinh vien vao file van ban
void GhiFile(SinhVien* dau, char tenFile[]) {
    FILE* f = fopen(tenFile, "w");
    if (f == NULL) {
        printf("Khong mo duoc file de ghi\n");
        return;
    }
    while (dau != NULL) {
        fprintf(f, "%s|%s|%.2f\n", dau->mssv, dau->hoTen, dau->diem);
        dau = dau->next;
    }
    fclose(f);
    printf("Da ghi danh sach vao file van ban.\n");
}

// Doc danh sach sinh vien tu file van ban
void DocFile(SinhVien** dau, char tenFile[]) {
    FILE* f = fopen(tenFile, "r");
    if (f == NULL) {
        printf("Khong mo duoc file de doc\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        SinhVien* svMoi = (SinhVien*)malloc(sizeof(SinhVien));
        svMoi->next = NULL;
        sscanf(line, "%[^|]|%[^|]|%f", svMoi->mssv, svMoi->hoTen, &svMoi->diem);

        // Chen vao danh sach theo thu tu MSSV
        if (*dau == NULL || strcmp(svMoi->mssv, (*dau)->mssv) < 0) {
            svMoi->next = *dau;
            *dau = svMoi;
        } else {
            SinhVien* p = *dau;
            while (p->next != NULL && strcmp(p->next->mssv, svMoi->mssv) < 0) {
                p = p->next;
            }
            svMoi->next = p->next;
            p->next = svMoi;
        }
    }

    fclose(f);
    printf("Da doc danh sach tu file van ban.\n");
}

// Hien thi menu lua chon
void Menu() {
    printf("\n===== MENU =====\n");
    printf("1. Them sinh vien\n");
    printf("2. Hien thi danh sach\n");
    printf("3. Tim theo MSSV\n");
    printf("4. Xoa sinh vien\n");
    printf("5. Tim diem cao nhat\n");
    printf("6. Cap nhat sinh vien\n");
    printf("7. Tim theo khoang diem\n");
    printf("8. Ghi file (.txt)\n");
    printf("9. Doc file (.txt)\n");
    printf("0. Thoat\n");
}

// Ham main
int main() {
    SinhVien* danhSach = NULL;
    int luaChon;
    char mssv[100];
    float min, max;

    do {
        Menu();
        printf("Nhap lua chon: ");
        scanf("%d", &luaChon);
        getchar();
        switch (luaChon) {
            case 1:
                ThemSinhVien(&danhSach); break;
            case 2:
                HienThiDanhSach(danhSach); break;
            case 3:
                printf("Nhap MSSV: ");
                fgets(mssv, sizeof(mssv), stdin);
                mssv[strcspn(mssv, "\n")] = 0;
                {
                    SinhVien* sv = TimTheoMssv(danhSach, mssv);
                    if (sv)
                        printf("Tim thay: %s - %s - %.2f\n", sv->mssv, sv->hoTen, sv->diem);
                    else
                        printf("Khong tim thay sinh vien.\n");
                }
                break;
            case 4:
                printf("Nhap MSSV can xoa: ");
                fgets(mssv, sizeof(mssv), stdin);
                mssv[strcspn(mssv, "\n")] = 0;
                XoaTheoMssv(&danhSach, mssv);
                break;
            case 5:
                TimDiemCaoNhat(danhSach); break;
            case 6:
                printf("Nhap MSSV can cap nhat: ");
                fgets(mssv, sizeof(mssv), stdin);
                mssv[strcspn(mssv, "\n")] = 0;
                CapNhatSinhVien(danhSach, mssv);
                break;
            case 7:
                printf("Nhap diem min: "); scanf("%f", &min);
                printf("Nhap diem max: "); scanf("%f", &max);
                getchar();
                TimTheoKhoangDiem(danhSach, min, max);
                break;
            case 8:
                GhiFile(danhSach, "sinhvien.txt"); break;
            case 9:
                DocFile(&danhSach, "sinhvien.txt"); break;
            case 0:
                printf("Ket thuc chuong trinh\n"); break;
            default:
                printf("Lua chon khong hop le\n");
        }
    } while (luaChon != 0);

    return 0;
}


