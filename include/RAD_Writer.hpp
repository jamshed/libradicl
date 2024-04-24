
#ifndef LIBRADICL_RAD_WRITER_HPP
#define LIBRADICL_RAD_WRITER_HPP



#include "Header.hpp"


namespace RAD
{

class RAD_Writer
{
private:

    const Header header;


public:

    RAD_Writer(const Header& header);
};

}



#endif
