#include <vector>
#include <tuple>
#include <string>

class Code
{
public:
  std::string class_name;
  std::vector<std::tuple<std::string, std::string>> fields;

  Code(std::string class_name): class_name(class_name) {};
};
