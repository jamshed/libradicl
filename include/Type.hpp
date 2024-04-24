
#ifndef LIBRADICL_TYPE_HPP
#define LIBRADICL_TYPE_HPP



#include <string>
#include <cstdint>
#include <type_traits>


namespace RAD
{

namespace Type
{

struct null {                   static constexpr uint8_t type_id() { return 255; } };

struct b    { bool val;         static constexpr uint8_t type_id() { return 0; } };

struct u8   { uint8_t val;      static constexpr uint8_t type_id() { return 1; } };

struct u16  { uint16_t val;     static constexpr uint8_t type_id() { return 2; } };

struct u32  { uint32_t val;     static constexpr uint8_t type_id() { return 3; } };

struct u64  { uint64_t val;     static constexpr uint8_t type_id() { return 4; } };

struct f32  { float val;        static constexpr uint8_t type_id() { return 5; } };

struct f64  { double val;       static constexpr uint8_t type_id() { return 6; } };

// template <typename T_1, typename T_2>
struct arr  { /* TODO ;*/       static constexpr uint8_t type_id() { return 7; } };

struct str  { std::string val;  static constexpr uint8_t type_id() { return 8; } };


template <typename T_>
inline static constexpr auto is_RAD_type()
{
    using std::is_same;
    return  is_same<T_, null>() || is_same<T_, b>() || is_same<T_, u8>() || is_same<T_, u16>() || is_same<T_, u32>() ||
            is_same<T_, f32>() || is_same<T_, f64>() || is_same<T_, arr>() || is_same<T_, str>();
}

}

}



#endif
