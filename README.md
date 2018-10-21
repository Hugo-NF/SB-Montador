# Montador e Ligador

Projeto 1 da disciplina **Software Básico (2018.2)** na Universidade de Brasília.
O projeto consiste em desenvolver um montador e um ligador para o *Assembly* fictício que é utilizado na disciplina.

### 1. Alunos
|Nome|Matrícula|
|--|--|
|Hugo Nascimento Fonseca (@Hugo-NF)|16/0008166|
|José Luiz Gomes Nogueira (@01oseluiz)|16/0032458|

### 2. Ambiente e ferramentas de desenvolvimento
- Linguagem: C++ 14
- Sistemas operacionais testados: Ubuntu 18.04 (g++ 7.3.0), Windows 10.0.17134.345 (g++ 5.3.0) 
- CMake: 3.10 ou superior
- Valgrind: 3.13.0


### 3. Instruções de compilação

    cmake CMakeLists.txt
    make
- Após isso, os executáveis *montador* e *ligador* serão criados
- Caso o Makefile já esteja presente no diretório, o primeiro comando é dispensável

### 4. Utilização e flags disponíveis

    ./montador (optional flags) myfile1 myfile2 ... myfileN
    ./ligador myfile1 myfile2 ... myfileN


- -h    : abre o menu de ajuda
- -pre  : grava em arquivo a saída do pré-processamento
- -c    : gera o arquivo objeto
- -o    : gera o executável (monta e chama o ligador em seguida)

* Por padrão, a montagem ocorre com a opção -c
* Os arquivos são assumidos com as seguintes extensões:
    * Código-fonte:     .asm
    * Pré-processado:   .pre
    * Código objeto:    .obj
    * Executável:       .e
* Os simuladores fornecidos na disciplina estão no diretório /docs