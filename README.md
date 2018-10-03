# Montador e Ligador

Projeto 1 da disciplina **Software Básico (2018.2)** na Universidade de Brasília.
O projeto consiste em desenvolver um montador e um ligador para o *Assembly* fictício que é utilizado na disciplina.

### 1. Alunos
|Nome|Matrícula|
|--|--|
|Hugo Nascimento Fonseca (@Hugo-NF)|16/0008166|
|José Luiz Gomes Nogueira (@01oseluiz)|16/0032458|

### 2. Ambiente de desenvolvimento
- Linguagem: C++ 14
- Sistemas operacionais testados: Ubuntu 16.04, Ubuntu 17.10, Windows 10
- Compiladores: Ubuntu = g++ 5.4.0, Windows =


### 3. Instruções de compilação

    cmake CMakeLists.txt
    make
- Após isso, os executáveis *montador* e *ligador* serão criados
- Caso o Makefile já esteja presente no diretório, o primeiro comando é dispensável

### 4. Utilização e flags disponíveis

    ./montador myfile1.asm myfile2.asm myfileN.asm
    ./ligador myfile1.obj myfile2.obj myfileN.obj


- -pre : grava em arquivo a saída do pré-processamento
- -c : gera o arquivo objeto
- -o : gera o executável (monta e chama o ligador em seguida)

* Por padrão, a montagem ocorre com a opção -c