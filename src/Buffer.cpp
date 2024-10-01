
#include "Buffer.hpp"

#include <cstdlib>


namespace RAD
{

Buffer::Buffer(const std::size_t cap, std::ofstream& os):
      cap(cap)
    , buf(static_cast<uint8_t*>(std::malloc(cap)))
    , sz(0)
    , os(os)
{}


Buffer::Buffer(Buffer&& rhs):
      cap(rhs.cap)
    , buf(rhs.buf)
    , sz(rhs.sz)
    , os(rhs.os)
{
    rhs.buf = nullptr;
}


Buffer::~Buffer()
{
    std::free(buf);
}

}
