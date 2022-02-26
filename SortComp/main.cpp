#include <iostream>
#include "classes/ArrayHelper.h"
#include "classes/Sorts.h"
#include <chrono>
#include <fstream>
#include <string>

// Пересоздание массивов.
void regenerate(std::vector<std::vector<int>> *arrays, ArrayHelper helper) {
    (*arrays)[0] = helper.zeroFiveArray();
    (*arrays)[1] = helper.zeroFourThousandArray();
    (*arrays)[2] = helper.almostSortedArray();
    (*arrays)[3] = helper.reversedArray();
}

// Вывод массива в файл.
void arr_to_file(std::vector<int> *list, std::ofstream *file) {
    for (int i = 0; i < list->size(); ++i) {
        (*file) << (*list)[i] << ' ';
    }
    (*file) << '\n';
}

// Проход теста по диапазону.
void range(const std::vector<std::vector<int>> &arrays, const int number_of_sorts,
           void (**sorts)(std::vector<int> *),
           std::vector<std::vector<int64_t>> &result,
           int start, int stop, int step
) {
    // Пробег по диапазону.
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

                // Отсортирован ли массив.
                if (!ArrayHelper::checkSorted(to_sort)) {
                    std::cout << "Not sorted";
                    throw std::exception();
                }

                // Сохраняем результат.
                result[row][1 + 4 * sort_num + arr_num] += ns;
            }
        }
        ++row;
    }
}

// Нормализация данных.
void normalize(std::vector<std::vector<int64_t>> &result, const int number_of_progons) {
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 1; j < result[i].size(); ++j) {
            result[i][j] = result[i][j] / number_of_progons;
        }
    }
}

// Вывод данных в .csv файл в требуемом формате.
void out_to_csv(std::vector<std::vector<int64_t>> &result, std::ofstream *file) {
    std::vector<std::string> sort_names{
            "Выбором",
            "Пузырьковая",
            "Пузырьковая_Айверсон1",
            "Пузырьковая_Айверсон2",
            "Вставками",
            "Бинарными_вставками",
            "Подсчетом_устойчивая",
            "Цифровая",
            "Слиянием",
            "Быстрая_Хоар",
            "Быстрая_Ломуто",
            "Пирамидальная"
    };

    std::vector<std::string> arr_type_names{
            "Случайные [0..5]",
            "Случайные [0..4000]",
            "Почти отсортированный [0..4000]",
            "Обратно отсортированный [4100 -> 1]"
    };

    // Создание верхней строки таблицы.
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

    // Запись непосредственно результатов.
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
    // Делаем сидом рандома текущее время системы.
    auto seed = static_cast<uint32_t>(time(nullptr)); // last: 1645897668

    // Записываем его значение.
    std::cout << seed << ' ' << std::endl;
    srand(seed);

    ArrayHelper helper(4100);

    const int number_of_arrays = 4;
    std::vector<std::vector<int>> arrays{
            std::vector<int>(),
            std::vector<int>(),
            std::vector<int>(),
            std::vector<int>()
    };
    regenerate(&arrays, helper);

    const int number_of_sorts = 12;
    void (*sorts[number_of_sorts])(std::vector<int> *) {
            Sorts::selectionSort,
            Sorts::bubbleSort,
            Sorts::bubbleAiversonOneSort,
            Sorts::bubbleAiversonTwoSort,
            Sorts::insertionSort,
            Sorts::binaryInsertionSort,
            Sorts::stableCountSort,
            Sorts::lsdSort,
            Sorts::mergeSort,
            Sorts::quickSortHoar,
            Sorts::quickSortLomuto,
            Sorts::heapSort,
    };


    // Фрагмент закомментирован, дабы не нагружать жесткий диск при каждом запуске.
    // Корректность сортировок все равно проверяется внутри прогонов.
    /*

    // Очистка input-output.
    std::ofstream ofs;
    ofs.open("../io/input.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open("../io/output.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    std::ofstream in("../io/input.txt", std::ios_base::app);
    std::ofstream out("../io/output.txt", std::ios_base::app);

    // Проверка сортировок.
    for (int sort_num = 0; sort_num < number_of_sorts; ++sort_num) {
        for (int arr_num = 0; arr_num < number_of_arrays; ++arr_num) {
            std::vector<int> to_sort(4100);
            for (int j = 0; j < 4100; ++j) {
                to_sort[j] = arrays[arr_num][j];
            }
            // Массив-остортированный массив в input.txt-output.txt.
            arr_to_file(&to_sort, &in);
            sorts[sort_num](&to_sort);
            arr_to_file(&to_sort, &out);
        }
    }

    in.close();
    out.close();

    */

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

    std::cout << "Warmed up first\n";
    regenerate(&arrays, helper);

    std::vector<std::vector<int64_t>> test_low(26, std::vector<int64_t>(49));
    std::vector<std::vector<int64_t>> test_big(41, std::vector<int64_t>(49));

    // Холостые прогоны, схожие с реальными.
    const int warmup_number = 10;
    for (int test_id = 0; test_id < warmup_number; ++test_id) {
        std::cout << test_id << std::endl;
        regenerate(&arrays, helper);
        range(arrays, number_of_sorts, sorts, test_low, 50, 300, 10);
        range(arrays, number_of_sorts, sorts, test_big, 100, 4100, 100);
    }

    std::cout << "Warmed up second\n";


    std::vector<std::vector<int64_t>> result_low(26, std::vector<int64_t>(49));
    std::vector<std::vector<int64_t>> result_big(41, std::vector<int64_t>(49));

    // Реальные тестовые прогоны.
    const int number_of_tests = 1000;
    for (int test_id = 0; test_id < number_of_tests; ++test_id) {
        std::cout << test_id << std::endl;
        regenerate(&arrays, helper);
        range(arrays, number_of_sorts, sorts, result_low, 50, 300, 10);
        range(arrays, number_of_sorts, sorts, result_big, 100, 4100, 100);
    }

    // Нормализация данных.
    normalize(result_low, number_of_tests);
    normalize(result_big, number_of_tests);

    // Запись в файлы результатов.
    std::ofstream file1("../tmp_tables/low.csv");
    std::ofstream file2("../tmp_tables/big.csv");

    out_to_csv(result_low, &file1);
    file1.close();
    out_to_csv(result_big, &file2);
    file2.close();

    return 0;
}


