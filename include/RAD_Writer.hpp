
#ifndef LIBRADICL_RAD_WRITER_HPP
#define LIBRADICL_RAD_WRITER_HPP



#include "Buffer.hpp"
#include "Header.hpp"
#include "Tags.hpp"

#include <cstddef>
#include <string>
#include <fstream>


namespace RAD
{

class RAD_Writer
{
private:

    const Header header;
    const Tag_Defn tag_defn;

    std::ofstream output;

    static constexpr std::size_t buf_cap_default = 4 * 1024;    // 4 KB.
    Buffer buf;


public:

    RAD_Writer(const Header& header, const Tag_Defn& tag_defn, const std::string& op_file_path, std::size_t buf_cap = buf_cap_default);
};

}



#endif
