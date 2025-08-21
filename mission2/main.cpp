#include "gmock/gmock.h"

#include "attendance.cpp"

using namespace testing;

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}