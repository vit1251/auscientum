
#include <cassert>
#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include "Hash.hpp"
#include "str.hpp"

TEST(CompatHashTest, HashOnStack) {

    Hash hash;
    hash.Update("Hello, world!");
    std::string digest = hash.Digest();

    ASSERT_EQ(digest, "c1527cd893c124773d811911970c8fe6e857d6df5dc9226bd8a160614c0cd963a4ddea2b94bb7d36021ef9d865d5cea294a82dd49a0bb269f51f6e7a57f79421");

}

TEST(CompatHashTest, HashOnHeap) {
    Hash *hash = new Hash();
    hash->Update("Hello, world!");
    std::string digest = hash->Digest();
    delete hash;

    ASSERT_EQ(digest, "c1527cd893c124773d811911970c8fe6e857d6df5dc9226bd8a160614c0cd963a4ddea2b94bb7d36021ef9d865d5cea294a82dd49a0bb269f51f6e7a57f79421");
}

TEST(CompatStrTest, endsWithEmpty) {

    ASSERT_EQ(str::endsWith("", "/"), false);
}

TEST(CompatStrTest, endsWithChar) {

    ASSERT_EQ(str::endsWith("http:", ":"), true);
}

TEST(CompatStrTest, endsWithStr) {

    ASSERT_EQ(str::endsWith("http://", "://"), true);
}

TEST(CompatStrTest, endsWithAll) {

    ASSERT_EQ(str::endsWith("://", "://"), true);
}

TEST(CompatStrTest, makeDurationHour) {

    ASSERT_EQ(str::makeDuration(3600), "01:00:00");
}

TEST(CompatStrTest, makeDurationAll) {

    ASSERT_EQ(str::makeDuration(5415), "01:30:15");
}
