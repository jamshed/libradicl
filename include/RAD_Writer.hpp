
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

class Read;

class RAD_Writer
{
private:

    std::ofstream output;

    const Header header;
    const Tag_Defn tag_defn;

    static constexpr std::size_t buf_cap_default = 512 * 1024;   // 512 KB.
    Buffer buf;
    uint32_t read_c_in_buf;


    void flush_chunk();


public:

    explicit RAD_Writer(const Header& header, const Tag_Defn& tag_defn, const Tag_List& file_tag_vals, const std::string& op_file_path, std::size_t buf_cap = buf_cap_default);

    void add(const Read& read_rec);

    void close();
};

}



#endif
