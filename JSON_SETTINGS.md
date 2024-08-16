# **Epilog PrintAPI Settings**

This document details everything you need to know about creating json settings files.

If you are new to the Epilog PrintAPI, consider starting off with the example svg and json files.

# Laser Types

It will be important when setting process `laser_type` parameters to know which machines support which laser types.

The following machine types can only have `co2` lasers:
- edge24
- edge36
- maker12
- maker24
- maker36

The following machine types can only have `fiber` lasers:
- g100_4x4
- g100_6x6

The following machine types have either laser type, but not both:
- edg12

The following machine types can have either or both laser types (dual source):
- pro24
- pro32
- pro36
- pro48

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

# Settings Structure

The settings are defined as a json tree with the properties seen below.

### `job_name`

The name of the job as it will show up on the machine. It must be between `1` and `255` characters.

### `firmware_version`

The firmware version of the machine that it is intended for. 

Note: No error is currently shown if the versions do not match.

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

### `copies`

The number of times a job is repeated. The value must be greater than or equal to `1`.

### `autofocus`

Specifies how the machine will handle auto-focusing.

The following options are available:
- `off` - No autofocus will occur.
- `plunger` - The plunger attached to the carriage will be used to determine the thickness of the material.
- `thickness` - A `thickness` value must be provided in each process and will be used to set the table to the specified height.

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

### `processes`

Describes the list of processes to be used. Each process type has a unique set of settings.

The following three options are available:
- `Engrave`
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

### `engrave_direction`

The direction in which the engraving will happen.

This can be set to `down` for top-down engraving or `up` for bottom-up engraving.

### `dithering`

The algorithm used to dither the artwork for the process into the binary (monochromatic) data used by the engraver.

