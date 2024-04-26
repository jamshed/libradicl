
#ifndef LIBRADICL_BUFFER_HPP
#define LIBRADICL_BUFFER_HPP



#include "Type.hpp"

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <type_traits>
#include <cassert>


namespace RAD
{

class Buffer
{
private:

    const std::size_t cap;

    uint8_t* buf;
    std::size_t sz;

    std::ofstream& os;


    template <typename T_> void add_POD(T_ val);

    void flush();

public:

    Buffer(std::size_t cap, std::ofstream& os);

    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&&) = delete;
    Buffer& operator=(Buffer&&) = delete;

    ~Buffer();

    template <typename T_> void add(const T_& val);
};


template <typename T_>
inline void Buffer::add(const T_& val)
{
    static_assert(is_RAD_type<T_>());
    add_POD(val.val());
}


template <>
inline void Buffer::add<Type::null>(const Type::null&)
{}


template <>
inline void Buffer::add<Type::str>(const Type::str& val)
{
    add(Type::u16(val.val().length()));
    for(const auto v : val.val())
        add_POD(v);
}


template <typename T_>
inline void Buffer::add_POD(const T_ val)
{
    static_assert(std::is_pod<T_>());

    if(sz + sizeof(val) > cap)
        flush();

    assert(sz + sizeof(val) <= cap);
    std::memcpy(reinterpret_cast<char*>(buf + sz), reinterpret_cast<const char*>(&val), sizeof(val));
    sz += sizeof(val);
}


inline void Buffer::flush()
{
    os.write(reinterpret_cast<const char*>(buf), sz * sizeof(uint8_t));
    sz = 0;
}

}



#endif
