#include <string>
#include <fstream>
#define config_path "config"
std::string get_config (std::string name)
{
 std::fstream file(config_path+(std::string)"/"+name);
 std::string result = "error";
 if(file.is_open())
 {
   file >> result;
 }
 return result;
}


bool set_config (std::string name, std::string value)
{
 std::ofstream file(config_path+(std::string)"/"+name, std::ios::trunc);
 if(file.is_open())
 {
   file << value;
   return 1;
 }


}
