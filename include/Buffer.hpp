
#ifndef LIBRADICL_BUFFER_HPP
#define LIBRADICL_BUFFER_HPP



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


    void flush();

    template <typename T_>
    void add_POD(const T_& val);

public:

    Buffer(std::size_t cap, std::ofstream& os);

    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&&) = delete;
    Buffer& operator=(Buffer&&) = delete;

    ~Buffer();

    template <typename T_>
    void add(const T_& val);
};


template <typename T_>
inline void Buffer::add(const T_& val)
{
    if constexpr(std::is_pod<T_>())
        add_POD(val);
    else
    {
        add(val.size());
        for(const auto& v : val)
            add(v);  
    }  
}


template <typename T_>
inline void Buffer::add_POD(const T_& val)
{
    if(sz + sizeof(val) >= cap)
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
