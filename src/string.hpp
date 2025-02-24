#ifndef STRING_HPP
#define STRING_HPP

#include <cstring>
#include <iostream>
#include <algorithm>

#include "allocator.hpp"

class String
{
public:
  using allocator_type = Allocator<char>;
  using size_type      = Allocator<char>::size_type;

class iterator
{
public:
  iterator(char * ptr);

  char & operator *();
  const char & operator *() const;

  iterator & operator ++();
  iterator & operator --();

  bool operator ==(const iterator & rhs) const;
  bool operator !=(const iterator & rhs) const;

private:
  char * ptr_;
};

  explicit String(allocator_type alloc = allocator_type());
  String(size_type n, const allocator_type & alloc = allocator_type());
  String(size_type n, char ch, const allocator_type & alloc = allocator_type());
  String(const char * s, size_type n, const allocator_type & alloc = allocator_type());
  String(const char * s, const allocator_type & alloc = allocator_type());
  String(const String & other);
  String(String && other) noexcept;
  String(std::initializer_list<char> list, const allocator_type & alloc = allocator_type());

  ~String();

  String & operator =(const String & rhs);
  String & operator =(String && rhs) noexcept;

  String operator +(const String & rhs) const;

  String & operator +=(const String & rhs);

  bool operator ==(const String & rhs) const;

  bool operator <(const String & rhs) const;

  const char * data() const;

  iterator begin();
  iterator end();

  bool empty() const;

  size_type size() const;
  size_type length() const;

  size_type max_size() const;


private:
  allocator_type alloc_;
  size_type      length_;
  size_type      capacity_;
  char         * buffer_;
};

inline String::iterator::iterator(char * ptr) :
  ptr_(ptr)
{
}

inline char & String::iterator::operator *()
{
  return *ptr_;
}

inline String::iterator & String::iterator::operator ++()
{
  ++ptr_;
  return *this;
}

inline String::iterator & String::iterator::operator --()
{
  --ptr_;
  return *this;
}

inline bool String::iterator::operator ==(const iterator & rhs) const
{
  return ptr_ == rhs.ptr_;
}

inline bool String::iterator::operator !=(const iterator & rhs) const
{
  return ptr_ != rhs.ptr_;
}

inline String::String(allocator_type alloc) :
  alloc_(alloc),
  length_(0),
  capacity_(0),
  buffer_(nullptr)
{
}

inline String::String(size_type n, const allocator_type & alloc) :
  alloc_(alloc),
  length_(0),
  capacity_(n),
  buffer_(alloc_.allocate(n))
{
}

inline String::String(size_type n, char ch, const allocator_type & alloc) :
  alloc_(alloc),
  length_(n),
  capacity_(n),
  buffer_(alloc_.allocate(n))
{
  std::fill(buffer_, buffer_ + length_, ch);
}

inline String::String(const char * s, size_type n, const allocator_type & alloc) :
  alloc_(alloc),
  length_(n),
  capacity_(n),
  buffer_(alloc_.allocate(n))
{
  std::memcpy(buffer_, s, n);
}

inline String::String(const char * s, const allocator_type & alloc) :
  alloc_(alloc),
  length_(std::strlen(s)),
  capacity_(length_),
  buffer_(alloc_.allocate(length_))
{
  std::memcpy(buffer_, s, length_);
}

inline String::String(const String & other) :
  alloc_(other.alloc_),
  length_(other.length_),
  capacity_(other.capacity_),
  buffer_(alloc_.allocate(length_))
{
  std::memcpy(buffer_, other.buffer_, length_);
}

inline String::String(String && other) noexcept :
  alloc_(other.alloc_),
  length_(other.length_),
  capacity_(other.capacity_),
  buffer_(other.buffer_)
{
  other.length_   = 0;
  other.capacity_ = 0;
  other.buffer_   = nullptr;
}

inline String::String(std::initializer_list<char> list, const allocator_type & alloc) :
  alloc_(alloc),
  length_(list.size()),
  capacity_(list.size()),
  buffer_(alloc_.allocate(length_))
{
  std::copy(list.begin(), list.end(), buffer_);
}

inline String::~String()
{
  alloc_.deallocate(buffer_, capacity_);
}

inline String & String::operator =(const String & rhs)
{
  if (buffer_ == rhs.buffer_)
    return *this;
  
  if (capacity_ < rhs.length_)
  {
    alloc_.deallocate(buffer_, capacity_);
    buffer_   = alloc_.allocate(rhs.length_);
    capacity_ = rhs.length_;
  }
  length_ = rhs.length_;
  std::memcpy(buffer_, rhs.buffer_, length_);
  return *this;
}

inline String & String::operator =(String && rhs) noexcept
{
  length_   = rhs.length_;
  capacity_ = rhs.capacity_;
  buffer_   = rhs.buffer_;

  rhs.length_   = 0;
  rhs.capacity_ = 0;
  rhs.buffer_   = nullptr;

  return *this;
}

inline String String::operator +(const String & rhs) const
{
  size_type newLength = length_ + rhs.length_;
  String result(newLength);
  result.length_ = newLength;
  std::memcpy(result.buffer_, buffer_, length_);
  std::memcpy(result.buffer_+length_, rhs.buffer_, rhs.length_);
  return result;
}

inline String & String::operator +=(const String & rhs)
{
  size_type newLength = length_ + rhs.length_;
  if (newLength > capacity_)
  {
    char * buff = buffer_;
    buffer_ = alloc_.allocate(newLength);
    std::memcpy(buffer_, buff, length_);
    alloc_.deallocate(buff, length_);
    capacity_ = newLength;
  }
  std::memcpy(buffer_+length_, rhs.buffer_, rhs.length_);
  length_ = newLength;
  return *this;
}

inline bool String::operator ==(const String & rhs) const
{
  return length_ == rhs.length_  &&
        *buffer_ == *rhs.buffer_ &&
        std::memcmp(buffer_, rhs.buffer_, length_) == 0;
}

inline bool String::operator <(const String & rhs) const
{  
  for (size_type i = 0; i < length_ && i < rhs.length_; ++i)
  {
    if (*(buffer_+i) < *(rhs.buffer_+i))
      return true;
    if (*(buffer_+i) > *(rhs.buffer_+i))
      return false;
  }
  return length_ < rhs.length_;
}

inline std::ostream & operator <<(std::ostream & os, const String & rhs)
{
  os << rhs.data();
  return os;
}

inline const char * String::data() const
{
  return buffer_;
}

inline String::iterator String::begin()
{
  return iterator(buffer_);
}

inline String::iterator String::end()
{
  return iterator(buffer_+length_);
}

inline bool String::empty() const
{
  return length_ < 1;
}

inline typename String::size_type String::size() const
{
  return length_;
}

inline typename String::size_type String::length() const
{
  return length_;
}

inline typename String::size_type String::max_size() const
{
  return capacity_;
}

#endif 