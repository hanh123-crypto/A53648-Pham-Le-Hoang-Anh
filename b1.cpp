
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int maSP;
    char tenSP[50];
    int soLuong;
    double donGia;
} Product;

typedef struct Node {
    Product data;
    struct Node *left;
    struct Node *right;
} Node;

/* Tao nut moi */
Node *taoNode(Product p) {
    Node *node = (Node *)malloc(sizeof(Node));

    if (node == NULL) {
        printf("Khong du bo nho!\n");
        return NULL;
    }

    node->data = p;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/* Them san pham vao cay BST */
Node *them(Node *root, Product p) {
    if (root == NULL) {
        return taoNode(p);
    }

    if (p.maSP < root->data.maSP) {
        root->left = them(root->left, p);
    } else if (p.maSP > root->data.maSP) {
        root->right = them(root->right, p);
    } else {
        printf("Ma san pham da ton tai!\n");
    }

    return root;
}

/* Tim san pham theo ma */
Node *tim(Node *root, int ma) {
    if (root == NULL || root->data.maSP == ma) {
        return root;
    }

    if (ma < root->data.maSP) {
        return tim(root->left, ma);
    }

    return tim(root->right, ma);
}

/* In thong tin san pham */
void inSanPham(Product p) {
    printf("%-8d %-20s %-10d %.2f\n",
           p.maSP, p.tenSP, p.soLuong, p.donGia);
}

/* Duyet LNR: in theo ma tang dan */
void duyetLNR(Node *root) {
    if (root != NULL) {
        duyetLNR(root->left);
        inSanPham(root->data);
        duyetLNR(root->right);
    }
}

/* Tim nut co ma nho nhat */
Node *timNhoNhat(Node *root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }

    return root;
}

/* Xoa san pham */
Node *xoa(Node *root, int ma, int *daXoa) {
    if (root == NULL) {
        return NULL;
    }

    if (ma < root->data.maSP) {
        root->left = xoa(root->left, ma, daXoa);
    } else if (ma > root->data.maSP) {
        root->right = xoa(root->right, ma, daXoa);
    } else {
        *daXoa = 1;

        /* Truong hop 1: nut la */
        if (root->left == NULL &&
            root->right == NULL) {
            free(root);
            return NULL;
        }

        /* Truong hop 2: nut co mot con */
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        /* Truong hop 3: nut co hai con */
        Node *temp = timNhoNhat(root->right);

        root->data = temp->data;

        int boQua = 0;
        root->right = xoa(
            root->right, temp->data.maSP, &boQua
        );
    }

    return root;
}

/* Dem so nut */
int demNut(Node *root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + demNut(root->left)
             + demNut(root->right);
}

/* Tinh chieu cao cay */
int chieuCao(Node *root) {
    if (root == NULL) {
        return 0;
    }

    int trai = chieuCao(root->left);
    int phai = chieuCao(root->right);

    if (trai > phai) {
        return trai + 1;
    }

    return phai + 1;
}

/* Giai phong bo nho */
void giaiPhong(Node *root) {
    if (root != NULL) {
        giaiPhong(root->left);
        giaiPhong(root->right);
        free(root);
    }
}