The following options are available:
- `none` - No dithering is applied.
- `standard` - The standard Epilog dithering pattern is applied.
- `floyd_steinberg` - The [Floyd-Steinberg](https://en.wikipedia.org/wiki/Floyd%E2%80%93Steinberg_dithering) dithering algorithm is applied.
- `jarvis` - The [Jarvis (a.k.a. Minimized Average Error)](https://en.wikipedia.org/wiki/Error_diffusion#minimized_average_error) dithering algorithm is applied.
- `stucki` - The [Stucki](https://tannerhelland.com/2012/12/28/dithering-eleven-algorithms-source-code.html) dithering algorithm is applied.
- `bayer` - A [Bayer](https://en.wikipedia.org/wiki/Ordered_dithering) dithering algorithm is applied.

### `speed`

A value which represents the percentage of the maximum speed that will be used.

This value must be between `0.01` and `100` and accepts decimal values.

### `power`

A value which represents the percentage of the maximum power that will be used.

This value must be between `0` and `100` and accepts decimal values.

### `frequency`

This is a percent value in which a value of `1` maps to the lowest available frequency and a value of `100` maps to the highest available frequency. The minimum and maximum frequency available depends on the laser installed in the machine and may also differ for different waveforms when applicable.

This must only be set when the `laser_type` (specified or implied) is `fiber`.

This value must be between `1` and `100` and accepts decimal values.

### `waveform`

For machines with waveform-enabled lasers, this option specified the waveform that is to be used.

Note: Currently, only `g100` machines have waveform-enabled lasers available.

This value must be between `0` and `15` and must be an integer.

### `precision_sync`

Enables the precision sync feature which extends the engraving bounds to the furthest left and right points of the artwork for every engrave line. This increases engrave time, but ensures that the length of each engrave line remains the same, thus improving engrave quality.

This value can be set to `true` or `false`.

### `unidirectional`

Enabled unidirectional engraving which that engrave lines are only output when the carriage moves from left to right. This effectively doubles the engrave time but completely reduces any laser match issues.

This value can be set to `true` or `false`.

### `laser_type`

For machines that only have one laser type allowed, this field is optional and will throw an error if the wrong laser type is specified. For machines that can have either or both laser types, this field must be set and will throw an error if it is not.

This value can be set to `co2` or `fiber`.

See the Laser Type section above for details on which laser options are available for each machine type.

### `thickness`

The thickness of the material that will be used. This value follows the length unit options described above.

This value must be specified if `autofocus` is set to `thickness` and must not be specified otherwise.

### `offset` (Optional)

If this value is set, it specifies an additional offset from the material thickness or from the starting position of the table. This value follows the length unit options described above.

### `air_assist` (Optional)

Whether or not the air assist feature should be engaged for this process. A value of `false` is always allowed, but a value of `true` will cause an error to be thrown if the specified machine type does not support the air assist feature.

This value can be set to `true` or `false` [default].

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

This value must be between `0.01` and `100` and accepts decimal values.

### `power`

A value which represents the percentage of the maximum power that will be used.

This value must be between `0` and `100` and accepts decimal values.

### `frequency`

This is a percent value in which a value of `1` maps to the lowest available frequency and a value of `100` maps to the highest available frequency. The minimum and maximum frequency available depends on the laser installed in the machine and may also differ for different waveforms when applicable.

This value must be between `1` and `100` and accepts decimal values.

### `waveform`

For machines with waveform-enabled lasers, this option specified the waveform that is to be used.

Note: Currently, only `g100` machines have waveform-enabled lasers available.

This value must be between `0` and `15` and must be an integer.

### `vector_sorting`

Specifies the sorting algorithm used to order paths.

The following options are available:
- `off` - No sorting will be applied.
- `optimize` - Paths will be optimally sorted to reduce run time.
- `inside_out` - Paths will be optimally sorted to reduce run time with the restriction that the inside-most paths must be done before the paths that they are contained within.

### `beziers`

Whether or not bezier output will be enabled. If this is `true`, smooth bezier curves will be used in the output where they exist in the artwork. If this  is `false`, all curves will be flattened to line segments which may decrease cut quality.

This value can be set to `true` or `false`.

### `laser_type`

For machines that only have one laser type allowed, this field is optional and will throw an error if the wrong laser type is specified. For machines that can have either or both laser types, this field must be set and will throw an error if it is not.

This value can be set to `co2` or `fiber`.

See the Laser Type section above for details on which laser options are available for each machine type.

### `thickness`

The thickness of the material that will be used. This value follows the length unit options described above.

This value must be specified if `autofocus` is set to `thickness` and must not be specified otherwise.

### `offset` (Optional)

If this value is set, it specifies an additional offset from the material thickness or from the starting position of the table. This value follows the length unit options described above.

### `air_assist` (Optional)

Whether or not the air assist feature should be engaged for this process. A value of `false` is always allowed, but a value of `true` will cause an error to be thrown if the specified machine type does not support the air assist feature.

This value can be set to `true` or `false` [default].

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

### `laser_type`

For machines that only have one laser type allowed, this field is optional and will throw an error if the wrong laser type is specified. For machines that can have either or both laser types, this field must be set and will throw an error if it is not.

This value can be set to `co2` or `fiber`.

See the Laser Type section above for details on which laser options are available for each machine type.

### `thickness`

The thickness of the material that will be used. This value follows the length unit options described above.

This value must be specified if `autofocus` is set to `thickness` and must not be specified otherwise.

### `offset` (Optional)

If this value is set, it specifies an additional offset from the material thickness or from the starting position of the table. This value follows the length unit options described above.

### `air_assist` (Optional)

Whether or not the air assist feature should be engaged for this process. A value of `false` is always allowed, but a value of `true` will cause an error to be thrown if the specified machine type does not support the air assist feature.

This value can be set to `true` or `false` [default].

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

This value must be between `0.01` and `100` and accepts decimal values.

### `power`

A value which represents the percentage of the maximum power that will be used.

This value must be between `0` and `100` and accepts decimal values.

### `frequency`

This is a percent value in which a value of `1` maps to the lowest available frequency and a value of `100` maps to the highest available frequency. The minimum and maximum frequency available depends on the laser installed in the machine and may also differ for different waveforms when applicable.

This value must be between `1` and `100` and accepts decimal values.

### `waveform`

For machines with waveform-enabled lasers, this option specified the waveform that is to be used.

Note: Currently, only `g100` machines have waveform-enabled lasers available.

This value must be between `0` and `15` and must be an integer.

### `passes`

The number of times the output for this hatch pattern is repeated.

The value must be greater than or equal to `1`.

# Currently Unimplemented Features

- 3D Engraving
- Stamp Engraving
- Legacy Machine (Mini, Helix, Ext, Zing, Fibermark) Support
- G2 Support