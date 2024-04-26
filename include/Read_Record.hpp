
#ifndef LIBRADICL_READ_RECORD_HPP
#define LIBRADICL_READ_RECORD_HPP



#include "Type.hpp"

#include <cstdint>
#include <vector>


namespace RAD
{

class Single_End_Read
{

private:

    Type::u32 aln_count;    // Number of alignment records to follow for this read.
    Type::u16 read_len; // Currently don’t support reads > 65,536bp.
    std::vector<Type::variant_t> tag;   // Array of specified read-level tags for this read.


public:

    void set(uint32_t aln_count, uint16_t read_len);

    template <typename T_tag_>
    void add_tag(const T_tag_& val);
};


inline void Single_End_Read::set(const uint32_t aln_count, const uint16_t read_len)
{
    this->aln_count = aln_count;
    this->read_len = read_len;

    tag.clear();
}


template <typename T_tag_>
inline void Single_End_Read::add_tag(const T_tag_& val)
{
    static_assert(is_RAD_type<T_tag_>());

    tag.emplace_back(val);
}

}



#endif
