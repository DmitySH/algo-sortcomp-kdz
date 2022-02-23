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

int main() {
    setlocale(LC_ALL, "ru");

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
//
            Sorts::mergeSort
//          Sorts::quickSortHoar,
//          Sorts::quickSortLomuto,
//
    };

    std::vector<std::string> sort_names{
            "Выбором",
            "Пузырьковая",
            "Пузырьковая Айв1",
            "Пузырьковая Айв2",
            "Вставками",
            "Бинарными вставками",
            "Подсчетом устойчивая",
//          "",
            "Слиянием",
            "Быстрая Хоар",
            "Быстрая Ломуто",
//          ""
    };

    std::vector<std::string> arr_type_names{
            "Маленькие числа",
            "Большие числа",
            "Почти отсортированный",
            "Обратно отсортированный"
    };

    // Пробегаем по всем сортировкам.
    for (int sort_num = 0; sort_num < number_of_sorts; ++sort_num) {
        // Создаем новые эталонные массивы.
        regenerate(&arrays, helper);

        // Создаем файловые потоки для двух видов размерностей.
        std::ofstream sort_file_small("../tables/sorts/" + sort_names[sort_num] + " small_range" + ".csv");
        std::ofstream sort_file_big("../tables/sorts/" + sort_names[sort_num] + " big_range" + ".csv");

        // Создаем верхнюю строку таблицы с сортировками.
        sort_file_small << "Число элементов;";
        sort_file_big << "Число элементов;";

        for (int i = 0; i < arr_type_names.size(); ++i) {
            sort_file_small << arr_type_names[i];
            sort_file_big << arr_type_names[i];

            if (i != arr_type_names.size() - 1) {
                sort_file_small << ';';
                sort_file_big << ';';
            }
        }
        sort_file_small << "\n";
        sort_file_big << "\n";

        // Пробегаем по всем количествам сортируемых элементов.
        for (int elements_num = 50; elements_num <= 300; elements_num += 10) {
            sort_file_small << std::to_string(elements_num) << ';';

            // Пробегаем по всем типам массивов.
            for (int arr_num = 0; arr_num < number_of_arrays; ++arr_num) {
                std::ofstream arrays_file("../tables/" + std::to_string(arr_num) + ".csv");

//                // Создаем верхнюю строку таблицы с массивами.
//                arrays_file << "Число элементов;";
//                for (int i = 0; i < sort_names.size(); ++i) {
//                    arrays_file << sort_names[i];
//                    if (i != sort_names.size() - 1) {
//                        arrays_file << ';';
//                    }
//                }
//
//                arrays_file << "\n";
//                arrays_file.close();


                std::vector<int> to_sort(elements_num);
                // Копируем из эталона в подопытный массив.
                for (int i = 0; i < elements_num; ++i) {
                    to_sort[i] = arrays[arr_num][i];
                }

                // Замеряем время.
                auto start = std::chrono::high_resolution_clock::now();
                sorts[sort_num](&to_sort);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                int64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();

                sort_file_small << ns;
                if (arr_num != number_of_arrays - 1) {
                    sort_file_small << ';';
                }
            }
            sort_file_small << '\n';
        }

        // Пробегаем по всем количествам сортируемых элементов.
        for (int elements_num = 100; elements_num <= 4100; elements_num += 100) {
            sort_file_big << std::to_string(elements_num) << ';';

            // Пробегаем по всем типам массивов.
            for (int arr_num = 0; arr_num < number_of_arrays; ++arr_num) {
                std::vector<int> to_sort(elements_num);

                for (int i = 0; i < elements_num; i++) {
                    to_sort[i] = arrays[arr_num][i];
                }

                // Замеряем время.
                auto start = std::chrono::high_resolution_clock::now();
                sorts[sort_num](&to_sort);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                int64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();

                sort_file_big << ns;
                if (arr_num != number_of_arrays - 1) {
                    sort_file_big << ';';
                }
            }
            sort_file_big << '\n';
        }

        sort_file_small.close();
        sort_file_big.close();
    }


    return 0;
}
