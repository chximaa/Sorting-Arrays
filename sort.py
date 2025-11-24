arr = [1,8,17,19,2,3,10,12,5,16,7,11,18,20,4,6,9,13,14,15]

# ---------------------------------------
# Selection Sort
# ---------------------------------------
def selection_sort(arr):
    n = len(arr)
    for i in range(n):
        min_index = i
        for j in range(i+1, n):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]
    return arr

# ---------------------------------------
# Insertion Sort
# ---------------------------------------
def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        
        while j >= 0 and arr[j] > key:
            arr[j+1] = arr[j]
            j -= 1
        
        arr[j+1] = key

    return arr

# ---------------------------------------
# Bubble Sort
# ---------------------------------------
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

# ---------------------------------------
# Quick Sort
# ---------------------------------------
def quick_sort(arr):
    if len(arr) <= 1:
        return arr

    pivot = arr[len(arr)//2]
    left = [x for x in arr if x < pivot]
    mid  = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]

    return quick_sort(left) + mid + quick_sort(right)

# ---------------------------------------
# Merge Sort
# ---------------------------------------
def merge_sort(arr):
    if len(arr) <= 1:
        return arr

    mid = len(arr)//2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])

    return merge(left, right)


def merge(left, right):
    result = []
    i = j = 0

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    result.extend(left[i:])
    result.extend(right[j:])
    return result

# ---------------------------------------
# Heap Sort
# ---------------------------------------
def heapify(arr, n, i):
    largest = i
    left = 2*i + 1
    right = 2*i + 2

    if left < n and arr[left] > arr[largest]:
        largest = left

    if right < n and arr[right] > arr[largest]:
        largest = right

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)


