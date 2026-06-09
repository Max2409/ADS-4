// Copyright 2021 NNTU-CS
#include <algorithm>

// Вспомогательные функции для бинарного поиска (countPairs3)
static int firstIndex(const int* arr, int left, int right, int value) {
    int l = left, r = right;
    int res = left; // будет указывать на начало, если value отсутствует
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] >= value) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    // Если число не равно value, возвращаем left (что даст нулевое количество)
    return (arr[res] == value) ? res : left;
}

// Находит индекс последнего вхождения value в подмассиве arr[left..right] или left-1, если значение не найдено.
static int lastIndex(const int* arr, int left, int right, int value) {
    int l = left, r = right;
    int res = left - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] <= value) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return res;
}


// 1. Полный перебор
int countPairs1(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len - 1; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] + arr[j] == value) {
                ++count;
            }
        }
    }
    return count;
}

// 2. Метод двух указателей
int countPairs2(int *arr, int len, int value) {
    if (len < 2) return 0;
    int left = 0;
    int right = len - 1;
    int pairs = 0;

    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum < value) {
            ++left;
        } else if (sum > value) {
            --right;
        } else { // sum == value
            // Если все элементы между left и right равны, считаем число сочетаний из (right - left + 1) по 2
            if (arr[left] == arr[right]) {
                int n = right - left + 1;
                pairs += n * (n - 1) / 2;
                break;
            }
            // Подсчитываем одинаковые элементы слева
            int leftVal = arr[left];
            int cntL = 0;
            while (left < right && arr[left] == leftVal) {
                ++cntL;
                ++left;
            }
            // Подсчитываем одинаковые элементы справа
            int rightVal = arr[right];
            int cntR = 0;
            while (left <= right && arr[right] == rightVal) {
                ++cntR;
                --right;
            }
            pairs += cntL * cntR;
        }
    }
    return pairs;
}

// 3. Бинарный поиск для каждого элемента
int countPairs3(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len - 1; ++i) {
        int target = value - arr[i];
        // Ищем target в правой части массива (индексы i+1 .. len-1)
        int first = firstIndex(arr, i + 1, len - 1, target);
        if (first > i && arr[first] == target) {
            int last = lastIndex(arr, first, len - 1, target);
            count += (last - first + 1);
        }
    }
    return count;
}
