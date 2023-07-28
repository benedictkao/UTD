#include "./helper.h"

void CustomMemoryManager::Start() {
  num_allocs     = 0;
  max_bytes_used = 0;
}

void CustomMemoryManager::Stop(Result& result) {
  result.num_allocs     = num_allocs;
  result.max_bytes_used = max_bytes_used;
}

char get_random_char() {
  char abc[52]  = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                    'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
  int  rand_idx = rand() % 52;
  return abc[rand_idx];
}

void generate_c_str(char* c_str_ptr, size_t str_len, bool random) {
  for (int i = 0; i < str_len; i++)
    c_str_ptr[i] = random ? get_random_char() : 'c';
  c_str_ptr[str_len] = '\0';
}
