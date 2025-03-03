# **Epilog PrintAPI Settings**

This document details everything you need to know about creating json settings files.

If you are new to the Epilog PrintAPI, consider starting off with the example svg and json files.

# Generators (IMPORTANT)

Before discussing the structure of the settings that can be passed into the Epilog PrintAPI, it must be known that different machines have different capabilities. As such, some settings are only applicable to certain machines. Similarly, machines manufactured around the same time will have similar constraints with each other and therefore a similar set of settings.

All of that is to say that the different machines can be broken up into four different groups, each with their own settings. These groups will be known as **generators** because the API will generate the output according to a different set of rules.

The four generators and their associated machines are as follows:
1. Processes
    - `pro24`
    - `pro32`
    - `pro36`
    - `pro48`
    - `edge12`
    - `edge24`
    - `edge36`
    - `maker12`
    - `maker24`
    - `maker36`
    - `g100_4x4`
    - `g100_6x6`
2. G2
    - `g2`
3. Fusion (the original Fusion series, not the current one)
    - `fusion32_m2`
    - `fusion40_m2`
    - `fusion32`
    - `fusion32_fibermark`
    - `fusion40`
4. Legacy
    - `fibermark24`
    - `fibermark24_s2`
    - `zing16`
    - `zing24`
    - `helix24`
    - `mini18`
    - `mini24`
    - `ext36`

Because most settings are the same or similar between different generators, only a single list of settings will be provided below. The difference in those settings across each generator will be denoted in a section that looks like the example below:

**[Processes Generator]**

An explanation of how this is implemented for the Processes generator or for how the implementation differs from that of other generators.

# Laser Types

It will be important when setting process `laser_type` parameters to know which machines support which laser types.

The following machine types can only have `co2` lasers:
- edge24
- edge36
- maker12
- maker24
- maker36
- fusion32
- fusion40
- zing16
- zing24
- helix24
- mini18
- mini24
- ext36

The following machine types can only have `fiber` lasers:
- g100_4x4
- g100_6x6
- g2
- fusion32_fibermark
- fibermark24
- fibermark24_s2

The following machine types have either laser type, but not both:
- edg12

The following machine types can have either or both laser types (dual source):
- pro24
- pro32
- pro36
- pro48
- fusion32_m2
- fusion40_m2

# Length Units
By default, all settings parameters are assumed to be provided in `mm`. However, other units can be specified by appending the unit string to end of the numeric value. The following options are available.
- `mm` - The default unit.
- `cm` - There are 10 millimeters in a centimeter (cm).
- `in` - There are 25.4 millimeters in an inch (in).
- `q`  - There are 4 quarter millimeters (q) in a millimeter.
- `pc` - There are 6 PostScript picas (pc) in an inch.
- `pt` - There are 72 points (pt) in an inch.
- `px` - There are 96 pixels (px) in an inch.

In the following examples, the focus thickness is assumed to be in `mm`:
```
"thickness": 25.4
```
```
"thickness": "25.4"
```

This could be equivalently described as such:
```
"thickness": "1in"
```

# Stamp and 3D Modes

Unlike the Software Suite, the PrintAPI allows users to have stamp and 3D enabled for each individual engrave process. This is done by adjusting the `dithering` and `operations` options.

### 3D Mode

3D engravings are enabled simply by settings the `dithering` parameter to `grayscale_3d`. This option dynamically adjusts the power according to the grayscale value of the engrave process rendering. This is in contrast to the other dithering types that convert the rendered image into discrete on/off values.

### Stamp Mode

There is no direct method of generating stamp processes as seen in Epilog's Software Suite. Instead, a combination of engrave operations can be used to create the same effect. This allows for a more flexible work flow.

All stamp processes also need to be 3D processes. As such, set the `dithering` parameter to `grayscale_3d`.

Stamp mode is enabled by using the following operations in order:
- `invert` - The inversion allows us to define the stamp area as white (i.e. a gray value of `1.0`).
- `threshold` - Converts the artwork into a monochrome image.
- `dilate` - This performs any desired widening of the stamp artwork. This can be omitted if widening is not needed.
- `distance_transform` - Creates the stamp ramp. The ramp width is defined by the `distance` value.
- `map` - The stamp profile can be adjusted by adding values to the `value_map`. If a simple ramp is all that is required, this can be omitted.
- `invert` - This inverts the artwork back to black being what is engraved since that's how engrave processes operate.
- `path_mask` - The `mask` parameter defines the stamp fence.
    - The `mask_operations` parameter can be used to adjust the fence. For example, a `dilate` operation would be used to expand the fence in the same way that Epilog's "fence margins" setting does.
    - Since `path_mask` cannot capture svg image elements, it may be desirable to use `image_mask` instead. However, that will require that the `invert` be performed first. See the documentation on `image_mask` for more details.

### Image Operations

Image operations can be performed on engrave processes for purposes other than creating stamp jobs as well. See the documentation for the `operations` parameter for more information on how to use each operation.

# Settings Structure

The settings are defined as a json tree with the properties seen below.

### `job_name`

The name of the job as it will show up on the machine. It must be between `1` and `255` characters.

### `firmware_version`

The firmware version of the machine that it is intended for. 

Note: No error is currently shown if the versions do not match.

**[Processes Generator Only]**

This setting is only applicable to the Processes generator and no others.

### `svg_origin` (Optional)

This property defines the origin point of the artwork. The following options are available:
- `zero` [default] - The origin is placed at the zero position of the svg viewbox.
- `half_table_size` - [`g100` only] The origin is placed at half the table size over from the top-left position of the svg viewbox.
- `view_rect_top_left` - The origin is placed at the top-left position of the svg viewbox.
- `view_rect_center` - The origin is placed at the center of the svg viewbox.
- `custom` - The origin is placed at a custom position relative to the zero location of the svg viewbox. An `x` and `y` value must be provided and follows the length unit options described above.

