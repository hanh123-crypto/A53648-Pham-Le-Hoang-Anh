
#include <stdio.h>
#include <string.h>

#define MAX 100

// Cau truc san pham
struct SanPham {
    char ma[20];
    char ten[50];
    long donGia;
    int soLuong;
};

// Doc du lieu tu file
int docFile(struct SanPham ds[]) {
    FILE *f = fopen("san_pham_7969.txt", "r");

    if (f == NULL) {
        printf("Khong mo duoc file!\n");
        return 0;
    }

    int n;
    fscanf(f, "%d", &n);

    if (n <= 0 || n > MAX) {
        printf("So luong san pham khong hop le!\n");
        fclose(f);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(f, "%19[^|]|%49[^|]|%ld|%d",
                   ds[i].ma, ds[i].ten,
                   &ds[i].donGia, &ds[i].soLuong) != 4) {
            printf("Du lieu file khong hop le!\n");
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    return n;
}

// Kiem tra ma san pham trung nhau
int kiemTraTrung(struct SanPham ds[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(ds[i].ma, ds[j].ma) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

// In danh sach san pham
void inDanhSach(struct SanPham ds[], int n) {
    printf("\n%-12s %-20s %-12s %-10s\n",
           "Ma SP", "Ten SP", "Don gia", "So luong");

    for (int i = 0; i < n; i++) {
        printf("%-12s %-20s %-12ld %-10d\n",
               ds[i].ma, ds[i].ten,
               ds[i].donGia, ds[i].soLuong);
    }
}

// Tim kiem tuan tu
int timTuanTu(struct SanPham ds[], int n,
              char ma[], int *soLan) {
    *soLan = 0;

    for (int i = 0; i < n; i++) {
        (*soLan)++;

        if (strcmp(ds[i].ma, ma) == 0) {
            return i;
        }
    }

    return -1;
}

// Sap xep tang dan theo ma san pham
void sapXep(struct SanPham ds[], int n) {
    struct SanPham tam;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(ds[j].ma, ds[j + 1].ma) > 0) {
                tam = ds[j];
                ds[j] = ds[j + 1];
                ds[j + 1] = tam;
            }
        }
    }
}

// Tim kiem nhi phan
int timNhiPhan(struct SanPham ds[], int n,
               char ma[], int *soLan) {
    int left = 0;
    int right = n - 1;

    *soLan = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        (*soLan)++;

        int kq = strcmp(ds[mid].ma, ma);

        if (kq == 0) {
            return mid;
        }

        if (kq < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

// In ket qua tim kiem
void inKetQua(struct SanPham ds[], int vt, int soLan) {
    if (vt == -1) {
        printf("Khong tim thay san pham!\n");
    } else {
        printf("Ma san pham: %s\n", ds[vt].ma);
        printf("Ten san pham: %s\n", ds[vt].ten);
        printf("Don gia: %ld\n", ds[vt].donGia);
        printf("So luong: %d\n", ds[vt].soLuong);
        printf("Vi tri: %d\n", vt + 1);
    }

    printf("So lan so sanh: %d\n", soLan);
}

int main() {
    struct SanPham ds[MAX];
    struct SanPham dsSapXep[MAX];

    int n = docFile(ds);

    if (n == 0) {
        return 0;
    }

    if (kiemTraTrung(ds, n)) {
        printf("File co ma san pham bi trung!\n");
        return 0;
    }

    printf("DANH SACH SAN PHAM BAN DAU\n");
    inDanhSach(ds, n);

    // Sao chep mang goc
    for (int i = 0; i < n; i++) {
        dsSapXep[i] = ds[i];
    }

    // Sap xep ban sao
    sapXep(dsSapXep, n);

    printf("\nDANH SACH SAU KHI SAP XEP\n");
    inDanhSach(dsSapXep, n);

    int chon;
    char ma[20];

    do {
        printf("\n===== MENU =====\n");
        printf("1. Tim kiem tuan tu\n");
        printf("2. Tim kiem nhi phan\n");
        printf("3. So sanh hai cach tim kiem\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &chon);

        if (chon >= 1 && chon <= 3) {
            printf("Nhap ma san pham can tim: ");
            scanf("%19s", ma);

            int vt1, vt2;
            int lan1, lan2;

            if (chon == 1) {
                vt1 = timTuanTu(ds, n, ma, &lan1);
                inKetQua(ds, vt1, lan1);
            }

            else if (chon == 2) {
                vt2 = timNhiPhan(dsSapXep, n, ma, &lan2);
                inKetQua(dsSapXep, vt2, lan2);
            }

            else {
                vt1 = timTuanTu(ds, n, ma, &lan1);
                vt2 = timNhiPhan(dsSapXep, n, ma, &lan2);

                printf("\n--- TIM KIEM TUAN TU ---\n");
                inKetQua(ds, vt1, lan1);

                printf("\n--- TIM KIEM NHI PHAN ---\n");
                inKetQua(dsSapXep, vt2, lan2);

                printf("\nSo sanh: Tuan tu %d lan, "
                       "nhi phan %d lan.\n", lan1, lan2);
            }
        } else if (chon != 0) {
            printf("Lua chon khong hop le!\n");
        }

    } while (chon != 0);

    return 0;
}
