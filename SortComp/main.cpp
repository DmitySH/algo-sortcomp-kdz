#include <iostream>
#include "classes/ArrayHelper.h"

int main() {
    ArrayHelper helper(10);
    auto small_ints_array = helper.zeroFiveArray();
    auto big_ints_array = helper.zeroFourThousandArray();
    auto almost_sorted_array = helper.almostSortedArray(5, 35);
    auto reversed_array = helper.reversedArray();

    helper.print(reversed_array);

//    std::cout << ArrayHelper::checkSorted(vec);



    return 0;
}
