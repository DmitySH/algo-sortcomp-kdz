#include <iostream>
#include "classes/ArrayHelper.h"
#include "classes/Sorts.h"
#include <chrono>
#include <fstream>
#include <string>

void regenerate(std::vector<std::vector<int>> *arrays, ArrayHelper helper) {
    (*arrays)[0] = helper.zeroFiveArray();
    (*arrays)[1] = helper.zeroFourThousandArray();
    (*arrays)[2] = helper.almostSortedArray();
    (*arrays)[3] = helper.reversedArray();
}

void range(const std::vector<std::vector<int>> &arrays, const int number_of_sorts,
           void (**sorts)(std::vector<int> *),
           std::vector<std::vector<int64_t>> &result,
           int start, int stop, int step
) {
    // Пробег по маленькому диапазону.
    int row = 0;
    for (int elements_num = start; elements_num <= stop; elements_num += step) {
        result[row][0] = elements_num;

        // Пробег по всем сортировкам.
        for (int sort_num = 0; sort_num < number_of_sorts; ++sort_num) {

            // Пробег по всем типам массивов.
            for (int arr_num = 0; arr_num < arrays.size(); ++arr_num) {
                std::vector<int> to_sort(elements_num);

                // Копируем из эталона в подопытный массив.
                for (int i = 0; i < elements_num; ++i) {
                    to_sort[i] = arrays[arr_num][i];
                }

                // Замеряем время.
                auto begin = std::chrono::high_resolution_clock::now();
                sorts[sort_num](&to_sort);
                auto elapsed = std::chrono::high_resolution_clock::now() - begin;
                int64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();

                // Сохраняем результат.
                result[row][1 + 4 * sort_num + arr_num] += ns;
            }
        }
        ++row;
    }
}

void normalize(std::vector<std::vector<int64_t>> &result, const int number_of_progons) {
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 1; j < result[i].size() - 1; ++j) {
            result[i][j] = result[i][j] / number_of_progons;
        }
    }
}

void out_to_csv(std::vector<std::vector<int64_t>> &result, std::ofstream *file) {
    std::vector<std::string> sort_names{
            "Выбором",
            "Пузырьковая",
            "Пузырьковая Айв1",
            "Пузырьковая Айв2",
            "Вставками",
            "Бинарными вставками",
            "Подсчетом устойчивая",
            "ЛПОЫВЛПАОЫЛВ",
            "Слиянием",
            "Быстрая Хоар",
            "Быстрая Ломуто",
            "43Ц423"
    };

    std::vector<std::string> arr_type_names{
            "Маленькие числа",
            "Большие числа",
            "Почти отсортированный",
            "Обратно отсортированный"
    };
    (*file) << "Размер массива;";
    for (int i = 0; i < sort_names.size(); ++i) {
        for (int j = 0; j < arr_type_names.size(); ++j) {
            (*file) << sort_names[i] + " " + arr_type_names[j];
            if (i != sort_names.size() - 1 || j != arr_type_names.size() - 1) {
                (*file) << ';';
            }
        }
    }
    (*file) << '\n';

    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[i].size(); ++j) {
            (*file) << result[i][j];
            if (j != result[i].size() - 1) {
                (*file) << ';';
            }
        }
        (*file) << '\n';
    }
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

//    std::cout << ArrayHelper::checkSorted(vec);
    const int number_of_sorts = 12;

    void (*sorts[number_of_sorts])(std::vector<int> *) {
            Sorts::selectionSort,
            Sorts::bubbleSort,
            Sorts::bubbleAiversonOneSort,
            Sorts::bubbleAiversonTwoSort,
            Sorts::insertionSort,
            Sorts::binaryInsertionSort,
            Sorts::stableCountSort,
//
            Sorts::stableCountSort,
//
            Sorts::mergeSort,
            Sorts::quickSortHoar,
            Sorts::quickSortLomuto,
//
            Sorts::stableCountSort,
//
    };


    // 10 холостых прогонов.
    for (int i = 0; i < 10; ++i) {
        for (int sort_num = 0; sort_num < number_of_sorts; ++sort_num) {
            for (int arr_num = 0; arr_num < number_of_arrays; ++arr_num) {
                std::vector<int> to_sort(4100);
                for (int j = 0; j < 4100; ++j) {
                    to_sort[j] = arrays[arr_num][j];
                }
                sorts[sort_num](&to_sort);
            }
        }
    }

    std::cout << "Warmed up\n";
    regenerate(&arrays, helper);


    std::vector<std::vector<int64_t>> result_low(26, std::vector<int64_t>(49));
    std::vector<std::vector<int64_t>> result_big(41, std::vector<int64_t>(49));

    const int number_of_progons = 20;

    for (int progon_id = 0; progon_id < number_of_progons; ++progon_id) {
        std::cout << progon_id << std::endl;
        range(arrays, number_of_sorts, sorts, result_low, 50, 300, 10);
        range(arrays, number_of_sorts, sorts, result_big, 100, 4100, 100);
    }

    normalize(result_low, number_of_progons);
    normalize(result_big, number_of_progons);


    std::ofstream file1("../tables/1.csv");
    std::ofstream file2("../tables/2.csv");

    out_to_csv(result_low, &file1);
    file1.close();
    out_to_csv(result_big, &file2);
    file2.close();

    int x = 5;

    return 0;
}


