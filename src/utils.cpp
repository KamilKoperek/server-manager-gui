#include <iostream>
gchar *str2gchar(std::string var) { return &var[0]; }

std::string command_result(std::string command) {
  std::FILE *temp_file = std::tmpfile();
  std::string path = tmpnam((char *)temp_file);
  system((command + " > " + path).c_str());

  std::fstream file(path);
  std::string result = "";
  std::string line;
  if (file.is_open()) {
    while (!file.eof()) {
      file >> line;
      result += line;
    }
  }
  return result;
}
