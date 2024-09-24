#include<bits/stdc++.h>

using namespace std;

//1 
void SelectionSort(int a[], int n) {
    for (int i = 0; i < n; i++) {
        int MinIdx = i;

        for (int j = i; j < n; j++) {
            if (a[MinIdx] > a[j]) {
                MinIdx = j;
            }
        }

        swap(a[MinIdx], a[i]);
    }
}

//2
void InterchangeSort(int a[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                swap(a[i], a[j]);
            }
        }
    }
} 

//3
void InsertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int temp = a[i];
        int j = i - 1;

        for (; (j >= 0) && (temp < a[j]); j--) {
            a[j + 1] = a[j];
        }

        a[j + 1] = temp;
    }
}

//4
//Tim kiem nhi phan tim phan tu trong mang con duoc sap xep dau tien nho hon x
int BinarySearch(int a[], int left, int right, int x) {
    int mid = (left + right) / 2;

    if (x < a[mid]) {
        goto FirstIndex;
    }

    while (left < right) {
        
        if (x >= a[mid]) {
            left = mid + 1;
        }

        mid = (left + right) / 2;

        if (x < a[mid]) {
            goto FirstIndex;
        }
    }

    return right; //neu x lon hon hoac bang toan bo mang con thi giu nguyen vi tri x tren mang that

FirstIndex:
    int l = mid;

    while ((x < a[l]) && (l >= 0)) {
        l--;
    }

    return l; //khi l = -1 thi x se duoc xep o dau mang con 
}

void BinaryInsertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int j = BinarySearch(a, 0, i - 1, a[i]);
        int k = i - 1;
        int temp = a[i];

        // cout << j << " " << temp << "\n";

        if (j <= -1) { //xu li truong hop BinarySearch tra ve -1, tuc la chen phan tu vao dau mang
            for (; k >= 0; k--) {
                a[k + 1] = a[k];
            }

            a[k + 1] = temp;
        } else {
            for (; k > j; k--) {
                a[k + 1] = a[k];
            }

            a[k + 1] = temp;
        }
        
    }
}

//5
void BubbleSort(int a[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (a[j - 1] > a[j]) {
                swap(a[j], a[j - 1]);
            }
        }
    }
}

//6
//Cocktail Shaker Sort? BubbleSort++
//https://www.geeksforgeeks.org/cocktail-sort/
void ShakerSort(int a[], int n) {
    bool Swapped = 1;
    int left = 0, right = n - 1;

    while (Swapped) {
        Swapped = 0;

        for (int i = left; i < right; i++) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                Swapped = 1;
            }
        }

        if (!Swapped) {
            break;
        }

        Swapped = 1;
        right--;

        for (int i = right; i > left; i--) {
            if (a[i] < a[i - 1]) {
                swap(a[i], a[i - 1]);
            }
        }
        left++;
    }
}

//7 stable / not in-place
//https://www.geeksforgeeks.org/counting-sort/
int* CountingSort(int a[], int n) {
    int Max = a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] > Max) {
            Max = a[i];
        }
    }
    //vi CountArr tinh tan suat xuat hien cua cac phan tu trong mang, nen ta can tim phan tu lon nhat trong mang cho truoc

    int* CountArr = new int[Max + 1];
    memset(CountArr, 0, (Max + 1) * (sizeof(CountArr[0]))); //gan tat ca phan tu trong mang CountArr bang 0

    //tinh tan suat xuat hien cua tung phan tu trong mang cho truoc
    for (int i = 0; i < n; i++) {
        CountArr[a[i]]++;
    }

    //can thuc hien prefix sum o mang dem de dam bao cac phan tu o mang xuat duoc tra ve chinh xac
    //VD: CountArr = {2, 2, 7, 7, 8}
    //CountArr cho ta biet mang xuat se la {0, 0, 2, 2, 2, 2, 2, 4}
    //phan tu 0 xuat hien o vi tri 1, 2, phan tu 1 khong xuat hien, phan tu 2 se xuat hien o vi tri 3, 4, 5, 6, 7
    //phan tu 3 khong xuat hien phan tu 4 se xuat hien o vi tri 8
    for (int i = 1; i < Max + 1; i++) { 
        CountArr[i] += CountArr[i - 1];
    }

    int* OutputArr = new int[n];

    //gia tri phan tu trong mang OutputArr co chi so la CountArr[a[i]] - 1 la a[i]
    for (int i = n - 1; i >= 0; i--) {
        OutputArr[CountArr[a[i]] - 1] = a[i];
        CountArr[a[i]]--;
    }

    return OutputArr;
}

