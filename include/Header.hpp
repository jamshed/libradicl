
#ifndef LIBRADICL_HEADER_HPP
#define LIBRADICL_HEADER_HPP



#include <cstdint>
#include <vector>
#include <string>


namespace RAD
{


class Header
{
private:

    const bool is_paired;   // Whether the mappings to follow for paired-end or single-end fragments.
    const uint64_t ref_count;   // Number of reference sequences being aligned against.
    std::vector<std::string> ref_names; // Strings encoding the names of the target references.
    uint64_t num_chunks;    // Number of chunks in the file following the header. If this value is 0, then the number of chunks is not known.

public:

    explicit Header(bool is_paired, uint64_t ref_count, const std::vector<std::string>& ref_names, uint64_t num_chunks = 0);

    Header(const Header&) = default;
    Header(Header&&) = default;
    Header& operator=(const Header&) = default;
    Header& operator=(Header&&) = default;
};

}



#endif
