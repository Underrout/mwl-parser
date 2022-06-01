// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

#include "../mwl_parser/Header.h"
#include "../mwl_parser/DataPointers.h"

using MWLParser::Header;
using MWLParser::DataPointers;

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

void showRange(const std::string data_area_name, MWLParser::DataIteratorPair pair)
{
    std::cout << std::endl << std::endl << "===============================================" << std::endl << std::endl
        << "> " << data_area_name << std::endl << std::endl;
    size_t i = 0;
    while (pair.first != pair.second)
    {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << unsigned(*pair.first++) << ' ';
        if (pair.first != pair.second && i == 15)
        {
            i = 0;
            std::cout << std::endl;
        }
        else
        {
            ++i;
        }
    }
}

int main()
{
    const std::vector<uint8_t> mwl_bytes = readFile("test_mwls\\level 105.mwl");

    Header header = Header(mwl_bytes);
    std::cout << header.getLunarMagicVersion() << std::endl << header.getCommentField() << std::endl;

    DataPointers data_pointers = DataPointers(mwl_bytes);

    showRange("Level Information", data_pointers.getLevelInformationIterators());
    showRange("Layer 1 Data", data_pointers.getLayer1DataIterators());
    showRange("Layer 2 Data", data_pointers.getLayer2DataIterators());
    showRange("Sprite Data", data_pointers.getSpriteDataIterators());
    showRange("Palette Data", data_pointers.getPaletteDataIterators());
    showRange("Secondary Entrances", data_pointers.getSecondaryEntrancesIterators());
    showRange("ExAnimation", data_pointers.getExAnimationIterators());
    showRange("Bypass Information", data_pointers.getBypassInformationIterators());
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
