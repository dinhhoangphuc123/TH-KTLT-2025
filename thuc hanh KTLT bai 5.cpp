//Tao danh sach lien ket don, moi Node chua mot he so va mot luy thua cua da thuc.
//Vi du:
//Da thuc 3x^3 - 4 se duoc luu thanh:
//[(3,3) ; (-4,0) ; NULL]
//(nghia la he so 3, luy thua 3; he so -4, luy thua 0)
//Nhap gia tri x, tinh:
//Gia tri cua da thuc tai x
//Dao ham cua da thuc tai x
//Tao 2 da thuc thong qua 2 danh sach lien ket don
//Tinh tong cua 2 da thuc do
// Danh sach lien ket don cho da thuc va cac phep tinh lien quan
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Dinh nghia cau truc Node
typedef struct Node {
    int heSo;
    int luyThua;
    struct Node* next;
} Node;
// Tao mot Node moi
Node* taoNode(int heSo, int luyThua) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Khong the cap phat bo nho!\n");
        exit(1);
    }
    newNode->heSo = heSo;
    newNode->luyThua = luyThua;
    newNode->next = NULL;
    return newNode;
}
// Them Node vao cuoi danh sach
void themNode(Node** dau, int heso, int luythua) {
    Node* newNode = taoNode(heso, luythua);
    if (*dau == NULL) {
        *dau = newNode;
        return;
    }
    Node* temp = *dau;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}
// Tinh gia tri da thuc tai x
double tinhGiaTri(Node* dau, double x) {
    double ketQua = 0.0;
    while (dau != NULL) {
        ketQua += dau->heSo * pow(x, dau->luyThua);
        dau = dau->next;
    }
    return ketQua;
}
// Tinh dao ham da thuc tai x
double tinhDaoHam(Node* dau, double x) {
    double ketQua = 0.0;
    while (dau != NULL) {
        if (dau->luyThua != 0)
            ketQua += dau->heSo * dau->luyThua * pow(x, dau->luyThua - 1);
        dau = dau->next;
    }
    return ketQua;
}
// Cong hai da thuc
Node* congDaThuc(Node* p1, Node* p2) {
    Node* ketQua = NULL;
    while (p1 != NULL && p2 != NULL) {
        if (p1->luyThua > p2->luyThua) {
            themNode(&ketQua, p1->heSo, p1->luyThua);
            p1 = p1->next;
        } else if (p1->luyThua < p2->luyThua) {
            themNode(&ketQua, p2->heSo, p2->luyThua);
            p2 = p2->next;
        } else {
            int tongHeso = p1->heSo + p2->heSo;
            if (tongHeso != 0)
                themNode(&ketQua, tongHeso, p1->luyThua);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while (p1 != NULL) {
        themNode(&ketQua, p1->heSo, p1->luyThua);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        themNode(&ketQua, p2->heSo, p2->luyThua);
        p2 = p2->next;
    }
    return ketQua;
}
// In danh sach da thuc
void inDaThuc(Node* dau) {
    while (dau != NULL) {
        printf("(%d, %d)", dau->heSo, dau->luyThua);
        if (dau->next != NULL) printf(" -> ");
        dau = dau->next;
    }
    printf(" -> NULL\n");
}
// Giai phong bo nho danh sach
void giaiPhong(Node* dau) {
    while (dau != NULL) {
        Node* temp = dau;
        dau = dau->next;
        free(temp);
    }
}
// Ham chinh
int main() {
    Node* daThuc1 = NULL;
    Node* daThuc2 = NULL;
    // Khoi tao da thuc 1: 3x^3 - 4
    themNode(&daThuc1, 3, 3);
    themNode(&daThuc1, -4, 0);
    // Khoi tao da thuc 2: 2x^2 + 5x + 1
    themNode(&daThuc2, 2, 2);
    themNode(&daThuc2, 5, 1);
    themNode(&daThuc2, 1, 0);
    printf("Da thuc 1: ");
    inDaThuc(daThuc1);
    printf("Da thuc 2: ");
    inDaThuc(daThuc2);
    double x;
    printf("Nhap gia tri x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Gia tri x khong hop le.\n");
        giaiPhong(daThuc1);
        giaiPhong(daThuc2);
        return 1;
    }
    printf("Gia tri da thuc 1 tai x = %.2lf: %.2lf\n", x, tinhGiaTri(daThuc1, x));
    printf("Dao ham da thuc 1 tai x = %.2lf: %.2lf\n", x, tinhDaoHam(daThuc1, x));
    Node* tong = congDaThuc(daThuc1, daThuc2);
    printf("Tong da thuc 1 + da thuc 2: ");
    inDaThuc(tong);
    giaiPhong(daThuc1);
    giaiPhong(daThuc2);
    giaiPhong(tong);
    return 0;
}

