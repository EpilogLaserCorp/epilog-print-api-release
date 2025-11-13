# Changelog

Note: This project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.3.0] 2025-11-12

### Added

- Now includes Windows Arm64, macOS Arm64, and macOS x64 builds for the executables and C++ library.
- Added `README.md` files in the svg/json example folders to provide a more in-depth understanding of how to use the examples.
- Added advanced job settings and advanced process settings svg/json examples to assist users in creating more complex jobs.
    - Advanced job features: custom autofocus plunger location, job alignment, SVG origin, and rotary.
    - Advanced process features: process filter, 3D engraving, stamp engraving, vector sorting.
    - Single process examples.
- A new dithering type `brighten` has been added which behaves similar to `standard`, but increases the overall brightness.

### Changed
- Updated settings in example json files to be more useful.
    - Settings have been tailored to mark on anodized aluminum.
    - Optimal engrave/mark quality is not guaranteed since the PrintAPI does not have knowledge of the laser system's characteristics.

### Fixed

- Fixed error for jobs that only have a thin horizontal or vertical line.
    - Previously, these jobs would return an error when trying to render the thumbnails.
    - This was only an issue when sending to machines that use the processes generator.
- Fixed output of hatch jobs with `isolate_shapes` enabled where in rare cases, the output would contain two shapes that overlap where there should be a gap instead.
- Fixed engrave operations which caused incorrect positioning and incorrect masking.
- Using an image as a mask no longer causes an error to be thrown complaining that it encountered an unexpected namespace of xlink.

## [1.2.1] 2025-07-28

### Added

- Custom autofocus plunger location is now available for the following machine types:
    - Fusion Pro 24 (`pro24`)
    - Fusion Pro 32 (`pro32`)
    - Fusion Pro 36 (`pro36`)
    - Fusion Pro 48 (`pro48`)
    - Fusion Edge 12 (`edge12`)
    - Fusion Edge 23 (`edge24`)
    - Fusion Edge 36 (`edge36`)
    - Fusion Maker 12 (`maker12`)
    - Fusion Maker 24 (`maker24`)
    - Fusion Maker 36 (`maker36`)
- More CSS `image-rendering` types are now supported.
    - The following options can now be used: `smooth`, `high-quality`, `pixelated`, `crisp-edges`.
    - In previous versions, only `optimizeSpeed` and `optimizeQuality` were valid. These options can still be used.
    - Note: `optimizeSpeed`, `pixelated`, and `crisp-edges` behave the same.
    - Note: `optimizeQuality` and `high-quality` behave the same.
    - Within a svg file, it would be used as such:
    ```svg
    <image style="image-rendering:high-quality" ... />
    ```

### Changed

- Updated the documentation for using the `epilog_print_api_runner` and `epilog_print_file_transmitter` through wasmtime to show how to enable network capabilities.
    - This is required to allow those executables to send print files to the laser engraver.

### Fixed

- Fixed bug where jobs with a `svg_origin` other than `none` (which is the default if not specified) might return an error.
- An error is returned when `grayscale_3d` is set as the `dithering` type for a G2 (`g2`) or Fusion Galvo G100 (`g100_4x4`, `g100_6x6`) machine since neither of these support 3D or stamp engravings.
- An error is returned when `plunger` is set as the `autofocus` type for Fusion Galvo G100 (`g100_4x4`, `g100_6x6`) machines since galvos do not have an autofocus plunger.
    - Some of the older machines have autofocus plungers, but those are not enabled through the print file like they are with the new machines that use the processes generator.
- Improved dithering quality. Some jobs had noticeable artifacts on the edges of the artwork. This is no longer the case.
- Fixed invalid LDP acknowledgements errors for the following machine types:
    - Helix 24 (`helix24`)
    - Mini 18 (`mini18`)
    - Mini 24 (`mini24`)
    - EXT 36 (`ext36`)
- Engrave processes with `image_mask` or `path_mask` operations now have the correct output.
- Frequency range for original Fusion models (see list below) had incorrect frequency bounds on engrave processes. Previously, the bounds incorrectly matched that of the legacy machines which take values in Hertz instead of percentages. The frequency range for these Fusion machines has been changed to be between `1` and `100` as stated in the documentation. This is the full list of machines affected:
    - Fusion 32 M2 (`fusion32_m2`)
    - Fusion 40 M2 (`fusion40_m2`)
    - Fusion 32 (`fusion32`)
    - Fusion 32 Fibermark (`fusion32_fibermark`)
    - Fusion 40 (`fusion40`)
