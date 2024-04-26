
#ifndef LIBRADICL_ALIGNMENT_RECORD_HPP
#define LIBRADICL_ALIGNMENT_RECORD_HPP



#include "Type.hpp"

#include <cstdint>
#include <vector>


namespace RAD
{

class Single_End_Aln
{

private:

    Type::u32 ref_id;   // The id of the reference where this alignment occurs.
    Type::u8 aln_type;  // Encodes the type of alignment to follow. Valid alignment types are: 0 — read fw, 1 — read rc.
    Type::aln_pos_t aln_pos;    // Position on the reference where the alignment of the read begins (0-based).
    std::vector<Type::variant_t> tag; // Array of specified alignment-level tags for this alignment.


public:

    void set(uint32_t ref_id, uint8_t aln_type);

    void set(uint32_t ref_id, uint8_t aln_type, uint32_t aln_pos);

    template <typename T_tag_>
    void add_tag(const T_tag_& val);
};


inline void Single_End_Aln::set(const uint32_t ref_id, const uint8_t aln_type)
{
    this->ref_id = ref_id;
    this->aln_type = aln_type;
    this->aln_pos = Type::null();

    tag.clear();
}


inline void Single_End_Aln::set(const uint32_t ref_id, const uint8_t aln_type, const uint32_t aln_pos)
{
    this->ref_id = ref_id;
    this->aln_type = aln_type;
    this->aln_pos = aln_pos;

    tag.clear();
}


template <typename T_tag_>
inline void Single_End_Aln::add_tag(const T_tag_& val)
{
    static_assert(is_RAD_type<T_tag_>());

    tag.emplace_back(val);
}

}



#endif
