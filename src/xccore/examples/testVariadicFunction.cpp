#include <iostream>

template <class T>
void print(const T& t)
{
  std::cout << t;
}

template <class Arg1, class ...ArgN>
void print(const Arg1& a1, const ArgN& ...an)
{
  std::cout << a1 << ' ';
  print(an...);
}

int main()
{
  print(1, 2.4, 'u', "hello world");
}
