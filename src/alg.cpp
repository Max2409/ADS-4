// Copyright 2021 NNTU-CS

int cbs(int* arr, int size, int value) {
    int l = 0, r = size, m = 0; 
    int firstPos, lastPos, result;

    while (l < r) {
        m = (l + r) / 2;
        if (value > arr[m]) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    firstPos = l;

    l = 0;
    r = size;
    while (l < r) {
        m = (l + r) / 2;
        if (value < arr[m]) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    lastPos = r;

    result = lastPos - firstPos;
    return result;
}

int countPairs1(int *arr, int len, int value) {
    int total = 0;
    for (int idx1 = 0; idx1 < len - 1; ++idx1) {
        for (int idx2 = idx1 + 1; idx2 < len; ++idx2) {
            if (arr[idx1] + arr[idx2] == value) {
                ++total;
            }
        }
    }
    return total;
}

int countPairs2(int *arr, int len, int value) {
    if (len < 2) return 0;
    int result = 0;
    int left = 0, right = len - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == value) {
            if (arr[left] == arr[right]) {
                
                int cnt = right - left + 1;
                result += cnt * (cnt - 1) / 2;
                break;
            } else {
                int leftCount = 1, rightCount = 1;
                
                while (left + 1 < right && arr[left] == arr[left + 1]) {
                    ++leftCount;
                    ++left;
                }
                
                while (right - 1 > left && arr[right] == arr[right - 1]) {
                    ++rightCount;
                    --right;
                }
                result += leftCount * rightCount;
                ++left;
                --right;
            }
        } else if (sum < value) {
            ++left;
        } else {
            --right;
        }
    }
    return result;
}

int countPairs3(int *arr, int len, int value) {
    int total = 0;
    int need;

    for (int idx = 0; idx < len; ++idx) {
        need = value - arr[idx];
        total += cbs(arr, len, need);
        if (need == value / 2) {
            --total;
        }
    }

    return total / 2;
}
