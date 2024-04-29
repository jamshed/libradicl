
#ifndef LIBRADICL_RAD_WRITER_HPP
#define LIBRADICL_RAD_WRITER_HPP



#include "Buffer.hpp"
#include "Tags.hpp"
#include "Header.hpp"

#include <cstdint>
#include <cstddef>
#include <string>
#include <fstream>


namespace RAD
{

class Single_End_Read;


class RAD_Writer
{
private:

    const Header header;
    const Tag_Defn tag_defn;

    static constexpr std::size_t buf_cap_default = 4 * 1024;    // 4 KB.
    Buffer buf;
    uint32_t read_c_in_buf;

    std::ofstream output;


    void flush_chunk();


public:

    RAD_Writer(const Header& header, const Tag_Defn& tag_defn, const std::string& op_file_path, std::size_t buf_cap = buf_cap_default);

    void add(const Single_End_Read& read_rec);

    void close();
};


inline void RAD_Writer::flush_chunk()
{
    const Type::u32 chunk_sz = buf.size();
    output.write(reinterpret_cast<const char*>(&chunk_sz), sizeof(chunk_sz));
    output.write(reinterpret_cast<const char*>(&read_c_in_buf), sizeof(read_c_in_buf));

    buf.flush();
    read_c_in_buf = 0;
}

}



#endif