Examples:
```
"svg_origin": {
    "_of": "zero"
}
```
```
"svg_origin": {
    "_of": "custom",
    "x": "1in",
    "y": "0.5in",
}
```

### `generic_font_families` (Optional)

This property defines the generic font families (serif, sans-serif, cursive, fantasy, or monospace).

Note: If the artwork has text nodes that reference a font that cannot be found, or that do not specify a font at all, the generic serif font will be used (if possible).

The following options are available:
- `none` - There are no generic font families. All text must specify a valid font family.
- `epilog_defaults` [default] - The generic font families will be set to the epilog defaults. These fonts are embedded into the PrintAPI and therefore always available. These can also be manually specified using the `single_named` and `named` variants. See below for the list of default font families.
- `system_defaults` [default] - The generic font families will be set to the defaults for the current operating system. See below for the list of default font families.
- `single_named` - All generic font families are set to a single provided family.
- `named` - Each type of generic font is specified. A `serif_family`, `sans_serif_family`, `cursive_family`, `fantasy_family`, and `monospace_family` value must be provided.

Examples:
```
"generic_font_families": {
    "_of": "none"
}
```
```
"generic_font_families": {
    "_of": "named",
    "serif_family": "Times New Roman",
    "sans_serif_family": "Arial",
    "cursive_family": "Comic Sans MS",
    "fantasy_family": "Impact",
    "monospace_family": "Courier New",
}
```

Epilog Defaults:
- Serif - Baskervville 
- Sans serif - Inter Tight
- Cursive - Great Vibes
- Fantasy - Kings
- Monospace - DM Mono

Windows Defaults:
- Serif - Times New Roman
- Sans serif - Arial
- Cursive - Comic Sans MS
- Fantasy - Impact
- Monospace - Courier New

Linux Defaults:
- Serif - DejaVu Serif
- Sans serif - DejaVu Sans
- Cursive - DejaVu Sans
- Fantasy - DejaVu Sans
- Monospace - DejaVu Sans Mono

### `copies`

The number of times a job is repeated. The value must be greater than or equal to `1`.

### `autofocus`

Specifies how the machine will handle auto-focusing.

**[Processes Generator]**

The following options are available:
- `off` - No autofocus will occur.
- `plunger` - The plunger attached to the carriage will be used to determine the thickness of the material.
- `thickness` - A `thickness` value must be provided in each process and will be used to set the table to the specified height.

**[G2, Fusion, and Legacy Generators]**

The following options are available:
- `false` - No autofocus will occur.
- `true` - A `focus` value must be provided in each process and will be used to set the table to the specified height.

### `job_alignment` (Optional)

If specified, determines the reference point for centering jobs. There are 3 fields that must be specified.
- `enabled` - Set this to `true` to enable centering. Setting this to `false` is the same as not providing the `job_alignment` setting.
- `centering_point` - Can be one of the following options:
  - `custom` - This one differs from the others in that it references the top-left position of the svg viewbox instead of being relative to some point in the artwork bounds. As such, the `offset` parameter below defines the reference point of the artwork relative to the svg origin point.
  - `center_center` - Use the center of the artwork bounds as the reference point.
  - `left_center` - Use the center of the left edge of the artwork bounds as the reference point.
  - `right_center` - Use the center of the right edge of the artwork bounds as the reference point.
  - `center_top` - Use the center of the top edge of the artwork bounds as the reference point.
  - `center_bottom` - Use the center of the bottom edge of the artwork bounds as the reference point.
  - `top_left` - Use the top-left corner of the artwork bounds as the reference point.
  - `top_right` - Use the top-right corner of the artwork bounds as the reference point.
  - `bottom_left` - Use the bottom-left corner of the artwork bounds as the reference point.
  - `bottom_right` - Use the bottom-right corner of the artwork bounds as the reference point.
- `offset` (Optional) - Provides an offset from the position specified by the `centering_point` parameter. An `x` and `y` value must be provided and follows the length unit options described above.

Examples:
```
"job_alignment": {
    "enabled": "true",
    "centering_point": {
        "_of": "center_center"
    }
}
```
```
"job_alignment": {
    "enabled": "true",
    "centering_point": {
        "_of": "custom",
        "offset": {
            "x": "1in",
            "y": "0.5in"
        }
    }
}
```

**[Processes, Fusion, and Legacy Generators Only]**

This setting is not available for the G2 generator.

### `rotary` (Optional)

If specified, tells the engraver what kind of rotary the job is designed to be used with and has the following options:
- `none` - This is the same as not specifying the `rotary` option. In this case, the job is designed to not be used with any rotary.
- `rim` - The job is designed for a rim-style rotary.
- `three_jaw` - The job is designed for a three-jaw rotary. A `diameter` value must be provided and follows the length unit options described above.

Examples:
```
"rotary": {
    "_of_": "rim"
}
```
```
"rotary": {
    "_of_": "three_jaw",
    "diameter": "1.5in"
}
```

An error will be thrown if the specified machine does not support the provided rotary type.

**[Processes and Fusion Generators Only]**

This setting is not available for the G2 and Legacy generators.

### `engrave_resolution`

The resolution for which the engrave data will rendered and output as. Lower values indicate lower quality but faster engrave times and vice versa for higher values.

for all Zing machines (`zing16` and `zing24`), the following values are available:
- `100`
- `200`
- `250`
- `400`
- `500`
- `1000`

For all non-Zing machines (Legacy and Fusion generators only), the following values are available:
- `75`
- `150`
- `200`
- `300`
- `400`
- `600`
- `1200`

