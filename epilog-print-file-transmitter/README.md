# **Epilog Print File Transmitter**

This executable sends existing print files to a laser system.

## Usage

**Windows**

```
epilog_print_file_transmitter.exe --machine-type edge12 --input-prn example.prn --ip-addr "192.168.1.1"
```

Note: The executable is contained in the `win-x64` and `win-arm64` folders.

**Linux**

```
./epilog_print_file_transmitter --machine-type edge12 --input-prn example.prn --ip-addr "192.168.1.1"
```

Note: The executable is contained in the `linux-x64` folder.

**macOS**

```
./epilog_print_file_transmitter --machine-type edge12 --input-prn example.prn --ip-addr "192.168.1.1"
```

Note: The executable is contained in the `macos-x64` and `macos-arm64` folders.

**Wasmtime**

```
wasmtime --dir=. --wasi inherit-network=true epilog_print_file_transmitter.wasi.wasm --machine-type edge12 --input-prn example.prn --ip-addr "192.168.1.1"
```

Note: `--dir` gives access to local file resources and `--wasi inherit-network=true` gives access to network resources. See <https://docs.wasmtime.dev/cli-options.html#additional-options>

Note: The binary is contained in the `wasi` folder.

## Arguments

### `-i, --input-prn <INPUT_PRN>`

The input print file or a directory containing print files.

### `-a, --ip-addr <IP_ADDR>`

The IP address of the engraver to send the generated print file to.

### `-r, --recursive` (Optional)

If specified, the directory will be searched recursively for print files with a `.prn` file extension.

Only valid if `INPUT_PRN` is a directory.

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

### `-h, --help`

Prints helpful information about using the `epilog_print_file_transmitter` executable to stdout.

### `-V, --version`

Prints the Epilog PrintAPI version to sdtout.
