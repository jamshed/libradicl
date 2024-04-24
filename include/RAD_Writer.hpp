
#ifndef LIBRADICL_RAD_WRITER_HPP
#define LIBRADICL_RAD_WRITER_HPP



#include "Header.hpp"
#include "Tags.hpp"


namespace RAD
{

class RAD_Writer
{
private:

    const Header header;
    const Tag_Defn tag_defn;


public:

    RAD_Writer(const Header& header, const Tag_Defn& tag_defn);
};

}



#endif