def heap_sort(arr):
    n = len(arr)

    for i in range(n//2 - 1, -1, -1):
        heapify(arr, n, i)

    for i in range(n-1, -1, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)

    return arr

# ---------------------------------------
# Counting Sort
# ---------------------------------------
def counting_sort(arr):
    if len(arr) == 0:
        return arr

    max_val = max(arr)
    count = [0] * (max_val + 1)

    for num in arr:
        count[num] += 1

    result = []
    for i in range(len(count)):
        result.extend([i] * count[i])

    return result

# ---------------------------------------
# Radix Sort
# ---------------------------------------
def counting_sort_for_radix(arr, exp):
    n = len(arr)
    output = [0] * n
    count = [0] * 10

    for number in arr:
        index = (number // exp) % 10
        count[index] += 1

    for i in range(1, 10):
        count[i] += count[i-1]

    for i in range(n-1, -1, -1):
        index = (arr[i] // exp) % 10
        output[count[index] - 1] = arr[i]
        count[index] -= 1

    return output

def radix_sort(arr):
    if len(arr) == 0:
        return arr

    max_val = max(arr)
    exp = 1

    while max_val // exp > 0:
        arr = counting_sort_for_radix(arr, exp)
        exp *= 10

    return arr

# ---------------------------------------
# Shell Sort
# ---------------------------------------
def shell_sort(arr):
    n = len(arr)
    gap = n // 2

    # Reduce the gap each time
    while gap > 0:
        for i in range(gap, n):
            temp = arr[i]
            j = i

            # Insertion sort with gap
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap]
                j -= gap

            arr[j] = temp

        gap //= 2

    return arr


# ---------------------------------------
# Cocktail Shaker Sort
# ---------------------------------------
def cocktail_sort(arr):
    n = len(arr)
    start = 0
    end = n - 1
    swapped = True

    while swapped:
        swapped = False

        # Forward pass
        for i in range(start, end):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True

        if not swapped:
            break

        swapped = False
        end -= 1

        # Backward pass
        for i in range(end - 1, start - 1, -1):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True

        start += 1

    return arr



# ---------------------------------------
# Main Program
# ---------------------------------------
while True:
    print("\n--- Sorting Algorithms Menu ---")
    print("1 - Selection Sort")
    print("2 - Insertion Sort")
    print("3 - Bubble Sort")
    print("4 - Quick Sort")
    print("5 - Merge Sort")
    print("6 - Heap Sort")
    print("7 - Counting Sort")
    print("8 - Radix Sort")
    print("0 - Exit")

    choice = int(input("Please choose a sort type: "))

    if choice == 0:
        print("Exiting program...")
        break

    if choice == 1:
        res = selection_sort(arr.copy())
        print("""
Selection Sort:
    We scan the array to find the smallest element and place it at the beginning.
    Then we repeat the process for the rest of the array.
    Complexity:
        Time: O(n²) - Memory: O(1) - Not stable
    Advantage: Simple
    Disadvantage: Very slow for large arrays.
        """)
        print("Result =", res)

    elif choice == 2:
        res = insertion_sort(arr.copy())
        print("""
Insertion Sort:
    We build the sorted list one element at a time by inserting each value
    into its correct position.
    Complexity:
        Time: O(n²) - Memory: O(1) - Stable
    Advantage: Fast if the array is nearly sorted.
    Disadvantage: Slow for large unsorted arrays.
        """)
        print("Result =", res)

    elif choice == 3:
        res = bubble_sort(arr.copy())
        print("""
Bubble Sort:
    We repeatedly compare adjacent elements and swap them if needed.
    Large values "bubble up" to the end.
    Complexity:
        Time: O(n²) - Memory: O(1) - Stable
    Advantage: Very simple to implement.
    Disadvantage: One of the slowest sorting algorithms.
        """)
        print("Result =", res)

    elif choice == 4:
        res = quick_sort(arr.copy())
        print("""
Quick Sort:
    We choose a pivot, split the array into smaller and greater elements,
    and sort the subarrays recursively.
    Complexity:
        Average: O(n log n) - Worst: O(n²) - Memory: O(log n)
    Advantage: Very fast in practice.
    Disadvantage: Bad pivot choice leads to worst-case behavior.
        """)
        print("Result =", res)

    elif choice == 5:
        res = merge_sort(arr.copy())
        print("""
Merge Sort:
    We divide the array into two halves, sort each half, then merge them.
    Complexity:
        Time: O(n log n) - Memory: O(n) - Stable
    Advantage: Very reliable and consistent performance.
    Disadvantage: Uses extra memory.
        """)
        print("Result =", res)

    elif choice == 6:
        res = heap_sort(arr.copy())
        print("""
Heap Sort:
    We build a heap and repeatedly extract the maximum element.
    Complexity:
        Time: O(n log n) - Memory: O(1) - Not stable
    Advantage: Uses constant memory.
    Disadvantage: More complex than other sorts.
        """)
        print("Result =", res)

    elif choice == 7:
        res = counting_sort(arr.copy())
        print("""
Counting Sort:
    We count how many times each value appears.
    Only works for integers in a limited range.
    Complexity:
        Time: O(n + k) - Memory: O(k) - Stable
    Advantage: Extremely fast when range is small.
    Disadvantage: Cannot be used for large or negative ranges.
        """)
        print("Result =", res)

    elif choice == 8:
        res = radix_sort(arr.copy())
        print("""
Radix Sort:
    We sort numbers digit by digit using Counting Sort as a subroutine.
    Complexity:
        Time: O(d * (n + k)) - Memory: O(n + k) - Stable
    Advantage: Very fast for large integers.
    Disadvantage: Works only for integers.
        """)
        print("Result =", res)

    elif choice == 9:
        res = shell_sort(arr.copy())
        print("""
Shell Sort:
    A generalization of insertion sort that allows exchanging elements far apart.
    The algorithm starts with a big gap and reduces it until it becomes 1.
    Complexity:
        Average: O(n^1.3) - Worst: O(n²) - Memory: O(1)
    Advantage: Faster than Insertion Sort for large arrays.
    Disadvantage: Complexity depends on the gap sequence.
        """)
        print("Result =", res)

    elif choice == 10:
        res = cocktail_sort(arr.copy())
        print("""
Cocktail Shaker Sort:
    A variation of Bubble Sort that sorts in both directions.
    This helps move small elements to the beginning faster.
    Complexity:
        Time: O(n²) - Memory: O(1) - Stable
    Advantage: Improves Bubble Sort's performance.
    Disadvantage: Still slow for large arrays.
        """)
        print("Result =", res)

    else:
        print("Invalid choice. Please try again.")
