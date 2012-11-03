#include <sstream>
#include <gtest/gtest.h>

#include "circular_buffer.h"

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
