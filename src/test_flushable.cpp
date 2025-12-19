
#include "FlushableBuffer.hpp"
#include "Header.hpp"
#include "Tags.hpp"
#include "Type.hpp"
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

void test_flushable_buffer() {
  std::string filename = "test_output.bin";
  std::ofstream os(filename, std::ios::binary);

  // Create a small buffer (e.g., 10 bytes)
  size_t cap = 10;
  RAD::FlushableBuffer buf(cap, os);

  // Add data smaller than capacity
  buf.add(RAD::Type::u32(0x12345678)); // 4 bytes
  assert(buf.size() == 4);

  // Add more data to trigger flush
  // Current size 4. Add 8 bytes (u64). 4 + 8 = 12 > 10. Should flush first.
  buf.add(RAD::Type::u64(0x1122334455667788));
  // After flush, size should be 8 (the new item)
  assert(buf.size() == 8);

  // Add Tag_List to test templated Tag_Defn::write
  RAD::Tag_Defn tag_defn;
  tag_defn.add_file_tag<RAD::Type::u32>("test_tag");

  RAD::Tag_List tags;
  tags.add(RAD::Type::u32(123));

  // Tag_List write will write:
  // u16 count (2 bytes)
  // string name ("test_tag") -> u16 len (2 bytes) + "test_tag" (8 bytes) = 10
  // bytes u8 type (1 byte) u32 value (4 bytes) Total: 2 + 10 + 1 + 4 = 17
  // bytes. Current buffer size is 8. 8 + 17 > 10. Should flush. Actually
  // Tag_Defn::write calls buf.add multiple times. buf.add(u16 count) -> 2
  // bytes. 8+2=10. Fits. buf.add(string name) -> 10 bytes. 10+10=20 > 10.
  // Flush.

  // We need to verify that Tag_Defn::write works with FlushableBuffer
  // This is a compile-time check mostly, but runtime check ensures no crash.
  tag_defn.write(buf);

  // Manually flush remaining
  buf.flush();
  os.close();

  // Verify file size
  std::ifstream is(filename, std::ios::binary | std::ios::ate);
  std::streamsize size = is.tellg();
  is.close();

  std::cout << "File size: " << size << std::endl;
  // 4 (first u32) + 8 (u64) + 2 (tag count) + 10 (tag name) + 1 (tag type) = 25
  // bytes? Wait, Tag_Defn::write writes the DEFINITION, not the values.
  // Tag_Defn::write writes:
  // count (u16)
  // for each tag:
  //   name (str)
  //   type (u8)
  //   if type is v_u64, extra stuff.

  // Our Tag_Defn has 1 file tag: "test_tag", u32.
  // count: 2 bytes
  // name: "test_tag" -> 2 bytes len + 8 bytes chars = 10 bytes
  // type: u8 -> 1 byte
  // Total Tag_Defn size = 2 + 10 + 1 = 13 bytes.

  // Total written:
  // 1. u32 (4 bytes) -> flushed? No.
  // 2. u64 (8 bytes) -> 4+8 > 10. Flush 4 bytes. Buffer has 8 bytes.
  // 3. Tag_Defn (13 bytes).
  //    - add u16 (2 bytes). Buffer 8+2=10. Full.
  //    - add str "test_tag" (10 bytes). 10+10 > 10. Flush 10 bytes. Buffer has
  //    10 bytes.
  //    - add u8 (1 byte). 10+1 > 10. Flush 10 bytes. Buffer has 1 byte.

  // Total file size should be 4 + 8 + 13 = 25 bytes.

  // Test Header::write with FlushableBuffer
  std::vector<std::string> refs;
  refs.push_back("ref1");
  refs.push_back("ref2");
  RAD::Header header(false, 2, refs, 0);

  // Header write:
  // is_paired (u8) -> 1 byte
  // ref_count (u64) -> 8 bytes
  // ref_names:
  //   "ref1" -> 2+4 = 6 bytes
  //   "ref2" -> 2+4 = 6 bytes
  // num_chunks (u64) -> 8 bytes
  // Total: 1 + 8 + 6 + 6 + 8 = 29 bytes.

  // Buffer currently has 1 byte (from Tag_Defn write u8 type).
  // 1 + 29 > 10. Flush.

  header.write(buf);

  // Manually flush remaining
  buf.flush();
  os.close();

  // Verify file size
  std::ifstream is2(filename, std::ios::binary | std::ios::ate);
  std::streamsize size2 = is2.tellg();
  is2.close();

  std::cout << "File size: " << size2 << std::endl;
  // Previous size: 29 bytes.
  // Header size: 29 bytes.
  // Total: 29 + 29 = 58 bytes.

  assert(size2 == 58);

  std::remove(filename.c_str());
  std::cout << "Test passed!" << std::endl;
}

int main() {
  test_flushable_buffer();
  return 0;
}
