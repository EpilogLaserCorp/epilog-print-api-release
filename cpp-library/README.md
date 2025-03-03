# **Epilog PrintAPI C++ Library**

This library calls the Epilog PrintAPI to generate a print file from an artwork svg file and a settings json file. That file can then be saved or sent to a laser system.

If you are new to the Epilog PrintAPI, consider starting off with the example svg and json files along with the example C++ program mentioned below.

## What's Included

### `CMakeLists.txt`

A CMake build file for the provided C++ program. See the "Building the Example" section below for details on how to build and run the cmake project.

### `epilog-print-api.h`

This is the file that provides the declarations for the Epilog PrintAPI and is linked to the `dll`/`so` files.

Note: `epilog-print-api.h` must not be modified.

### `example`

Contains the `cpp` and `h` files for the provided example C++ program to run the Epilog PrintAPI.

### `win-x64`

This folder contains the `dll` and `lib` files necessary to build for 64-bit Windows.

### `ubuntu-20.04`

The folder contains the `so` file necessary to build for Ubuntu 20.04 and higher.

## Building the Example

The included C++ example provides a good starting point for understanding how to use the Epilog PrintAPI Library.

To build the provided cmake project, run the commands below from the same directory as the `CMakeLists.txt` file.

```
cmake -S . -B ./build
cmake --build ./build/ --clean-first --config Release
cmake --install ./build/ --config Release --prefix "./build/install"
```

## Functions

Any C++ project that wants to use the Epilog PrintAPI, will first need to include the provided header.

```
#include <epilog-print-api.h>
```

Once that has been included, you will have access to the functions listed below.

### `api_version`

Provides a the current version of the Epilog PrintAPI.

- [return: `const char *`] A C-string representation of the current version.

### `prn_gen_new`

Provides a `PrnGen` Object. This object will be passed to all other `prn_gen_*` functions.

- [param: `const char *` `svg`] The svg artwork file in string format.
- [param: `const char *` `settings`] The settings json file in string format.
- [param: `EpilogMachine` `machine`] The type of machine that the print file will be generated for.
- [return: `PrnGen*`] A new `PrnGen` that can be passed to other functions to generate a print file.

Note: The object created by this function must be freed using the `free_prn_gen` function.

```
PrnGen* prnGen = prn_gen_new(svgFileStr, settingsJsonStr, machine);

// Do stuff here...

free_prn_gen(prnGen);
```

Note: It may be desirable to create a `unique_ptr` type that can automatically call `free_prn_gen` upon destruction.

```
struct PrnGenDeleterFunctor
{
    template<class T>
    void operator()(T* obj)
    {
        // Free the print file generator pointer.
        free_prn_gen(obj);
    }
};

std::unique_ptr<PrnGen, PrnGenDeleterFunctor> prnGen =  std::unique_ptr<PrnGen, PrnGenDeleterFunctor>(
    prn_gen_new(
        svgContents.data(),
        settingsJson.data(),
        machine
        )
    );

// Do stuff here...

// When prnGen goes out of scope, it will be freed automatically.
```

### `prn_gen_add_font_data`

Adds font file data to the print generator so that fonts can be parsed.

Important: Fonts located in the system font directories are loaded automatically.

Note: The font data is copied so that the memory can be freed immediately after calling this function without causing issues.

- [param: `PrnGen *` `gen`] A `PrnGen` object created by the `prn_gen_new` function.
- [param: `const char *` `data`] A pointer to the font file contents.
- [param: `uintptr_t` `data_length`] The number of bytes contained in the font file data.
- [return: `CApiError`] An error string which lets us know if the something went wrong. Note that `error` will be empty if this function succeeded.

### `prn_gen_run_chunk`

Runs a chunk of work on the PrnGen.

- [param: `PrnGen *` `gen`] A `PrnGen` object created by the `prn_gen_new` function.
- [return: `bool`] Whether or not there is more work to do.

Note: This function will return `false` if the `PrnGen` object was previously aborted or has already finished.

Note: If this function returns `false`, use the `prn_gen_get_result` function to get the generated print file (or error message).

### `prn_gen_run_until_complete`

Runs until all work is complete.

- [param: `PrnGen *` `gen`] A `PrnGen` object created by the `prn_gen_new` function.
- [return: `CApiResult`] The generated print file (or error message). This object must be free using the `free_c_api_result` function.

Note: This is equivalent to the following:

```
while (prn_gen_run_chunk(prnGen)) {}
return prn_gen_get_result(prnGen);
```

### `prn_gen_request_abort`

Requests that print file generation be aborted. All future calls to do work will fail.

### `prn_gen_run_until_complete`

Aborts the print file generation so that future calls to `prn_gen_run_chunk` will fail.

- [param: `PrnGen *` `gen`] A `PrnGen` object created by the `prn_gen_new` function.
- [return: `bool`] Whether or not the abort request was successful.

### `prn_gen_get_progress`

Gets the current progress of the print file generation.

- [param: `PrnGen *` `gen`] A `PrnGen` object created by the `prn_gen_new` function.
- [return: `CProgressReport`] Information about the current progress of the print file generation.

### `prn_gen_get_result`

Gets the final result of the print file generation.

- [param: `PrnGen *` `gen`] A `PrnGen` object created by the `prn_gen_new` function.
- [return: `CApiResult`] The generated print file (or error message). This object must be free using the `free_c_api_result` function.

