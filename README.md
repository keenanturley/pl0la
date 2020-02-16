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

## Notes To the TA

- The requested test case output is located in `pl0la/tests/sample.out`.

- Output is printed to stdout, which should be redirected if a test case output file is desired.

- Errors are printed to stderr after the source program printout and before the lexeme table printout.

- Due to the ambiguity of the specification, we took some liberties as to where things go and how some things output.

    - For example, the format of error output was not specified, so we made the decision to detect as many errors as possible and report them.

    - After printing the errors, we chose to still print the lexeme table and list, as to be transparent about the data, even though the specification makes no mention of that desired behavior.

    - When an error is encountered, the associated token is still added to the token table, using the nul symbol as its type, because it seemed like the most appropriate choice to us.

    - The name of the erroneous token is truncated to the maximum length
