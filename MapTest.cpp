#include <iostream>
#include <string>
#include "Map.h"


int main()
{
    Map<std::string,int> str_int;

    std::cout << "Test 1: Emplacing value 10 with key 'Hello'\n";

    std::string key{"Hello"};

    str_int.Emplace(key, 10);

    std::cout << "Contents of 'Hello': " << str_int[key] << "\n\n";

    std::cout << "Test 2: Search for key 'Hello'.\n";
    std::cout << "Is 'Hello' an existing key that can be found?: " << std::boolalpha << str_int.Find("Hello") << "\n\n";

    std::cout << "Test 3: Try to re-emplace the same key.\n";
    std::cout << "Able to emplace another value by using the same key?: " << str_int.Emplace(key, 5) << "\n\n";

    std::cout << "Test 4: Try to erase key then find the key\n";
    str_int.Erase(key);
    std::cout << "Can 'Hello' key be found after erasure?: " << str_int.Find("Hello") << "\n\n";

    std::cout << "Test 5: Insert 'test key' and see if it can be read from a constant copy vs constant reference before/after clearing\n";
    str_int.Emplace("test key", 5);
    Map<std::string,int> str_int_const{str_int};
    Map<std::string,int> & str_int_const_ref{str_int};
    std::cout << "Can 'test key' key be found after insertion?: " << str_int_const.Find("test key") << '\n';
    str_int.Clear();
    std::cout << "Can 'test key' key be found in the constant after original map has been cleared?: " << str_int_const.Find("test key") << '\n';
    std::cout << "Can 'test key' key be found in the constant reference now?: " << str_int_const_ref.Find("test key") << '\n';

}
