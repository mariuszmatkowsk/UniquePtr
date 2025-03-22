#pragma once

namespace foo {

template <typename T>
struct default_delete {
    void operator()(T* ptr) {
        delete ptr;
    }
};

template <typename T, typename D = default_delete<T>>
class UniquePtr {
public:
    using element_type = T;
    using pointer      = element_type*;
    using deleter_type = D;

    explicit constexpr UniquePtr() : UniquePtr(nullptr) {}

    explicit constexpr UniquePtr(pointer ptr) : ptr_{ptr}, deleter_{D{}} {}

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // TODO: to be implemented
    UniquePtr(UniquePtr&&) = default;
    UniquePtr& operator=(UniquePtr&&) = default;

private:
    pointer      ptr_{};
    deleter_type deleter_{};
};

}  // namespace foo
