#ifndef SORTCOMP_ARRAYHELPER_H
#define SORTCOMP_ARRAYHELPER_H


#include <vector>

class ArrayHelper {
public:
    explicit ArrayHelper(int size) {
        this->size_ = size;
    }

    ~ArrayHelper() = default;

    std::vector<int> zeroFiveArray();

    std::vector<int> zeroFourThousandArray();

    std::vector<int> almostSortedArray(int step = 1025, int swaps = 25);

    std::vector<int> reversedArray() const;


    static bool checkSorted(const std::vector<int> &arr);

    void print(const std::vector<int> &arr);

private:
    int size_;

    std::vector<int> createArray(int min, int max) const;
};


#endif
