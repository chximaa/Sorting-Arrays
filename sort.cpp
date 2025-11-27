#include <iostream>
using namespace std;

/* ---------------------------------------------------
                 SELECTION SORT
----------------------------------------------------*/
void selection_sort(int arr[], int n){
    for(int i = 0; i < n; i++){
        int min_indx = i;
        for(int j = i + 1; j < n; j++)
            if(arr[j] < arr[min_indx])
                min_indx = j;

        swap(arr[i], arr[min_indx]);
    }
}

/* ---------------------------------------------------
                 INSERTION SORT
----------------------------------------------------*/
void insertion_sort(int a[], int n){
    for(int i = 1; i < n; i++){
        int key = a[i];
        int j = i - 1;
        while(j >= 0 && a[j] > key){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

/* ---------------------------------------------------
                   BUBBLE SORT
----------------------------------------------------*/
void bubble_sort(int a[], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
        }
    }
}

/* ---------------------------------------------------
                   QUICK SORT
----------------------------------------------------*/
void quick_sort(int a[], int low, int high){
    if(low >= high) return;

    int pivot = a[(low + high) / 2];
    int i = low, j = high;

    while(i <= j){
        while(a[i] < pivot) i++;
        while(a[j] > pivot) j--;

        if(i <= j){
            swap(a[i], a[j]);
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
    int size = r - l + 1;
    int* temp = new int[size];

    int i = l, j = m + 1, k = 0;

    while(i <= m && j <= r){
        if(a[i] <= a[j]) temp[k++] = a[i++];
        else            temp[k++] = a[j++];
    }

    while(i <= m) temp[k++] = a[i++];
    while(j <= r) temp[k++] = a[j++];

    for(i = l, k = 0; i <= r; i++, k++)
        a[i] = temp[k];

    delete[] temp;
}

void merge_sort(int a[], int l, int r){
    if(l >= r) return;
    int m = (l + r) / 2;
    merge_sort(a, l, m);
    merge_sort(a, m + 1, r);
    merge(a, l, m, r);
}

/* ---------------------------------------------------
                   HEAP SORT
----------------------------------------------------*/
void heapify(int a[], int n, int i){
    int largest = i;
    int left  = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && a[left] > a[largest])
        largest = left;

    if(right < n && a[right] > a[largest])
        largest = right;

    if(largest != i){
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heap_sort(int a[], int n){
    for(int i = n/2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for(int i = n - 1; i >= 0; i--){
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

/* ---------------------------------------------------
               COUNTING SORT
----------------------------------------------------*/
void counting_sort(int a[], int n){
    int max = a[0];
    for(int i = 1; i < n; i++)
        if(a[i] > max) max = a[i];

    int* count = new int[max + 1]();
    int* out   = new int[n];

    for(int i = 0; i < n; i++)
        count[a[i]]++;

    int idx = 0;
    for(int i = 0; i <= max; i++){
        while(count[i]--)
            out[idx++] = i;
    }

    for(int i = 0; i < n; i++)
        a[i] = out[i];

    delete[] count;
    delete[] out;
}

/* ---------------------------------------------------
                 RADIX SORT
----------------------------------------------------*/
void counting_sort_radix(int a[], int n, int exp){
    int out[n];
    int count[10] = {0};

    for(int i = 0; i < n; i++)
        count[(a[i] / exp) % 10]++;

    for(int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for(int i = n - 1; i >= 0; i--){
        int digit = (a[i] / exp) % 10;
        out[count[digit] - 1] = a[i];
        count[digit]--;
    }

    for(int i = 0; i < n; i++)
        a[i] = out[i];
}

void radix_sort(int a[], int n){
    int max = a[0];
    for(int i = 1; i < n; i++)
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
            for(j = i; j >= gap && a[j - gap] > temp; j -= gap)
                a[j] = a[j - gap];
            a[j] = temp;
        }
    }
}

/* ---------------------------------------------------
            COCKTAIL SHAKER SORT
----------------------------------------------------*/
void cocktail_sort(int a[], int n){
    int start = 0, end = n - 1;
    bool swapped = true;

    while(swapped){
        swapped = false;
        for(int i = start; i < end; i++){
            if(a[i] > a[i+1]){
                swap(a[i], a[i+1]);
                swapped = true;
            }
        }
        if(!swapped) break;

        swapped = false;
        end--;

        for(int i = end - 1; i >= start; i--){
            if(a[i] > a[i+1]){
                swap(a[i], a[i+1]);
                swapped = true;
            }
        }
        start++;
    }
}

/* ---------------------------------------------------
                 UTILS
----------------------------------------------------*/
void print_array(int a[], int n){
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

void copy_array(int dst[], int src[], int n){
    for(int i = 0; i < n; i++)
        dst[i] = src[i];
}

/* ---------------------------------------------------
                        MAIN (MENU)
----------------------------------------------------*/
int main() {
    int arr[] = {8, 3, 1, 7, 0, 10, 2};
    int n = sizeof(arr)/sizeof(arr[0]);
    int temp[n];
    int choice;

    do {
        cout << "\n===== SORTING MENU =====\n";
        cout << "1. Selection Sort\n";
        cout << "2. Insertion Sort\n";
        cout << "3. Bubble Sort\n";
        cout << "4. Quick Sort\n";
        cout << "5. Merge Sort\n";
        cout << "6. Heap Sort\n";
        cout << "7. Counting Sort\n";
        cout << "8. Radix Sort\n";
        cout << "9. Shell Sort\n";
        cout << "10. Cocktail Sort\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if(choice == 0) break;

        copy_array(temp, arr, n);

        switch(choice){
    case 1:
        cout << "=== Selection Sort ===\n";
        cout << "Idea: Find the smallest element and place it at the beginning.\n";
        cout << "Time Complexity: O(n^2)\nMemory: O(1)\nStable: No\n";
        cout << "Advantages:\n- Very simple to implement\n- Requires minimal memory\n";
        cout << "Disadvantages:\n- Very slow for large data\n- Not stable\n";
        selection_sort(temp, n);
        break;

    case 2:
        cout << "=== Insertion Sort ===\n";
        cout << "Idea: Build the sorted array by inserting elements in the correct place.\n";
        cout << "Time Complexity: O(n^2) (worst), O(n) (best)\nMemory: O(1)\nStable: Yes\n";
        cout << "Advantages:\n- Excellent for small or nearly sorted data\n- Stable and simple\n";
        cout << "Disadvantages:\n- Slow on large datasets\n";
        insertion_sort(temp, n);
        break;

    case 3:
        cout << "=== Bubble Sort ===\n";
        cout << "Idea: Repeatedly swap adjacent elements that are in the wrong order.\n";
        cout << "Time Complexity: O(n^2)\nMemory: O(1)\nStable: Yes\n";
        cout << "Advantages:\n- Very easy to understand\n";
        cout << "Disadvantages:\n- One of the slowest sorting algorithms\n";
        bubble_sort(temp, n);
        break;

    case 4:
        cout << "=== Quick Sort ===\n";
        cout << "Idea: Pick a pivot, partition the array, and sort recursively.\n";
        cout << "Time Complexity: O(n log n) average, O(n^2) worst\nMemory: O(log n)\nStable: No\n";
        cout << "Advantages:\n- Very fast in practice\n- Efficient for large datasets\n";
        cout << "Disadvantages:\n- Worst case: very slow\n- Not stable\n";
        quick_sort(temp, 0, n-1); 
        break;

    case 5:
        cout << "=== Merge Sort ===\n";
        cout << "Idea: Divide array into halves, sort each, then merge.\n";
        cout << "Time Complexity: O(n log n)\nMemory: O(n)\nStable: Yes\n";
        cout << "Advantages:\n- Guaranteed O(n log n)\n- Stable and efficient\n";
        cout << "Disadvantages:\n- Requires extra memory\n";
        merge_sort(temp, 0, n-1); 
        break;

    case 6:
        cout << "=== Heap Sort ===\n";
        cout << "Idea: Build a max heap and extract max repeatedly.\n";
        cout << "Time Complexity: O(n log n)\nMemory: O(1)\nStable: No\n";
        cout << "Advantages:\n- Good worst-case performance\n- No extra space\n";
        cout << "Disadvantages:\n- Not stable\n- Slower than quicksort in practice\n";
        heap_sort(temp, n); 
        break;

    case 7:
        cout << "=== Counting Sort ===\n";
        cout << "Idea: Count frequencies of numbers and rebuild array.\n";
        cout << "Time Complexity: O(n + k)\nMemory: O(k)\nStable: Yes\n";
        cout << "Advantages:\n- Extremely fast for small ranges\n- Stable\n";
        cout << "Disadvantages:\n- Uses large memory if max value is big\n- Only works for integers\n";
        counting_sort(temp, n); 
        break;

    case 8:
        cout << "=== Radix Sort ===\n";
        cout << "Idea: Sort integers digit-by-digit using counting sort.\n";
        cout << "Time Complexity: O((n + k) * d)\nMemory: O(n + k)\nStable: Yes\n";
        cout << "Advantages:\n- Very fast for fixed-size integers\n- Stable\n";
        cout << "Disadvantages:\n- Not good for floats or negative numbers\n- Needs counting sort\n";
        radix_sort(temp, n); 
        break;

    case 9:
        cout << "=== Shell Sort ===\n";
        cout << "Idea: Compare far apart elements using gaps.\n";
        cout << "Time Complexity: O(n^1.3) average (depends on gaps)\nMemory: O(1)\nStable: No\n";
        cout << "Advantages:\n- Faster than insertion for large arrays\n- Easy to implement\n";
        cout << "Disadvantages:\n- No guaranteed complexity\n- Not stable\n";
        shell_sort(temp, n); 
        break;

    case 10:
        cout << "=== Cocktail Sort ===\n";
        cout << "Idea: Bubble sort but in both directions.\n";
        cout << "Time Complexity: O(n^2)\nMemory: O(1)\nStable: Yes\n";
        cout << "Advantages:\n- Better than bubble sort when small elements are at the end\n";
        cout << "Disadvantages:\n- Still slow (O(n^2))\n";
        cocktail_sort(temp, n); 
        break;

    default:
        cout << "Invalid choice!\n";
        continue;
}


        cout << "Sorted array: ";
        print_array(temp, n);

    } while(choice != 0);

    return 0;
}
