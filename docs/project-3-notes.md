# Project 3 Modifications

## Token types

Since `call`, `proc`, and `else` are not included in the project 3 language specification, they are not allowed to be used.

As per the professor, if we include references to these symbols anywhere in the source code of the project we will receive an automatic 0.

Therefore, we have to modify the `token_type` enum to omit these, and remove other instances of these words in all source files.
