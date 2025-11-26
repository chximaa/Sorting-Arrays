#include <stdio.h>
#include <stdlib.h>

int arr[] = {1,8,17,19,2,3,10,12,5,16,7,11,18,20,4,6,9,13,14,15};
int n = 20;

/* ---------------------------------------------------
                 SELECTION SORT
----------------------------------------------------*/
void selection_sort(int a[], int n){
    int i, j, min_index, temp;
    for(i = 0; i < n; i++){
        min_index = i;
        for(j = i+1; j < n; j++){
            if(a[j] < a[min_index])
                min_index = j;
        }
        temp = a[i];
        a[i] = a[min_index];
        a[min_index] = temp;
    }
}

/* ---------------------------------------------------
                 INSERTION SORT
----------------------------------------------------*/
void insertion_sort(int a[], int n){
    int i, j, key;
    for(i = 1; i < n; i++){
        key = a[i];
        j = i - 1;
        while(j >= 0 && a[j] > key){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

/* ---------------------------------------------------
                   BUBBLE SORT
----------------------------------------------------*/
void bubble_sort(int a[], int n){
    int i, j, temp;
    for(i = 0; i < n; i++){
        for(j = 0; j < n-i-1; j++){
            if(a[j] > a[j+1]){
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

/* ---------------------------------------------------
                      QUICK SORT
----------------------------------------------------*/
void quick_sort(int a[], int low, int high){
    if(low >= high) return;

    int pivot = a[(low + high) / 2];
    int i = low, j = high, temp;

    while(i <= j){
        while(a[i] < pivot) i++;
        while(a[j] > pivot) j--;

        if(i <= j){
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++; j--;
        }
    }

    quick_sort(a, low, j);
    quick_sort(a, i, high);
}

/* ---------------------------------------------------
                      MERGE SORT
----------------------------------------------------*/
void merge(int a[], int l, int m, int r){
    int i = l, j = m+1, k = 0;
    int size = r - l + 1;
    int* temp = malloc(size * sizeof(int));

    while(i <= m && j <= r){
        if(a[i] <= a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }

    while(i <= m) temp[k++] = a[i++];
    while(j <= r) temp[k++] = a[j++];

    for(i = l, k = 0; i <= r; i++, k++)
        a[i] = temp[k];

    free(temp);
}

void merge_sort(int a[], int l, int r){
    if(l >= r) return;
    int m = (l + r) / 2;
    merge_sort(a, l, m);
    merge_sort(a, m+1, r);
    merge(a, l, m, r);
}

/* ---------------------------------------------------
                       HEAP SORT
----------------------------------------------------*/
void heapify(int a[], int n, int i){
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && a[left] > a[largest])
        largest = left;

    if(right < n && a[right] > a[largest])
        largest = right;

    if(largest != i){
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        heapify(a, n, largest);
    }
}

void heap_sort(int a[], int n){
    int i, temp;
    for(i = n/2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for(i = n - 1; i >= 0; i--){
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        heapify(a, i, 0);
    }
}

/* ---------------------------------------------------
                     COUNTING SORT
----------------------------------------------------*/
void counting_sort(int a[], int n){
    int max = a[0], i;
    for(i = 1; i < n; i++)
        if(a[i] > max) max = a[i];

    int* count = calloc(max+1, sizeof(int));
    int* out = malloc(n * sizeof(int));

    for(i = 0; i < n; i++)
        count[a[i]]++;

    int idx = 0;
    for(i = 0; i <= max; i++)
        while(count[i]--)
            out[idx++] = i;

    for(i = 0; i < n; i++)
        a[i] = out[i];

    free(count);
    free(out);
}

/* ---------------------------------------------------
                       RADIX SORT
----------------------------------------------------*/
void counting_sort_radix(int a[], int n, int exp){
    int out[n], count[10] = {0};
    int i;

    for(i = 0; i < n; i++)
        count[(a[i] / exp) % 10]++;

    for(i = 1; i < 10; i++)
        count[i] += count[i-1];

    for(i = n-1; i >= 0; i--){
        int digit = (a[i] / exp) % 10;
        out[count[digit] - 1] = a[i];
        count[digit]--;
    }

    for(i = 0; i < n; i++)
        a[i] = out[i];
}

void radix_sort(int a[], int n){
    int max = a[0], i;
    for(i = 1; i < n; i++)
        if(a[i] > max) max = a[i];

    for(int exp = 1; max / exp > 0; exp *= 10)
        counting_sort_radix(a, n, exp);
}

/* ---------------------------------------------------
              SHELL SORT
----------------------------------------------------*/
void shell_sort(int a[], int n){
    for(int gap = n/2; gap > 0; gap /= 2){
        for(int i = gap; i < n; i++){
            int temp = a[i], j;
            for(j = i; j >= gap && a[j-gap] > temp; j -= gap)
                a[j] = a[j-gap];
            a[j] = temp;
        }
    }
}

/* ---------------------------------------------------
            COCKTAIL SHAKER SORT
----------------------------------------------------*/
void cocktail_sort(int a[], int n){
    int start = 0, end = n - 1, swapped = 1;

    while(swapped){
        swapped = 0;

        for(int i = start; i < end; i++){
            if(a[i] > a[i+1]){
                int t = a[i]; a[i] = a[i+1]; a[i+1] = t;
                swapped = 1;
            }
        }

        if(!swapped) break;
        swapped = 0;
        end--;

        for(int i = end - 1; i >= start; i--){
            if(a[i] > a[i+1]){
                int t = a[i]; a[i] = a[i+1]; a[i+1] = t;
                swapped = 1;
            }
        }
        start++;
    }
}

/* ---------------------------------------------------
                  UTILS
----------------------------------------------------*/
void copy_array(int dst[], int src[]){
    for(int i = 0; i < n; i++) dst[i] = src[i];
}

void print_array(int a[]){
    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

/* ---------------------------------------------------
                      MENU
----------------------------------------------------*/
int main(){
    int choice;
    int a[20];

    while(1){
        printf("\n--- Sorting Algorithms Menu ---\n");
        printf("1 - Selection Sort\n");
        printf("2 - Insertion Sort\n");
        printf("3 - Bubble Sort\n");
        printf("4 - Quick Sort\n");
        printf("5 - Merge Sort\n");
        printf("6 - Heap Sort\n");
        printf("7 - Counting Sort\n");
        printf("8 - Radix Sort\n");
        printf("9 - Shell Sort\n");
        printf("10 - Cocktail Sort\n");
        printf("0 - Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 0){
            printf("Exiting...\n");
            break;
        }

        copy_array(a, arr);

        switch(choice){

            case 1: selection_sort(a, n); printf("Selection Sort Result:\n"); break;
            case 2: insertion_sort(a, n); printf("Insertion Sort Result:\n"); break;
            case 3: bubble_sort(a, n); printf("Bubble Sort Result:\n"); break;
            case 4: quick_sort(a, 0, n-1); printf("Quick Sort Result:\n"); break;
            case 5: merge_sort(a, 0, n-1); printf("Merge Sort Result:\n"); break;
            case 6: heap_sort(a, n); printf("Heap Sort Result:\n"); break;
            case 7: counting_sort(a, n); printf("Counting Sort Result:\n"); break;
            case 8: radix_sort(a, n); printf("Radix Sort Result:\n"); break;
            case 9: shell_sort(a, n); printf("Shell Sort Result:\n"); break;
            case 10: cocktail_sort(a, n); printf("Cocktail Sort Result:\n"); break;

            default: printf("Invalid choice.\n"); continue;
        }

        print_array(a);
    }
}
