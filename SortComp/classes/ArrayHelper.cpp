#include <ctime>
#include <cstdlib>
#include <iostream>
#include "ArrayHelper.h"
#include <utility>
#include <algorithm>

void ArrayHelper::print(const std::vector<int> &arr) {
    for (int elem: arr) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

bool ArrayHelper::checkSorted(const std::vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }

    return true;
}


std::vector<int> ArrayHelper::zeroFiveArray() {
    return createArray(0, 5);
}

std::vector<int> ArrayHelper::zeroFourThousandArray() {
    return createArray(0, 4000);
}

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





