#include "pch.h"

#include <string>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include "fmt/color.h"

#include "../mwl_parser/Level.h"
#include "../mwl_parser/MWLConstants.h"

using namespace MWLParser::Constants;

#define TEST_MWL_DIR GetDirectoryName(__FILE__)

namespace Test
{
    std::array test_mwls
    {
        "test_mwls\\original\\level 105.mwl",
        "test_mwls\\custom\\0.mwl"
    };

    std::string GetDirectoryName(std::string path) {
        const size_t last_slash = path.rfind('\\');

        if (last_slash != std::string::npos)
        {
            return path.substr(0, last_slash + 1);
        }
        return "";
    }

    std::vector<uint8_t> readFile(const char* filename)
    {
        // open the file:
        std::ifstream file(filename, std::ios::binary);

        // Stop eating new lines in binary mode!!!
        file.unsetf(std::ios::skipws);

        // get its size:
        std::streampos fileSize;

        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        // reserve capacity
        std::vector<uint8_t> vec;
        vec.reserve(fileSize);

        // read the data:
        vec.insert(vec.begin(),
            std::istream_iterator<uint8_t>(file),
            std::istream_iterator<uint8_t>());

        return vec;
    }

    using MWLParser::Level;

    class ByteConversionTest : public testing::TestWithParam<const char*>
    {
    protected:
        void SetUp() override
        {
            auto path = std::filesystem::path(TEST_MWL_DIR);
            path /= GetParam();
            mwl_bytes = readFile(path.string().c_str());

            level = std::make_unique<Level>(mwl_bytes);
        }

        std::unique_ptr<Level> level;
        std::vector<uint8_t> mwl_bytes;
    };

    std::string getDifferenceString(const std::vector<uint8_t>& expected, 
        const std::vector<uint8_t> actual, size_t padding = 0, size_t bytes_per_line = 0x8)
    {
        std::string output{};

        if (expected.size() != actual.size())
        {
            output += fmt::format("Actual size: {:#x}, expected size: {:#x}\n\n", actual.size(), expected.size());
        }

        size_t line_idx = 0;
        for (size_t i = 0; i != std::max(expected.size(), actual.size()) + padding; ++i)
        {

            if (i % 0x8 == 0)
            {
                output += fmt::format("{}{:03X}: ", i != 0 ? "\n" : "", line_idx * bytes_per_line);
                ++line_idx;
            }

            if (i < padding)
            {
                output += "--     ";
                continue;
            }

            size_t idx = i - padding;
            std::string expected_byte, actual_byte;

            if (idx >= actual.size())
            {
                expected_byte = fmt::format("{:02X}", expected.at(idx));
                actual_byte = "--";
            }
            else if (idx >= expected.size())
            {
                expected_byte = "--";
                actual_byte = fmt::format("{:02X}", actual.at(idx));
            }
            else if (expected.at(idx) != actual.at(idx))
            {
                expected_byte = fmt::format("{:02X}", expected.at(idx));
                actual_byte = fmt::format("{:02X}", actual.at(idx));
            }
            else
            {
                expected_byte = fmt::format("{:02X}", expected.at(idx));
                actual_byte = expected_byte;
            }

            output += fmt::format("{}{}  ", actual_byte, 
                expected_byte != actual_byte ? '(' + expected_byte + ')' : "    ");
        }

        output += "\n\nFormat: XX(YY), XX -> actual byte, YY -> expected byte";

        return output;
    }

    TEST_P(ByteConversionTest, ConvertsHeaderCorrectly)
    {
        std::vector<uint8_t> expected{};
        std::copy(mwl_bytes.begin(), mwl_bytes.begin() + 0x40, std::back_inserter(expected));

        auto actual = level->header->toBytes();

        if (expected != actual)
        {
            ADD_FAILURE() << "Re-converted header bytes differed from original header bytes:\n\n" <<
                getDifferenceString(expected, actual);
        }
    }

    TEST_P(ByteConversionTest, ConvertsPaletteDataCorrectly)
    {
        std::vector<uint8_t> expected{};
        const auto iterators = level->data_pointers->getPaletteDataIterators();
        // ignore the header since we're just zeroing it out cause we don't care about it
        std::copy(iterators.first + PaletteData::HEADER_SIZE,
            iterators.second, std::back_inserter(expected));

        const auto bytes = level->palette_data->toBytes();
        std::vector<uint8_t> actual;
        // ignore the header here too
        std::copy(bytes.begin() + PaletteData::HEADER_SIZE, bytes.end(),
            std::back_inserter(actual));

        if (expected != actual)
        {
            ADD_FAILURE() << "Re-converted palette data bytes differed from original palette data bytes:\n\n" <<
                getDifferenceString(expected, actual, PaletteData::HEADER_SIZE);
        }
    }

    TEST_P(ByteConversionTest, ConvertsExAnimationDataCorrectly)
    {
        std::vector<uint8_t> expected{};
        const auto iterators = level->data_pointers->getExAnimationIterators();
        std::copy(iterators.first, iterators.second, std::back_inserter(expected));

        auto actual = level->exanimation_data->toBytes();

        if (expected != actual)
        {
            ADD_FAILURE() << "Re-converted ExAnimation data bytes differed from original ExAnimation data bytes:\n\n" <<
                getDifferenceString(expected, actual);
        }
    }

    TEST_P(ByteConversionTest, ConvertsBypassInformationCorrectly)
    {
        std::vector<uint8_t> expected{};
        const auto iterators = level->data_pointers->getBypassInformationIterators();
        std::copy(iterators.first, iterators.second, std::back_inserter(expected));

        auto actual = level->bypass_information->toBytes();

        if (expected != actual)
        {
            ADD_FAILURE() << "Re-converted bypass information bytes differed from original bypass information bytes:\n\n" <<
                getDifferenceString(expected, actual);
        }
    }

    INSTANTIATE_TEST_CASE_P(MWLConversion, ByteConversionTest, ::testing::ValuesIn(test_mwls));
}
