#include <iostream>
#include "Vector.h"

int main() {
    std::cout << "Test 1: Creation of an empty vector.\n";
    Vector<int> myVec{};
    std::cout << "Vector Size: " << myVec.Size() << '\n';
    std::cout << "Successful.\n\n";

    std::cout << "Test 2: Creation of a 5-value vector.\n";
    Vector<int> myVec2(5);
    std::cout << "Vector Size: " << myVec2.Size() << '\n';
    std::cout << "Successful.\n\n";

    std::cout << "Test 3: Setting values 54321 to list of 5 elements\n";
    myVec2[0] = 5;
    myVec2[1] = 4;
    myVec2[2] = 3;
    myVec2[3] = 2;
    myVec2[4] = 1;
    std::cout << "Entered Values: " <<  myVec2[0] << myVec2[1] << myVec2[2] << myVec2[3] << myVec2[4];
    std::cout << "\n\n";

    std::cout << "Test 4: Insertion of value 4 in position 3.\n";
    myVec2.Insert(3, 4);
    std::cout << "After Insertion: " << myVec2[0] << myVec2[1] << myVec2[2] << myVec2[3] << myVec2[4] << myVec2[5] << '\n';
    std::cout << "\n\n";

    std::cout << "Test 5: Appending value 4 to an empty array.\n";
    myVec.Insert(myVec.Size(), 4);
    std::cout << "Value in first position: " << myVec[0];
    std::cout << "\n\n";

    std::cout << "Test 6: Deleting a value from a single value array\n";
    std::cout << "Current Size: " << myVec.Size() << '\n';
    myVec.Delete(0);
    std::cout << "New Size: " << myVec.Size();
    std::cout << "\n\n";

    std::cout << "Test 7: Copy assignment, setting first value to 1 to confirm deep copy\n";
    myVec = myVec2;
    myVec[0] = 1; // make sure copy is deep
    std::cout << "Original Vector Elements: " << myVec2[0] << myVec2[1] << myVec2[2] << myVec2[3] << myVec2[4] << myVec2[5] << '\n';
    std::cout << "Copied Vector Elements: " << myVec[0] << myVec[1] << myVec[2] << myVec[3] << myVec[4] << myVec[5];
    std::cout << "\n\n";

    std::cout << "Test 8: Copy Construction, setting first value to 2 to confirm deep copy\n";
    Vector<int> myVec3(myVec2);
    myVec3[0] = 2; // make sure copy is deep
    std::cout << "Original Vector Elements: " << myVec2[0] << myVec2[1] << myVec2[2] << myVec2[3] << myVec2[4] << myVec2[5] << '\n';
    std::cout << "New Vector Elements: " << myVec3[0] << myVec3[1] << myVec3[2] << myVec3[3] << myVec3[4] << myVec3[5];
    std::cout << "\n\n";

    std::cout << "Test 9: Clearing a Vector\n";
    std::cout << "Original Size: " << myVec2.Size() << '\n';
    myVec2.Clear();
    std::cout << "New Size: " << myVec2.Size();
    std::cout << "\n\n";

    return 0;
}