/* Xoa ky tu con lai trong ban phim */
void xoaDongDu(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* Nhap thong tin san pham */
int nhapSanPham(Product *p) {
    printf("Nhap ma san pham: ");

    if (scanf("%d", &p->maSP) != 1) {
        xoaDongDu();
        printf("Ma khong hop le!\n");
        return 0;
    }

    xoaDongDu();

    if (p->maSP <= 0) {
        printf("Ma phai lon hon 0!\n");
        return 0;
    }

    printf("Nhap ten san pham: ");
    if (fgets(p->tenSP, 50, stdin) == NULL) {
        return 0;
    }

    p->tenSP[strcspn(p->tenSP, "\n")] = '\0';

    if (strlen(p->tenSP) == 0) {
        printf("Ten khong duoc de trong!\n");
        return 0;
    }

    printf("Nhap so luong: ");

    if (scanf("%d", &p->soLuong) != 1) {
        xoaDongDu();
        printf("So luong khong hop le!\n");
        return 0;
    }

    printf("Nhap don gia: ");

    if (scanf("%lf", &p->donGia) != 1) {
        xoaDongDu();
        printf("Don gia khong hop le!\n");
        return 0;
    }

    xoaDongDu();

    if (p->soLuong < 0 || p->donGia < 0) {
        printf("So luong va don gia khong duoc am!\n");
        return 0;
    }

    return 1;
}

/* Tao du lieu mau theo de bai */
void duLieuMau(Node **root) {
    Product ds[] = {
        {50, "But bi", 120, 5000},
        {30, "Vo o ly", 80, 12000},
        {70, "Bia ho so", 35, 15000},
        {20, "Thuoc ke", 40, 8000},
        {40, "Tay", 65, 4000},
        {60, "So tay", 25, 25000},
        {80, "But chi", 110, 3000}
    };

    int n = sizeof(ds) / sizeof(ds[0]);

    for (int i = 0; i < n; i++) {
        *root = them(*root, ds[i]);
    }

    printf("Da nap 7 san pham mau!\n");
}

/* Menu chuong trinh */
void menu(void) {
    printf("\n====== QUAN LY SAN PHAM BST ======\n");
    printf("1. Nap du lieu mau\n");
    printf("2. Them san pham\n");
    printf("3. Tim kiem san pham\n");
    printf("4. Xoa san pham\n");
    printf("5. In danh sach tang dan\n");
    printf("6. Dem nut va chieu cao cay\n");
    printf("0. Thoat\n");
    printf("Lua chon: ");
}

int main(void) {
    Node *root = NULL;
    int chon;
    int daNapMau = 0;

    do {
        menu();

        if (scanf("%d", &chon) != 1) {
            printf("Vui long nhap so!\n");
            xoaDongDu();
            continue;
        }

        xoaDongDu();

        switch (chon) {
            case 1:
                if (daNapMau) {
                    printf("Du lieu mau da duoc nap!\n");
                } else {
                    duLieuMau(&root);
                    daNapMau = 1;
                }
                break;

            case 2: {
                Product p;

                if (nhapSanPham(&p)) {
                    if (tim(root, p.maSP) != NULL) {
                        printf("Ma san pham da ton tai!\n");
                    } else {
                        Node *moi = them(root, p);

                        if (moi != NULL || root != NULL) {
                            root = moi;
                            printf("Them thanh cong!\n");
                        } else {
                            printf("Them that bai!\n");
                        }
                    }
                }
                break;
            }

            case 3: {
                int ma;

                printf("Nhap ma can tim: ");

                if (scanf("%d", &ma) != 1) {
                    printf("Ma khong hop le!\n");
                    xoaDongDu();
                    break;
                }

                xoaDongDu();

                Node *kq = tim(root, ma);

                if (kq == NULL) {
                    printf("Khong tim thay san pham!\n");
                } else {
                    printf("\nMa SP   Ten san pham        So luong  Don gia\n");
                    inSanPham(kq->data);
                }
                break;
            }

            case 4: {
                int ma;
                int daXoa = 0;

                printf("Nhap ma can xoa: ");

                if (scanf("%d", &ma) != 1) {
                    printf("Ma khong hop le!\n");
                    xoaDongDu();
                    break;
                }

                xoaDongDu();

                root = xoa(root, ma, &daXoa);

                if (daXoa) {
                    printf("Xoa thanh cong!\n");
                } else {
                    printf("Khong tim thay san pham!\n");
                }
                break;
            }

            case 5:
                if (root == NULL) {
                    printf("Cay dang rong!\n");
                } else {
                    printf("\nMa SP   Ten san pham        So luong  Don gia\n");
                    duyetLNR(root);
                }
                break;

            case 6:
                printf("So nut: %d\n", demNut(root));
                printf("Chieu cao cay: %d\n", chieuCao(root));
                break;

            case 0:
                giaiPhong(root);
                root = NULL;
                printf("Da giai phong bo nho. Tam biet!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }

    } while (chon != 0);

    return 0;
}
