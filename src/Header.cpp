
#include "Header.hpp"


namespace RAD
{

Header::Header(const bool is_paired, const uint64_t ref_count, const std::vector<std::string>& ref_names, const uint64_t num_chunks):
      is_paired(is_paired)
    , ref_count(ref_count)
    , ref_names(ref_names)
    , num_chunks(num_chunks)
{}

}
