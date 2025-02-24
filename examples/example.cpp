#include <vector>
#include <iostream>

#include "string.hpp"

bool comparator(const String & a, const String & b)
{
  String lowerA = a;
  String lowerB = b;

  std::transform(lowerA.begin(), lowerA.end(), lowerA.begin(), tolower);
  std::transform(lowerB.begin(), lowerB.end(), lowerB.begin(), tolower);

  return lowerA < lowerB;
}

int main(int argc, char ** argv)
{
  if (argc < 2)
    std::cout << "Usage: " << argv[0] << " string1 string2 ...\n";

  std::vector<String> strings;

  for (int i = 1; i < argc; ++i)
    strings.emplace_back(argv[i]);

  std::sort(strings.begin(), strings.end(), comparator);

  for (auto it = strings.rbegin(); it != strings.rend(); ++it)
    std::cout << *it << '\n';
}