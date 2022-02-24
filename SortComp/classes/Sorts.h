#ifndef MAIN_CPP_SORTS_H
#define MAIN_CPP_SORTS_H


class Sorts {
public:
    static void selectionSort(std::vector<int> *a);
    static void bubbleSort(std::vector<int> *a);
    static void bubbleAiversonOneSort(std::vector<int> *a);
    static void bubbleAiversonTwoSort(std::vector<int> *a);
    static void insertionSort(std::vector<int> *a);
    static void binaryInsertionSort(std::vector<int> *a);
    static void stableCountSort(std::vector<int> *a);
    static void lsdSort(std::vector<int> *list);
    static void mergeSort(std::vector<int> *list);
    static void quickSortHoar(std::vector<int> *list);
    static void quickSortLomuto(std::vector<int> *list);
    static void heapSort(std::vector<int> *list);

private:
    static void heapify(std::vector<int> *heap, int parent, int num);
    static void quickSortHoar(std::vector<int> *list, int from, int to);
    static void quickSortLomuto(std::vector<int> *list, int from, int to);
    static int sorterBS(const std::vector<int> &a, int len, int key);
    static void merge(std::vector<int> *list, int begin, int mid, int end);
    static std::pair<int, int> hoar(std::vector<int> *list, int from, int to);
    static int lomuto(std::vector<int> *list, int from, int to);
};


#endif
