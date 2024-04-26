
#ifndef LIBRADICL_TAGS_HPP
#define LIBRADICL_TAGS_HPP



#include "Type.hpp"
#include "Buffer.hpp"
#include "boost/variant/variant.hpp"

#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>


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


class Tag_List
{
private:

    typedef boost::variant<Type::null, Type::b, Type::u8, Type::u16, Type::u64, Type::f32, Type::f64, Type::str> Tag;
    std::vector<Tag> tag;


    class Writer : public boost::static_visitor<>
    {
    private:

        Buffer& buf;

    public:

        Writer(Buffer& buf): buf(buf) {}

        template <typename T_>
        void operator()(const T_& operand) const { buf.add(operand); }
    };


public:

    void add(const Tag& t) { tag.emplace_back(t); }

    void clear() { tag.clear(); }

    void write(Buffer& buf) const;
};


inline void Tag_List::write(Buffer& buf) const
{
    Writer writer(buf);
    std::for_each(tag.cbegin(), tag.cend(), boost::apply_visitor(writer));
}

}



#endif
