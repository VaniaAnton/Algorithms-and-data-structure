#include <iostream>
#include <cstdlib> // for rand()
#include <chrono>
#include <vector>
#include <string>

using namespace std;

class SimpleSortingAlgorithms
{
public:
    void bubbleSort(int arr[], int n, int &counter)
    {
        int i, j;
        bool swapped;
        for (i = 0; i < n - 1; i++)
        {
            swapped = false;
            for (j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                    counter++;
                }
            }
            if (swapped == false)
                break;
        }
    }

    void insertionSort(int arr[], int n, int &counter)
    {
        int i, key, j;
        for (i = 1; i < n; i++)
        {
            key = arr[i];
            j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
                counter++;
            }
            arr[j + 1] = key;
        }
    }
    void selectionSort(int arr[], int n, int &counter)
    {
        int i, j, min_idx;
        for (i = 0; i < n - 1; i++)
        {

            min_idx = i;
            for (j = i + 1; j < n; j++)
            {
                if (arr[j] < arr[min_idx])
                    min_idx = j;
            }
            if (min_idx != i)
            {
                swap(arr[min_idx], arr[i]);
                counter++;
            }
        }
    }
};
class QuickSortingAlgorithms
{
public:
    void quickSort(int arr[], int left, int right, int &counter)
    {
        int i = left, j = right;
        int pivot = arr[(left + right) / 2];
        int temp;
        while (i <= j)
        {
            while (arr[i] < pivot)
            {
                i++;
                counter++;
            }
            while (arr[j] > pivot)
            {
                j--;
                counter--;
            }
            if (i <= j)
            {
                temp = arr[i];
                arr[i++] = arr[j];
                arr[j--] = temp;
                counter++;
            }
        }
        if (left < j)
        {
            quickSort(arr, left, j, counter);
        }
        if (i < right)
        {
            quickSort(arr, i, right, counter);
        }
    }
    void heapify(int arr[], int N, int i, int &counter)
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < N && arr[l] > arr[largest])
        {
            counter++;
            largest = l;
        }
        if (r < N && arr[r] > arr[largest])
        {
            counter++;
            largest = r;
        }
        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            heapify(arr, N, largest, counter);
        }
    }
    void heapSort(int arr[], int N, int &counter)
    {
        for (int i = N / 2 - 1; i >= 0; i--)
            heapify(arr, N, i, counter);

        for (int i = N - 1; i > 0; i--)
        {

            swap(arr[0], arr[i]);
            counter++;
            heapify(arr, i, 0, counter);
        }
    }
    void merge(int arr[], int left, int mid, int right, int &counter)
    {
        int i, j, k;
        int n1 = mid - left + 1;
        int n2 = right - mid;
        int L[n1], R[n2];
        for (i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];
        i = 0;
        j = 0;
        k = left;
        while (i < n1 && j < n2)
        {
            counter++;
            if (L[i] <= R[j])
            {
                arr[k++] = L[i++];
            }
            else
            {
                arr[k++] = R[j++];
            }
        }
        while (i < n1)
        {
            arr[k++] = L[i++];
        }
        while (j < n2)
        {
            arr[k++] = R[j++];
        }
    }
    void mergeSort(int arr[], int left, int right, int &counter)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid, counter);
            mergeSort(arr, mid + 1, right, counter);
            merge(arr, left, mid, right, counter);
        }
    }
    int shellSort(int arr[], int n, int &counter)
    {
        for (int gap = n / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i += 1)
            {
                int temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                    arr[j] = arr[j - gap];
                counter++;
                arr[j] = temp;
            }
        }
        return 0;
    }
    int getMax(int arr[], int n)
    {
        int mx = arr[0];
        for (int i = 1; i < n; i++)
            if (arr[i] > mx)
                mx = arr[i];
        return mx;
    }
    void countSort(int arr[], int n, int exp, int &counter)
    {

        int output[n];
        int i, count[10] = {0};

        for (i = 0; i < n; i++)
            count[(arr[i] / exp) % 10]++;
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];
        for (i = n - 1; i >= 0; i--)
        {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        for (i = 0; i < n; i++)
            arr[i] = output[i];
        counter++;
    }
    void radixSort(int arr[], int n, int &counter)
    {
        int m = getMax(arr, n);
        for (int exp = 1; m / exp > 0; exp *= 10)
            countSort(arr, n, exp, counter);
    }
};

