# Engrave-Only Examples

The jobs contained in this folder demonstrate the use of engrave processes. These examples can serve as a reference for creating your own jobs.

## Artwork Files

### Multi-Process-Raster.svg

- For use with all of the `Multi-Process-Raster-*.json` settings files in this folder.

### Single-Process-Raster.svg

- For use with all of the `Single-Process-Raster-*.json` settings files in this folder.

## Settings Files

### Multi-Process-Raster-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `ascent12`, `ascent24`, `ascent36`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
- Contains multiple processes. Some settings like `speed`, `power`, and `precision_sync` will vary between processes.

### Multi-Process-Raster-Fusion.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `fusion32_m2`, `fusion40_m2`, `fusion32`, `fusion40`.
- To use with `fusion32_fibermark`, change the `laser_type` to `fiber` in all processes and add the `frequency` setting to the engrave processes.
- Contains multiple processes. Some settings like `speed` and `power` will vary between processes.

### Multi-Process-Raster-Legacy.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `zing16`, `zing24`, `helix24`, `mini18`, `mini24`, `ext36`.
- To use with `fibermark24` and `fibermark24_s2`, add the `frequency` setting to the engrave processes.
- Contains multiple processes. Some settings like `speed` and `power` will vary between processes.

### Single-Process-Raster-Processes.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `pro24`, `pro32`, `pro36`, `pro48`, `ascent12`, `ascent24`, `ascent36`, `edge12`, `edge24`, `edge36`, `maker12`, `maker24`, `maker36`.
- Contains one process.

### Single-Process-Raster-Fusion.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `fusion32_m2`, `fusion40_m2`, `fusion32`, `fusion40`.
- To use with `fusion32_fibermark`, change the `laser_type` to `fiber` in all processes and add the `frequency` setting to the engrave processes.
- Contains one process.

### Single-Process-Raster-Legacy.json

- For use with the following machine types without modification (if they have a CO2 laser installed): `zing16`, `zing24`, `helix24`, `mini18`, `mini24`, `ext36`.
- To use with `fibermark24` and `fibermark24_s2`, add the `frequency` setting to the engrave processes.
- Contains one process.

## Material Suggestion

These settings will mark on **anodized aluminum**.

_Note: Because some of the settings are modified to show how different parameters can be modified and because the PrintAPI does not have knowledge of the machine and laser, an optimal mark is not guaranteed._
