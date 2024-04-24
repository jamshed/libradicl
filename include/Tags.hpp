
#ifndef LIBRADICL_TAGS_HPP
#define LIBRADICL_TAGS_HPP



#include "Type.hpp"
#include "Buffer.hpp"

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

    typedef std::pair<Type::str, Type::u8> tag_desc;

    std::vector<tag_desc> file_tag;
    std::vector<tag_desc> read_tag;
    std::vector<tag_desc> aln_tag;


public:

    template <typename T_>
    void add_file_tag(const std::string& name) { static_assert(is_RAD_type<T_>()); file_tag.emplace_back(name, T_::type_id()); }

    template <typename T_>
    void add_read_tag(const std::string& name) { static_assert(is_RAD_type<T_>()); read_tag.emplace_back(name, T_::type_id()); }

    template <typename T_>
    void add_aln_tag(const std::string& name)  { static_assert(is_RAD_type<T_>()); aln_tag.emplace_back(name, T_::type_id()); }

    void write(Buffer& buf) const;
};

}



#endif