**[Fusion and Legacy Generators Only]**

This setting is not available for the G2 generator because the `g2` machine does not support engraving. It is not applicable to the Processes generator because newer machines have a per-process resolution for greater control.

### `engrave_direction`

The direction in which the engraving will happen.

This can be set to `down` for top-down engraving or `up` for bottom-up engraving.

**[Fusion and Legacy Generators Only]**

This setting is not available for the G2 generator because the `g2` machine does not support engraving. It is not applicable to the Processes generator because newer machines have a per-process resolution for greater control.

**[Fusion and Legacy Generators Only]**

This setting is not available for the G2 generator because the `g2` machine does not support engraving. It is not applicable to the Processes generator because newer machines have a per-process resolution for greater control.

### `vector_grid`

Whether or not a vector grid is installed for this job.

This setting is necessary for the Fusion and Fusion M2 machines because they have a vector grid attachment that sits on top of the flatbed. The result is that the table has to move down by about 3 inches to accommodate the vector grid when it is installed.

**[Fusion Generator Only]**

This setting is only available for the Fusion generator because no other machine has as vector grid that sits on top of the flatbed.

### `vector_speed_half`

Whether or not the vector speed should be halved to get greater control of the speed. Enabling this gives 0.5% increments of speed below 50% instead 1% increments.

**[Fusion Generator Only]**

This setting is only available for the Fusion generator. Newer machines allow for decimal precision of speed.

### `vector_power_comp`

Whether or not the power compensation feature should be used. When this is on, power is decreased as the carriage slows down at the start and stop as well as around corners.

**[Fusion Generator Only]**

This setting is only available for the Fusion generator. Newer machines always have this feature enabled.

### `processes`

Describes the list of processes to be used. Each process type has a unique set of settings.

The following three options are available:
- `Engrave` **[not available for the G2 generator]**
- `Vector`
- `Hatch`

Example:
```
"processes": [
    {
        "_of": "engrave_process"
        ...
    },
    {
        "_of": "vector_process"
        ...
    },
    {
        "_of": "hatch_process"
        ...
    }
]
```

Each process type and their settings are described in more detail below.

There must be at least one enabled process.

# Artwork Filters

Each process contains a filter. These filters determine which elements of the artwork that will be associated with that process. It's important to note that no element of the artwork can belong to more than one process and an error will thrown if filters are set up in such a way to cause that.

The Epilog PrintAPI supports four different filter types for assigning graphical elements to processes:
- `Color`
- `Stroke`
- `Attribute`
- `All`

