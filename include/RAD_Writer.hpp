
#ifndef LIBRADICL_RAD_WRITER_HPP
#define LIBRADICL_RAD_WRITER_HPP



#include "Buffer.hpp"
#include "Tags.hpp"
#include "Header.hpp"
#include "utility.hpp"

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>
#include <fstream>


namespace RAD
{

class Read;

class Token;

class RAD_Writer
{
private:

    std::ofstream output;

    const Header header;
    const Tag_Defn tag_defn;

    static constexpr std::size_t buf_cap_default = 1 * 1024 * 1024; // 1 MB.
    std::vector<Padded_Data<Buffer>> buf_;
    std::vector<Padded_Data<uint32_t>> read_c_in_buf_;

    uint64_t worker_c;
    Spin_Lock lock;

    void flush_chunk(std::size_t w_id);


public:

    explicit RAD_Writer(const Header& header, const Tag_Defn& tag_defn, const Tag_List& file_tag_vals, const std::string& op_file_path, std::size_t writer_count, std::size_t buf_cap = buf_cap_default);

    const Token get_token();

    void add(const Read& read_rec, const Token& token);

    void close();
};


class Token
{
    friend class RAD_Writer;

private:

    uint64_t val;

    Token(const uint64_t val): val(val)
    {}
};

}



#endif
