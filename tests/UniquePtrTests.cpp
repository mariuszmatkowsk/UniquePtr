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

TEST(UniquePtr, sameSizeAsStdUniquePtr) {
    static_assert(sizeof(UniquePtr<int>) == sizeof(std::unique_ptr<int>));
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

TEST(UniquePtr, convertToBool) {
    constexpr UniquePtr<int> p1;
    EXPECT_FALSE(p1);

    UniquePtr<int> p2{new int{10}};
    EXPECT_TRUE(p2);
}

TEST(UniquePtr, release) {
    UniquePtr<int> p{new int{3}};

    auto ptr = p.release();

    EXPECT_EQ(p.get(), nullptr);
    EXPECT_EQ(*ptr, 3);

    delete ptr;
}

TEST(UniquePtr, reset) {
    UniquePtr p1{new int{7}};

    p1.reset(new int{10});

    EXPECT_EQ(*p1, 10);
}

TEST(UniquePtr, swap) {
    UniquePtr p1{new int{7}};
    UniquePtr p2{new int{9}};

    ASSERT_EQ(*p1, 7);
    ASSERT_EQ(*p2, 9);

    p1.swap(p2);

    EXPECT_EQ(*p1, 9);
    EXPECT_EQ(*p2, 7);
}

TEST(UniquePtr, moveConstructor) {
    UniquePtr p1{new int{10}};
    UniquePtr p2 = std::move(p1);

    EXPECT_EQ(p1.get(), nullptr);
    EXPECT_EQ(*p2, 10);
}

TEST(UniquePtr, moveAssignmentOperator) {
    UniquePtr p1{new int{2}};
    UniquePtr p2{new int{7}};

    p1 = std::move(p2);

    EXPECT_EQ(p2.get(), nullptr);
    EXPECT_EQ(*p1, 7);
}

TEST(UniquePtr, ostreamOperator) {
    UniquePtr p{new int{10}};

    std::stringstream ss1;
    ss1 << p;

    std::stringstream ss2;
    ss2 << p.get();

    EXPECT_EQ(ss1.str(), ss2.str());
}

TEST(UniquePtr, equalOperator) {
    UniquePtr p1{new int{20}};

    EXPECT_EQ(p1, p1);
}

TEST(UniquePtr, equalOperatorConstexpr) {
    constexpr UniquePtr<int> p;

    constexpr bool result = p == p;

    EXPECT_TRUE(result);
}

TEST(UniquePtr, notEqualOperator) {
    UniquePtr p1{new int{11}};
    UniquePtr p2{new int{13}};

    EXPECT_NE(p1, p2);
}

TEST(UniquePtr, notEqualOperatorConstexpr) {
    constexpr UniquePtr<int> p;

    constexpr bool result = p != p;

    EXPECT_FALSE(result);
}

TEST(UniquePtr, makeUniquePtr) {
    const auto p = make_UniquePtr<int>(4);

    EXPECT_EQ(*p, 4);
}

TEST(UniquePtr, makeUniquePtrWithCustomType) {
    struct Foo {
        int a{};
        int b{};

        constexpr auto operator<=>(const Foo&) const = default;
    };

    const auto p = make_UniquePtr<Foo>(3, 2);

    Foo expected{.a = 3, .b = 2};
    EXPECT_EQ(*p, expected);
}

