
#ifndef LIBRADICL_TAGS_HPP
#define LIBRADICL_TAGS_HPP



#include "Type.hpp"

#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <utility>


namespace RAD
{


class Tag_Defn
{
private:

    typedef std::pair<std::string, uint8_t> tag_desc;

    std::vector<tag_desc> file_tag;
    std::vector<tag_desc> read_tag;
    std::vector<tag_desc> aln_tag;


public:

    template <typename T_>
    void add_file_tag(const std::string& name) { static_assert(RAD::Type::is_RAD_type<T_>()); file_tag.emplace_back(name, T_::type_id()); }

    template <typename T_>
    void add_read_tag(const std::string& name) { static_assert(RAD::Type::is_RAD_type<T_>()); read_tag.emplace_back(name, T_::type_id()); }

    template <typename T_>
    void add_aln_tag(const std::string& name)  { static_assert(RAD::Type::is_RAD_type<T_>()); aln_tag.emplace_back(name, T_::type_id()); }
};

}



#endif
