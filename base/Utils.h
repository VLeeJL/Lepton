//
// Created by user on 18-12-17.
//

#ifndef LEPTON_UTILS_H
#define LEPTON_UTILS_H
#include <algorithm>
namespace util
{
    template <typename Collection, typename Value>
    bool containsValue(const Collection &collection, const Value &value) {
        return std::find(collection.cbegin(), collection.cend(), value) !=
               collection.cend();
    }
}

#endif //LEPTON_UTILS_H
