#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <utility>
#include <cstdlib>

template<class T>
class Allocator
{
public:
  using pointer   = T*;
  using size_type = std::size_t;

  Allocator() = default;
  Allocator(const Allocator<T> &) {}

  pointer allocate(size_type n);

  void deallocate(pointer ptr, size_type n);

  template<class U, class ...Args>
  void construct(U * ptr, Args && ...args);

  template<class U>
  void destroy(U * ptr);
};

template<class T>
typename Allocator<T>::pointer Allocator<T>::allocate(size_type n)
{
  return reinterpret_cast<pointer>(::operator new(n * sizeof(T)));
}

template<class T>
void Allocator<T>::deallocate(pointer ptr, size_type n)
{
  ::operator delete(ptr);
}

template<class T>
template<class U, class ...Args>
void Allocator<T>::construct(U * ptr, Args && ...args)
{
  ::new(reinterpret_cast<void*>(ptr)) U(std::forward<Args>(args)...);
}

template<class T>
template<class U>
void Allocator<T>::destroy(U * ptr)
{
  ptr->~U();
}
#endif // ALLOCATOR_HPP