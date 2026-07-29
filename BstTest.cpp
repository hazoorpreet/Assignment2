#include <iostream>
#include <functional>
#include <fstream>
#include "Bst.h"

void printInt(const int & num);
void fillTree(Bst<int> & intTree);
void Test1(const Bst<int> & intTree);
void Test2(const Bst<int> & intTree);
void Test3(const Bst<int> & intTree);
void Test4(const Bst<int> & intTree);
void Test5(const Bst<int> & intTree);
void Test6(const Bst<int> & intTree);
void Test7(const Bst<int> & intTree);

std::istream & operator>>(std::istream & input, const Bst<int> & intTree);

int main()
{
    Bst<int> intTree{};
    fillTree(intTree);
    Test1(intTree);
    Test2(intTree);
    Test3(intTree);
    Test4(intTree);
    Test5(intTree);
    Test6(intTree);

    return 0;
}

void fillTree(Bst<int> & intTree)
{
    int nums[11] = {2949, 1697, 4689, 353, 485, 4337, 4337, 1692, 4322, 3841, 4383};
    for (int i{0}; i < 11; i++)
    {
        intTree.Insert(nums[i]);
    }
}

void Test1(const Bst<int> & intTree)
{
    std::cout << "Test 1: Searching for numbers\n";
    std::cout << "Search for number '353': "
              << (intTree.Search(353) ? "Found" : "Not Found") << '\n';

    std::cout << "Search for number '648': "
              << (intTree.Search(648) ? "Found" : "Not Found") << '\n';
}

void Test2(const Bst<int> & intTree)
{
    std::cout << "\nTest 2: Print PreOrder\n";
    intTree.PreOrder(printInt);
}

void Test3(const Bst<int> & intTree)
{
    std::cout << "\n\nTest 3: Print InOrder\n";
    intTree.InOrder(printInt);
}
void Test4(const Bst<int> & intTree)
{
    std::cout << "\n\nTest 4: Print PostOrder\n";
    intTree.PostOrder(printInt);
}
void Test5(const Bst<int> & intTree)
{
    std::cout << "\n\nTest 5: Copy constructor + add an additional key (12)\n";
    Bst<int> copTree(intTree);
    copTree.Insert(12);
    std::cout << "Copied tree in order:\n";
    copTree.InOrder(printInt);
    std::cout << "\nOriginal tree in order:\n";
    intTree.InOrder(printInt);
}

void Test6(const Bst<int> & intTree)
{
    Bst<int> copTree{};
    std::cout << "\n\nTest 6: Assignment copying + add an additional key (19)\n";
    copTree = intTree;
    copTree.Insert(19);
    std::cout << "Copied tree in order:\n";
    copTree.InOrder(printInt);
    std::cout << "\nOriginal tree in order:\n";
    intTree.InOrder(printInt);
}

void printInt(const int & num)
{
    std::cout << num << ' ';
}
