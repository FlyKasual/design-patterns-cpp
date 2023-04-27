#include <iostream>
#include "Builder.cpp"

int main() {
  auto cb = CodeBuilder{ "Person" }.add_field("name", "string").add_field("age", "int");

  std::cout << cb;
}
