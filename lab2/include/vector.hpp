#pragma once

#include <initializer_list>
#include <memory>

class Vector {
public:
    Vector();
    Vector(size_t count, unsigned char value);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);
    Vector(std::initializer_list<unsigned char> init);
    ~Vector();

    unsigned char& operator[](size_t pos);
    const unsigned char& operator[](size_t pos) const;
    bool IsEmpty() const noexcept;
    size_t Size() const noexcept;
    void PushBack(unsigned char value);
    void PopBack();
    void Clear() noexcept;
    void Resize(size_t count, unsigned char value);
    void Reserve(size_t new_cap);
    unsigned char* Data() const noexcept;

private:
    size_t cap_ = 0;
    size_t sz_ = 0;
    unsigned char* arr_ = nullptr;
    std::allocator<unsigned char> alloc_;
    using alloc_traits = std::allocator_traits<std::allocator<unsigned char>>;
};