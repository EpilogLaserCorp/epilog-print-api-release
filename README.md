<img src='./.github/epilog-banner.png' alt="banner"></img>

# **Epilog PrintAPI**
*Revolutionizing Laser Printing Integration*

&nbsp;

Epilog is thrilled to present PrintAPI, a powerful tool that opens new possibilities for developers and users of Epilog Laser machines. Designed as a flexible library, PrintAPI empowers developers to seamlessly create and send print jobs to Epilog Laser machines directly from their own software environments.

With PrintAPI, users can effortlessly generate print files by combining three key components: artwork in the form of an svg file, laser settings specified in a json file, and the model of the Epilog Laser machine to be used. The result is a streamlined print file ready to be sent directly to the machine, simplifying and enhancing the entire printing process.

This new capability allows customers to fully integrate Epilog Laser machines into their existing workflows, tailoring the print file generation process to meet their specific needs and preferences. Whether for automation, customization, or scalability, PrintAPI brings the power of laser printing directly into the hands of the developers, offering unmatched flexibility and control.

&nbsp;

## What's Included

### Complete Documentation

  - Read the [Json Settings Document](./JSON_SETTINGS.md) for details on how to format the settings file and which machines are supported.
  - Each component has it's own separate documentation linked below.

### C++ Library

  - Includes a header file along with Windows and Ubuntu build files.
  - An example C++ program is provided.
  - See the [C++ Readme](./cpp-library/README.md) for more details.

### Executables

  - Executables are provided for Windows and Ubuntu.
  - Epilog PrintAPI Runner
    - The Epilog PrintAPI Runner performs the task of generating print files and optionally sending them to the specified machine.
    - See the [Epilog PrintAPI Runner Readme](./epilog-print-api-runner/README.md) for more details.
  - Epilog Print File Transmitter
    - The Epilog Print File Transmitter sends previously generated print files to the specified machine.
    - See the [Epilog Print File Transmitter Readme](./epilog-print-file-transmitter/README.md) for more details.

### Schemas

  - These files are a template for the format of the json settings files.
  - They specify _most_ of the constraints on any given parameter.
  - Each generator type has a different schema.
  - The [Json Settings Document](./JSON_SETTINGS.md) also has details on each parameter's constraints and on how each generator is used.

### Example Svg and Json Files

  - These examples provide a quick and easy way to see how the Epilog PrintAPI works.
  - Each type of generator has a different `json` file. The `Processes` generator will most likely be correct generator since it is used for all new machine types. If you're not sure, take a look at the [JSON Settings Document](./JSON_SETTINGS.md) to see which generator to use.

## Support

Epilog wants to provide the best service possible. If you encounter a bug or have a feature request for the Epilog PrintAPI, please let us know by submitting a ticket on the [Issues Page](https://github.com/EpilogLaserCorp/epilog-print-api-release/issues).

If you're having an issue that is not related to the Epilog PrintAPI, please visit the [Epilog Support Page](https://www.epiloglaser.com/support/).
