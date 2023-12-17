#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>


using namespace std;
using namespace chrono;

void quadExchange(int& a, int& b, int& c, int& d) 
{
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
    if (b > d) swap(b, d);
}

void quadSort(vector<int>& arr, int start, int end) 
{
    if (start >= end) 
    {
        return;
    }

    int middle = start + (end - start) / 2;
    quadSort(arr, start, middle);
    quadSort(arr, middle + 1, end);
    quadExchange(arr[start], arr[middle], arr[middle + 1], arr[end]);
    quadSort(arr, start + 1, end - 1);
}

void printArray(const vector<int>& arr) 
{
    for (int num : arr) 
    {
        cout << num << " ";
    }
    cout << "\n";
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    // Покажем, что сортировка работает:
    /*
    vector<int> arr = { 4, 1, 2, 7, 3, 5, 8, 6 }; // Пример случайного массива

    cout << "Исходный массив: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    // Вызываем quadSort для сортировки массива
    quadSort(arr, 0, arr.size() - 1);

    cout << "Отсортированный массив: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";
    */

    // а теперь посмотрим на время работы

    
    // Размер массива
    int arraySize;
    cout << "Введите размер массива: ";
    cin >> arraySize;

    vector<int> arrRandom(arraySize);
    vector<int> arrSorted(arraySize);
    vector<int> arrPartiallySorted(arraySize);
    vector<int> arrReversed(arraySize);

    // Генерация случайного массива
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < arraySize; ++i) 
    {
        arrRandom[i] = rand() % 1000; // Максимальное значение - 1000 (просто для примера)
    }

    // Сортировка исходных массивов
    iota(arrSorted.begin(), arrSorted.end(), 1);
    iota(arrReversed.rbegin(), arrReversed.rend(), 1);

    int partialSortSize = arraySize / 2;
    iota(arrPartiallySorted.begin(), arrPartiallySorted.begin() + partialSortSize, 1);
    iota(arrPartiallySorted.begin() + partialSortSize, arrPartiallySorted.end(), partialSortSize + 1);

    // Измерение времени для случайного массива
    auto start = high_resolution_clock::now();
    quadSort(arrRandom, 0, arraySize - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Время для случайного массива: " << duration.count() << " микросекунд\n";

    // Измерение времени для отсортированного массива
    start = high_resolution_clock::now();
    quadSort(arrSorted, 0, arraySize - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Время для отсортированного массива: " << duration.count() << " микросекунд\n";

    // Измерение времени для частично отсортированного массива
    start = high_resolution_clock::now();
    quadSort(arrPartiallySorted, 0, arraySize - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Время для частично отсортированного массива: " << duration.count() << " микросекунд\n";

    // Измерение времени для обратно отсортированного массива
    start = high_resolution_clock::now();
    quadSort(arrReversed, 0, arraySize - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    cout << "Время для обратно отсортированного массива: " << duration.count() << " микросекунд\n";

    


    return 0;
}
