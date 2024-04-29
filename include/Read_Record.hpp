
#ifndef LIBRADICL_READ_RECORD_HPP
#define LIBRADICL_READ_RECORD_HPP



#include "Type.hpp"
#include "Byte_Array.hpp"
#include "Alignment_Record.hpp"
#include "Buffer.hpp"

#include <cstdint>
#include <vector>


namespace RAD
{

class Single_End_Read
{

private:

    Type::u32 aln_count;    // Number of alignment records to follow for this read.
    Type::u16 read_len; // Currently don’t support reads > 65,536bp.

    Byte_Array byte_arr;    // Container for tag-values and alignment records.


public:

    void set(uint32_t aln_count, uint16_t read_len);

    template <typename T_tag_>
    void add_tag(const T_tag_& val);

    void add_aln_rec(const Aln_Record& aln_rec);

    const auto& byte_array() const { return byte_arr; }

    std::size_t size_in_bytes() const { return byte_arr.size(); }

    void dump(Buffer& buf) const;
};


inline void Single_End_Read::set(const uint32_t aln_count, const uint16_t read_len)
{
    this->aln_count = aln_count;
    this->read_len = read_len;

    byte_arr.clear();
    byte_arr.add(this->aln_count);
    byte_arr.add(this->read_len);
}


template <typename T_tag_>
inline void Single_End_Read::add_tag(const T_tag_& val)
{
    static_assert(is_RAD_type<T_tag_>());

    byte_arr.add(val);
}


inline void Single_End_Read::add_aln_rec(const Aln_Record& aln_rec)
{
    aln_rec.dump(byte_arr);
}


inline void Single_End_Read::dump(Buffer& buf) const
{
    buf.add(byte_arr);
}

}



#endif
