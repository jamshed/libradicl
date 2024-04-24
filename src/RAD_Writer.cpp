
#include "RAD_Writer.hpp"


namespace RAD
{

RAD_Writer::RAD_Writer(const Header& header, const Tag_Defn& tag_defn, const std::string& op_file_path, const std::size_t buf_cap):
      header(header)
    , tag_defn(tag_defn)
    , output(op_file_path, std::ios::out | std::ios::binary)
    , buf(buf_cap, output)
{}

}
