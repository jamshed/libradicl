
#ifndef LIBRADICL_HEADER_HPP
#define LIBRADICL_HEADER_HPP

#include "Buffer.hpp"
#include "Type.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace RAD {

class Header {
private:
  const Type::b is_paired; // Whether the mappings to follow for paired-end or
                           // single-end fragments.
  const Type::u64
      ref_count; // Number of reference sequences being aligned against.
  std::vector<Type::str>
      ref_names; // Strings encoding the names of the target references.
  Type::u64
      num_chunks; // Number of chunks in the file following the header. If this
                  // value is 0, then the number of chunks is not known.

public:
  explicit Header(uint8_t is_paired, uint64_t ref_count,
                  const std::vector<std::string> &refs,
                  uint64_t num_chunks = 0);

  template <typename BufferT> void write(BufferT &buf) const;
};

template <typename BufferT> inline void Header::write(BufferT &buf) const {
  buf.add(is_paired);
  buf.add(ref_count);
  for (const auto &v : ref_names)
    buf.add(v);
  buf.add(num_chunks);
}

} // namespace RAD

#endif
