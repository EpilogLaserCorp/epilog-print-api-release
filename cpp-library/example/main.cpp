#include <iostream>
#include <fstream>
#include <sstream>

#include "epilogprintfilegenerator.h"
#include "epilog-print-api.h"

static std::pair<bool, std::string> readFile(const std::string &path)
{
    // Open the file.
    std::ifstream stream(path);
    if (!stream.is_open())
    {
        // Could not open!
        return std::make_pair(false, "");
    }

    // Read the file contents.
    std::ostringstream out;
    out << stream.rdbuf();
    return std::make_pair(true, out.str());
}

static bool writeToFile(const std::string &path, const std::string &data)
{
    // Open the file.
    std::ofstream stream(path, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!stream.is_open())
    {
        // Could not open!
        return false;
    }

    // Write the file contents.
    stream << data;
    return true;
}

int main(int argc, char *argv[])
{
    std::cout << "Using Epilog PrintAPI "
              << EpilogPrintFileGenerator::apiVersion()
              << std::endl;

    if (argc != 3)
    {
        std::cerr << "Program usage: epilog-print-api-example.exe <SVG_FILE> <SETTINGS_FILE>" << std::endl;
        std::cerr << "    <SVG_FILE>      The path to the svg artwork file.:" << std::endl;
        std::cerr << "    <SETTINGS_FILE> The path to the json settings file.:" << std::endl;
        return 0;
    }

    // Read the svg file.
    const auto svgFile = argv[1];
    const auto svgContents = readFile(svgFile);
    if (!svgContents.first)
    {
        std::cerr << "Unable to read contents of svg file: " << svgFile
                  << std::endl;
        return -1;
    }

    // Read the settings file.
    const auto settingsFile = argv[2];
    const auto settingsContents = readFile(settingsFile);
    if (!settingsContents.first)
    {
        std::cerr << "Unable to read contents of settings file: "
                  << settingsFile << std::endl;
        return -1;
    }

    // Create a print file generator for the specified svg and settings data.
    EpilogPrintFileGenerator gen(
        svgContents.second,
        settingsContents.second,
        EpilogMachine::Edge12 // The target machine type
    );

    // // Load extra fonts not contained in the system font directories.
    // const auto fontFileContents = readFile(path_to_file);
    // if (!fontFileContents.first)
    // {
    //     std::cerr << "Unable to read contents of font file: "
    //               << path_to_file << std::endl;
    //     return -1;
    // }
    // const auto fontDataResult = gen.add_font_data(fontFileContents.second);
    // if (!fontDataResult.didSucceed)
    // {
    //     std::cerr << "Unable to add font data for print file generation: "
    //               << fontDataResult.error << std::endl;
    //     return -1;
    // }

    // Generate the print file.
    std::cout << "Generating print file..." << std::endl;
    const auto printFile = gen.generatePrintFile();
    if (!printFile.didSucceed)
    {
        std::cerr << "Unable to generate print file: " << printFile.error
                  << std::endl;
        return -1;
    }
    std::cout << "Print file successfully generated with "
              << printFile.result.length() << " bytes." << std::endl;

    // Write the output to a file.
    const auto outputFile = "test.out.prn";
    const auto writeSuccess = writeToFile(outputFile, printFile.result);
    if (!writeSuccess)
    {
        std::cerr << "Unable to write output to file: " << outputFile
                  << std::endl;
        return -1;
    }
    std::cout << "Output successfully written to " << outputFile
              << std::endl;

    // // Send the output to a machine.
    // const auto ipAddress = "192.168.1.1";
    // const auto sendSuccess = prn_gen_send_file(
    //     printFile.result.data(),
    //     printFile.result.length(),
    //     ipAddress
    //     );
    // if(!sendSuccess)
    // {
    //     std::cerr << "Unable to send output to machine: " << ipAddress
    //               << std::endl;
    //     return -1;
    // }
    // std::cout << "Output successfully sent to " << ipAddress << std::endl;

    // Success!
    return 0;
}
