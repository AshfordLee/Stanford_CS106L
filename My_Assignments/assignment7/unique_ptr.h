#pragma once

#include <cstddef>
#include <utility>

namespace cs106l {

/**
 * @brief A smart pointer that owns an object and deletes it when it goes out of scope.
 * @tparam T The type of the object to manage.
 * @note This class is a simpler version of `std::unique_ptr`.
 */
template <typename T> class unique_ptr {
private:
  T* ptr = nullptr;  // 存储指向管理对象的指针

public:
  /**
   * @brief Constructs a new `unique_ptr` from the given pointer.
   * @param ptr The pointer to manage.
   * @note You should avoid using this constructor directly and instead use `make_unique()`.
   */
  unique_ptr(T* ptr) : ptr(ptr) {}

  /**
   * @brief Constructs a new `unique_ptr` from `nullptr`.
   */
  unique_ptr(std::nullptr_t) : ptr(nullptr) {}

  /**
   * @brief Constructs an empty `unique_ptr`.
   * @note By default, a `unique_ptr` points to `nullptr`.
   */
  unique_ptr() : unique_ptr(nullptr) {}

  /**
   * @brief Dereferences a `unique_ptr` and returns a reference to the object.
   * @return A reference to the object.
   */
  T& operator*() {
    return *ptr;
  }

  /**
   * @brief Dereferences a `unique_ptr` and returns a const reference to the object.
   * @return A const reference to the object.
   */
  const T& operator*() const {
    return *ptr;
  }

  /**
   * @brief Returns a pointer to the object managed by the `unique_ptr`.
   * @note This allows for accessing the members of the managed object through the `->` operator.
   * @return A pointer to the object.
   */
  T* operator->() {
    return ptr;
  }

  /**
   * @brief Returns a const pointer to the object managed by the `unique_ptr`.
   * @note This allows for accessing the members of the managed object through the `->` operator.
   * @return A const pointer to the object.
   */
  const T* operator->() const {
    return ptr;
  }

  /**
   * @brief Returns whether or not the `unique_ptr` is non-null.
   * @note This allows us to use a `unique_ptr` inside an if-statement.
   * @return `true` if the `unique_ptr` is non-null, `false` otherwise.
   */
  operator bool() const {
    return ptr != nullptr;
  }

  // 析构函数
  ~unique_ptr() {
    delete ptr;
  }

  // 删除拷贝构造函数
  unique_ptr(const unique_ptr& other) = delete;

  // 删除拷贝赋值运算符
  unique_ptr& operator=(const unique_ptr& other) = delete;

  // 移动构造函数
  unique_ptr(unique_ptr&& other) noexcept {
    ptr = other.ptr;
    other.ptr = nullptr;  // 重要：将other的指针设为nullptr
  }

  // 移动赋值运算符
  unique_ptr& operator=(unique_ptr&& other) noexcept {
    if (this != &other) {
      delete ptr;  // 删除当前资源
      ptr = other.ptr;  // 获取other的资源
      other.ptr = nullptr;  // 重要：将other的指针设为nullptr
    }
    return *this;
  }
};

/**
 * @brief Creates a new unique_ptr for a type with the given arguments.
 * @example auto ptr = make_unique<int>(5);
 * @tparam T The type to create a unique_ptr for.
 * @tparam Args The types of the arguments to pass to the constructor of T.
 * @param args The arguments to pass to the constructor of T.
 */
template <typename T, typename... Args> 
unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}