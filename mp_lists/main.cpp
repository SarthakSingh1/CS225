#include "List.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream> // std::stringstream

int main() {

  std::stringstream ss;

  List<int> list;
  list.insertBack(1);
  list.insertBack(2);
  list.insertBack(3);
  list.insertBack(4);
  list.insertBack(5);
  list.insertBack(6);
  list.insertBack(7);

  list.print(ss);

  list.reverse();

  list.print(ss);
  std::cout << ss.str() << std::endl ;

  return 0;
}
