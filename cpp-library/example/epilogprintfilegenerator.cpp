#include "epilogprintfilegenerator.h"

// Epilog PrintApi header.
#include "epilog-print-api.h"

static std::string
fromCStringAndFree(const char *cstr)
{
    // Convert c string into c++ string.
    const auto result = std::string(cstr);

    // IMPORTANT: Free the memory of cstr.
    free_cstring(const_cast<char *>(cstr));

    // Return the result.
    return result;
}

static EpilogPrintFileGenerator::ApiResult
fromCGenerateResultAndFree(const CApiResult &cresult)
{
    // Convert c strings into c++ strings.
    const auto result = std::string(cresult.result, cresult.result_size);
    const auto error_string = std::string(cresult.error);

    // IMPORTANT: Free the memory of cresult.
    free_c_api_result(&cresult);

    // Return the result.
    return EpilogPrintFileGenerator::ApiResult{result, error_string, error_string.empty()};
}

EpilogPrintFileGenerator::EpilogPrintFileGenerator(std::string svgContents,
                                                   std::string settingsJson,
                                                   EpilogMachine machine)
{
    // Create a print file generator.
    m_prnGen = std::unique_ptr<PrnGen, PrnGenDeleterFunctor>(
        prn_gen_new(
            svgContents.data(),
            settingsJson.data(),
            machine));
}

EpilogPrintFileGenerator::~EpilogPrintFileGenerator()
{
}

EpilogPrintFileGenerator::ApiResult EpilogPrintFileGenerator::generatePrintFile()
{
    // Note: work could instead be done in chunks by repeatedly calling
    // prn_gen_run_chunk until the function returns false.

    // Note: If using prn_gen_run_chunk, progress can be checked by calling
    // prn_gen_get_progress. Make sure to call free_c_progress_report after
    // using the resulting struct.

    // Do all work and return the result.
    return fromCGenerateResultAndFree(prn_gen_run_until_complete(m_prnGen.get()));
}

std::string EpilogPrintFileGenerator::apiVersion()
{
    return fromCStringAndFree(api_version());
}
