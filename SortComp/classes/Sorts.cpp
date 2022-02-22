#include <vector>
#include "Sorts.h"
#include <utility>
#include <algorithm>

void Sorts::selectionSort(std::vector<int> *a) {
    for (int index = 0; index < a->size() - 1; ++index) {
        int min = index;

        for (int j = index + 1; j < a->size(); ++j) {
            if ((*a)[j] < (*a)[min]) {
                min = j;
            }
        }
        if (index != min) {
            std::swap((*a)[index], (*a)[min]);
        }
    }
}

void Sorts::bubbleSort(std::vector<int> *a) {
    for (int i = 0; i < a->size() - 1; ++i) {
        for (int j = 0; j < a->size() - i - 1; ++j) {
            if ((*a)[j + 1] < (*a)[j]) {
                std::swap((*a)[j + 1], (*a)[j]);
            }
        }
    }
}

void Sorts::bubbleAiversonOneSort(std::vector<int> *a) {
    int count = 0;
    int i = 0;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int j = 0; j < a->size() - i - 1; ++j) {
            if ((*a)[j + 1] < (*a)[j]) {
                std::swap((*a)[j + 1], (*a)[j]);
                ++count;
                swapped = true;
            }
        }
        ++i;
    }
}

void Sorts::bubbleAiversonTwoSort(std::vector<int> *a) {
    int swapped_pos = a->size() - 1;
    while (swapped_pos != 0) {
        int new_swapped_pos = 0;
        for (int j = 0; j < swapped_pos; ++j) {
            if ((*a)[j + 1] < (*a)[j]) {
                std::swap((*a)[j + 1], (*a)[j]);
                new_swapped_pos = j;
            }
        }
        swapped_pos = new_swapped_pos;
    }
}

void Sorts::insertionSort(std::vector<int> *a) {
    for (int index = 1; index < a->size(); ++index) {
        int j = index - 1;
        int cur = (*a)[index];

        while (j >= 0 && cur < (*a)[j]) {
            (*a)[j + 1] = (*a)[j];
            --j;
        }

        (*a)[j + 1] = cur;
    }
}

int Sorts::sorterBS(const std::vector<int> &a, int len, int key) {
    int left = 0;
    int right = len;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (key >= a[mid]) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

void Sorts::binaryInsertionSort(std::vector<int> *a) {
    for (int i = 1; i < a->size(); ++i) {
        int cur = (*a)[i];
        if (cur < (*a)[i - 1]) {
            int t = sorterBS(*a, i - 1, cur);
            for (int j = i - 1; j >= t; --j) {
                std::swap((*a)[j], (*a)[j + 1]);
            }
        }
    }
}

void Sorts::stableCountSort(std::vector<int> *a) {
    int min = *std::min_element(a->begin(), a->end());
    int max = *std::max_element(a->begin(), a->end());
    auto *res = new std::vector<int>(a->size());

    int k = max - min + 1;
    auto *pre = new std::vector<int64_t>(k);

    for (int i = 0; i < k; ++i) {
        (*pre)[i] = 0;
    }

    for (int i : *a) {
        ++(*pre)[i - min];
    }

    for (int i = 1; i < k; ++i) {
        (*pre)[i] += (*pre)[i - 1];
    }

    for (int i = a->size() - 1; i >= 0; --i) {
        (*res)[(*pre)[(*a)[i] - min] - 1] = (*a)[i];
        --(*pre)[(*a)[i] - min];
    }
    std::vector<int> *to_del = res;
    *a = *res;

    delete to_del;
    delete pre;
}

// Цифровая сортировка.



void Sorts::merge(std::vector<int> *list, int begin, int mid, int end) {
    int left = 0;
    int right = 0;
    std::vector<int> res(end - begin);

    while (begin + left < mid && mid + right < end) {
        int left_elem = (*list)[begin + left];
        int right_elem = (*list)[mid + right];
        if (left_elem < right_elem) {
            res[left + right] = left_elem;
            ++left;
        } else {
            res[left + right] = right_elem;
            ++right;
        }
    }

    while (begin + left < mid) {
        res[left + right] = (*list)[begin + left];
        ++left;
    }

    while (mid + right < end) {
        res[left + right] = (*list)[mid + right];
        ++right;
    }

    for (int i = 0; i < res.size(); ++i) {
        (*list)[begin + i] = res[i];
    }
}

void Sorts::mergeSort(std::vector<int> *list) {
    for (int i = 1; i < list->size(); i <<= 1) {
        for (int j = 0; j < list->size() - i; j += 2 * i) {
            merge(list, j, j + i, std::min<int>(j + 2 * i, list->size()));
        }
    }
}

std::pair<int, int> Sorts::hoar(std::vector<int> *list, int from, int to) {
    int pivot = (*list)[from + (to - from) / 2];
    do {
        while ((*list)[from] < pivot) {
            ++from;
        }
        while ((*list)[to] > pivot) {
            --to;
        }

        if (from <= to) {
            ++from;
            --to;
            std::swap((*list)[from - 1], (*list)[to + 1]);
        }
    } while (from <= to);

    return std::make_pair(to, from);
}

void Sorts::quickSortHoar(std::vector<int> *list, int from, int to) {
    if (from < to) {
        std::pair<int, int> pivot = hoar(list, from, to);

        if (from < pivot.first) {
            quickSortHoar(list, from, pivot.first);
        }

        if (pivot.second < to) {
            quickSortHoar(list, pivot.second, to);
        }
    }
}

int Sorts::lomuto(std::vector<int> *list, int from, int to) {
    int pivot = (*list)[to];
    int new_pivot_index = from;

    for (int i = from; i < to; ++i) {
        if ((*list)[i] <= pivot) {
            std::swap((*list)[new_pivot_index], (*list)[i]);
            ++new_pivot_index;
        }
    }
    std::swap((*list)[new_pivot_index], (*list)[to]);

    return new_pivot_index;
}

void Sorts::quickSortLomuto(std::vector<int> *list, int from, int to) {
    if (from < to) {
        int pivot = lomuto(list, from, to);
        quickSortLomuto(list, from, pivot - 1);
        quickSortLomuto(list, pivot + 1, to);
    }
}


// Пирамидальная сортировка.







