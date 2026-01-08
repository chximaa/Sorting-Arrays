import java.util.*;

public class sort{

    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {

        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();

        int[] arr = new int[n];
        System.out.println("Enter elements:");
        for (int i = 0; i < n; i++)
            arr[i] = sc.nextInt();

        while (true) {
            System.out.println("\n====== SORTING MENU ======");
            System.out.println("1. Selection Sort");
            System.out.println("2. Insertion Sort");
            System.out.println("3. Bubble Sort");
            System.out.println("4. Quick Sort");
            System.out.println("5. Merge Sort");
            System.out.println("6. Heap Sort");
            System.out.println("7. Counting Sort");
            System.out.println("8. Radix Sort");
            System.out.println("9. Shell Sort");
            System.out.println("10. Cocktail Shaker Sort");
            System.out.println("0. Exit");
            System.out.print("Choose: ");

            int choice = sc.nextInt();
            int[] copy = arr.clone();

            switch (choice) {
                case 1 -> { explainSelection(); selectionSort(copy); }
                case 2 -> { explainInsertion(); insertionSort(copy); }
                case 3 -> { explainBubble(); bubbleSort(copy); }
                case 4 -> { explainQuick(); quickSort(copy, 0, copy.length - 1); }
                case 5 -> { explainMerge(); mergeSort(copy, 0, copy.length - 1); }
                case 6 -> { explainHeap(); heapSort(copy); }
                case 7 -> { explainCounting(); countingSort(copy); }
                case 8 -> { explainRadix(); radixSort(copy); }
                case 9 -> { explainShell(); shellSort(copy); }
                case 10 -> { explainCocktail(); cocktailSort(copy); }
                case 0 -> System.exit(0);
                default -> System.out.println("Invalid choice!");
            }

            if (choice >= 1 && choice <= 10) {
                System.out.println("Sorted Array: " + Arrays.toString(copy));
            }
        }
    }

    /* =================== SORTING ALGORITHMS =================== */

    static void selectionSort(int[] a) {
        for (int i = 0; i < a.length - 1; i++) {
            int min = i;
            for (int j = i + 1; j < a.length; j++)
                if (a[j] < a[min]) min = j;
            swap(a, i, min);
        }
    }

    static void insertionSort(int[] a) {
        for (int i = 1; i < a.length; i++) {
            int key = a[i], j = i - 1;
            while (j >= 0 && a[j] > key) {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = key;
        }
    }

    static void bubbleSort(int[] a) {
        for (int i = 0; i < a.length - 1; i++)
            for (int j = 0; j < a.length - i - 1; j++)
                if (a[j] > a[j + 1])
                    swap(a, j, j + 1);
    }

    static void quickSort(int[] a, int low, int high) {
        if (low < high) {
            int p = partition(a, low, high);
            quickSort(a, low, p - 1);
            quickSort(a, p + 1, high);
        }
    }

    static int partition(int[] a, int low, int high) {
        int pivot = a[high];
        int i = low - 1;
        for (int j = low; j < high; j++)
            if (a[j] <= pivot)
                swap(a, ++i, j);
        swap(a, i + 1, high);
        return i + 1;
    }

    static void mergeSort(int[] a, int l, int r) {
        if (l < r) {
            int m = (l + r) / 2;
            mergeSort(a, l, m);
            mergeSort(a, m + 1, r);
            merge(a, l, m, r);
        }
    }

    static void merge(int[] a, int l, int m, int r) {
        int[] left = Arrays.copyOfRange(a, l, m + 1);
        int[] right = Arrays.copyOfRange(a, m + 1, r + 1);
        int i = 0, j = 0, k = l;
        while (i < left.length && j < right.length)
            a[k++] = left[i] <= right[j] ? left[i++] : right[j++];
        while (i < left.length) a[k++] = left[i++];
        while (j < right.length) a[k++] = right[j++];
    }

    static void heapSort(int[] a) {
        for (int i = a.length / 2 - 1; i >= 0; i--)
            heapify(a, a.length, i);
        for (int i = a.length - 1; i > 0; i--) {
            swap(a, 0, i);
            heapify(a, i, 0);
        }
    }

    static void heapify(int[] a, int n, int i) {
        int largest = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && a[l] > a[largest]) largest = l;
        if (r < n && a[r] > a[largest]) largest = r;
        if (largest != i) {
            swap(a, i, largest);
            heapify(a, n, largest);
        }
    }

