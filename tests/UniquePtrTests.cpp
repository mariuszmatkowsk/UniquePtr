#include "UniquePtr/UniquePtr.hpp"

#include <gtest/gtest.h>

using namespace foo;

TEST(UniquePtr, canCreateDefault) {
    UniquePtr<int> p;
}

TEST(UniquePtr, canCreateDefaultConstexpr) {
    constexpr UniquePtr<int> p;
}

