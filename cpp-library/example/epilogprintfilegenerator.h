#pragma once

#include <string>
#include <memory>

struct PrnGen;            // From epilog-print-api.h
enum class EpilogMachine; // From epilog-print-api.h

class EpilogPrintFileGenerator
{
    struct PrnGenDeleterFunctor
    {
        template <class T>
        void operator()(T *obj)
        {
            // Free the print file generator pointer.
            free_prn_gen(obj);
        }
    };

public:
    struct ApiResult
    {
        std::string result;
        std::string error;
        bool didSucceed;
    };

    struct ApiError
    {
        std::string error;
        bool didSucceed;
    };

    EpilogPrintFileGenerator(const std::string &svgContents,
                             const std::string &settingsJson,
                             EpilogMachine machine);

    ~EpilogPrintFileGenerator();

    ApiError add_font_data(const std::string &data);
    ApiResult generatePrintFile();

    static std::string apiVersion();

private:
    std::unique_ptr<PrnGen, PrnGenDeleterFunctor> m_prnGen;
};
