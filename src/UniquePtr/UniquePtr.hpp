#pragma once

namespace foo {

template <typename T>
struct default_delete {
    constexpr void operator()(T* ptr) {
        delete ptr;
    }
};

template <typename T, typename D = default_delete<T>>
class UniquePtr {
public:
    using element_type = T;
    using pointer      = element_type*;
    using deleter_type = D;

    explicit constexpr UniquePtr() noexcept : UniquePtr(nullptr) {}

    explicit constexpr UniquePtr(pointer ptr) noexcept
        : ptr_{ptr}, deleter_{D{}} {}

    constexpr ~UniquePtr() {
        if (ptr_) deleter_(ptr_);
    }

    UniquePtr(const UniquePtr&)            = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // TODO: to be implemented
    constexpr UniquePtr(UniquePtr&&)            noexcept = default;
    constexpr UniquePtr& operator=(UniquePtr&&) noexcept = default;

    constexpr element_type& operator*()  const noexcept { return *ptr_; }
    constexpr pointer       operator->() const noexcept { return  ptr_; }
    constexpr pointer       get()        const noexcept { return  ptr_; }

    constexpr explicit operator bool() const noexcept { return ptr_; }

private:
    pointer      ptr_{};
    deleter_type deleter_{};
};

}  // namespace foo
