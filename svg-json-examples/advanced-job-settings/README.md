# Advanced Job Settings Examples

The jobs contained in this folder demonstrate the use of advanced job settings for advanced users. These examples can serve as a reference for creating your own jobs.

## Artwork Files

### Advanced-Job-Settings.svg

- For use with all of the settings files in this folder.

## Settings Files

### Custom-Autofocus-Plunger-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - Not compatible with any other machine type.
- Note that the use of `custom_position` under `autofocus` sets the plunger location to **(2 in, 2 in)** (using inches and mm).

### Job-Alignment-Center-Center-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - This feature is compatible with all machine types except the `g2`, but the example must be modified to use with the other types not listed above.
- Note that the use of `centering_point` under `job_alignment` sets the reference point to the center of the artwork. As such, the centering point set at the machine will correspond to the center of the artwork.

### Job-Alignment-Custom-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - This feature is compatible with all machine types except the `g2`, but the example must be modified to use with the other types not listed above.
- Note that the use of `centering_point` under `job_alignment` sets the reference point to the bottom tip of the letter `v` in the artwork. As such, the centering point set at the machine will correspond to that point in the artwork.

### Svg-Origin-Custom-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - This feature is compatible with all machine types, but the example must be modified to use with the other types not listed above.
- Note that the use of `svg_origin` sets the origin of the SVG artwork to **(-1in, -0.5in)** in svg space. Moving the origin in the negative direction (left and up), has the effect of offsetting the artwork in the positive direction (right and down) since we are setting the zero point of the artwork.

### Rim-Rotary-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - This feature is compatible with all machine types, but the example must be modified to use with the other types not listed above.
- Note that the use of `rotary` enabled rotary mode for that job when run on the machine.
- This job also uses a `center_center` job alignment since this feature allows you to center the artwork in the desired location before engraving.

### Three-Jaw-Rotary-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
    - This feature is compatible with all machine types, but the example must be modified to use with the other types not listed above.
- Be sure to update the `diameter` value to match the material being used.
- Note that the use of `rotary` enabled rotary mode for that job when run on the machine.
- This job also uses a `center_center` job alignment since this feature allows you to center the artwork in the desired location before engraving.

## Material Suggestion

These settings will mark on **anodized aluminum**.

_Note: Because some of the settings are modified to show how different parameters can be modified and because the PrintAPI does not have knowledge of the machine and laser, an optimal mark is not guaranteed._
