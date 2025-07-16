#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// a. 
void CapPhat1(int n, int **&a) {
    a = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        a[i] = (int *)malloc(n * sizeof(int));
}

int **CapPhat2(int n) {
    int **a = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        a[i] = (int *)malloc(n * sizeof(int));
    return a;
}

// b. 
void XoaBN(int n, int **a) {
    for (int i = 0; i < n; i++)
        free(a[i]);
    free(a);
}

// c. 
void Nhap(int *n, int **&a) {
    printf("Nhap cap cua ma tran vuong: ");
    scanf("%d", n);
    CapPhat1(*n, a);
    printf("Nhap cac phan tu cua ma tran:\n");
    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *n; j++) {
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
        }
}

// d. 
void Xuat(int n, int **a) {
    printf("Ma tran: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d", a[i][j]);
        printf("\n");
    }
}

// e. 
int DoiXungPhu(int n, int **a) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[i][j] != a[n - j - 1][n - i - 1])
                return 0;
    return 1;
}

// f.
void LietKe(int n, int **a) {
    int max = INT_MIN;
    int *tong = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        tong[i] = 0;
        for (int j = 0; j < n; j++)
            tong[i] += a[i][j];
        if (tong[i] > max) max = tong[i];
    }

    printf("Cac hang co tong lon nhat (max = %d):\n", max);
    for (int i = 0; i < n; i++)
        if (tong[i] == max) {
            printf("Hang %d: ", i);
            for (int j = 0; j < n; j++)
                printf("%4d", a[i][j]);
            printf("\n");
        }
    free(tong);
}

// g. Menu
int Menu() {
    int options;
    printf("\n===== MENU =====\n");
    printf("1. Nhap ma tran\n");
    printf("2. Xuat ma tran\n");
    printf("3. Kiem tra doi xung duong cheo phu\n");
    printf("4. Liet ke hang co tong max\n");
    printf("5. Thoat\n");
    printf("Chon: ");
    scanf("%d", &options);
    return options;
}

// main
int main() {
    int **a = NULL, n = 0, options;
    do {
        options = Menu();
        switch (options) {
            case 1:
                if (a != NULL)
                    XoaBN(n, a);
                Nhap(&n, a);
                break;
            case 2:
                if (a != NULL)
                    Xuat(n, a);
                else
                    printf("Chua nhap ma tran.\n");
                break;
            case 3:
                if (a != NULL)
                    if (DoiXungPhu(n, a))
                        printf("Ma tran doi xung qua duong cheo phu.\n");
                    else
                        printf("Ma tran KHONG doi xung.\n");
                else
                    printf("Chua nhap ma tran.\n");
                break;
            case 4:
                if (a != NULL)
                LietKe(n, a);
                else
                    printf("Chua nhap ma tran.\n");
                break;
            case 5:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (options != 5);
    if (a != NULL)
        XoaBN(n, a);
    return 0;
}
