#include <sstream>
#include <gtest/gtest.h>

#include "circular_buffer/circular_buffer.h"

TEST(MainTest, capacity) {
    CircularBuffer<int> buffer(5);

    EXPECT_EQ(5, buffer.capacity());
}

TEST(MainTest, basic) {
    CircularBuffer<int> buffer(5);

    std::stringstream s;

    int o;
    for (int i=0; i<=30; i++) {
        buffer.write(&i, 1);
        buffer.read(&o, 1);

        s << o << ',';
    }

    EXPECT_STREQ(s.str().c_str(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,");
}

TEST(MainTest, size) {
    CircularBuffer<int> buffer(5);

    int o[] = {0,1,2,3,4};

    buffer.write(o, 3);
    ASSERT_EQ(3, buffer.size());

    buffer.read(o, 3);
    ASSERT_EQ(0, buffer.size());

    buffer.write(o, 4);
    ASSERT_EQ(4, buffer.size());

    buffer.read(o, 4);
    ASSERT_EQ(0, buffer.size());
}

TEST(MainTest, NonDestructiveRead) {
    CircularBuffer<char> buffer(10);

    char in[10] = "abcdefghi";
    buffer.write(in, 10);


    char out1[5];
    buffer.read(out1, 5, false);

    EXPECT_EQ(10, buffer.size());
    EXPECT_STREQ("abcde", out1);


    char out2[10];
    buffer.read(out2, 10);

    EXPECT_EQ(0, buffer.size());
    EXPECT_STREQ(in, out2);
}

TEST(MainTest, Overread) {
    CircularBuffer<char> buffer(10);

    char in[10] = "abcdefghi";
    buffer.write(in, 10);

    char out[15];
    EXPECT_DEATH(buffer.read(out, 15), "");
}

TEST(MainTest, Overwrite) {
    CircularBuffer<char> buffer(10);

    char in[10] = "abcdefghi";
    buffer.write(in, 10);

    char out1[5];
    buffer.read(out1, 5);

    char in2[10] = "jklmnopqr";
    EXPECT_DEATH(buffer.write(in2, 9), "");
}
