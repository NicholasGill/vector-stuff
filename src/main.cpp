#include "ArrayVector.hpp"
#include "DequeVector.hpp"
#include "LinkedListDequeVector.hpp"
#include "LinkedListVector.hpp"

#include <iostream>

int main() {
    ArrayVector<int> array_vector;
    LinkedListVector<int> linked_list_vector;
    LinkedListDequeVector<int> linked_list_deque_vector;
    DequeVector<int> deque_vector;

    std::cout << "Vector implementations scaffold is ready.\n";
    std::cout << "ArrayVector size: " << array_vector.size() << "\n";
    std::cout << "LinkedListVector size: " << linked_list_vector.size() << "\n";
    std::cout << "LinkedListDequeVector size: " << linked_list_deque_vector.size() << "\n";
    std::cout << "DequeVector size: " << deque_vector.size() << "\n";

    return 0;
}
