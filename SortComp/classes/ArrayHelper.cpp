#include <ctime>
#include <cstdlib>
#include <iostream>
#include "ArrayHelper.h"
#include <utility>
#include <algorithm>

// Печать массива.
void ArrayHelper::print(const std::vector<int> &arr) {
    for (int elem: arr) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

// Проверка, что массив отсортирован.
bool ArrayHelper::checkSorted(const std::vector<int> &arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }

    return true;
}

// Первый тип массива.
std::vector<int> ArrayHelper::zeroFiveArray() {
    return createArray(0, 5);
}

// Второй тип массива.
std::vector<int> ArrayHelper::zeroFourThousandArray() {
    return createArray(0, 4000);
}

// Третий тип массива.
std::vector<int> ArrayHelper::almostSortedArray(int step, int swaps) {
    std::vector<int> arr = createArray(0, 4000);

    std::sort(arr.begin(), arr.end());
    for (int i = 0; i < arr.size(); i += step) {
        for (int j = 0; j < swaps; ++j) {
            int first_ind = i + rand() % step;
            int second_ind = i + rand() % step;
            std::swap(arr[first_ind], arr[second_ind]);
        }
    }

    return arr;
}

// Четвертый тип массива.
std::vector<int> ArrayHelper::reversedArray() const {
    std::vector<int> arr(size_);

    for (int i = 0; i < size_; ++i) {
        arr[i] = size_ - i;
    }

    return arr;
}

std::vector<int> ArrayHelper::createArray(int min, int max) const {
    std::vector<int> arr(size_);

    for (int i = 0; i < size_; ++i) {
        int num = min + rand() % (max - min + 1);
        arr[i] = num;
    }

    return arr;
}





