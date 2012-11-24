#include <sstream>
#include <gtest/gtest.h>

#include "circular_buffer/circular_buffer.h"

TEST(MainTest, basic) {
    CircularBuffer<int> *buffer = new CircularBuffer <int> (5);

    std::stringstream s;

    int o;
    for (int i=0; i<=30; i++) {
        buffer->write(&i, 1);
        buffer->read(&o, 1);

        s << o << ',';
    }

    EXPECT_STREQ(s.str().c_str(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,");
}

TEST(MainTest, size) {
    CircularBuffer<int> *buffer = new CircularBuffer <int> (5);

    int o[] = {0,1,2,3,4};

    buffer->write(o, 5);
    ASSERT_EQ(5, buffer->size());

    buffer->read(o, 5);
    ASSERT_EQ(0, buffer->size());
}

TEST(MainTest, NonDestructiveRead) {
    CircularBuffer<int> *buffer = new CircularBuffer <int> (5);

    int a[] = {0,1,2,3,4};
    buffer->write(a, 5);

    int ii[5];
    buffer->read(ii, 5, false);

    ASSERT_EQ(5, buffer->size());

    std::stringstream s;

    int i;
    for (i=0; i<5; i++)
        s << ii[i] << ',';

    ASSERT_STREQ(s.str().c_str(), "0,1,2,3,4,");

    std::stringstream s2;

    int o;
    for (i=0; i<5; i++) {
        buffer->read(&o, 1);
        s2 << o << ',';
    }

    ASSERT_STREQ(s2.str().c_str(), "0,1,2,3,4,");
}
