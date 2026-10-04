#include <stdio.h>
template<class T> T square(T x) { return x * x; }
struct Pair { int first, second; int sum() const { return first + second; } };
int main() {
  Pair p = {17, 25};
  const int answer = p.sum() + square(3);
  printf("MSVC71 compile/link smoke: %d\n", answer);
  return answer == 51 ? 0 : 1;
}
