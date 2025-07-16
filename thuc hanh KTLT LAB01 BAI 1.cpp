//a. Ham nhap vao mot day n so thuc thoa man:
//Mau ham: int Nhap(float **a);
//Ham tra ve so phan tu nhap vao mang
//Than ham cap phat bo nho cho con tro (VD: *a = new float[n + 1];)
//b. Ham tim max cua nhung phan tu duong (neu co):
//Mau ham: int MaxDuong(int n, float *a, float *max);
//Ham tra ve 0 neu mang khong co so duong va 1 neu nguoc lai
//Truyen gia tri ra qua tham bien con tro float *max
//c. Kiem tra day vua nhap co tinh chat Fibonaccy khong
//Tuc la tu a3 tro di deu phai bang tong 2 so dung truoc no
//Mau ham: int Fibo(int n, float *a);
//Ham tra ve 0 neu mang khong co tinh chat va 1 neu nguoc lai
//d. Viet ham menu sau do la ham main thuc hien cac thao tac
//Mau ham: int Menu();
//Ham tra ve gia tri menu neu duoc chon trong [1…5]
//markdown
//Sao chep
//Chinh sua  
//1. Nhap day  
//2. Xuat day  
//3. Tim max duong  
//4. Kiem tra tinh Fibonacci  
//5. Thoat
#include<stdio.h> 
#include<math.h> 
#include <stdlib.h>
int Nhap(float **a) {
    int n;
    printf("Nhap so luong phan tu: ");
    scanf("%d", &n);
    *a = (float *)malloc((n + 1) * sizeof(float));
    if (*a == NULL) {
        printf("Khong du bo nho!\n");
        return 0;
    }
    printf("Nhap %d phan tu:\n", n);
    for (int i = 0; i < n; i++) {
        printf("a[%d] = ", i);
        scanf("%f", &(*a)[i]);
    }
    return n;
}
void Xuat(int n, float *a) {
    if (n == 0 || a == NULL) {
        printf("Chua co du lieu de xuat!\n");
        return;
    }

    printf("Day vua nhap: ");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", a[i]);
    }
    printf("\n");
}

int MaxDuong(int n, float *a, float *max) {
    int soDuong = 0;
    *max = -1e9; 
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            if (a[i] > *max) {
                *max = a[i];
            }
            soDuong = 1;
        }
    }
    return soDuong; 
}
int Fibonacci(int n, float *a) {
    if (n < 3) {
        return 1; 
    }
    for (int i = 2; i < n; i++) {
        if (a[i] != a[i - 1] + a[i - 2]) {
            return 0; 
        }
    }
    return 1; 
}
int Menu() {
    int choice;
    printf("\n*****************************************\n");
    printf("1. Nhap day\n");
    printf("2. Xuat day\n");
    printf("3. Tim max duong\n");
    printf("4. Kiem tra tinh Fibonacci\n");
    printf("5. Thoat\n");
    printf("Moi ban chon cac thao tac thich hop: ");
    scanf("%d", &choice);
    return choice;
}
int main() {
    float *a = NULL;
    int n = 0;
    int choice;
    float max;
    do {
        choice = Menu();
        switch (choice) {
            case 1:
                n= Nhap(&a);
                break;
            case 2:
                Xuat(n,a); 
                break;
            case 3:
                if (MaxDuong(n, a, &max)) {
                    printf("Max so duong trong day la: %.2f\n", max);
                } else {
                    printf("Khong co so duong trong day so tren\n");
                }
                break;
            case 4:
                if (Fibonacci(n, a)) {
                    printf("Day so tren thoa man tinh chat Fibonacci\n");
                } else {
                    printf("Day so tren khong thoa man tinh chat Fibonacci\n");
                }
                break;
            case 5:
                printf("Ban da thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon cua ban khong hop le.\n");
        }
    } while (choice != 5);
    free(a); 
    return 0;
}