class Tests : public SimpleSortingAlgorithms, public QuickSortingAlgorithms
{
public:
    void forBubbleSort(int arr[], int n)
    {
        int counter = 0;
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arr, n, counter);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time and integration taken by Bubble sorting Algorithm: "
             << duration.count() << " microseconds"
             << " and " << counter << " swaps: " << endl;
    }
    void forInsertionSort(int arr[], int n)
    {
        int counter = 0;
        auto start = chrono::high_resolution_clock::now();
        insertionSort(arr, n, counter);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time and integration taken by Insertion sorting Algorithm: "
             << duration.count() << " microseconds"
             << " and " << counter << " swaps: " << endl;
    }
    void forSelectionSort(int arr[], int n)
    {
        int counter = 0;
        auto start = chrono::high_resolution_clock::now();
        selectionSort(arr, n, counter);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time and integration taken by Selection sorting Algorithm: "
             << duration.count() << " microseconds"
             << " and " << counter << " swaps: " << endl;
    }
    void forQuickSort(int arr[], int n)
    {
        int counter = 0;
        auto start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, n - 1, counter);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time and integration taken by Quick sorting Algorithm: "
             << duration.count() << " microseconds"
             << " and " << counter << " swaps: " << endl;
    }
    void forHeapSort(int arr[], int n)
    {
        int counter = 0;
        auto start = chrono::high_resolution_clock::now();
        heapSort(arr, n, counter);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time and integration taken by Heap sorting Algorithm: "
             << duration.count() << " microseconds"
             << " and " << counter << " swaps: " << endl;
    }
    void forMergeSort(int arr[], int n)
    {
        int counter = 0;
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arr, 0, n - 1, counter);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time and integration taken by Merge sorting Algorithm: "
             << duration.count() << " microseconds"
             << " and " << counter << " swaps: " << endl;
    }
    void forShellSort(int arr[], int n)
    {
        int counter = 0;
        auto start = chrono::high_resolution_clock::now();
        shellSort(arr, n, counter);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time and integration taken by Shell sorting Algorithm: "
             << duration.count() << " microseconds"
             << " and " << counter << " swaps: " << endl;
    }
    void forRadixSort(int arr[], int n)
    {
        int counter = 0;
        auto start = chrono::high_resolution_clock::now();
        radixSort(arr, n, counter);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time and integration taken by Radix sorting Algorithm: "
             << duration.count() << " microseconds"
             << " and " << counter << " swaps: " << endl;
    }

    void checkTime(int arr[], int n)
    {
        int optionSimple = 1; // 1 for bubble, 2 for insertion, 3 for selection
        int optionQuick = 2;  // 1 for quick, 2 for heap, 3 for merge, 4 for shell, 5 for radix
        switch (optionSimple)
        {
        case 1:
            forBubbleSort(arr, n);
            break;
        case 2:
            forInsertionSort(arr, n);
            break;
        case 3:
            forSelectionSort(arr, n);
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
        switch (optionQuick)
        {
        case 1:
            forQuickSort(arr, n);
            break;
        case 2:
            forHeapSort(arr, n);
            break;
        case 3:
            forMergeSort(arr, n);
            break;
        case 4:
            forShellSort(arr, n);
            break;
        case 5:
            forRadixSort(arr, n);
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
    }
    void test5k_unsorted()
    {
        int arr[5000];
        for (int i = 0; i < 5000; i++)
        {
            arr[i] = rand() % 5000;
        }
        int n = sizeof(arr) / sizeof(arr[0]);
        checkTime(arr, n);
    }
    void test5k_reverseSorted()
    {
        int arr[5000];
        for (int i = 0; i < 5000; i++)
        {
            arr[i] = 5000 - i;
        }
        int n = sizeof(arr) / sizeof(arr[0]);
        checkTime(arr, n);
    }
    void test5k_sorted()
    {
        int arr[5000];
        for (int i = 0; i < 5000; i++)
        {
            arr[i] = i;
        }
        int n = sizeof(arr) / sizeof(arr[0]);
        checkTime(arr, n);
    }
    void test10k_unsorted()
    {
        int arr[10000];
        for (int i = 0; i < 10000; i++)
        {
            arr[i] = rand() % 10000;
        }
        int n = sizeof(arr) / sizeof(arr[0]);
        checkTime(arr, n);
    }
    void test10k_reverseSorted()
    {
        int arr[10000];
        for (int i = 0; i < 10000; i++)
        {
            arr[i] = 10000 - i;
        }
        int n = sizeof(arr) / sizeof(arr[0]);
        checkTime(arr, n);
    }
    void test10k_sorted()
    {
        int arr[10000];
        for (int i = 0; i < 10000; i++)
        {
            arr[i] = i;
        }
        int n = sizeof(arr) / sizeof(arr[0]);
        checkTime(arr, n);
    }
    void test50k_unsorted()
    {
        int arr[50000];
        for (int i = 0; i < 50000; i++)
        {
            arr[i] = rand() % 50000;
        }
        int n = sizeof(arr) / sizeof(arr[0]);
        checkTime(arr, n);
    }
    void test50k_reverseSorted()
    {
        int arr[50000];
        for (int i = 0; i < 50000; i++)
        {
            arr[i] = 50000 - i;
        }
        int n = sizeof(arr) / sizeof(arr[0]);
        checkTime(arr, n);
    }
    void test50k_sorted()
    {
        int arr[50000];
        for (int i = 0; i < 50000; i++)
        {
            arr[i] = i;
        }
        int n = sizeof(arr) / sizeof(arr[0]);
        checkTime(arr, n);
    }
    void test100k_unsorted()
    {
        int arr[100000];
        for (int i = 0; i < 100000; i++)
        {
            arr[i] = rand() % 100000;
        }
        int n = sizeof(arr) / sizeof(arr[0]);
        checkTime(arr, n);
    }
    void test100k_reverseSorted()
    {
        int arr[100000];
        for (int i = 0; i < 100000; i++)
        {
            arr[i] = 100000 - i;
        }
        int n = sizeof(arr) / sizeof(arr[0]);
        checkTime(arr, n);
    }
    void test100k_sorted()
    {
        int arr[100000];
        for (int i = 0; i < 100000; i++)
        {
            arr[i] = i;
        }
        int n = sizeof(arr) / sizeof(arr[0]);
        checkTime(arr, n);
    }
};
class AllTests : public Tests
{
public:
    void testAll()
    {
        cout << "-----------5k_unsorted-------------" << endl;
        test5k_unsorted();
        cout << "-----------5k_sorted-------------" << endl;
        test5k_sorted();
        cout << "-----------5k_reverseSorted-------------" << endl;
        test5k_reverseSorted();
        cout << "-----------10k_unsorted-------------" << endl;
        test10k_unsorted();
        cout << "-----------10k_sorted-------------" << endl;
        test10k_sorted();
        cout << "-----------10k_reverseSorted-------------" << endl;
        test10k_reverseSorted();
        cout << "-----------50k_unsorted-------------" << endl;
        test50k_unsorted();
        cout << "-----------50k_sorted-------------" << endl;
        test50k_sorted();
        cout << "-----------50k_reverseSorted-------------" << endl;
        test50k_reverseSorted();
        cout << "-----------100k_unsorted-------------" << endl;
        test100k_unsorted();
        cout << "-----------100k_sorted-------------" << endl;
        test100k_sorted();
        cout << "-----------100k_reverseSorted-------------" << endl;
        test100k_reverseSorted();
    }
};
int main()
{
    AllTests test;
    test.testAll();
}