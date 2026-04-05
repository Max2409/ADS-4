// Copyright 2021 NNTU-CS

int cbs(int* arr, int size, int value) {
    int l = 0, r = size, m;
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
              total++;
          }
      }
  }
  return total;
}

int countPairs2(int *arr, int len, int value) {
  int result = 0;
  int left = 0, right = len - 1;

  while (arr[right] > value) {
      right--;
  }
  right++;

  int savedRight = right;

  do {
      if ((left != right) && (arr[left] + arr[right] == value)) {
          result++;
          right--;
      } else if (arr[left] + arr[right] < value) {
          left++;
          right = savedRight;
      } else {
          right--;
      }
  } while (left != savedRight);

  return result / 2;
}

int countPairs3(int *arr, int len, int value) {
    int total = 0;
    int need;

    for (int idx = 0; idx < len; ++idx) {
        need = value - arr[idx];
        total += cbs(arr, size, value);
        if (need == value / 2) {
            total--;
        }
    }

    return total / 2;
}
