#include <iostream>
#include "classes/ArrayHelper.h"
#include "classes/Sorts.h"
#include <chrono>

void regenerate(std::vector<std::vector<int>> *arrays, ArrayHelper helper) {
    (*arrays)[0] = helper.zeroFiveArray();
    (*arrays)[1] = helper.zeroFourThousandArray();
    (*arrays)[2] = helper.almostSortedArray();
    (*arrays)[3] = helper.reversedArray();
}

int main() {
    ArrayHelper helper(4100);

    const int number_of_arrays = 4;
    std::vector<std::vector<int>> arrays{
            std::vector<int>(),
            std::vector<int>(),
            std::vector<int>(),
            std::vector<int>()
    };

    regenerate(&arrays, helper);

    regenerate(&arrays, helper);

//    std::cout << ArrayHelper::checkSorted(vec);
    const int number_of_sorts = 8;

    void (*sorts[number_of_sorts])(std::vector<int> *) {
            Sorts::selectionSort,
            Sorts::bubbleSort,
            Sorts::bubbleAiversonOneSort,
            Sorts::bubbleAiversonTwoSort,
            Sorts::insertionSort,
            Sorts::binaryInsertionSort,
            Sorts::stableCountSort,

            Sorts::mergeSort
//        Sorts::quickSortHoar,
//        Sorts::quickSortLomuto,

    };

    // Пробегаем по всем сортировкам.
    for (int sort_num = 0; sort_num < number_of_sorts; ++sort_num) {
        // Пробегаем по всем типам массивов.
        regenerate(&arrays, helper);
        for (int arr_num = 0; arr_num < number_of_arrays; ++arr_num) {
            // Пробегаем по всем количествам сортируемых элементов.
            for (int elements_num = 50; elements_num <= 300; elements_num += 10) {
                std::vector<int> to_sort(elements_num);
                // Копируем из эталона в подопытный массив.
                for (int i = 0; i < elements_num; ++i) {
                    to_sort[i] = arrays[arr_num][i];
                }

                auto start = std::chrono::high_resolution_clock::now();
                sorts[sort_num](&to_sort);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                int64_t ms = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
                std::cout << ms << '\n';

                if (!ArrayHelper::checkSorted(to_sort)) {
                    std::cout << "Not ok\n";
                }
            }

            for (int elements_num = 100; elements_num <= 4100; elements_num += 100) {
                std::vector<int> to_sort(elements_num);
                for (int i = 0; i < elements_num; i++) {
                    to_sort[i] = arrays[arr_num][i];
                }

                auto start = std::chrono::high_resolution_clock::now();
                sorts[sort_num](&to_sort);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                int64_t ms = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
                std::cout << ms << '\n';

                if (!ArrayHelper::checkSorted(to_sort)) {
                    std::cout << "Not ok\n";
                }
            }

        }

    }


    return 0;
}
