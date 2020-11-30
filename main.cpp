#include <iostream>
#include "regex_data_extractor.hpp"

int main(int argc, const char* argv[])
{
    if (argc != 4)
    {
        std::cout << "params: <regex> <folder-path> <output-file>\n";
        return -1;
    }

    try
    {
        regex_data_extractor extractor(argv[1], argv[2], argv[3]);
        extractor();

        auto& statistics = extractor.statistics();
        std::cout << "file-count: " << statistics.file_count << '\n';
        std::cout << "file-processed-count: " << statistics.file_processed_count << '\n';

        auto not_processed = statistics.file_count - statistics.file_processed_count;
        if (not_processed != 0)
        {
            std::cout << "file-not-processed-count: " << not_processed << '\n';
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << '\n';
        return -2;
    }
    catch (...)
    {
        std::cerr << "unknown exception\n";
        return -3;
    }

    return 0;
}
