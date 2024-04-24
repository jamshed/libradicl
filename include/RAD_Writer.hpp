
#ifndef LIBRADICL_RAD_WRITER_HPP
#define LIBRADICL_RAD_WRITER_HPP



#include "Header.hpp"
#include "Tags.hpp"

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


public:

    RAD_Writer(const Header& header, const Tag_Defn& tag_defn, const std::string& op_file_path);

    RAD_Writer(const RAD_Writer&) = delete;
    RAD_Writer(RAD_Writer&&) = default;
    RAD_Writer& operator=(const RAD_Writer&) = delete;
    RAD_Writer& operator=(RAD_Writer&&) = delete;
};

}



#endif
