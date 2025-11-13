# **Epilog PrintAPI Runner**

This executable calls the Epilog PrintAPI to generate a print file from an artwork svg file and a settings json file. That file can then be saved or sent to a laser system.

## Usage

**Windows**

```
epilog_print_api_runner.exe --machine-type edge12 --input-svg example.svg --input-settings example.json
```

Note: The executable is contained in the `win-x64` and `win-arm64` folders.

**Linux**

```
./epilog_print_api_runner --machine-type edge12 --input-svg example.svg --input-settings example.json
```

Note: The executable is contained in the `linux-x64` folder.

**macOS**

```
./epilog_print_api_runner --machine-type edge12 --input-svg example.svg --input-settings example.json
```

Note: The executable is contained in the `macos-x64` and `macos-arm64` folders.

**Wasmtime**

```
wasmtime --dir=. --wasi inherit-network=true epilog_print_api_runner.wasi.wasm --machine-type edge12 --input-svg example.svg --input-settings example.json
```

Note: `--dir` gives access to local file resources and `--wasi inherit-network=true` gives access to network resources. See <https://docs.wasmtime.dev/cli-options.html#additional-options>

Note: The binary is contained in the `wasi` folder.

## Arguments

### `-i, --input-svg <INPUT_SVG>`

The input artwork svg file.

### `-s, --input-settings <INPUT_SETTINGS>`

The input settings json file.

See the [Json Settings Document](../JSON_SETTINGS.md) on how to form the settings json file.

### `-m, --machine-type <MACHINE_TYPE>` (Optional)

The target machine type that the output is being generated for.

The available `machine-type` values are:
- `pro24`
- `pro32`
- `pro36`
- `pro48`
- `edge12` [default]
- `edge24`
- `edge36`
- `maker12`
- `maker24`
- `maker36`
- `g100_4x4`
- `g100_6x6`
- `g2`
- `fusion32_m2`
- `fusion40_m2`
- `fusion32`
- `fusion32_fibermark`
- `fusion40`
- `fibermark24`
- `fibermark24_s2`
- `zing16`
- `zing24`
- `helix24`
- `mini18`
- `mini24`
- `ext36`

### `-j, --json-output` (Optional)

If this option is specified, output will be generated in json format instead of as a print file. This can be useful for debugging.

Note: This cannot be specified in conjunction with the `--ip-addr`/`a` option.

### `-a, --ip-addr <IP_ADDR>` (Optional)

The IP address of the engraver to send the generated print file to.

### `-o, --output-path <OUTPUT_PATH>` (Optional)

A file to store the resulting generated data.

If the file does not exist, one will be created. However, the directory that will contain the output file must exist. The output file will always have a `'.prn` file extension (or `.json` if the `--json-output` option is specified).

If this option is not specified, an output file with the same base name as the input svg file will be written to in the working directory of the `epilog_print_api_runner` executable.

### `-f, --font-paths <FONT_PATHS>` (Optional)
The location of any addition font files or directories.

This can be a comma-separated list or you can provide the argument multiple times. For example, '--font-paths path1,path2' OR '--font-paths path1 --font-paths path2'.

### `-r, --font-paths-recursive` (Optional)
Font directories should be scanned recursively (can only be specified if any of <FONT_PATHS> is a directory)

### `-e, --font-extensions <FONT_EXTENSIONS>` (Optional)
The file extensions allowed when finding font files. If not specified, 'ttf' and 'otf' will be allowed.

This can be a comma-separated list or you can provide the argument multiple times. For example, '--font-extensions ttf,otf' OR '--font-extensions ttf --font-extensions otf'.

### `--to-stdout`

If this option is specified, the generated output will be sent to stdout.

### `-h, --help`

Prints helpful information about using the `epilog_print_api_runner` executable to stdout.

### `-V, --version`

Prints the Epilog PrintAPI version to sdtout.
