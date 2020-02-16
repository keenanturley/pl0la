# PL/0 Lexical Analyzer - UCF COP3402 Project 2

## Authors

**Keenan Turley** <keenan.turley@knights.ucf.edu> and **Alexander Desmond** <alexdesmond@knights.ucf.edu>

## Introduction

This project is an implementation a lexical analyzer for the PL/0 programming language in C.

The specifications of the lexical analyzer are provided in `docs/specification.pdf`.

To compile or run, first navigate to directory src:

```sh
cd src
```

## Compiling

Using GNU make:

```sh
make
```

Using gcc:

```sh
gcc -o pl0la main.c list.c scanner.c token.c util.c
```

## Running

Using shell

```sh
./pl0la (file-path)
```

Where `file-path` is the path to the source file you want to analyze.

Note: Output is printed to stdout, which should be redirected if a test case output file is desired.

Errors are printed to stderr.

## To the TA

The requested test case output is located in `pl0la/tests/sample.out`.
