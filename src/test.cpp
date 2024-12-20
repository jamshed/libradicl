
#include "RAD_Writer.hpp"
#include "Alignment_Record.hpp"
#include "Read_Record.hpp"
#include "Byte_Array.hpp"
#include "Tags.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>


int main()
{
    const std::vector<std::string> refs{"ref-path-0"};
    const RAD::Header header(false, refs.size(), refs);

    RAD::Tag_Defn tag_defn;
    tag_defn.add_file_tag<RAD::Type::str>("read_tech");
    tag_defn.add_file_tag<RAD::Type::v_u64>("ref-lens");

    tag_defn.add_read_tag<RAD::Type::str>("read_name");
    tag_defn.add_read_tag<RAD::Type::f32>("avg_read_qual");

    tag_defn.add_aln_tag<RAD::Type::u32>("aln_pos");
    tag_defn.add_aln_tag<RAD::Type::f32>("aln_score");

    RAD::Tag_List file_tag_vals;
    file_tag_vals.add(RAD::Type::str("ATAC-seq"));

    const std::size_t ref_count = 10;
    std::vector<uint64_t> len;
    for(std::size_t i = 0; i < ref_count; ++i)
        len.push_back(250 + i);

    file_tag_vals.add(RAD::Type::v_u64(len));


    RAD::RAD_Writer rad_writer(header, tag_defn, file_tag_vals, "op-RAD-path", 1);
    const auto token = rad_writer.get_token();

    RAD::Read read_rec;
    RAD::Aln_Record aln_rec;
    constexpr std::size_t read_example = 10;
    constexpr std::size_t aln_count = 5;
    for(std::size_t i = 0; i < read_example; ++i)
    {
        read_rec.set(aln_count);
        read_rec.add_tag(RAD::Type::str("dummy-read-name"));
        read_rec.add_tag(RAD::Type::f32(20.5));

        for(std::size_t j = 0; j < aln_count; ++j)
        {
            aln_rec.clear();
            aln_rec.add_tag(RAD::Type::u32(77));
            aln_rec.add_tag(RAD::Type::f32(99.0));

            read_rec.add_aln_rec(aln_rec);
        }

        rad_writer.add(read_rec, token);
    }


    rad_writer.close();

    return 0;
}
