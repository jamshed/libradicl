
#include "Tags.hpp"
#include "Buffer.hpp"


namespace RAD
{

void Tag_Defn::write(Buffer& buf) const
{
    const auto& write_tag_vec =
        [&](const auto& vec)
        {
            buf.add(Type::u16(vec.size()));
            for(const auto& v : vec)
            {
                buf.add(v.first);
                buf.add(v.second);
                if(v.second.val() == Type::v_u64::type_id())
                {
                    buf.add(Type::u8(Type::u64::type_id()));
                    buf.add(Type::u8(Type::u64::type_id()));
                }
            }
        };

    write_tag_vec(file_tag);
    write_tag_vec(read_tag);
    write_tag_vec(aln_tag);
}

}
