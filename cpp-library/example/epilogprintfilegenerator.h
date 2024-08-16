#pragma once

#include <string>
#include <memory>

struct PrnGen; // From epilog-print-api.h
enum class EpilogMachine; // From epilog-print-api.h

class EpilogPrintFileGenerator
{
    struct PrnGenDeleterFunctor
    {
        template<class T>
        void operator()(T* obj)
        {
            // Free the print file generator pointer.
            free_prn_gen(obj);
        }
    };

public:
    struct ApiResult {
        std::string result;
        std::string errorString;
        bool isValid;
    };

    EpilogPrintFileGenerator(std::string svgContents,
                             std::string settingsJson,
                             EpilogMachine machine);

    ~EpilogPrintFileGenerator();

    ApiResult generatePrintFile();

    static std::string apiVersion();

private:
    std::unique_ptr<PrnGen, PrnGenDeleterFunctor> m_prnGen;
};
