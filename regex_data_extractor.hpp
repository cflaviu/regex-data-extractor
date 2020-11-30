#pragma once
#ifndef PCH
    #include <string>
    #include <regex>
    #include <fstream>
    #include <filesystem>
#endif

class regex_data_extractor
{
public:
    struct statistic_data
    {
      uint file_count = 0;
      uint file_processed_count = 0;
      uint match_count = 0;
    };

    regex_data_extractor(std::string pattern, std::string input_folder_path, std::string output_file_path);

    const statistic_data& statistics() const noexcept { return _statistics; }

    void operator () ();

protected:
    statistic_data _statistics;
    std::regex _regex;
    std::smatch _matches;
    std::filesystem::directory_iterator _directory_iterator;
    std::ofstream _output;
};
