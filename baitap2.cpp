
#include <stdio.h>

struct SinhVien {
    char maSV[10];
    char ten[30];
    float gpa;
    int tinChi;
    int kyLuat;
};

void nhap(struct SinhVien ds[], int *n) {
    *n = 8;

    struct SinhVien a[8] = {
        {"SV08", "Lan", 3.70, 30, 0},
        {"SV02", "Minh", 3.85, 28, 0},
        {"SV05", "Ha", 3.70, 33, 0},
        {"SV01", "An", 3.20, 25, 0},
        {"SV07", "Binh", 3.90, 22, 0},
        {"SV06", "Dung", 3.70, 33, 0},
        {"SV03", "Vy", 3.10, 40, 0},
        {"SV04", "Huy", 3.85, 28, 1}
    };

    for (int i = 0; i < *n; i++)
        ds[i] = a[i];
}

int duDieuKien(struct SinhVien sv) {
    return sv.gpa >= 3.20 &&
           sv.tinChi >= 24 &&
           sv.kyLuat == 0;
}

int dungThuTu(struct SinhVien a, struct SinhVien b) {
    if (a.gpa != b.gpa)
        return a.gpa < b.gpa;

    if (a.tinChi != b.tinChi)
        return a.tinChi < b.tinChi;

    return a.maSV[3] > b.maSV[3];
}

void doiCho(struct SinhVien *a, struct SinhVien *b) {
    struct SinhVien temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(struct SinhVien ds[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (dungThuTu(ds[j], ds[j + 1]))
                doiCho(&ds[j], &ds[j + 1]);
}

void selectionSort(struct SinhVien ds[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int vt = i;

        for (int j = i + 1; j < n; j++)
            if (dungThuTu(ds[vt], ds[j]))
                vt = j;

        if (vt != i)
            doiCho(&ds[i], &ds[vt]);
    }
}

void insertionSort(struct SinhVien ds[], int n) {
    for (int i = 1; i < n; i++) {
        struct SinhVien x = ds[i];
        int j = i - 1;

        while (j >= 0 && dungThuTu(ds[j], x)) {
            ds[j + 1] = ds[j];
            j--;
        }

        ds[j + 1] = x;
    }
}

void hienThi(struct SinhVien ds[], int n) {
    printf("\n%-6s %-10s %-8s %-10s\n",
           "Ma SV", "Ten", "GPA", "Tin chi");

    for (int i = 0; i < n; i++) {
        printf("%-6s %-10s %-8.2f %-10d\n",
               ds[i].maSV, ds[i].ten,
               ds[i].gpa, ds[i].tinChi);
    }
}

int main() {
    struct SinhVien ds[100], dat[100];
    int n, m = 0, chon, k;

    nhap(ds, &n);

    for (int i = 0; i < n; i++)
        if (duDieuKien(ds[i]))
            dat[m++] = ds[i];

    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Insertion Sort\n");
    printf("Chon thuat toan: ");
    scanf("%d", &chon);

    if (chon == 1)
        bubbleSort(dat, m);
    else if (chon == 2)
        selectionSort(dat, m);
    else if (chon == 3)
        insertionSort(dat, m);
    else {
        printf("Lua chon khong hop le!");
        return 0;
    }

    printf("\nDanh sach sinh vien du dieu kien:\n");
    hienThi(dat, m);

    printf("\nNhap K de xem Top K: ");
    scanf("%d", &k);

    if (k < 0)
        k = 0;
    if (k > m)
        k = m;

    printf("\nTOP %d:\n", k);
    hienThi(dat, k);

    return 0;
}