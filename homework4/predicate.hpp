#include <cstdlib>
#include <iostream>
#include "tuple"
#include "vector"

template<typename Iterator, typename F>
bool allOf(Iterator first, Iterator second, const F &predicate) {
    while (first != second) {
        if (!predicate(*first)) {
            return false;
        }
        first++;
    }
    return true;
}


template<typename Iterator, typename F>
bool anyOf(Iterator first, Iterator second, const F &predicate) {
    while (first != second) {
        if (predicate(*first)) {
            return true;
        }
        first++;
    }
    return false;
}


template<typename Iterator, typename F>
bool noneOf(Iterator first, Iterator second, const F &predicate) {
    while (first != second) {
        if (predicate(*first)) {
            return false;
        }
        first++;
    }
    return true;
}


template<typename Iterator, typename F>
bool oneOf(Iterator first, Iterator second, const F &predicate) {
    int quantity = 0;
    while (first != second) {
        if (predicate(*first)) {
            quantity++;
        }
        first++;
    }
    if (quantity == 1) return true;
    else return false;
}


template<typename Iterator, typename F = std::less<>>
bool isSorted(Iterator first, Iterator second, F predicate = F()) {
    while (first != second - 1) {
        if (!predicate(*first, *(first + 1))) {
            return false;
        }
        first++;
    }
    return true;
}


template<typename Iterator, typename F>
bool isPartitioned(Iterator first, Iterator second, const F &predicate) {
    bool changed = false;
    while (first != second) {
        if (!predicate(*first)) {
            if (!changed) {
                changed = true;
            } else {
                return false;
            }
        }
        first++;
    }
    return true;
}


template<typename Iterator, typename F>
Iterator findNot(Iterator first, Iterator second, const F &value) {
    while (first != second) {
        if (*first != value) {
            return first;
        }
        first++;
    }
    return first;
}


template<typename Iterator, typename F>
Iterator findBackward(Iterator first, Iterator second, const F &value) {
    auto temp_value = second;
    while (first != second) {
        if (*first == value) {
            temp_value = first;
        }
        first++;
    }
    return temp_value;
}


template<typename Iterator, typename F>
bool isPalindrome(Iterator first, Iterator second, const F &predicate) {
    int n = 0;
    auto temp_first = first;
    while (temp_first != second) {
        temp_first++;
        n++;
    }

    n /= 2;
    second--;
    while (n > 0) {
        if (!predicate(*first, *second)) {
            return false;
        }
        n--;
        first++;
        second--;
    }
    return true;
}
