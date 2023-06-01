#include <algorithm>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <vector>
#include <string>

using CodeType = std::uint16_t;

namespace globals {
    const CodeType dms{std::numeric_limits<CodeType>::max()};
}

void compress(std::istream &is, std::ostream &os) {
    std::map <std::pair<CodeType, char>, CodeType> dictionary;

    const auto reset_dictionary = [&dictionary] {
        dictionary.clear();

        const long int minc = std::numeric_limits<char>::min();
        const long int maxc = std::numeric_limits<char>::max();

        for (long int c = minc; c <= maxc; ++c) {
            const CodeType dictionary_size = dictionary.size();

            dictionary[{globals::dms, static_cast<char>(c)}] = dictionary_size;
        }
    };

    reset_dictionary();

    CodeType i{globals::dms};
    char c;

    while (is.get(c)) {

        if (dictionary.size() == globals::dms)
            reset_dictionary();

        if (dictionary.count({i, c}) == 0) {

            const CodeType dictionary_size = dictionary.size();

            dictionary[{i, c}] = dictionary_size;
            os.write(reinterpret_cast<const char *>(&i), sizeof(CodeType));
            i = dictionary.at({globals::dms, c});
        } else
            i = dictionary.at({i, c});
    }

    if (i != globals::dms)
        os.write(reinterpret_cast<const char *>(&i), sizeof(CodeType));
}

void decompress(std::istream &is, std::ostream &os) {
    std::vector <std::pair<CodeType, char>> dictionary;

    const auto reset_dictionary = [&dictionary] {
        dictionary.clear();
        dictionary.reserve(globals::dms);

        const long int minc = std::numeric_limits<char>::min();
        const long int maxc = std::numeric_limits<char>::max();

        for (long int c = minc; c <= maxc; ++c)
            dictionary.push_back({globals::dms, static_cast<char>(c)});
    };

    const auto rebuild_string = [&dictionary](CodeType k) -> std::vector<char> {
        std::vector<char> s;

        while (k != globals::dms) {
            s.push_back(dictionary.at(k).second);
            k = dictionary.at(k).first;
        }

        std::reverse(s.begin(), s.end());
        return s;
    };

    reset_dictionary();

    CodeType i{globals::dms};
    CodeType k;

    while (is.read(reinterpret_cast<char *>(&k), sizeof(CodeType))) {

        if (dictionary.size() == globals::dms)
            reset_dictionary();

        if (k > dictionary.size())
            throw std::runtime_error("invalid compressed code");

        std::vector<char> s;

        if (k == dictionary.size()) {
            dictionary.push_back({i, rebuild_string(i).front()});
            s = rebuild_string(k);
        } else {
            s = rebuild_string(k);

            if (i != globals::dms)
                dictionary.push_back({i, s.front()});
        }

        os.write(&s.front(), s.size());
        i = k;
    }

    if (!is.eof() || is.gcount() != 0)
        throw std::runtime_error("corrupted compressed file");
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "\tcheck README\n";
        return EXIT_FAILURE;
    }

    std::string Action = "";

    if (std::string(argv[1]) == "-c")
        Action = "compress";
    else if (std::string(argv[1]) == "-d")
        Action = "decompress";
    else {
        std::cerr << std::string("flag `") + argv[1] + "' is not recognized.";
        return EXIT_FAILURE;
    }

    const std::size_t buffer_size{1024 * 1024};

    const std::unique_ptr<char[]> input_buffer(new char[buffer_size]);
    const std::unique_ptr<char[]> output_buffer(new char[buffer_size]);

    std::ifstream input_file;
    std::ofstream output_file;

    input_file.rdbuf()->pubsetbuf(input_buffer.get(), buffer_size);
    input_file.open(argv[2], std::ios_base::binary);

    if (!input_file.is_open()) {
        std::cerr << std::string("input_file `") + argv[2] + "' could not be opened.";
        return EXIT_FAILURE;
    }

    output_file.rdbuf()->pubsetbuf(output_buffer.get(), buffer_size);
    output_file.open(argv[3], std::ios_base::binary);

    if (!output_file.is_open()) {
        std::cerr << std::string("output_file `") + argv[3] + "' could not be opened.";
        return EXIT_FAILURE;
    }

    try {
        input_file.exceptions(std::ios_base::badbit);
        output_file.exceptions(std::ios_base::badbit | std::ios_base::failbit);

        if (Action == "compress")
            compress(input_file, output_file);
        else if (Action == "decompress")
            decompress(input_file, output_file);
    }
    catch (const std::ios_base::failure &f) {
        std::cerr << std::string("File input/output failure: ") + f.what() + '.', false;
        return EXIT_FAILURE;
    }
    catch (const std::exception &e) {
        std::cerr << std::string("Caught exception: ") + e.what() + '.', false;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