- Fixed documentation for `job_alignment` which had incorrect formatting in the examples.
- The `job_alignment` `offset` parameter can now take string values with units like the documentation states.

## [1.2.0] 2025-03-03

### Added

- Print file generation and transmission for the following machine types:
    - Galvo G2 (`g2`)
    - Fusion 32 M2 (`fusion32_m2`)
    - Fusion 40 M2 (`fusion40_m2`)
    - Fusion 32 (`fusion32`)
    - Fusion 32 Fibermark (`fusion32_fibermark`)
    - Fusion 40 (`fusion40`)
    - Fibermark 24 (`fibermark24`)
    - Fibermark 24 S2 (`fibermark24_s2`)
    - Zing 16 (`zing16`)
    - Zing 24 (`zing24`)
    - Helix 24 (`helix24`)
    - Mini 18 (`mini18`)
    - Mini 24 (`mini24`)
    - EXT 36 (`ext36`)
- Added `grayscale_3d` as an option for engrave `dithering`.
    - This is equivalent to the 3D job mode seen in the Software Suite but can be set separately for each individual engrave process.
    - Unlike other dithering options, this does not convert the output to black and white pixels. Instead, the engrave output is kept as grayscale which causes the generated print file to be larger but also allows for depth-map engravings.
- Added `operations` as an option for engrave processes.
    - This is available for all machine types except the Galvo G2 (`g2`) since that machine does not have engrave processes.
    - This allows for image operations that occur before the dithering stage.
    - These can be combined to be the equivalent of Epilog's stamp job mode seen in the Software Suite but can be set separately for each individual engrave process..
- Added `laser_side` as an option for vector processes.
    - This is available for all machine types.
    - This enables kerf offset to account for the width of the laser, thus allowing for extremely accurate cutting.
- Added the `epilog_defaults` as an option for `generic_font_families`.
    - These font families are packaged with the PrintAPI and are always available for text artwork.
    - This ensures that artwork with text can always be rendered without errors by substituting a packaged font family if a font in the artwork wasn't specified or found.
    - Fonts: Baskervville, Inter Tight, Great Vibes, Kings, DM Mono.

### Changed

- Improved the isolate-shapes algorithm in hatch processes.
    - When `isolate_shapes` is `true`, shapes contained within shapes (ex. a circle contained inside of a ring), are combined and hatched together. This will decrease runtimes for that scenario.
    - There is no change in behavior when `isolate_shapes` is `false`.
- Improved performance of engrave processes by using multiple threads to render.
    - The increase in performance is dependent on the capabilities of the computer running the PrintAPI.

### Fixed

- Fixed isolate-shapes algorithm.
    - The isolate shapes algorithm would sometimes hatch insides the holes of shapes when that hole contained another shape.
- Fixed subtraction of white objects overlaying objects in vector processes.
    - Vector objects that are under objects with white fill subtract the area of the white fill to more closely match what is seen visually. However, the result of this subtraction sometimes produced vastly incorrect results with stray lines between different segments of the original path.

## [1.0.3] Initial Release - 2024-09-16

### Added

- Print file generation and transmission for the following machine types:
    - Fusion Pro 24 (`pro24`)
    - Fusion Pro 32 (`pro32`)
    - Fusion Pro 36 (`pro36`)
    - Fusion Pro 48 (`pro48`)
    - Fusion Edge 12 (`edge12`)
    - Fusion Edge 23 (`edge24`)
    - Fusion Edge 36 (`edge36`)
    - Fusion Maker 12 (`maker12`)
    - Fusion Maker 24 (`maker24`)
    - Fusion Maker 36 (`maker36`)
    - Fusion Galvo G100 (`g100_4x4`, `g100_6x6`)
- C++ Library
    - Windows, Linux
- Epilog PrintAPI Runner (Executable)
    - Windows, Linux, Wasi
- Epilog Print File Transmitter (Executable)
    - Windows, Linux, Wasi
- Schema file for reference
- Svg and json file examples
- Documentation for all components.