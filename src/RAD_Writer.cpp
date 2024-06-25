
#include "RAD_Writer.hpp"
#include "Read_Record.hpp"

#include <cassert>


namespace RAD
{

RAD_Writer::RAD_Writer(const Header& header, const Tag_Defn& tag_defn, const Tag_List& file_tag_vals, const std::string& op_file_path, const std::size_t writer_count, const std::size_t buf_cap):
      output(op_file_path, std::ios::out | std::ios::binary)
    , header(header)
    , tag_defn(tag_defn)
    , read_c_in_buf_(writer_count, 0)
    , worker_c(0)
{
    buf_.reserve(writer_count);
    for(std::size_t i = 0; i < writer_count; ++i)
        buf_.emplace_back(Buffer(buf_cap, output));

    header.write(buf_[0].data());
    tag_defn.write(buf_[0].data());
    buf_[0].data().add(file_tag_vals);

    buf_[0].data().flush();
}


const Token RAD_Writer::get_token()
{
    lock.lock();
    Token token(worker_c++);
    lock.unlock();

    return token;
}


void RAD_Writer::add(const Read& read_rec, const Token& token)
{
    const auto w_id = token.val;
    auto& buf = buf_[w_id].data();
    if(buf.size() + read_rec.size_in_bytes() > buf.capacity())
        flush_chunk(w_id);

    assert(buf.size() + read_rec.size_in_bytes() <= buf.capacity());
    buf.add(read_rec.byte_array());
    read_c_in_buf_[w_id].data()++;
}


void RAD_Writer::flush_chunk(const std::size_t w_id)
{
    auto& buf = buf_[w_id].data();
    auto& read_c_in_buf = read_c_in_buf_[w_id].data();
    assert(!buf.empty() && read_c_in_buf > 0);

    const Type::u32 chunk_sz = buf.size();

    lock.lock();
    output.write(reinterpret_cast<const char*>(&chunk_sz), sizeof(chunk_sz));
    output.write(reinterpret_cast<const char*>(&read_c_in_buf), sizeof(read_c_in_buf));
    lock.unlock();

    buf.flush();
    read_c_in_buf = 0;
}


void RAD_Writer::close()
{
    for(std::size_t w_id = 0; w_id < buf_.size(); ++w_id)
        if(read_c_in_buf_[w_id].data() > 0)
            flush_chunk(w_id);
}

}
