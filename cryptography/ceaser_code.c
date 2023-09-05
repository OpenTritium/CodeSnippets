#include <malloc.h>
#include <stdio.h>
#include <string.h>

const unsigned char ROUND = 26;

static char encrypt(const char *c, const unsigned offset,
                    const unsigned char order) {
  if (*c >= 'a' && *c <= 'z') {
    return (*c - 'a' + ROUND + (order * offset) % ROUND) % ROUND + 'a';
  } else if (*c >= 'A' && *c <= 'Z') {
    return (*c - 'A' + ROUND + (order * offset) % ROUND) % ROUND + 'A';
  } else
    return *c;
}

int main() {
  const size_t BUFFER_MAX_SIZE = 128;
  char buffer[BUFFER_MAX_SIZE];
  fgets(buffer, BUFFER_MAX_SIZE, stdin);
  unsigned offset;
  scanf("%d", &offset);
  size_t str_len = strnlen(buffer, BUFFER_MAX_SIZE);
  char *cipher_text = malloc(str_len);
  if (cipher_text == NULL) {
    fprintf(stderr, "分配堆内存失败\n");
    return 0;
  }
  strncpy(cipher_text, buffer, str_len);
  char text[str_len];
  for (char i = 0; i != ROUND; ++i) {
    char *ptr = cipher_text;
    size_t j = 0;
    while (*ptr != '\n') {
      text[j] = encrypt(ptr, offset, i);
      ++j;
      ++ptr;
    }
    text[j] = '\0';
    printf("暴力破解第%d轮：%s\n", i, text);
  }
  free(cipher_text);
  return 0;
}