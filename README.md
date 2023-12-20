# UnBiohazard

Cláudio Barros - 190097591

## Pré-Requisitos

- SDL2
- CMake
- C++11 ou superior
  
### Compilando com CMake:

* Os arquivos .lib da SDL2 devem ser colocados na pasta 'lib/'
* Os arquivos .dll da SDL2 devem ser colocados na mesma pasta que o arquivo executável.

Para compilar utilizando **CMake**, considerando que os pré-requisitos foram cumpridos e você está utilizando um terminal com comandos linux (os comandos para o Windows são similares):

Para uma build de Debug:
```bash
mkdir build/ && cd build/
cmake -B./ -S ../ -DCMAKE_BUILD_TYPE=Debug
make
```
Para uma build de Release:
```bash
mkdir build/ && cd build/
cmake -B./ -S../ -DCMAKE_BUILD_TYPE=Release
make
```