//8 unstable
//https://www.algolist.net/Algorithms/Sorting/Quicksort
int Partition(int a[], int left, int right) {
    int pivot = a[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (a[i] < pivot) {
            i++;
        }
        while (a[j] > pivot) {
            j--;
        }

        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    return i;
}

void QuickSort(int a[], int left, int right) {
    if (left >= right) {
        return;
    }
    
    int p = Partition(a, left, right);

    QuickSort(a, left, p - 1);
    QuickSort(a, p, right);
}

//9 stable/non-inplace
//https://www.geeksforgeeks.org/merge-sort/
void Merge(int a[], int Left, int Mid, int Right)
{
    //xac dinh vi tri hai mang con, sau do tao hai mang tam de chua cac mang con tren
    int n1 = Mid - Left + 1;
    int n2 = Right - Mid;

    
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = a[Left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = a[Mid + 1 + j];
    }

    int i = 0, j = 0;
    int k = Left;

    // ket hop hai mang con duoc sap xep thanh mot mang moi duoc sap xep
    // mang nao dai hon thi chung ta chi can them cac phan tu cuoi vao cuoi mang moi
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        }
        else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }

    // for (int i = 0; i < Right; i++) {
    //     cout << a[i] << " ";
    // }
    // cout << "\n";
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void MergeSort(int a[], int Left, int Right)
{   
    //truong hop co ban: neu mang chi con 1 phan tu thi khong can sort nua
    if (Left >= Right) {
        return;
    } 

    int Mid = (Right + Left) / 2; 

    MergeSort(a, Left, Mid);
    MergeSort(a, Mid + 1, Right);
    Merge(a, Left, Mid, Right);
}


//10 unstable/in-place
//https://www.geeksforgeeks.org/heap-sort/
void Heapify(int a[], int n, int i ) {
    int Root = i; 
    int Left = 2 * i + 1, Right = 2 * i + 2; //mang duoc danh dau dua theo duyet BFS

    //hai lenh if duoc dung de xac dinh node cha nen mang gia tri gi de thoa man quy luat Max Heap
    //neu node con ben trai khong phai nullptr, so sanh voi node cha
    if ((Left < n) && (a[Left] > a[Root])) {
        Root = Left;        
    }
    //neu node con ben phai khong phai nullptr, so sanh voi node cha
    if ((Right < n) && (a[Right] > a[Root])) {
        Root = Right;
    }

    if (Root != i) {
        swap(a[i], a[Root]);
        // for (int i = 0; i < n; i++) {
        //     cout << a[i] << " ";
        // }
        // cout << "\n";
        Heapify(a, n, Root);
        //chay de quy tren cay con 
    }
}

void HeapSort(int a[], int n) {
    //xay dung max heap tu mang cho truoc
    //bat dau bang n / 2 - 1 de uu tien ben co chieu cao lon hon, tu phai qua trai neu co chieu cao bang nhau
    for (int i = n / 2 - 1; i >= 0; i--) {
        Heapify(a, n, i);
    }

    //sau khi xay dung max heap xong
    //tien hanh dat phan tu lon nhat len cuoi mang, va tao lai max heap
    for (int i = n - 1; i > 0; i--) {
        // hoan vi root voi phan tu cuoi
        swap(a[0], a[i]);

        // tao lai max heap tren heap da bi giam di phan tu cuoi
        Heapify(a, i, 0);
        
    }
}

