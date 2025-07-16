//Khai bao cau truc tu tro Node gom hai thanh phan int Item va Node 
//*Next de tao danh sach lien ket don. Viet cac ham thuc hien cac cong viec sau:
//a. Ham tao ra Node moi
//Mau ham: Node *TaoMoi(int x = 0);
//Tao ra mot Node moi thong qua cap phat bo nho cho con tro Node *p = new Node; va gan gia tri x
//Ham tra ve con tro p da duoc cap phat va gan gia tri
//b. Ham them moi vao dau danh sach
//Mau ham: Node *ThemDau(Node *H, int x);
//Tao ra mot Node moi nho ham TaoMoi o muc a, noi vao dau danh sach H (chu y truong hop H = NULL)
//Ham tra ve con tro H da duoc bo sung vao dau
//c. Ham them moi vao cuoi danh sach
//Mau ham: void ThemCuoi(Node *&H, int x);
//Tao ra mot Node moi nho ham TaoMoi o muc a, noi vao cuoi danh sach H (chu y truong hop H = NULL)
//Ham truyen tham bien con tro H da duoc bo sung vao cuoi
//d. Ham tao danh sach lien ket don kieu LIFO bang cach cu nhap lien
// tuc du lieu toi khi so 0 thi dung va khong bo sung so 0
//Mau ham: void LIFO(Node *&H);
//e. Ham tao danh sach lien ket don kieu FIFO bang cach nhap 
//truoc so phan tu n va bo sung vao cuoi danh sach
//Mau ham: void FIFO(Node *&H);
//f. Ham xuat danh sach ra man hinh
//Mau ham: void Xuat(Node *H);
//g. Xoa mot gia tri x ra khoi danh sach lien ket neu co
//Mau ham: void Xoa(Node *&H, int x);
//Tim vi tri x xuat hien dau tien de xoa (co the viet ham de quy)
//h. Viet ham menu sau do la ham main thuc hien cac thao tac
//Mau ham: int Menu();
//Ham tra ve gia tri menu neu duoc chon trong [1…7]
//Cac chuc nang cua menu:
//Tao danh sach LIFO a
//Tao danh sach FIFO b
//Xuat danh sach a
//Xuat danh sach b
//Nhap x va xoa 1 x ra khoi a
//Noi lan luot tung phan tu cua b vao cuoi day a
//Thoat 
// Bai so 4 - Danh sach lien ket don voi cac thao tac LIFO, FIFO, Xuat, Xoa, Noi

#include <stdio.h>
#include <stdlib.h>

// a. Khai bao cau truc Node
typedef struct Node {
    int Item;
    struct Node *Next;
} Node;

// a. Ham tao ra Node moi
Node *TaoMoi(int x) {
    Node *p = (Node *)malloc(sizeof(Node));
    if (p == NULL) {
        printf("Khong cap phat duoc bo nho!\n");
        exit(1);
    }
    p->Item = x;
    p->Next = NULL;
    return p;
}

// b. Ham them moi vao dau danh sach
Node *ThemDau(Node *H, int x) {
    Node *p = TaoMoi(x);
    p->Next = H;
    return p;
}

// c. Ham them moi vao cuoi danh sach
void ThemCuoi(Node **H, int x) {
    Node *p = TaoMoi(x);
    if (*H == NULL) {
        *H = p;
    } else {
        Node *q = *H;
        while (q->Next != NULL) {
            q = q->Next;
        }
        q->Next = p;
    }
}

// d. Tao danh sach LIFO
void LIFO(Node **H) {
    int x;
    *H = NULL;
    printf("Nhap cac so (0 de dung):\n");
    while (1) {
        printf("Nhap x: ");
        scanf("%d", &x);
        if (x == 0) break;
        *H = ThemDau(*H, x);
    }
}

// e. Tao danh sach FIFO
void FIFO(Node **H) {
    int n, x;
    *H = NULL;
    printf("Nhap so luong phan tu: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Nhap x: ");
        scanf("%d", &x);
        ThemCuoi(H, x);
    }
}

// f. Xuat danh sach
void Xuat(Node *H) {
    printf("Danh sach: ");
    while (H != NULL) {
        printf("%d ", H->Item);
        H = H->Next;
    }
    printf("\n");
}

// g. Xoa mot gia tri x ra khoi danh sach
void Xoa(Node **H, int x) {
    Node *p = *H, *truoc = NULL;
    while (p != NULL) {
        if (p->Item == x) {
            if (truoc == NULL)
                *H = p->Next;
            else
                truoc->Next = p->Next;
            free(p);
            printf("Da xoa %d\n", x);
            return;
        }
        truoc = p;
        p = p->Next;
    }
    printf("Khong tim thay %d\n", x);
}

// Noi danh sach b vao cuoi danh sach a
void Noi(Node **a, Node *b) {
    while (b != NULL) {
        ThemCuoi(a, b->Item);
        b = b->Next;
    }
}

// h. Ham menu
int Menu() {
    int choice;
    printf("\n========= MENU =========\n");
    printf("1. Tao danh sach LIFO a\n");
    printf("2. Tao danh sach FIFO b\n");
    printf("3. Xuat danh sach a\n");
    printf("4. Xuat danh sach b\n");
    printf("5. Nhap x va xoa trong a\n");
    printf("6. Noi b vao cuoi a\n");
    printf("7. Thoat\n");
    printf("Moi ban chon: ");
    scanf("%d", &choice);
    return choice;
}

// Ham main
int main() {
    Node *a = NULL, *b = NULL;
    int chon, x;

    do {
        chon = Menu();
        switch (chon) {
            case 1:
                LIFO(&a);
                break;
            case 2:
                FIFO(&b);
                break;
            case 3:
                Xuat(a);
                break;
            case 4:
                Xuat(b);
                break;
            case 5:
                printf("Nhap gia tri x can xoa: ");
                scanf("%d", &x);
                Xoa(&a, x);
                break;
            case 6:
                Noi(&a, b);
                break;
            case 7:
                printf("Dang thoat chuong trinh...\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (chon != 7);

    return 0;
}