Note: If print file generation has not completed, was aborted, or an error occurred, an error message will be returned instead of a print file.

### `prn_gen_is_complete`

Tests whether the print file generation has finished yet.

- [param: `PrnGen *` `gen`] A `PrnGen` object created by the `prn_gen_new` function.
- [return: `bool`] Whether or not the print file generation is complete.

### `prn_gen_has_error`

Tests whether the print file generation encountered an error.

- [param: `PrnGen *` `gen`] A `PrnGen` object created by the `prn_gen_new` function.
- [return: `bool`] Whether or not the print file generation failed due to an error.

### `prn_gen_was_aborted`

Tests whether the print file generation was aborted.

- [param: `PrnGen *` `gen`] A `PrnGen` object created by the `prn_gen_new` function.
- [return: `bool`] Whether or not the print file generation was aborted by the `prn_gen_request_abort` function.

### `prn_gen_error_string`

Returns the error message that has been provided by the print file generation. If no error has occurred, an empty string is returned.

- [param: `PrnGen *` `gen`] A `PrnGen` object created by the `prn_gen_new` function.
- [return: `const char *`] A C-string representation of the error that has occurred.

### `prn_gen_send_file`

Sends a generated print file to the specified IP address.

- [param: `const char *` `data`] A pointer to the generated print file.
- [param: `uintptr_t` `data_length`] The number of bytes contained in the generated output.
- [param: `const char *` `data`] A C-string representation of the IP address for the machine.
- [return: `bool`] Whether or not the file was successfully sent to the machine.

### `free_prn_gen`

Frees the memory of a `PrnGen` pointer.

- [param: `PrnGen *` `gen`] A `PrnGen` object created by the `prn_gen_new` function.
- [return: `bool`] Whether or not the memory was successfully freed.

### `free_cstring`

Frees the specified string memory.

- [param: `char *` `text`] A C-string pointer.
- [return: `bool`] Whether or not the memory was successfully freed.

Note: This function must be called on any C-string objects generated by an API function call.

### `free_carray`

Frees the specified character array memory.

- [param: `char *` `data`] A C-style array of characters pointer.
- [param: `uintptr_t` `data_length`] The length of the array array.
- [return: `bool`] Whether or not the memory was successfully freed.

Note: This function must be called on any C-style arrays generated by an API function call.

### `free_c_api_result`

Frees the string memory of a `CApiResult` pointer.

- [param: `CApiResult *` `result`] A `CApiResult` pointer.
- [return: `bool`] Whether or not the memory was successfully freed.

Note: This is equivalent to the following:

```
free_carray(result->result, result->result_size);
free_cstring(result->error);
```

### `free_c_api_error`

Frees the string memory of a `CApiError` pointer.

- [param: `CApiError *` `result`] A `CApiError` pointer.
- [return: `bool`] Whether or not the memory was successfully freed.

Note: This is equivalent to the following:

```
free_cstring(result->error);
```

### `free_c_progress_report`

Frees the string memory of a `CProgressReport` pointer.

- [param: `CProgressReport *` `result`] A `CProgressReport` pointer.
- [return: `bool`] Whether or not the memory was successfully freed.

Note: This is equivalent to the following:

```
free_cstring(result->stage_name);
free_cstring(result->stage_json);
```

## Types

### `EpilogMachine`

The type of machine that the print file will be generated for.

### `CProgressReport`

- [param: `ProgressType` `progress_type`] The type of progress report that this is and may indicate that an error has occurred or that print file generation is complete.
- [param: `const char *` `stage_name`] The name of the stage that is currently being worked on.
- [param: `const char *` `stage_json`] A json-formatted string that may contain additional information about the current stage.
- [param: `bool` `stage_has_progress`] Some stages only have one step and therefore do not report progress intermittently. As such, `stage_has_progress` for these stages will return `false`.
- [param: `float` `stage_progress`] A floating point value between `0.0` and `1.0` that indicates how far along the given stage is. For stages that do not report intermittent progress, this value will be `0.0`.
- [param: `uintptr_t` `stage_index`] The index of the current stage.
- [param: `uintptr_t` `stage_count`] The total number of stages that will be processed.
- [param: `float` `total_progress`] A floating point value between `0.0` and `1.0` that indicates how far along the print file generation is.

### `CApiResult`

- [param: `const char *` `result`] The result of the function called in the form of a character array.
- [param: `uintptr_t` `result_size`] The size of the result data.
- [param: `const char *` `error`] The error that occurred during the function call. If no error occurred, this will be an empty string.
- [param: `uintptr_t` `error_size`] The size of the error data/string.

### `CApiError`

- [param: `const char *` `error`] The error that occurred during the function call. If no error occurred, this will be an empty string.
- [param: `uintptr_t` `error_size`] The size of the error data/string.

### `ProgressType`

An enumeration with the following variants:
- [variant: `NotStarted`] Print file generation has not yet started. Call the `prn_gen_run_chunk` or `prn_gen_run_until_complete` functions to start print file generation.
- [variant: `InProgress`] Print file generation has started, but is not complete.
- [variant: `Finished`] Print file generation has finished successfully. Call the `prn_gen_get_result` function to get the final result.
- [variant: `Error`] En error occurred during print file generation. Call the `prn_gen_get_result` function to read the error message.
