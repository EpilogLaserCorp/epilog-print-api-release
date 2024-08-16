#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

constexpr static const double IN_TO_MM_F64 = 25.4;

constexpr static const double MM_TO_IN_F64 = (1.0 / IN_TO_MM_F64);

constexpr static const float IN_TO_MM = (float)IN_TO_MM_F64;

constexpr static const float MM_TO_IN = (float)MM_TO_IN_F64;

constexpr static const double SVG_IN_TO_PX_F64 = 96.;

constexpr static const double SVG_MM_TO_PX_F64 = (MM_TO_IN_F64 * SVG_IN_TO_PX_F64);

constexpr static const float SVG_IN_TO_PX = (float)SVG_IN_TO_PX_F64;

constexpr static const float SVG_MM_TO_PX = (float)SVG_MM_TO_PX_F64;

enum class EpilogMachine {
  Pro24,
  Pro32,
  Pro36,
  Pro48,
  Edge12,
  Edge24,
  Edge36,
  Maker12,
  Maker24,
  Maker36,
  G100_4x4,
  G100_6x6,
};

enum class ProgressType {
  NotStarted,
  InProgress,
  Finished,
  Error,
};

struct PrnGen;

struct CApiResult {
  const char *result;
  uintptr_t result_size;
  const char *error;
};

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

extern "C" {

/// Frees the memory from a c_char pointer that was created by this api.
///
/// # Safety
///
/// This is unsafe because it takes a pointer and deallocates it but we cannot
/// guarantee that the pointer is valid.
bool free_cstring(char *text);

/// Frees the memory from a c_char pointer that was created by this api.
///
/// # Safety
///
/// This is unsafe because it takes a pointer and deallocates it but we cannot
/// guarantee that the pointer is valid.
bool free_carray(char *data, uintptr_t data_length);

/// Frees the memory from a `CApiResult`` that was created by this api.
///
/// # Safety
///
/// This is unsafe because it calls free_cstring which is unsafe.
bool free_c_api_result(const CApiResult *result);

/// Frees the memory from a `CProgressReport`` that was created by this api.
///
/// # Safety
///
/// This is unsafe because it calls free_cstring which is unsafe.
bool free_c_progress_report(const CProgressReport *result);

/// Provides the current version of the Epilog PrintAPI.
///
/// # Safety
///
/// This is unsafe because it generates a pointer that must be manually freed later.
const char *api_version();

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
bool free_prn_gen(PrnGen *gen);

/// Requests that the specified `PrnGen` object aborts as soon as possible.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool prn_gen_request_abort(PrnGen *gen);

/// Does work for the specified `PrnGen` object.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool prn_gen_run_chunk(PrnGen *gen);

/// Does work for the specified `PrnGen` object until all work is complete or until an error has
/// occurred.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
CApiResult prn_gen_run_until_complete(PrnGen *gen);

/// Determines the progress of the specified `PrnGen` object.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
CProgressReport prn_gen_get_progress(const PrnGen *gen);

/// Determines the progress of the specified `PrnGen` object.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
CApiResult prn_gen_get_result(const PrnGen *gen);

/// Checks if the specified `PrnGen` object has been completed.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool prn_gen_is_complete(const PrnGen *gen);

/// Checks if the specified `PrnGen` object is in an error state.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool prn_gen_has_error(const PrnGen *gen);

/// Checks if the specified `PrnGen` object has been aborted.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool prn_gen_was_aborted(const PrnGen *gen);

/// Gets the current error string (if there is one) of the specified `PrnGen` object.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
const char *prn_gen_error_string(const PrnGen *gen);

/// Sends a print file to a laser engraver at the specified IP address.
///
/// ### Safety
///
/// This is unsafe because it takes a pointer but we cannot guarantee that the pointer is valid.
bool prn_gen_send_file(const char *data, uintptr_t data_length, const char *ip_address);

}  // extern "C"
