#include "gtest/gtest.h"
#include "My_Vector.h"

// Right destruction order
class DestructionOrderTracker {
public:
    static std::vector<int> destructionOrder;
    int id;
    DestructionOrderTracker(int id) : id(id) {
        std::cout << "Constructing " << id << "\n";
    }
    DestructionOrderTracker(const DestructionOrderTracker& other) : id(other.id) {
        std::cout << "Copy constructing " << id << "\n";
    }
    DestructionOrderTracker(DestructionOrderTracker&& other) noexcept : id(other.id) {
        other.id = -1; // Invalidate the moved object
        std::cout << "Move constructing " << id << "\n";
    }
    DestructionOrderTracker& operator=(const DestructionOrderTracker& other) {
        std::cout << "Copy assigning " << id << "\n";
        if (this != &other) {
            id = other.id;
        }
        return *this;
    }
    DestructionOrderTracker& operator=(DestructionOrderTracker&& other) noexcept {
        std::cout << "Move assigning " << id << "\n";
        if (this != &other) {
            id = other.id;
            other.id = -1; // Invalidate the moved object
        }
        return *this;
    }
    ~DestructionOrderTracker() {
        if (id != -1) { // We don`t take into account the moved objects
            std::cout << "Destructing " << id << "\n";
            destructionOrder.push_back(id);
        }
    }
};

std::vector<int> DestructionOrderTracker::destructionOrder;

TEST(My_Vector_Test, DestructionOrder) {
    DestructionOrderTracker::destructionOrder.clear();
    {
        My_Vector<DestructionOrderTracker> vec;
        vec.emplace_back(1);
        vec.emplace_back(2);
        vec.emplace_back(3);
    } // went out from scope and elements will be destroyed

    for (int id : DestructionOrderTracker::destructionOrder) {
        std::cout << "Destroyed: " << id << "\n";
    }

    ASSERT_EQ(DestructionOrderTracker::destructionOrder.size(), 3);
    EXPECT_EQ(DestructionOrderTracker::destructionOrder[0], 3);
    EXPECT_EQ(DestructionOrderTracker::destructionOrder[1], 2);
    EXPECT_EQ(DestructionOrderTracker::destructionOrder[2], 1);
}