    static void countingSort(int[] a) {
        int max = Arrays.stream(a).max().getAsInt();
        int[] count = new int[max + 1];
        for (int x : a) count[x]++;
        int idx = 0;
        for (int i = 0; i < count.length; i++)
            while (count[i]-- > 0)
                a[idx++] = i;
    }

    static void radixSort(int[] a) {
        int max = Arrays.stream(a).max().getAsInt();
        for (int exp = 1; max / exp > 0; exp *= 10)
            countingSortByDigit(a, exp);
    }

    static void countingSortByDigit(int[] a, int exp) {
        int[] output = new int[a.length];
        int[] count = new int[10];
        for (int x : a) count[(x / exp) % 10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];
        for (int i = a.length - 1; i >= 0; i--) {
            int d = (a[i] / exp) % 10;
            output[--count[d]] = a[i];
        }
        System.arraycopy(output, 0, a, 0, a.length);
    }

    static void shellSort(int[] a) {
        for (int gap = a.length / 2; gap > 0; gap /= 2)
            for (int i = gap; i < a.length; i++) {
                int temp = a[i], j;
                for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
                    a[j] = a[j - gap];
                a[j] = temp;
            }
    }

    static void cocktailSort(int[] a) {
        boolean swapped = true;
        int start = 0, end = a.length - 1;
        while (swapped) {
            swapped = false;
            for (int i = start; i < end; i++)
                if (a[i] > a[i + 1]) {
                    swap(a, i, i + 1);
                    swapped = true;
                }
            end--;
            for (int i = end; i > start; i--)
                if (a[i] < a[i - 1]) {
                    swap(a, i, i - 1);
                    swapped = true;
                }
            start++;
        }
    }

    static void swap(int[] a, int i, int j) {
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }

    /* =================== EXPLANATIONS =================== */

    static void explainSelection() {
        System.out.println("\nSelection Sort:");
        System.out.println("Time: O(n²)");
        System.out.println("Advantage: Simple, minimal swaps");
        System.out.println("Disadvantage: Very slow for large data");
    }

    static void explainInsertion() {
        System.out.println("\nInsertion Sort:");
        System.out.println("Time: O(n²), Best O(n)");
        System.out.println("Advantage: Efficient for small/nearly sorted data");
        System.out.println("Disadvantage: Poor for large datasets");
    }

    static void explainBubble() {
        System.out.println("\nBubble Sort:");
        System.out.println("Time: O(n²)");
        System.out.println("Advantage: Easy to understand");
        System.out.println("Disadvantage: Extremely inefficient");
    }

    static void explainQuick() {
        System.out.println("\nQuick Sort:");
        System.out.println("Time: Avg O(n log n), Worst O(n²)");
        System.out.println("Advantage: Very fast in practice");
        System.out.println("Disadvantage: Worst case if bad pivot");
    }

    static void explainMerge() {
        System.out.println("\nMerge Sort:");
        System.out.println("Time: O(n log n)");
        System.out.println("Advantage: Stable, predictable performance");
        System.out.println("Disadvantage: Uses extra memory");
    }

    static void explainHeap() {
        System.out.println("\nHeap Sort:");
        System.out.println("Time: O(n log n)");
        System.out.println("Advantage: No extra memory");
        System.out.println("Disadvantage: Not stable");
    }

    static void explainCounting() {
        System.out.println("\nCounting Sort:");
        System.out.println("Time: O(n + k)");
        System.out.println("Advantage: Extremely fast for small ranges");
        System.out.println("Disadvantage: Works only for non-negative integers");
    }

    static void explainRadix() {
        System.out.println("\nRadix Sort:");
        System.out.println("Time: O(d(n + k))");
        System.out.println("Advantage: Faster than comparison sorts");
        System.out.println("Disadvantage: Limited to integers");
    }

    static void explainShell() {
        System.out.println("\nShell Sort:");
        System.out.println("Time: Depends on gap sequence");
        System.out.println("Advantage: Faster than insertion sort");
        System.out.println("Disadvantage: Complex analysis");
    }

    static void explainCocktail() {
        System.out.println("\nCocktail Shaker Sort:");
        System.out.println("Time: O(n²)");
        System.out.println("Advantage: Better than bubble sort");
        System.out.println("Disadvantage: Still slow");
    }
}
