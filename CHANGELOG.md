# Changelog

Note: This project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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
    - Fusion Pro 24 (pro24)
    - Fusion Pro 32 (pro32)
    - Fusion Pro 36 (pro36)
    - Fusion Pro 48 (pro48)
    - Fusion Edge 12 (edge12)
    - Fusion Edge 23 (edge24)
    - Fusion Edge 36 (edge36)
    - Fusion Maker 12 (maker12)
    - Fusion Maker 24 (maker24)
    - Fusion Maker 36 (maker36)
    - Fusion Galvo G100 (g100_4x4, g100_6x6)
- C++ Library
    - Windows, Linux
- Epilog PrintAPI Runner (Executable)
    - Windows, Linux, Wasi
- Epilog Print File Transmitter (Executable)
    - Windows, Linux, Wasi
- Schema file for reference
- Svg and json file examples
- Documentation for all components.