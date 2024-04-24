
#ifndef LIBRADICL_TYPE_HPP
#define LIBRADICL_TYPE_HPP



#include <string>
#include <cstdint>


namespace RAD
{

namespace Type
{

struct null {                   uint8_t type_id() const { return 255; } };

struct b    { bool val;         uint8_t type_id() const { return 0; } };

struct u8   { uint8_t val;      uint8_t type_id() const { return 1; } };

struct u16  { uint16_t val;     uint8_t type_id() const { return 2; } };

struct u32  { uint32_t val;     uint8_t type_id() const { return 3; } };

struct u64  { uint64_t val;     uint8_t type_id() const { return 4; } };

struct f32  { float val;        uint8_t type_id() const { return 5; } };

struct f64  { double val;       uint8_t type_id() const { return 6; } };

// template <typename T_1, typename T_2>
struct arr  { /* TODO ;*/       uint8_t type_id() const { return 7; } };

struct str  { std::string val;  uint8_t type_id() const { return 8; } };

}

}



#endif
