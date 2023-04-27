#include <ostream>
#include <sstream>
#include <string>
#include <tuple>

#include "Code.cpp"
using namespace std;

class CodeBuilder
{
protected:
  Code code_;

public:
  CodeBuilder() = delete;
  CodeBuilder(const string& class_name): code_{ class_name } {};

  CodeBuilder& add_field(const string& name, const string& type) {
    code_.fields.emplace_back(name, type);
    return *this;
  }

  friend ostream& operator<<(ostream& os, const CodeBuilder& obj) {
    os << "class " << obj.code_.class_name << "\n{\n";
    for (const auto& [key, value] : obj.code_.fields) {
      os << "  " << value << " " << key << ";\n";
    }
    os << "}";
    return os;
  }
};
