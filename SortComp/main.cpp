#include <iostream>
#include "classes/ArrayHelper.h"

int main() {
    ArrayHelper helper(10);
    auto vec = helper.zeroFiveArray();
    helper.print(vec);

    std::cout << ArrayHelper::checkSorted(vec);

    return 0;
}
