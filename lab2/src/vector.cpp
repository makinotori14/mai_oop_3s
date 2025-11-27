#include "../include/vector.hpp"
#include <utility>

const int START_SIZE = 10;
const int NEW_SIZE_MULT = 2;

Vector::Vector() = default;

Vector::Vector(size_t count, unsigned char value) {
    Resize(count, value);
}

Vector::Vector(const Vector& other) : Vector() {
    for (size_t i = 0; i < other.Size(); ++i) {
        PushBack(other[i]);
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        Clear();
        for (size_t i = 0; i < other.Size(); ++i) {
            PushBack(other[i]);
        }
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept
    : cap_(other.cap_), sz_(other.sz_), arr_(other.arr_) {
    other.cap_ = 0;
    other.sz_ = 0;
    other.arr_ = nullptr;
}

Vector& Vector::operator=(Vector&& other) {
    if (this != &other) {
        Clear();
        alloc_traits::deallocate(alloc_, arr_, cap_);

        cap_ = other.cap_;
        sz_ = other.sz_;
        arr_ = other.arr_;

        other.cap_ = 0;
        other.sz_ = 0;
        other.arr_ = nullptr;
    }
    return *this;
}

Vector::Vector(std::initializer_list<unsigned char> init) : Vector() {
    for (auto x : init) {
        PushBack(x);
    }
}

Vector::~Vector() {
    Clear();
    alloc_traits::deallocate(alloc_, arr_, cap_);
}

unsigned char& Vector::operator[](size_t pos) {
    return *(arr_ + pos);
}

const unsigned char& Vector::operator[](size_t pos) const {
    return *(arr_ + pos);
}

bool Vector::IsEmpty() const noexcept {
    return sz_ == 0;
}

size_t Vector::Size() const noexcept {
    return sz_;
}

unsigned char* Vector::Data() const noexcept {
    return arr_;
}

void Vector::Reserve(size_t new_cap) {
    if (new_cap <= cap_) return;

    unsigned char* newarr = alloc_traits::allocate(alloc_, new_cap);

    try {
        for (size_t i = 0; i < sz_; ++i) {
            alloc_traits::construct(alloc_, newarr + i, std::move_if_noexcept(arr_[i]));
        }
    } catch (...) {
        for (size_t i = 0; i < sz_; ++i) {
            alloc_traits::destroy(alloc_, newarr + i);
        }
        alloc_traits::deallocate(alloc_, newarr, new_cap);
        throw;
    }

    for (size_t i = 0; i < sz_; ++i) {
        alloc_traits::destroy(alloc_, arr_ + i);
    }
    alloc_traits::deallocate(alloc_, arr_, cap_);

    arr_ = newarr;
    cap_ = new_cap;
}

void Vector::Clear() noexcept {
    while (!IsEmpty()) {
        PopBack();
    }
}

void Vector::PushBack(unsigned char value) {
    if (cap_ == 0) {
        Reserve(START_SIZE);
    }
    if (sz_ == cap_) {
        Reserve(NEW_SIZE_MULT * sz_);
    }
    alloc_traits::construct(alloc_, arr_ + sz_, value);
    ++sz_;
}

void Vector::PopBack() {
    --sz_;
    alloc_traits::destroy(alloc_, arr_ + sz_);
}

void Vector::Resize(size_t count, unsigned char value) {
    Reserve(count);
    while (sz_ < count) {
        PushBack(value);
    }
    while (sz_ > count) {
        PopBack();
    }
}