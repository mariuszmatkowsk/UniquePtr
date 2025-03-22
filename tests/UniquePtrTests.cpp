#include "UniquePtr/UniquePtr.hpp"

#include <gtest/gtest.h>

using namespace foo;

TEST(UniquePtr, createDefault) {
    UniquePtr<int> p;
}

TEST(UniquePtr, createDefaultConstexpr) {
    constexpr UniquePtr<int> p;
}

TEST(UniquePtr, createWithPointer) {
    UniquePtr p{new int{3}};
}

TEST(UniquePtr, shouldFreeMemoryWhenOutOfScope) {
    struct Foo {
        bool& is_deleted;

        explicit Foo(bool& is_deleted) : is_deleted{is_deleted} {}

        ~Foo() {
            is_deleted = true;
        }
    };

    bool is_deleted{false};
    {
        UniquePtr p{new Foo{is_deleted}};
    }
    EXPECT_TRUE(is_deleted);
}

TEST(UniquePtr, canDereferencePointer) {
    UniquePtr<int> p{new int{3}};

    EXPECT_EQ(*p, 3);
}

TEST(UniquePtr, canModifyUnderlyingValue) {
    UniquePtr<int> p{new int{7}};

    EXPECT_EQ(*p, 7);

    *p = 10;

    EXPECT_EQ(*p, 10);
}

TEST(UniquePtr, get) {
    constexpr UniquePtr<int> p;

    EXPECT_EQ(p.get(), nullptr);
}

TEST(UniquePtr, getValue) {
    UniquePtr<int> p{new int{10}};

    EXPECT_EQ(*p.get(), 10);
}

TEST(UniquePtr, arrowOperator) {
    struct Foo {
        int x;
    };

    UniquePtr<Foo> p{new Foo{.x = 10}};

    EXPECT_EQ(p->x, 10);
}



