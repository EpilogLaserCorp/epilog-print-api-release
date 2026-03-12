#ifndef epilog_print_api_h
#define epilog_print_api_h

#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

enum class ProgressType {
    NotStarted = 0,
    InProgress = 1,
    Finished = 2,
    Error = 3,
};

enum class EpilogMachine {
    Pro24 = 0,
    Pro32 = 1,
    Pro36 = 2,
    Pro48 = 3,
    Ascent12 = 26,
    Ascent24 = 27,
    Ascent36 = 28,
    Edge12 = 4,
    Edge24 = 5,
    Edge36 = 6,
    Maker12 = 7,
    Maker24 = 8,
    Maker36 = 9,
    G100_4x4 = 10,
    G100_6x6 = 11,
    G2 = 12,
    Fusion32M2 = 13,
    Fusion40M2 = 14,
    Fusion32 = 15,
    Fusion32Fibermark = 16,
    Fusion40 = 17,
    Fibermark24 = 18,
    Fibermark24S2 = 19,
    Zing16 = 20,
    Zing24 = 21,
    Helix24 = 22,
    Mini18 = 23,
    Mini24 = 24,
    Ext36 = 25,
};

enum class EpilogGeneratorType {
    Processes = 0,
    G2 = 1,
    Fusion = 2,
    Legacy = 3,
};

struct PrnGen;

struct CProgressReport {
    ProgressType progress_type;
    const char *stage_name;
    const char *stage_json;
    bool stage_has_progress;
    float stage_progress;
    uintptr_t stage_index;
    uintptr_t stage_count;
    float total_progress;
};

#if (!defined(DEFINE_WASM32) || defined(DEFINE_WASI))
struct CApiError {
    const char *error;
};
#endif

#if (!defined(DEFINE_WASM32) || defined(DEFINE_WASI))
struct CApiResult {
    const char *result;
    uintptr_t result_size;
    const char *error;
};
#endif

extern "C" {

/// Frees the memory from a `CProgressReport`` that was created by this api.
///
/// # Safety
///
/// This is unsafe because it calls free_cstring which is unsafe.
bool free_c_progress_report(const CProgressReport *result);

/// Creates a new print file generator.
///
/// # Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointers are valid.
PrnGen *prn_gen_new(const char *svg, const char *settings, EpilogMachine machine);

/// Frees memory for the specified `PrnGen` object.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool free_prn_gen(PrnGen *generator);

/// Does work for the specified `PrnGen` object.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
CApiError prn_gen_add_font_data(PrnGen *generator, const char *data, uintptr_t data_length);

/// Does work for the specified `PrnGen` object.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool prn_gen_run_chunk(PrnGen *generator);

/// Does work for the specified `PrnGen` object until all work is complete or until an error has
/// occurred.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
CApiResult prn_gen_run_until_complete(PrnGen *generator);

/// Requests that the specified `PrnGen` object aborts as soon as possible.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool prn_gen_request_abort(PrnGen *generator);

/// Determines the progress of the specified `PrnGen` object.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
CProgressReport prn_gen_get_progress(const PrnGen *generator);

/// Determines the progress of the specified `PrnGen` object.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
CApiResult prn_gen_get_result(const PrnGen *generator);

/// Checks if the specified `PrnGen` object has been completed.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool prn_gen_is_complete(const PrnGen *generator);

/// Checks if the specified `PrnGen` object is in an error state.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool prn_gen_has_error(const PrnGen *generator);

/// Checks if the specified `PrnGen` object has been aborted.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool prn_gen_was_aborted(const PrnGen *generator);

/// Gets the current error string (if there is one) of the specified `PrnGen` object.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
const char *prn_gen_error_string(const PrnGen *generator);

/// Sends a print file to a laser engraver at the specified IP address.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool prn_gen_send_file(EpilogMachine machine,
                       const char *data,
                       uintptr_t data_length,
                       const char *ip_address);

/// Converts machine type to generator type.
EpilogGeneratorType generator_type_from_machine_c(EpilogMachine machine);

#if (!defined(DEFINE_WASM32) || defined(DEFINE_WASI))
/// Frees the memory from a `CApiResult`` that was created by this api.
///
/// # Safety
///
/// This is unsafe because it calls free_cstring which is unsafe.
bool free_c_api_result(const CApiResult *result);
#endif

#if (!defined(DEFINE_WASM32) || defined(DEFINE_WASI))
/// Frees the memory from a `CApiError`` that was created by this api.
///
/// # Safety
///
/// This is unsafe because it calls free_cstring which is unsafe.
bool free_c_api_error(const CApiError *result);
#endif

#if (!defined(DEFINE_WASM32) || defined(DEFINE_WASI))
/// Frees the memory from a c_char pointer that was created by this api.
///
/// # Safety
///
/// This is unsafe because it takes a pointer and deallocates it but we cannot
/// guarantee that the pointer is valid.
bool free_cstring(char *text);
#endif

#if ((!defined(DEFINE_WASM32) || defined(DEFINE_WASI)) && (!defined(DEFINE_WASM32) || defined(DEFINE_WASI)))
/// Frees the memory from a c_char pointer that was created by this api.
///
/// # Safety
///
/// This is unsafe because it takes a pointer and deallocates it but we cannot
/// guarantee that the pointer is valid.
bool free_carray(char *data,
                 uintptr_t data_length);
#endif

#if ((!defined(DEFINE_WASM32) || defined(DEFINE_WASI)) && (!defined(DEFINE_WASM32) || defined(DEFINE_WASI)))
/// Provides the current version of the Epilog PrintAPI.
///
/// # Safety
///
/// This is unsafe because it generates a pointer that must be manually freed later.
const char *api_version();
#endif

}  // extern "C"

#endif  // epilog_print_api_h
