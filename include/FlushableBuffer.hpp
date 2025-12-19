
#ifndef LIBRADICL_FLUSHABLE_BUFFER_HPP
#define LIBRADICL_FLUSHABLE_BUFFER_HPP

#include "Byte_Array.hpp"
#include "Tags.hpp"
#include "Type.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <type_traits>

namespace RAD {

class FlushableBuffer {
private:
  const std::size_t cap{0};

  uint8_t *buf{nullptr};
  std::size_t sz{0};

  std::ofstream &os;

  template <typename T_> void add_POD(T_ val);

public:
  explicit FlushableBuffer(std::size_t cap, std::ofstream &os)
      : cap(cap), buf(static_cast<uint8_t *>(std::malloc(cap))), sz(0), os(os) {
  }

  FlushableBuffer(const FlushableBuffer &) = delete;
  FlushableBuffer &operator=(const FlushableBuffer &) = delete;

  FlushableBuffer(FlushableBuffer &&rhs)
      : cap(rhs.cap), buf(rhs.buf), sz(rhs.sz), os(rhs.os) {
    rhs.buf = nullptr;
  }

  FlushableBuffer &operator=(FlushableBuffer &&) = delete;

  ~FlushableBuffer() {
    if (buf != nullptr) {
      flush();
      std::free(buf);
    }
  }

  auto empty() const { return sz == 0; }

  auto size() const { return sz; }

  auto capacity() const { return cap; }

  template <typename T_> void add(const T_ &val);

  void add(const Byte_Array &byte_arr);

  void flush();
};

template <typename T_> inline void FlushableBuffer::add(const T_ &val) {
  static_assert(is_RAD_type<T_>() && !std::is_same<T_, Type::null>());
  add_POD(val.val());
}

template <> inline void FlushableBuffer::add<Type::null>(const Type::null &) {}

template <> inline void FlushableBuffer::add<Tag_List>(const Tag_List &tags) {
  tags.write(*this);
}

template <> inline void FlushableBuffer::add<Type::str>(const Type::str &val) {
  add(Type::u16(val.val().length()));
  for (const auto v : val.val())
    add_POD(v);
}

template <>
inline void FlushableBuffer::add<Type::v_u64>(const Type::v_u64 &val) {
  add(Type::u64(val.val().size()));
  for (const auto v : val.val())
    add_POD(v);
}

template <typename T_> inline void FlushableBuffer::add_POD(const T_ val) {
  static_assert(std::is_pod<T_>());

  if (sz + sizeof(val) > cap) {
    flush();
  }
  // If a single item is larger than capacity, we can't handle it with this
  // simple logic but assuming reasonable capacity and small PODs.
  assert(sz + sizeof(val) <= cap);

  std::memcpy(reinterpret_cast<char *>(buf + sz),
              reinterpret_cast<const char *>(&val), sizeof(val));
  sz += sizeof(val);
}

inline void FlushableBuffer::add(const Byte_Array &byte_arr) {
  if (sz + byte_arr.size() > cap) {
    flush();
  }
  // If byte_arr is larger than capacity, we still have a problem.
  // For now, assume it fits if empty.
  assert(sz + byte_arr.size() <= cap);

  std::memcpy(reinterpret_cast<char *>(buf + sz),
              reinterpret_cast<const char *>(byte_arr.data()), byte_arr.size());
  sz += byte_arr.size();
}

inline void FlushableBuffer::flush() {
  if (sz > 0) {
    os.write(reinterpret_cast<const char *>(buf), sz * sizeof(uint8_t));
    sz = 0;
  }
}

} // namespace RAD

#endif
