#include "My_Vector.h"
#include <gtest/gtest.h>

// int
TEST(My_Vector_Test, PushBack_Int) {
    My_Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(My_Vector_Test, PopBack_Int) {
    My_Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.pop_back();

    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 1);
}

TEST(My_Vector_Test, Clear_Int) {
    My_Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.clear();

    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(My_Vector_Test, Resize_Int) {
    My_Vector<int> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    EXPECT_EQ(vec.size(), 10);
    EXPECT_EQ(vec.capacity(), 16); // initial capacity 2, doubled to 4, 8, and finally 16

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(vec[i], i);
    }
}

// Printer
TEST(My_Vector_Test, PushBack_Printer) {
    My_Vector<Printer> vec;
    vec.push_back(Printer());
    vec.push_back(Printer());

    EXPECT_EQ(vec.size(), 2);
}

TEST(My_Vector_Test, PopBack_Printer) {
    My_Vector<Printer> vec;
    vec.push_back(Printer());
    vec.push_back(Printer());
    vec.pop_back();

    EXPECT_EQ(vec.size(), 1);
}

TEST(My_Vector_Test, Clear_Printer) {
    My_Vector<Printer> vec;
    vec.push_back(Printer());
    vec.push_back(Printer());
    vec.clear();

    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
}

// int
TEST(My_Vector_Test, PushBack_VectorOfVector) {
    My_Vector<My_Vector<int>> vec;
    vec.push_back(My_Vector<int>());
    vec[0].push_back(1);

    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0].size(), 1);
    EXPECT_EQ(vec[0][0], 1);
}

TEST(My_Vector_Test, PopBack_VectorOfVector) {
    My_Vector<My_Vector<int>> vec;
    vec.push_back(My_Vector<int>());
    vec.pop_back();

    EXPECT_EQ(vec.size(), 0);
}

// Inner tests
class
Outer {
public:
    class Inner {
    public:
        int value;
        Inner(int v) : value(v) {}
    };

    My_Vector<Inner> inners;
    void addInner(int value) {
        inners.push_back(Inner(value));
    }
};

TEST(My_Vector_Test, NestedClasses) {
    Outer outer;
    outer.addInner(1);
    outer.addInner(2);
    outer.addInner(3);

    EXPECT_EQ(outer.inners.size(), 3);
    EXPECT_EQ(outer.inners[0].value, 1);
    EXPECT_EQ(outer.inners[1].value, 2);
    EXPECT_EQ(outer.inners[2].value, 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
