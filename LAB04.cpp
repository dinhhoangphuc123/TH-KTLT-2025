#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h> 
#define MAX_LEN 100
// Ham an mat khau khi nhap
void nhapMatKhau(char *password) {
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == 13) { // Enter
            break;
        } else if (ch == 8 && i > 0) { // Backspace
            printf("\b \b");
            i--;
        } else if (i < MAX_LEN - 1 && ch >= 32 && ch <= 126) {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}

// Ham kiem tra mat khau hop le
int kiemTraMatKhau(const char *password) {
    int coHoa = 0, coThuong = 0, coSo = 0;
    if (strlen(password) < 8)
        return 0;
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) coHoa = 1;
        if (islower(password[i])) coThuong = 1;
        if (isdigit(password[i])) coSo = 1;
    }
    return coHoa && coThuong && coSo;
}

// Ham dang ky
void dangKy() {
    char *ten = (char *)malloc(MAX_LEN);
    char *matkhau = (char *)malloc(MAX_LEN);
    char *xacnhan = (char *)malloc(MAX_LEN);

    printf("Dang ky tai khoan\n");
    do {
        printf("Nhap ten dang nhap (>=5 ky tu): ");
        fgets(ten, MAX_LEN, stdin);
        ten[strcspn(ten, "\n")] = '\0'; // xoa '\n'
    } while (strlen(ten) < 5);

    do {
        printf("Nhap mat khau (>=8 ky tu, co hoa, thuong, so): ");
        nhapMatKhau(matkhau);

        if (!kiemTraMatKhau(matkhau)) {
            printf("Mat khau khong hop le. Vui long thu lai.\n");
            continue;
        }

        printf("Nhap lai mat khau: ");
        nhapMatKhau(xacnhan);

        if (strcmp(matkhau, xacnhan) != 0) {
            printf("Mat khau khong khop. Vui long thu lai.\n");
        }

    } while (!kiemTraMatKhau(matkhau) || strcmp(matkhau, xacnhan) != 0);

    FILE *f = fopen("account.txt", "w");
    if (f != NULL) {
        fprintf(f, "%s\n%s\n", ten, matkhau);
        fclose(f);
        printf("Dang ky thanh cong!\n");
    } else {
        printf("Loi mo tap tin.\n");
    }

    free(ten);
    free(matkhau);
    free(xacnhan);
}

// Ham dang nhap
void dangNhap() {
    char *ten = (char *)malloc(MAX_LEN);
    char *matkhau = (char *)malloc(MAX_LEN);
    char fileTen[MAX_LEN], fileMatkhau[MAX_LEN];
    int lanThu = 0;

    FILE *f = fopen("account.txt", "r");
    if (f == NULL) {
        printf("Khong tim thay tai khoan. Vui long dang ky truoc.\n");
        free(ten); free(matkhau);
        return;
    }
    fgets(fileTen, MAX_LEN, f);
    fgets(fileMatkhau, MAX_LEN, f);
    fileTen[strcspn(fileTen, "\n")] = '\0';
    fileMatkhau[strcspn(fileMatkhau, "\n")] = '\0';
    fclose(f);

    printf("\nDang nhap\n");
    while (lanThu < 3) {
        printf("Nhap ten dang nhap: ");
        fgets(ten, MAX_LEN, stdin);
        ten[strcspn(ten, "\n")] = '\0';

        printf("Nhap mat khau: ");
        nhapMatKhau(matkhau);

        if (strcmp(ten, fileTen) == 0 && strcmp(matkhau, fileMatkhau) == 0) {
            printf("Dang nhap thanh cong!\n");
            break;
        } else {
            printf("Sai ten dang nhap hoac mat khau. Thu lai.\n");
            lanThu++;
        }
    }

    if (lanThu == 3) {
        printf("Ban da thu qua 3 lan. Dang nhap that bai.\n");
    }

    free(ten);
    free(matkhau);
}

// Ham main
int main() {
    int luaChon;
    do {
        printf("\n**************MENU**************\n");
        printf("1. Dang ky\n");
        printf("2. Dang nhap\n");
        printf("0. Thoat\n");
        printf("Lua chon: ");
        scanf("%d", &luaChon);
        getchar(); // loai bo '\n'

        switch (luaChon) {
            case 1: dangKy(); break;
            case 2: dangNhap(); break;
            case 0: printf("Ban da thoat khoi chuong trinh!\n"); break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (luaChon != 0);

    return 0;
}

