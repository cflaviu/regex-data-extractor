import qbs

CppApplication {
    consoleApplication: true
    files: [
        "main.cpp",
        "regex_data_extractor.cpp",
        "regex_data_extractor.hpp",
    ]
    cpp.cxxLanguageVersion: "c++17"
    Group {
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
