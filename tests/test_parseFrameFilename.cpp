#define CATCH_CONFIG_MAIN
#include "minicatch.hpp"
#include <string>

// Function under test (not exposed via header)
bool parseFrameFilename(const std::string& frame_filename, size_t timestamp_sequence[2]);

TEST_CASE(ValidDepth)
{
    size_t ts[2] = {0};
    REQUIRE(parseFrameFilename("123_foo_456.depth", ts));
    REQUIRE(ts[0] == 123);
    REQUIRE(ts[1] == 456);
}

TEST_CASE(ValidJpg)
{
    size_t ts[2] = {0};
    REQUIRE(parseFrameFilename("1_a_2.jpg", ts));
    REQUIRE(ts[0] == 1);
    REQUIRE(ts[1] == 2);
}

TEST_CASE(InvalidExtension)
{
    size_t ts[2] = {0};
    REQUIRE(!parseFrameFilename("123_foo_456.png", ts));
}

TEST_CASE(ZeroTimestamp)
{
    size_t ts[2] = {0};
    REQUIRE(!parseFrameFilename("0_a_1.depth", ts));
}

TEST_CASE(MissingUnderscore)
{
    size_t ts[2] = {0};
    REQUIRE(!parseFrameFilename("123depth", ts));
}

TEST_CASE(NonNumericTimestamp)
{
    size_t ts[2] = {0};
    REQUIRE(!parseFrameFilename("abc_1_2.depth", ts));
}
