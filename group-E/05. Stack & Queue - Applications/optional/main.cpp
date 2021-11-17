#include "optional.hpp"
#include <iostream>

int main()
{
    optional<int> a;
    optional<int> b{10};
    std::cout<<a.has_value()<<" "<<b.has_value()<<std::endl;
    std::cout<<b.value()<<std::endl;
    return 0;
}