//Lam viec voi ma tran vuong: Viet cac ham sau lam viec voi ma tran nguyen vuong co su dung
//cap phat bo nho dong cho mang hai chieu thong qua toan tu new hoac ham calloc hay malloc.
//a. Ham cap phat bo nho dong:
//Mau ham : void CapPhat1(int n, int **&a);
//Hoac mau ham int **CapPhat2(int n);
//Cap phat bo nho cho con tro hai chieu doi voi ham CapPhat2 tra ve con tro da duoc cap phat.
//b. Ham giai phong bo nho co mau ham void XoaBN(int n, int **a).
//c. Nhap ma tran vuong tu ban phim:
//Mau ham : void Nhap(int &n, int **&a);
//Goi ham cap phat de cap phat dong cho con tro a.
//Nhap du lieu tu ban phim.
//d. Xuat ma tran ra man hinh dang bang co:
//Mau ham void Xuat(int n, int **a).
//e. Kiem tra ma tran co doi xung qua duong cheo phu khong?
//Mau ham : int DoiXungPhu(int n, int **a);
//Ham tra ve 0 neu khong doi xung va 1 neu nguoc lai.
//f. Liet ke cac hang co tong max:
//Mau ham : void LietKe(int n, int **a).
//g. Viet ham menu sau do la ham main thuc hien cac thao tac:
//Mau ham : int Menu();
//Ham tra ve gia tri menu neu duoc chon trong [1…5]:
//Nhap ma tran
//Xuat ma tran
//Kiem tra doi xung
//Liet ke cac hang co tong max
//Thoat.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
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
void XoaBN(int n, int **a) {
    for (int i = 0; i < n; i++)
        free(a[i]);
    free(a);
}
void Nhap(int &n, int **&a) {
    printf("Nhap cap cua ma tran vuong: ");
    scanf("%d", &n);

    // Cap phat dong cho ma tran
    CapPhat1(n, a);

    printf("Nhap cac phan tu cua ma tran:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
        }
}

// d. Xuat ma tran ra man hinh dang bang co
void Xuat(int n, int **a) {
    printf("Ma tran:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d", a[i][j]);
        printf("\n");
    }
}

// e. Kiem tra ma tran co doi xung qua duong cheo phu khong?
int DoiXungPhu(int n, int **a) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[i][j] != a[n - j - 1][n - i - 1]){
            	return 0;
			}
                
    return 1;
}

// f. Liet ke cac hang co tong max
void LietKe(int n, int **a) {
    int *tong = (int *)malloc(n * sizeof(int));
    int max = INT_MIN;
    for (int i = 0; i < n; i++) {
        tong[i] = 0;
        for (int j = 0; j < n; j++)
            tong[i] += a[i][j];
        if (tong[i] > max)
            max = tong[i];
    }

    printf("Cac hang co tong lon nhat (tong = %d):\n", max);
    for (int i = 0; i < n; i++) {
        if (tong[i] == max) {
            printf("Hang %d: ", i);
            for (int j = 0; j < n; j++)
                printf("%4d", a[i][j]);
            printf("\n");
        }
    }

    free(tong);
}

// g. Ham menu
int Menu() {
    int chon;
    printf("\n========= MENU =========\n");
    printf("1. Nhap ma tran\n");
    printf("2. Xuat ma tran\n");
    printf("3. Kiem tra doi xung qua duong cheo phu\n");
    printf("4. Liet ke cac hang co tong max\n");
    printf("5. Thoat\n");
    printf("Moi ban chon: ");
    scanf("%d", &chon);
    return chon;
}

// Ham chinh
int main() {
    int **a = NULL;
    int n = 0;
    int luaChon;

    do {
        luaChon = Menu();
        switch (luaChon) {
            case 1:
                if (a != NULL)
                    XoaBN(n, a); // Giai phong cu truoc khi nhap moi
                Nhap(n, a);
                break;
            case 2:
                if (a != NULL)
                    Xuat(n, a);
                else
                    printf("Chua nhap ma tran!\n");
                break;
            case 3:
                if (a != NULL) {
                    if (DoiXungPhu(n, a))
                        printf("Ma tran doi xung qua duong cheo phu.\n");
                    else
                        printf("Ma tran KHONG doi xung.\n");
                } else {
                    printf("Chua nhap ma tran!\n");
                }
                break;
            case 4:
                if (a != NULL)
                    LietKe(n, a);
                else
                    printf("Chua nhap ma tran!\n");
                break;
            case 5:
                printf("Dang thoat chuong trinh...\n");
                break;
            default:
                printf("Lua chon khong hop le. Moi chon lai!\n");
        }
    } while (luaChon != 5);

    if (a != NULL)
        XoaBN(n, a);

    return 0;
}

