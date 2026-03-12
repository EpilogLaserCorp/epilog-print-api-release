# Advanced Process Settings Examples

The jobs contained in this folder demonstrate the use of advanced process settings for advanced users. These examples can serve as a reference for creating your own jobs.

## Artwork Files

### Advanced-Process-Settings.svg

- For use with all of the settings files in this folder.

## Settings Files

### Filter-All-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `ascent12`, `ascent24`, `ascent36`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - This feature is compatible with all machine types, but the example must be modified to use with the other types not listed above.
- Note that the use of `all_filter` under `filter` sets the filter to capture all objects not previously contained in a process. Using this filter for any process other than the last will cause an error as all subsequent processes will have no objects to capture.

### Filter-Attribute-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `ascent12`, `ascent24`, `ascent36`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - This feature is compatible with all machine types, but the example must be modified to use with the other types not listed above.
- Note that the use of `attribute_filter` under `filter` sets the filter to specify which objects are contained in the process and whether that process will contain the stroke, the fill, or both.

### Filter-Color-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `ascent12`, `ascent24`, `ascent36`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - This feature is compatible with all machine types, but the example must be modified to use with the other types not listed above.
- Note that the use of `color_filter` under `filter` sets the filter to specify which colors of objects are contained in the process.

### 3D-Engraving-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `ascent12`, `ascent24`, `ascent36`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - This feature is compatible with all machine types, but the example must be modified to use with the other types not listed above.
- Note that the use of `grayscale_3d` for `dithering` sets the output of that process into 3D engraving mode.

### Stamp-Engraving-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `ascent12`, `ascent24`, `ascent36`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - This feature is compatible with all machine types, but the example must be modified to use with the other types not listed above.
- Note that the use of `grayscale_3d` for `dithering` sets the output of that process into 3D engraving mode.
- Note that the use of `operations` implements the stamp mode.
    - The `invert` operation inverts the grayscale values since in normal artwork, dark areas correspond to what will be engraved (i.e. those pixels are "on"), but image operations consider white values to be "on".
    - The `threshold` operation with a low value to clean up the edges of the stamp artwork. This also converts the image to monochrome which is necessary for the upcoming operations.
    - The `dilate` operation expands the white areas of the image to slightly increase the area of the stamp. This is equivalent to the `Widening` setting in the Epilog Software Suite.
    - The `distance_transform` operation creates a ramp away from the edges of the stamp artwork.
    - _[Optional]_ The `map` operation modifies the distance transform values to provide the desired ramp shape. This can often be omitted. In this example, it adds a small flat area in the middle of the ramp. This is equivalent to the `Shoulder` setting in the Epilog Software Suite.
    - The next `invert` operation inverts the grayscale values again so that we engrave everything within the fence.
    - The `path_mask` operation ensures that the engraving only occurs within the specified vector paths. This is roughly equivalent to `Fence` setting in the Epilog Software Suite, but it is more precise since specific vector paths must be provided.
    - _[Optional]_ The `dilate` operation for the mask expands (or contracts) the area of the mask. This is equivalent to the `Fence Margins` setting in the Epilog Software Suite. This can often be omitted.

### Vector-Sorting-Optimize-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `ascent12`, `ascent24`, `ascent36`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - This feature is compatible with all machine types, but the example must be modified to use with the other types not listed above.
- Note that the use of `optimize` for `vector_sorting` ensures that vector paths are processed in the most efficient order to reduce run times.

### Vector-Sorting-Inside-Out-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `ascent12`, `ascent24`, `ascent36`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - This feature is compatible with all machine types, but the example must be modified to use with the other types not listed above.
- Note that the use of `inside_out` for `vector_sorting` ensures that vector paths are processed in the most efficient order to reduce run times with the caveat that it will do the inner-most paths first. This is preferable when completely cutting through the material in a vector process.

## Material Suggestion

These settings will mark on **anodized aluminum**.

_Note: Because some of the settings are modified to show how different parameters can be modified and because the PrintAPI does not have knowledge of the machine and laser, an optimal mark is not guaranteed._
