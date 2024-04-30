#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <algorithm>

std::vector<int> generateData(int size)
{
    std::vector<int> data;
    for (int i = 1; i <= size; ++i)
    {
        data.push_back(i);
    }
    return data;
}

int binarySearch(const std::vector<int> &data, int key)
{
    int left = 0;
    int right = data.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (data[mid] == key)
        {
            return mid;
        }
        else if (data[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

void printVector(const std::vector<int> &vec)
{
    for (int num : vec)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void insertionSort(std::vector<int> &data)
{
    int n = data.size();
    for (int i = 1; i < n; ++i)
    {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j = j - 1;
        }
        data[j + 1] = key;
    }
}

void merge(std::vector<int> &data, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = data[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            data[k] = L[i];
            i++;
        }
        else
        {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        data[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortHelper(std::vector<int> &data, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSortHelper(data, left, mid);
        mergeSortHelper(data, mid + 1, right);
        merge(data, left, mid, right);
    }
}

void mergeSort(std::vector<int> &data)
{
    int n = data.size();
    mergeSortHelper(data, 0, n - 1);
}

int partition(std::vector<int> &data, int low, int high)
{
    int pivot = data[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (data[j] < pivot)
        {
            i++;
            std::swap(data[i], data[j]);
        }
    }
    std::swap(data[i + 1], data[high]);
    return i + 1;
}

void quickSortHelper(std::vector<int> &data, int low, int high)
{
    if (low < high)
    {
        int pi = partition(data, low, high);
        quickSortHelper(data, low, pi - 1);
        quickSortHelper(data, pi + 1, high);
    }
}

void quickSort(std::vector<int> &data)
{
    int n = data.size();
    quickSortHelper(data, 0, n - 1);
}

std::vector<int> generateRandomData(int size, int range)
{
    std::vector<int> data;
    srand(time(0)); 
    for (int i = 0; i < size; ++i)
    {
        data.push_back(rand() % range + 1);
    }
    return data;
}

void displayMenu()
{
    int choice;
    std::vector<int> data;
    int searchData;
    int dataSize;
    int range;

    do
    {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Generate Data\n";
        std::cout << "2. Binary Search\n";
        std::cout << "3. Insertion Sort\n";
        std::cout << "4. Additional Sorting Algorithms\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Enter data size: ";
            std::cin >> dataSize;
            data = generateData(dataSize);
            std::cout << "Data generated successfully." << std::endl;
            break;

        case 2:
            if (data.empty())
            {
                std::cout << "Data is empty. Please generate data first." << std::endl;
                break;
            }
            std::cout << "Enter the number to search: ";
            std::cin >> searchData;
            if (binarySearch(data, searchData) != -1)
                std::cout << "Number found at index: " << binarySearch(data, searchData) << std::endl;
            else
                std::cout << "Number not found." << std::endl;
            break;
        case 3:
            std::cout << "Enter data size for insertion sort: ";
            std::cin >> dataSize;
            data = generateRandomData(dataSize, 100);
            std::cout << "Data before sorting: ";
            printVector(data);
            insertionSort(data);
            std::cout << "Data after insertion sort: ";
            printVector(data);
            break;

        case 4:
            std::cout << "Choose sorting algorithm:\n";
            std::cout << "1. Merge Sort\n";
            std::cout << "2. Quick Sort\n";
            std::cout << "Enter your choice: ";
            int sortChoice;
            std::cin >> sortChoice;
            if (sortChoice == 1)
            {
                std::cout << "Applying Merge Sort\n";
                std::vector<int> randomData = generateRandomData(10, 100);
                std::cout << "Random data before sorting: ";
                printVector(randomData);
                mergeSort(randomData);
                std::cout << "Random data after sorting: ";
                printVector(randomData);
            }
            else if (sortChoice == 2)
            {
                std::cout << "Applying Quick Sort\n";
                std::vector<int> randomData = generateRandomData(10, 100);
                std::cout << "Random data before sorting: ";
                printVector(randomData);
                quickSort(randomData);
                std::cout << "Random data after sorting: ";
                printVector(randomData);
            }
            else
            {
                std::cout << "Invalid choice." << std::endl;
            }
            break;

        case 5:
            std::cout << "Exiting program..." << std::endl;
            break;

        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 5." << std::endl;
        }
    } while (choice != 5);
}

int main()
{
    displayMenu();
    return 0;
}
