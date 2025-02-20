#ifndef STRING_HPP
#define STRING_HPP

#include <cstdlib>

#include "allocator.hpp"

class String
{
public:
  using allocator_type = Allocator<char>;
  using size_type      = Allocator<char>::size_type;

  explicit String(allocator_type alloc = allocator_type());
  String(size_type count, char ch, const allocator_type & alloc = allocator_type());
  String(const char * s, size_type count, const allocator_type & alloc = allocator_type());
  String(const char * s, const allocator_type & alloc = allocator_type());
  String(const String & other);
  String(String && other) noexcept;
  String(const String & other, const allocator_type & alloc = allocator_type());
  String(String && other, const allocator_type & alloc = allocator_type()) noexcept;
  String(std::initializer_list<char> list, const allocator_type & alloc = allocator_type());

  String & operator =(const String & rhs);
  String & operator =(String && rhs) noexcept;

  String & operator +(const String & rhs);
  String & operator +(String && rhs) noexcept;

  bool empty() const;

  size_type size() const;
  size_type length() const;

  size_type max_size() const;


private:
  char    * buffer_;
  size_type length_;
  size_type capacity_;
};

#endif 