//11 InsertionSort++
//https://www.geeksforgeeks.org/shell-sort/
//gap = n / 2^k
void ShellSort(int a[], int n) {
    //lam giam gap moi lan lap, o day la chia 2
    for (int gap = n/2; gap > 0; gap /= 2) {
        //thuc hien InsertionSort tren mang con voi cac phan tu cach nhau mot khoang cach bang gap
        //va thuc hien InsertionSort lai sau khi tinh tien mang con 1 don vi
        for (int i = gap; i < n; i++) {
            int temp = a[i]; //tuong duong a[1] trong mang con tuong ung
            int j; //luu tru vi tri phan tu dau tien ma temp lon hon

            //thao tac chen temp vao mang con
            for (j = i; (j >= gap) && (a[j - gap] > temp); j -= gap) {
                a[j] = a[j - gap];
            }

            a[j] = temp;
        }
    //     for (int i = 0; i < n; i++) {
    //         cout << a[i] << " ";
    //     }
    //     cout << "\n";
    }
}

//12 CountingSort++
//https://www.geeksforgeeks.org/radix-sort/

//CountingSort theo chu so exp = 10^x
//thuat toan chu yeu tu CountingSort, nen tham khao tu ham goc
void CountingSort2(int a[], int n, int exp) {

    // Output array
    int* output = new int[n];
    int i, count[10] = {0}; //mang count luu chu so tu 0 toi 9

    // Tinh tan suat xuat hien cua cac chu so tuong ung cua phan tu trong mang
    for (i = 0; i < n; i++) {
        count[(a[i] / exp) % 10]++;
    }

    // Su dung prefix sum de xuat dung vi tri
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (i = n - 1; i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++) {
        a[i] = output[i];
    }
}

void RadixSort(int a[], int n) {
    int Max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > Max) {
            Max = a[i];
        }
    }

    //chay vong lap tu hang don vi den hang chu so cao nhat cua phan tu Max, va su dung CountingSort2
    //de sap xep mang theo tung chu so
    for (int exp = 1; Max / exp > 0; exp *= 10) {
        CountingSort2(a, n, exp);
    }
}

int main() {
    srand(time(NULL));
    
    int n, m;
    char choice;
    do {
        do {
            cout << "Please enter a number in range 1 .. 100,000,000: ";
            cin >> n;
        } while (n < 1 || n > 100000000);

        cout << "**************MENU***************\n";
        cout << "1. Selection Sort\n";
        cout << "2. Interchange Sort\n";
        cout << "3. Insertion Sort\n";
        cout << "4. Binary Insertion Sort\n";
        cout << "5. Bubble Sort\n";
        cout << "6. Shake/Shaker Sort\n";
        cout << "7. Counting Sort\n";
        cout << "8. Quick Sort\n";
        cout << "9. Merge Sort\n";
        cout << "10. Heap Sort\n";
        cout << "11. Shell Sort\n";
        cout << "12. Radix Sort\n";
        cout << "Please choose an algorithm (Enter an interger): ";
        cin >> m;
        
        if (m < 1 || m > 12) {
            cout << "See you again\n";
            return 0;
        }

        int* arr = new int[n];
        
        for (int i = 0; i < n; i++) {
            arr[i] = (rand() % 10000);
        }

        clock_t begin = clock();
        // for (int i = 0; i < n; i++) {
        //     cout << arr[i] << " ";
        // }
        // cout << "\n";

    
        switch(m) {
            case 1: {
                SelectionSort(arr, n);
                break;
            }
            case 2: {
                InterchangeSort(arr, n);
                break;
            }
            case 3: {
                InsertionSort(arr, n);
                break;
            }
            case 4: {
                BinaryInsertionSort(arr, n);
                break;
            }
            case 5: {
                BubbleSort(arr, n);
                break;
            }
            case 6: {
                ShakerSort(arr, n);
                break;
            }
            case 7: {
                int* OutputArr = CountingSort(arr, n);
                break;
            }
            case 8: {
                QuickSort(arr, 0, n - 1);
                break;
            }
            case 9: {
                MergeSort(arr, 0, n - 1);
                break;
            }
            case 10: {
                HeapSort(arr, n);
                break;
            }
            case 11: {
                ShellSort(arr, n);
                break;
            }
            case 12: {
                RadixSort(arr, n);
                break;
            }
        }

        clock_t end = clock();

        // for (int i = 0; i < n; i++) {
        //     cout << arr[i] << " ";
        // }
        // cout << "\n";

        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        cout << "\nTime taken to finish sorting: " << time_spent << " second(s)";
        cout << "\nDo you want to continue(y/n): ";
        cin >> choice;
    } while (choice != 'n');
    
    cout << "See you again\n";
    return 0;
}