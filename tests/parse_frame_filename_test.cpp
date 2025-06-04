#include <cstdlib>
#include <iostream>
#include <string>

namespace libfreenect2 {
bool parseFrameFilename(const std::string& frame_filename, size_t timestamp_sequence[2]);
}

void expect_success(const std::string& filename, size_t ts, size_t seq)
{
    size_t out[2] = {0};
    if(!libfreenect2::parseFrameFilename(filename, out))
    {
        std::cerr << "Expected success for '" << filename << "'\n";
        std::exit(EXIT_FAILURE);
    }
    if(out[0] != ts || out[1] != seq)
    {
        std::cerr << "Unexpected values for '" << filename << "': "
                  << out[0] << ", " << out[1] << "\n";
        std::exit(EXIT_FAILURE);
    }
}

void expect_failure(const std::string& filename)
{
    size_t out[2] = {0};
    if(libfreenect2::parseFrameFilename(filename, out))
    {
        std::cerr << "Expected failure for '" << filename << "'\n";
        std::exit(EXIT_FAILURE);
    }
}

int main()
{
    expect_success("frame_12345_7.depth", 12345, 7);
    expect_success("img_9999_2.jpg", 9999, 2);

    expect_failure("frame_123_45.png");
    expect_failure("badformat.depth");
    expect_failure("frame_0_1.depth");

    std::cout << "All tests passed" << std::endl;
    return 0;
}
