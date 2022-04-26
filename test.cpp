
extern "C" {
#include "include/config.h"
#include "include/xdelta3.h"
}
#include <cassert>
#include <memory>
#include <vector>

typedef uint8_t byte_t;
std::vector<byte_t> xd3_encode(const byte_t *in, size_t in_size,
                               const byte_t *ref, size_t ref_size) {
  const auto max_buffer_size = (in_size + ref_size) * 2;
  std::unique_ptr<byte_t[]> buffer(new byte_t[max_buffer_size]);
  size_t sz;
  xd3_encode_memory(in, in_size, ref, ref_size, buffer.get(), &sz,
                    max_buffer_size, 0);
  std::vector<byte_t> res;
  res.assign(buffer.get(), buffer.get() + sz);
  return res;
}

std::vector<byte_t> xd3_decode(const byte_t *delta, size_t delta_size,
                               const byte_t *ref, size_t ref_size) {
  const auto max_buffer_size = (ref_size + delta_size) * 2;
  std::unique_ptr<byte_t[]> buffer(new byte_t[max_buffer_size]);
  size_t sz;
  xd3_decode_memory(delta, delta_size, ref, ref_size, buffer.get(), &sz,
                    max_buffer_size, 0);
  std::vector<byte_t> res;
  res.assign(buffer.get(), buffer.get() + sz);
  return res;
}

void simple_test() {
  byte_t in[] = {'x', 'c', 'c', 'a', 'y', 'c', 'c'};
  byte_t ref[] = {'x', 'c', 'c', 'a', 'm', 't', 't'};
  auto delta = xd3_encode(in, sizeof(in), ref, sizeof(ref));
  auto ori = xd3_decode(delta.data(), delta.size(), ref, sizeof(ref));
  assert(sizeof(in) == ori.size());
  for (int i = 0; i < sizeof(in); i++) {
    assert(in[i] == ori[i]);
  }
}

int main() {
  simple_test();
  return 0;
}