
#ifndef LIBRADICL_BUFFER_HPP
#define LIBRADICL_BUFFER_HPP



#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <fstream>


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
    if(sz + sizeof(val) >= cap)
        flush();

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