### `Color Filter`
The color filter will select elements of the given input color or colors in valid [CSS colors](https://developer.mozilla.org/en-US/docs/Web/CSS/color), additional details [here](https://7thsigil.github.io/css-color-parser-rs/css_color_parser/index.html). Multiple colors can be specified in a list. For example:
```
"filter": {
    "_of": "color_filter",
    "colors": [
        "red",
        "black",
        "#AABBCC"
    ]
}
```
**NOTE:** Color filters are currently only able to select stroked elements for vector operations. Stroked elements can be filtered for either engrave or vector processes while filled elements can only be filtered for engrave processes.

### `Stroke Filter`
The stroke filter allows the selection of element by stroke width via different operators. The available operators are:
- `<` (Less than)
- `<=` (Less than or equal)
- `>` (Greater than)
- `>=` (Greater than or equal)
- `==` (Equal)
- `!=` (Not Equal)

Note: The `width` can use the length unit options described above.

A stroke filter is specified by the width and the operation like so:
```
"filter": {
    "_of": stroke_filter",
    "width": "1mm",
    "op": "<"
}
```
This creates a stroke filter selecting any stroked items less than 1mm in width.

### `Attribute filter`
The attribute filter uses the `id` attribute within the svg along with stroke, fill, or both to select the object. For example:
```
"filter": {
    "_of": "attribute_filter",
    "attributes": [
        {
            "id": "path851",
            "attribute": "fill"
        }
    ]
}
```
would select the filled part of the object in the svg with `id` of `path851`. The same `id` can be used in different processes so long as different attributes are used, that is:
```
"processes": [
    {
        "_of": "engrave_process",
        "name": "Engrave Example",
        "filter": {
            "_of": "attribute_filter",
            "attributes": [
                {
                    "id": "path851",
                    "attribute": "fill"
                }
            ]
        },
        ...
    },
    {
        "_of": "vector_process",
        "name": "Vector Example",
        "filter": {
            "_of": "attribute_filter",
            "attributes": [
                {
                    "id": "path851",
                    "attribute": "stroke"
                }
            ]
        },
        ...
    }
]
```
but selecting the same attribute (stroke for example) in both processes would result in an error.

### `All filter`
The all filter selects all remaining elements for a given process. If there are additional processes after a process that has used the all filter there will be no graphical elements available for those processes to match against. The filter is instantiated like so:
```
"filter":{
    "_of": "all_filter"
},
```

# Engrave Process

The engrave process converts the input graphical information into pixels which are then engraved along the width of the engraving machine.

### `name`

The name of the process as it will be seen on the UI of the engraver.

### `enabled` (Optional)

If this is `true`, then output will be generated for this process. If it is `false`, this process will be ignored. 

This value can be set to `true` [default] or `false`.

Note: The artwork is still filtered even if this value is `false`.

### `filter`

The artwork filter as described above.

### `cycles`

The number of times the output for this process is repeated.

The value must be greater than or equal to `1`.

### `resolution`

The resolution for which the engrave data will rendered and output as. Lower values indicate lower quality but faster engrave times and vice versa for higher values.

This value must be between `50` and `1200`.

**[Processes Generator Only]**

This setting is only applicable to the Processes generator and no others. The Fusion and Legacy generators use a global setting called `engrave_resolution`.

### `engrave_direction`

The direction in which the engraving will happen.

This can be set to `down` for top-down engraving or `up` for bottom-up engraving.

**[Processes Generator Only]**

This setting is only applicable to the Processes generator and no others. The Fusion and Legacy generators use a global setting called `engrave_direction`.

### `dithering`

The algorithm used to dither the artwork for the process into the binary (monochromatic) data used by the engraver.

The following options are available:
- `none` - No dithering is applied.
- `standard` - The standard Epilog dithering pattern is applied.
- `floyd_steinberg` - The [Floyd-Steinberg](https://en.wikipedia.org/wiki/Floyd%E2%80%93Steinberg_dithering) dithering algorithm is applied.
- `jarvis` - The [Jarvis (a.k.a. Minimized Average Error)](https://en.wikipedia.org/wiki/Error_diffusion#minimized_average_error) dithering algorithm is applied.
- `stucki` - The [Stucki](https://tannerhelland.com/2012/12/28/dithering-eleven-algorithms-source-code.html) dithering algorithm is applied.
- `bayer` - A [Bayer](https://en.wikipedia.org/wiki/Ordered_dithering) dithering algorithm is applied.
- `grayscale_3d` - This acts in the same way as Epilog's 3D mode where instead of dithering an image into discrete on/off states, the power is dynamically adjusted according to the grayscale value while engraving.

**[Processes, Fusion, and Legacy Generators Only]**

This setting is not applicable to the G2 generator because it does not have engrave processes.

### `operations`

A list of image operations that can be applied to the engrave process after rendering but before dithering.

Operations can be applied to two different image types: grayscale and monochrome. The initial engrave process rendering is considered to be a grayscale image. Some operations are only valid on grayscale images and some are only valid on monochrome images. Some operations also output a different type than the input.

Grayscale float values of `0.0` correspond to black and `1.0` corresponds to white.

Important note: When engraving, black pixels are the ones that get engraved and white pixels do not. However, image operations tend to operate inversely. As such, it may be helpful to start and end with inverting operations.

Below is a list of the available operations and their associated parameters.

#### `threshold`

Converts a grayscale image to a monochrome image by applying a threshold value.

Pre-Conditions:
- The current image must be grayscale. If a threshold has already been applied, and thus the image is monochrome, this operation will fail.

Parameters:
- `value` - A Float value between `0.0` and `1.0`. All pixel values greater than `value` are mapped to `1.0` and all other values are mapped to `0.0`.

Output:
- This operation produces a monochrome image.

Example:
```json
{
    "_of": "threshold",
    "value": 0.5
}
```

#### `invert`

Inverts each pixel value such that white becomes black and vise versa.

This operation can be performed on any image and the output image is the same type as the input image.

Example:
```json
{
    "_of": "invert",
}
```

#### `dilate`

Dilates the current engrave image if `distance` is positive, or erodes the image if `distance` is negative.

When implementing Epilog's stamp mode, this transform creates the stamp widening. See the stamp mode section above for more details.

Pre-Conditions:
- The current image must be monochrome or this operation will fail.

Parameters:
- `distance` - The distance in which to dilate or erode the image. This value follows the length unit options described above.

Output:
- This operation produces a monochrome image.

Examples:

This example dilates by a distance of 2.54 mm (0.1 inches).
```json
{
    "_of": "dilate",
    "distance": 2.54
}
```

This example erodes by a distance of 0.1 inches (2.54 mm).
```json
{
    "_of": "dilate",
    "distance": "-0.1in"
}
```

#### `distance_transform`

Performs a distance transform of a monochrome image such that any white pixels become black and then a linear gradient to white is generated outwardly from every formerly-white pixel over the specified `distance`.

When implementing Epilog's stamp mode, this transform creates the stamp ramp. See the stamp mode section above for more details.

Pre-Conditions:
- The current image must be monochrome or this operation will fail.

Parameters:
- `distance` - The distance over which the gradient transitions from black to white. This value follows the length unit options described above.

Output:
- This operation produces a grayscale image.

Example:
```json
{
    "_of": "distance_transform",
    "distance": "0.05in"
}
```

#### `path_mask`

Applies a mask to the image such that only the parts of the input image contained in the mask remain in the output image. The objects contained by the `mask` filter are drawn white onto a black background which means that no `invert` or `threshold` operation is necessary for normal masking.

When implementing Epilog's stamp mode, this defines the stamp fence. See the stamp mode section above for more details.

This operation can be performed on any image and the output image is the same type as the input image.

Parameters:
- `mask` - The objects in the svg artwork that should act as the stamp fence. This is an artwork filter as described above. Like filters for vector processes, this filter only accepts objects with a valid stroke.
- `mask_operations` (Optional) - An array of operations to be applied to the mask image before the input image is masked. When implementing Epilog's stamp mode, a dilation operation could be applied to simulate the fence margins.

Example:

This example applies a mask to the image defined by all svg objects with a color of red or black. The mask is dilated by 0.1 inches before being applied. 
```json
{
    "_of": "path_mask",
    "mask": {
        "_of": "color_filter",
        "colors": ["red", "black"]
    },
    "mask_operations": [
        {
            "_of": "dilate",
            "distance": "0.1in"
        }
    ]
}
```

#### `image_mask`

Applies a mask to the image such that only the parts of the input image contained in the mask remain in the output image. The objects contained by the `mask` filter are drawn in the normal way which means that an `invert` operation is needed for normal masking.

When implementing Epilog's stamp mode, this defines the stamp fence. See the stamp mode section above for more details.

This operation can be performed on any image and the output image is the same type as the input image.

Parameters:
- `mask` - The objects in the svg artwork that should act as the stamp fence. This is an artwork filter as described above. Like filters for engrave processes, this filter accepts all objects with a valid stroke, fill, or image.
- `mask_operations` (Optional) - An array of operations to be applied to the mask image before the input image is masked. When implementing Epilog's stamp mode, a dilation operation could be applied to simulate the fence margins. It is recommended that this starts with the `invert` operation in most cases.

Example:

This example applies a mask to the image defined by all svg objects with a color of red or black. The mask is dilated by 0.1 inches before being applied. The `invert` and `threshold` is necessary so that red and black objects in the artwork create a monochrome mask.
```json
{
    "_of": "image_mask",
    "mask": {
        "_of": "color_filter",
        "colors": ["red", "black"]
    },
    "mask_operations": [
        {
            "_of": "invert"
        },
        {
            "_of": "threshold",
            "value": 0.0
        },
        {
            "_of": "dilate",
            "distance": "0.1in"
        }
    ]
}
```

This example applies a mask to the image defined by another image in the svg. Black parts of the mask image will allow the input image to show completely, gray parts of the mask image will fade the input image.
```json
{
    "_of": "image_mask",
    "mask": {
        "_of": "attribute_filter",
        "attributes": [
            {
            "id": "mask_image",
            "attribute": "all"
            }
        ]
    },
    "mask_operations": [
        {
            "_of": "invert",
        },
    ]
}
```

#### `map`

Maps pixels values in the input image to different values. 

Each value of the input image is interpolated between the nearest `value_map` input value below (or the `min` value in the `interpolate_type` parameter if not found in `value_map`) and the nearest `value_map` input value above (or the `max` value in the `interpolate_type` parameter if not found in `value_map`).

When implementing Epilog's stamp mode, this would be used to define the stamp profile. See the stamp mode section above for more details.

This operation can be performed on any image.

Parameters:
- `value_map` - A list of input and output value pairs that defines intermediate values between `0.0` and `1.0` should be mapped.
- `interpolate_type` - Defines how values should be interpolated between value pairs in the `value_map`. It also describes the value mapping for pixel values below the minimum `value_map` pair and for pixel values above the maximum `value_map` pair.

Output:
- This operation produces a grayscale image.

Examples:

This example provides no mapping such that the input and output are the same.
```json
{
    "_of": "map",
    "interpolate_type": {
        "_of": "linear",
    }
}
```

This example maps all values below `0.5` to `0.0` and keeps all other values the same. This is sometimes called a to-zero threshold in image processing.
```json
{
    "_of": "map",
    "value_map": [ [0.5, 0.0], [0.5, 0.5] ],
    "interpolate_type": {
        "_of": "linear",
    }
}
```

_Linear Interpolation_

Pixel values are linearly interpolated between the `min` value, values in `value_map`, and the `max` value.

Parameters:
- `min` (Optional) - Any values below the minimum value in `value_map` are linearly interpolated between `min` and that minimum value's output. The default value is `0.0` if not specified.
- `max` (Optional) - Any values above the maximum value in `value_map` are linearly interpolated between that maximum value's output and `max`. The default value is `1.0` if not specified.

Example:

This example linearly maps values between `0.0` and `0.3` to `0.1` and `0.5`, maps all values between `0.3` and `0.7` to a constant value of `0.5`, and linearly maps values between `0.7` and `1.0` to `0.5` and `0.9`.
```json
{
    "_of": "map",
    "value_map": [ [0.3, 0.5], [0.7, 0.5] ],
    "interpolate_type": {
        "_of": "linear",
        "min": 0.1,
        "max": 0.9
    }
}
```

_Nearest Below Interpolation_

Pixel values are mapped to the nearest value in `value_map` below the pixel value or to the `min` value.

Parameters:
- `min` (Optional) - Any values below the minimum value in `value_map` are are set to the `min` value. The default value is `0.0` if not specified.

Example:

This example creates a 5-step threshold function where the lowest values are mapped to `0.1`.
```json
{
    "_of": "map",
    "value_map": [ [0.2, 0.3], [0.4, 0.5], [0.6, 0.7], [0.8, 0.9] ],
    "interpolate_type": {
        "_of": "nearest_below",
        "min": 0.1,
    }
}
```

_Nearest Above Interpolation_

Pixel values are mapped to the nearest value in `value_map` above the pixel value or to the `max` value.

Parameters:
- `max` (Optional) - Any values above the maximum value in `value_map` are are set to the `max` value. The default value is `1.0` if not specified.

Example:

This example also creates a 5-step threshold function equivalent to the example for `nearest_below`.
```json
{
    "_of": "map",
    "value_map": [ [0.2, 0.1], [0.4, 0.3], [0.6, 0.5], [0.8, 0.7] ],
    "interpolate_type": {
        "_of": "nearest_above",
        "max": 0.9,
    }
}
```

**[Processes, Fusion, and Legacy Generators Only]**

This setting is not applicable to the G2 generator because it does not have engrave processes.

### `speed`

A value which represents the percentage of the maximum speed that will be used.

**[Processes Generator]**

This value must be between `0.01` and `100` and accepts decimal values.

**[Fusion and Legacy Generators]**

This value must be between `1` and `100` and must be an integer.

### `power`

A value which represents the percentage of the maximum power that will be used.

**[Processes Generator]**

This value must be between `0` and `100` and accepts decimal values.

**[Fusion and Legacy Generators]**

This value must be between `0` and `100` and must be an integer.

### `frequency`

Except in the Legacy generator, this is a percent value in which a value of `1` maps to the lowest available frequency and a value of `100` maps to the highest available frequency. The minimum and maximum frequency available depends on the laser installed in the machine and may also differ for different waveforms when applicable.

In the legacy generator, the value is provided in Hertz (Hz) and therefore have a different range of values as noted below.

This must only be set when the `laser_type` (specified or implied) is `fiber`.

**[Processes Generator]**

This value must be between `1` and `100` and accepts decimal values.

**[Fusion Generator]**

This value must be between `1` and `100` and must be an integer.

**[Legacy Generator]**

This value must be between `10` and `5000` and must be an integer.

### `waveform`

For machines with waveform-enabled lasers, this option specified the waveform that is to be used.

Note: Currently, only `g100` and `g2` machines have waveform-enabled lasers available.

**[Processes Generator]**

This value must be between `0` and `15` and must be an integer.

**[G2 Generator]**

This value must be between `0` and `7` and must be an integer.

### `precision_sync`

Enables the precision sync feature which extends the engraving bounds to the furthest left and right points of the artwork for every engrave line. This increases engrave time, but ensures that the length of each engrave line remains the same, thus improving engrave quality.

This value can be set to `true` or `false`.

### `unidirectional`

Enabled unidirectional engraving which that engrave lines are only output when the carriage moves from left to right. This effectively doubles the engrave time but completely reduces any laser match issues.

This value can be set to `true` or `false`.

**[Processes Generator Only]**

This setting is only applicable to the Processes generator and no others.

### `laser_type`

For machines that only have one laser type allowed, this field is optional and will throw an error if the wrong laser type is specified. For machines that can have either or both laser types, this field must be set and will throw an error if it is not.

This value can be set to `co2` or `fiber`.

See the Laser Type section above for details on which laser options are available for each machine type.

**[Processes and Fusion Generators Only]**

This setting is only applicable to the Processes generator and no others since the only dual source machines belong to these generators.

### `thickness`

The thickness of the material that will be used. This value follows the length unit options described above.

This value must be specified if `autofocus` is set to `thickness` and must not be specified otherwise.

**[Processes Generator Only]**

This setting is only applicable to the Processes generator and no others. The other generators use the `focus` setting mentioned below.

### `offset` (Optional)

If this value is set, it specifies an additional offset from the material thickness or from the starting position of the table. This value follows the length unit options described above.

**[Processes Generator Only]**

This setting is only applicable to the Processes generator and no others. The other generators use the `focus` setting mentioned below.

### `focus` (Optional)

The thickness of the material that will be used or simply the offset of the table from its starting point. This value follows the length unit options described above.

This value must be specified if `autofocus` is set to `true` and must not be specified otherwise.

**[G2, Fusion, and Legacy Generators Only]**

This setting is not applicable to the Processes generator because it uses the `thickness` and `offset` settings.

### `air_assist` (Optional)

Whether or not the air assist feature should be engaged for this process. A value of `false` is always allowed, but a value of `true` will cause an error to be thrown if the specified machine type does not support the air assist feature.

This value can be set to `true` or `false` [default].

**[Processes, Fusion, and Legacy Generators Only]**

This setting is not applicable to the G2 generator because it did not have an air assist feature.

# Vector Process

The vector process can be used to make cuts or thin lined marks where the machine follows the input path while lasing.

### `name`

The name of the process as it will be seen on the UI of the engraver.

### `enabled` (Optional)

If this is `true`, then output will be generated for this process. If it is `false`, this process will be ignored. 

This value can be set to `true` [default] or `false`.

Note: The artwork is still filtered even if this value is `false`.

### `filter`

The artwork filter as described above.

### `cycles`

The number of times the output for this process is repeated.

The value must be greater than or equal to `1`.

### `speed`

A value which represents the percentage of the maximum speed that will be used.

**[Processes Generator]**

This value must be between `0.01` and `100` and accepts decimal values.

**[Fusion and Legacy Generators]**

This value must be between `1` and `100` and must be an integer.

### `power`

A value which represents the percentage of the maximum power that will be used.

**[Processes Generator]**

This value must be between `0` and `100` and accepts decimal values.

**[Fusion and Legacy Generators]**

This value must be between `0` and `100` and must be an integer.

### `frequency`

Except in the Legacy generator, this is a percent value in which a value of `1` maps to the lowest available frequency and a value of `100` maps to the highest available frequency. The minimum and maximum frequency available depends on the laser installed in the machine and may also differ for different waveforms when applicable.

In the legacy generator, the value is provided in Hertz (Hz) and therefore have a different range of values as noted below.

**[Processes Generator]**

This value must be between `1` and `100` and accepts decimal values.

**[Fusion Generator]**

This value must be between `1` and `100` and must be an integer.

**[Legacy Generator]**

This value must be between `10` and `5000` and must be an integer.

### `waveform`

For machines with waveform-enabled lasers, this option specified the waveform that is to be used.

Note: Currently, only `g100` and `g2` machines have waveform-enabled lasers available.

**[Processes Generator]**

This value must be between `0` and `15` and must be an integer.

**[G2 Generator]**

This value must be between `0` and `7` and must be an integer.

### `vector_sorting`

Specifies the sorting algorithm used to order paths.

The following options are available:
- `off` - No sorting will be applied.
- `optimize` - Paths will be optimally sorted to reduce run time.
- `inside_out` - Paths will be optimally sorted to reduce run time with the restriction that the inside-most paths must be done before the paths that they are contained within.

### `laser_side` (Optional)

Specifies the side of the artwork paths that we would like to lase on. In practice, this allows users to specify the behavior of a kerf offset.

Example:
```
"laser_side": {
    "closed": {
        "_of": "outside"
    },
    "open": {
        "_of": "right_hand_rule"
    },
    "kerf": {
        "offset": "0.02in",
        "line_join": {
            "_of": "bevel"
        }
    },
    "overrides": {

    }
}
```

#### `closed`

Specifies which side of closed artwork paths that we would like to lase on.

The following options are available:
- `outside` - The outside of the path is the side that will be lased. This is sometimes more computationally expensive than the `right_hand_rule` and `left_hand_rule` options.
- `inside` - The inside of the path is the side that will be lased. This is sometimes more computationally expensive than the `right_hand_rule` and `left_hand_rule` options.
- `right_hand_rule` - The cross product of the direction of the path with a vector pointing out of the screen the direction that will be lased. In simpler terms, clockwise paths will offset inwards.
- `left_hand_rule` - The negative cross product of the direction of the path with a vector pointing out of the screen gives the direction that will be lased. In simpler terms, clockwise paths will offset outwards.

Example:
```
"closed": {
    "_of": "outside"
}
```

#### `open`

Specifies which side of open artwork paths that we would like to lase on.

The following options are available:
- `right_hand_rule` - The cross product of the direction of the path with a vector pointing out of the screen the direction that will be lased. In simpler terms, clockwise paths will offset inwards.
- `left_hand_rule` - The negative cross product of the direction of the path with a vector pointing out of the screen gives the direction that will be lased. In simpler terms, clockwise paths will offset outwards.

Example:
```
"open": {
    "_of": "right_hand_rule"
}
```

#### `kerf`

Specifies an offset to be applied to the artwork paths in order to accommodate for the width of the laser.

The following parameters must be specified:
- `offset` - The distance to offset the cut paths by. This value follows the length unit options described above.
- `line_join` - The way in which the ends of artwork segments will be joined together when expanding outwards. For example, when offsetting a rectangle outwards, the individual lines would need to be joined in some way. The options for this are bevel (a straight line connects the two segment ends), round (an arc connects to the two segment ends), and miter (the ends of the segments extend in a straight line until they meet).

Example:
```
"kerf": {
    "offset": "0.02in",
    "line_join": {
        "_of": "bevel"
    }
}
```

#### `overrides` (Optional)

A filter specifying which objects in the artwork should lase on the opposite side of what has been established by the other settings within `laser_side`.

### `beziers`

Whether or not bezier output will be enabled. If this is `true`, smooth bezier curves will be used in the output where they exist in the artwork. If this  is `false`, all curves will be flattened to line segments which may decrease cut quality.

This value can be set to `true` or `false`.

**[Processes and Fusion Generators Only]**

This setting is only applicable to the Processes and Fusions generators because other machines do not support bezier curves in the output.

### `laser_type`

For machines that only have one laser type allowed, this field is optional and will throw an error if the wrong laser type is specified. For machines that can have either or both laser types, this field must be set and will throw an error if it is not.

This value can be set to `co2` or `fiber`.

See the Laser Type section above for details on which laser options are available for each machine type.

**[Processes and Fusion Generators Only]**

This setting is only applicable to the Processes generator and no others since the only dual source machines belong to these generators.

### `thickness`

The thickness of the material that will be used. This value follows the length unit options described above.

This value must be specified if `autofocus` is set to `thickness` and must not be specified otherwise.

**[Processes Generator Only]**

This setting is only applicable to the Processes generator and no others. The other generators use the `focus` setting mentioned below.

### `offset` (Optional)

If this value is set, it specifies an additional offset from the material thickness or from the starting position of the table. This value follows the length unit options described above.

**[Processes Generator Only]**

This setting is only applicable to the Processes generator and no others. The other generators use the `focus` setting mentioned below.

### `focus` (Optional)

The thickness of the material that will be used or simply the offset of the table from its starting point. This value follows the length unit options described above.

This value must be specified if `autofocus` is set to `true` and must not be specified otherwise.

**[G2, Fusion, and Legacy Generators Only]**

This setting is not applicable to the Processes generator because it uses the `thickness` and `offset` settings.

### `air_assist` (Optional)

Whether or not the air assist feature should be engaged for this process. A value of `false` is always allowed, but a value of `true` will cause an error to be thrown if the specified machine type does not support the air assist feature.

This value can be set to `true` or `false` [default].

**[Processes, Fusion, and Legacy Generators Only]**

This setting is not applicable to the G2 generator because it did not have an air assist feature.

### `optimize_cycles` (Optional)

Whether or not vector cycle optimization should be applied. If this value is `true`, paths will be sorted in such a way to prevent move-tos as much as possible when this process has multiple cycles.

This value can be set to `true` [default] or `false`.

# Hatch Process

The hatch process is primarily used with Galvo based systems.

### `name`

The name of the process as it will be seen on the UI of the engraver.

### `enabled` (Optional)

If this is `true`, then output will be generated for this process. If it is `false`, this process will be ignored. 

This value can be set to `true` [default] or `false`.

Note: The artwork is still filtered even if this value is `false`.

### `filter`

The artwork filter as described above.

### `cycles`

The number of times the output for this process is repeated.

The value must be greater than or equal to `1`.

### `patterns`

Describes the list of hatch patterns to be used. The hatch pattern structure will be described in the next section.

There must be at least one enabled pattern.

Example:
```
"patterns": [
    {
        "name": "hatch sweep",
        "pattern_type": {
            "_of": "sweep",
            "spacing": 2.54,
            "angle": 0
        },
        "speed": 100,
        "power": 100,
        "frequency": 1,
        "passes": 1
    },
    {
        "name": "hatch sweep (connected)",
        "pattern_type": {
            "_of": "s_sweep",
            "spacing": "2.54mm",
            "angle": 45
        },
        "speed": 100,
        "power": 100,
        "frequency": 1,
        "passes": 1
    },
    {
        "name": "hatch unidirectional",
        "pattern_type": {
            "_of": "unidirectional",
            "spacing": "0.1in",
            "angle": 90
        },
        "speed": 100,
        "power": 100,
        "frequency": 1,
        "passes": 1
    },
    {
        "name": "hatch outline",
        "pattern_type": {
            "_of": "outline"
        },
        "speed": 100,
        "power": 100,
        "frequency": 1,
        "passes": 1
    }
]
```

### `isolate_shapes`

Whether or not separated shapes should be hatched separately.

Note: When this is set to `true`, shapes contained within other shapes are hatched together to optimize runtime.

### `laser_type`

For machines that only have one laser type allowed, this field is optional and will throw an error if the wrong laser type is specified. For machines that can have either or both laser types, this field must be set and will throw an error if it is not.

This value can be set to `co2` or `fiber`.

See the Laser Type section above for details on which laser options are available for each machine type.

**[Processes and Fusion Generators Only]**

This setting is only applicable to the Processes generator and no others since the only dual source machines belong to these generators.

### `thickness`

The thickness of the material that will be used. This value follows the length unit options described above.

This value must be specified if `autofocus` is set to `thickness` and must not be specified otherwise.

**[Processes Generator Only]**

This setting is only applicable to the Processes generator and no others. The other generators use the `focus` setting mentioned below.

### `offset` (Optional)

If this value is set, it specifies an additional offset from the material thickness or from the starting position of the table. This value follows the length unit options described above.

**[Processes Generator Only]**

This setting is only applicable to the Processes generator and no others. The other generators use the `focus` setting mentioned below.

### `focus` (Optional)

The thickness of the material that will be used or simply the offset of the table from its starting point. This value follows the length unit options described above.

This value must be specified if `autofocus` is set to `true` and must not be specified otherwise.

**[G2, Fusion, and Legacy Generators Only]**

This setting is not applicable to the Processes generator because it uses the `thickness` and `offset` settings.

### `air_assist` (Optional)

Whether or not the air assist feature should be engaged for this process. A value of `false` is always allowed, but a value of `true` will cause an error to be thrown if the specified machine type does not support the air assist feature.

This value can be set to `true` or `false` [default].

**[Processes, Fusion, and Legacy Generators Only]**

This setting is not applicable to the G2 generator because it did not have an air assist feature.

### `optimize_hatch_sort` (Optional)

Whether or not hatch optimization should be applied. If this value is `true`, paths will be sorted in such a way to prevent move-tos as much as possible when hatch patterns have multiple passes and/or this process has multiple cycles.

This value can be set to `true` [default] or `false`.

# Hatch Patterns

Hatch patterns describe the way in which a shape can be hatched.

### `name`

The name of the hatch pattern as it will be seen on the UI of the engraver.

### `enabled` (Optional)

If this is `true`, then output will be generated for this hatch pattern. If it is `false`, this pattern will be ignored. 

This value can be set to `true` [default] or `false`.

### `pattern_type`

The type of hatch pattern that is to be created.

The following options are available:
- `sweep` - Hatch lines are disconnected and alternate in direction.
  - A `spacing`, which follows the length unit options described above, and an `angle`, which is specified in degrees, must be provided.
  - Example:
    ```
    "pattern_type": {
        "_of": "sweep",
        "spacing": 2.54,
        "angle": 45
    },
    ```
- `s_sweep` - Hatch lines are connected and alternate in direction.
  - A `spacing`, which follows the length unit options described above, and an `angle`, which is specified in degrees, must be provided.
  - Example:
    ```
    "pattern_type": {
        "_of": "s_sweep",
        "spacing": 2.54,
        "angle": 45
    },
    ```
- `unidirectional` - Hatch lines are disconnected and remain in direction which can increase run time.
  - A `spacing`, which follows the length unit options described above, and an `angle`, which is specified in degrees, must be provided.
  - Example:
    ```
    "pattern_type": {
        "_of": "unidirectional",
        "spacing": 2.54,
        "angle": 45
    },
    ```
- `outline` - Creates an outline of the shape and is often used to clean up the edges after using the other hatch pattern types.
  - No additional parameters are specified.
  - Example:
    ```
    "pattern_type": {
        "_of": "outline",
    },
    ```

### `speed`

A value which represents the percentage of the maximum speed that will be used.

**[Processes Generator]**

This value must be between `0.01` and `100` and accepts decimal values.

**[Fusion and Legacy Generators]**

This value must be between `1` and `100` and must be an integer.

### `power`

A value which represents the percentage of the maximum power that will be used.

**[Processes Generator]**

This value must be between `0` and `100` and accepts decimal values.

**[Fusion and Legacy Generators]**

This value must be between `0` and `100` and must be an integer.

### `frequency`

Except in the Legacy generator, this is a percent value in which a value of `1` maps to the lowest available frequency and a value of `100` maps to the highest available frequency. The minimum and maximum frequency available depends on the laser installed in the machine and may also differ for different waveforms when applicable.

In the legacy generator, the value is provided in Hertz (Hz) and therefore have a different range of values as noted below.

**[Processes Generator]**

This value must be between `1` and `100` and accepts decimal values.

**[Fusion Generator]**

This value must be between `1` and `100` and must be an integer.

**[Legacy Generator]**

This value must be between `10` and `5000` and must be an integer.

### `waveform`

For machines with waveform-enabled lasers, this option specified the waveform that is to be used.

Note: Currently, only `g100` and `g2` machines have waveform-enabled lasers available.

**[Processes Generator]**

This value must be between `0` and `15` and must be an integer.

**[G2 Generator]**

This value must be between `0` and `7` and must be an integer.

### `passes`

The number of times the output for this hatch pattern is repeated.

The value must be greater than or equal to `1`.
