//
// Created by skamath on 13/03/21.
//

#include "gtest/gtest.h"
#include <iostream>
#include <array>

using namespace std;

TEST(StdArray, basic) {
    typedef array<int, 3> int_arr_t;
    int_arr_t arr = {10, 20,30};

    // iterator tests<
    ASSERT_EQ(3, arr.size());
    ASSERT_EQ(10, arr.front());
    ASSERT_EQ(20, arr.at(1));
    ASSERT_EQ(20, arr[1]);
    ASSERT_EQ(30, arr.back());

    // sort in descending order
    sort(arr.begin(), arr.end(), std::greater<int>());

    EXPECT_THROW(arr.at(3), std::out_of_range);
    EXPECT_NO_THROW(arr[3]);        // out of bounds check is not performed

    ASSERT_EQ(arr.size(), arr.max_size());

    // compilation error
    // std::get<3>(arr) = 20;

    array<int, 3> other = {};
    arr.swap(other);

    arr.at(0) = 100;
    for (const auto a: arr) {
        cout << a << ", ";
    }
}

TEST(Array, basic) {
    int arr[3] = {10, 20, 30};

    // iterator tests<
    ASSERT_EQ(3, sizeof(arr)/sizeof(arr[0]));
    ASSERT_EQ(10, arr[0]);
    ASSERT_EQ(20, arr[1]);
    ASSERT_EQ(30, arr[2]);

    sort(begin(arr), end(arr), std::greater<int>());

    for (const auto a: arr) {
        cout << a << ", ";
    }
}
