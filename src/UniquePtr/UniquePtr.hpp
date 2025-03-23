#pragma once

#include <utility>
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

    [[nodiscard]]
    constexpr pointer release() noexcept {
        return std::exchange(ptr_, nullptr);
    }

    void reset(pointer new_ptr = pointer()) noexcept {
        if (ptr_) deleter_(ptr_);
        ptr_ = new_ptr;
    }

    constexpr void swap(UniquePtr& u) noexcept {
        // // Enable ADL
        // using std::swap;
        // swap(this->ptr_,     u.ptr_);
        // swpa(this->deleter_, u.deleter_);

        // When using std::ranges::swap ADL is enabled by default
        std::ranges::swap(ptr_,      u.ptr_);
        std::ranges::swap(deleter_,  u.deleter_);
    }

    constexpr element_type& operator*()  const noexcept { return *ptr_; }
    constexpr pointer       operator->() const noexcept { return  ptr_; }
    constexpr pointer       get()        const noexcept { return  ptr_; }

    constexpr explicit operator bool() const noexcept { return ptr_; }

private:
    pointer      ptr_{};
    deleter_type deleter_{};
};

}  // namespace foo
