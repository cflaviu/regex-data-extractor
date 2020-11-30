#include "regex_data_extractor.hpp"
#include <iostream>

regex_data_extractor::regex_data_extractor(std::string pattern, std::string input_folder_path, std::string output_file_path):
  _regex(pattern),
  _directory_iterator(input_folder_path),
  _output(output_file_path)
{
    if (input_folder_path.empty() || !std::filesystem::exists(input_folder_path))
    {
        throw std::runtime_error("folder \" + input_folder_path + \" doesn't exists");
    }

    if (!_output.is_open())
    {
        throw std::runtime_error("output file \"" + output_file_path + "\" cannot be opened");
    }
}

void regex_data_extractor::operator () ()
{
    _statistics = statistic_data();
    std::smatch matches;
    std::string line;
    std::ifstream input;
    for(auto& entry : _directory_iterator)
    {
        if (entry.is_regular_file())
        {
            ++_statistics.file_count;
            input.open(entry.path());
            if (input.is_open())
            {
                while(std::getline(input, line))
                {
                    if (regex_search(line, matches, _regex))
                    {
                        _statistics.match_count += matches.size();
                        for(auto i = matches.begin() + 1; i != matches.end(); ++i)
                        {
                            _output << *i << '\n';
                        }
                    }
                }

                input.close();
                input.clear();
                ++_statistics.file_processed_count;
                std::cout << "processed " << entry.path() << "\n";
                std::cout << "match-count: " << _statistics.match_count << "\n";
            }
            else
            {
                std::cerr << "failed to open \"" << entry.path() << '\n';
            }
        }
    }
}
