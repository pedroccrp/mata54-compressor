# MATA54 Compressor
 
## Table of Contents

  - [About The Project](#about-the-project)
    - [Built With](#built-with)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
  - [Usage](#usage)
  - [License](#license)
  <!-- - [Contact](#contact) -->
  - [Contributing](#contributing)
    - [Contributors](#contributors)
  <!-- - [Acknowledgements](#acknowledgements) -->


## About The Project

A simple file compressor made as a work for Data Structures class

### Built With

* C++

## Getting Started

Be mindful that the commands bellow are to be used with Linux and similar operational systems.

### Prerequisites

* C++ Compiler

    ```
    sudo apt-get install g++
    ```

* Makefile

    ```
    sudo apt-get install make
    ```

### Installation

* Run the makefile

    ```
    make
    ```

## Usage

After installation, the executable will be in **bin/mata54comp**

- Running
  
  - Compress
  
    ```
    bin/mata54comp -c file
    ```

    - After compression there will be created a **file.cmp**

  - Decompress
 
    ```
    bin/mata54comp -d file.cmp
    ```

    - After decompression there will be created a **file**


## License

Distributed under the MIT License. See `LICENSE` for more information.

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/amazing-feature`)
3. Commit your Changes (`git commit -m 'Add some amazing-feature'`)
4. Push to the Branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Contributors

* Antônio Dias - [antoniofdias](https://github.com/antoniofdias)
* Eduardo Seifert - [EduardoRSeifert](https://github.com/EduardoRSeifert)
* Pedro Pontes - [pedroccrp](https://github.com/pedroccrp)

See [contributors](https://github.com/pedroccrp/mata54-compressor/graphs/contributors) page for more info.

<!-- 
## Acknowledgements
* [Google Fonts](https://fonts.google.com/) 
-->