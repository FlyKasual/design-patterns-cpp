#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <map>
#include <algorithm>

struct Sentence
{
public:
  struct WordToken
  {
    bool capitalize;
  };
  std::vector<std::string> words;
  std::map<int, WordToken> tokens;

  Sentence(const std::string& text)
  {
    std::istringstream ss{text};
    words = std::vector<std::string>(std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>{});
  }

  WordToken& operator[](std::size_t index)
  {
    tokens[index] = WordToken{false};
    return tokens.at(index);
  }

  std::string str() const
  {
    std::ostringstream oss;

  for (std::size_t i = 0; i < words.size(); ++i) {
    std::string w = words.at(i);
    auto t = tokens.find(i);

    if (t != tokens.end() && t->second.capitalize)
      std::transform(w.begin(), w.end(), w.begin(), ::toupper);
    oss << w;
    if (i != words.size() - 1)
      oss << " ";
  }

    return oss.str();
  }
};
