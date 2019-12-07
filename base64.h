#include <string>

std::string base64_encode(char const* ESI, unsigned int len); //char const * 指明函数对此参数只进行读取
std::string base64_decode(std::string const& Str); //引用传递参数快，不浪费资源。const指定不能修改，完美。
