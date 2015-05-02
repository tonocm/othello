// my first program in C++
#include <iostream>

namespace hi {
int a = 2;
}

void func(std::string &a) {
  a = NULL;
}

class File {
public:
  File(const std::string &name) {
    f = fopen(name.c_str(), "r");
  }
  ~File() {
    if (f != NULL) {
      fclose(f);
    }
  }
  std::string read() {
    // read the file
  }
protected:
  FILE *f;
};

template <int N>
class array {
  enum { a = N * array<N - 1>::a; };
};

template <>
class array<0> {
  enum { a = 1; };
};

template <typename T>
int time(const T &func) {
  // get start time
  func();
  // get end time; return diff
 }

void func() {
  File f ("hi.txt");

  std::string content = f.read();
}


namespace bye {
int a = 3;
}
int main()
{
  hi::a = 3;
  std::vector<int> v (3);
  std::vector<int> a = {1, 2, 3};
  int *b = &hi::a;
  func(b);
  std::cout << b;
  std::cout << "Hello world\n";
  bye::a = 4;
  printf("Sup Niqaaaaaaaas\n");
  return 0;
}
