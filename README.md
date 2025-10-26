# Pangram Checker — Code Challenge 7 (C, cJSON)

A fast C program that reads **`list_of_1000_strings.json`** (array of strings), classifies each string as **NON_PANGRAM**, **PANGRAM**, or **PERFECT_PANGRAM**, and prints overall counts.

> **Verified sample result (from one run):**  
> Non Pangram: **819** · Pangram: **132** · Perfect Pangram: **49**

---

## Contents

- [Features](#features)
- [Repo Structure](#repo-structure)
- [Requirements](#requirements)
- [Build](#build)
- [Run](#run)
- [Expected Output](#expected-output)
- [How It Works](#how-it-works)
- [Design Notes & Edge Cases](#design-notes--edge-cases)
- [Testing Tips](#testing-tips)
- [Troubleshooting](#troubleshooting)
- [License](#license)

---

## Features

- Parses a JSON array of 1,000 strings and classifies each into one of three categories.
- **Case-insensitive**; ignores punctuation, digits, and symbols.
- Clear modular design: file I/O, JSON parsing, classification, and result reporting.
- Minimal dependencies (only [cJSON](https://github.com/DaveGamble/cJSON)).

## Repo Structure

```
.
├── main.c                  # Program entry point
├── pangram.c               # Core logic (I/O, parsing, classification, results)
├── pangram.h               # Public types & function prototypes (with Doxygen-style docs)
├── list_of_1000_strings.json  # Input dataset (array of strings)
└── Makefile                # Build and clean targets
```
Relevant implementation is in these files: fileciteturn0file0 fileciteturn0file1 fileciteturn0file2 fileciteturn0file3

## Requirements

- **C compiler** with C standard library (tested with `gcc`/`clang`).
- **cJSON** library and headers available to the compiler/linker.
  - If installed system-wide (e.g., via package manager), linking with `-lcjson` should work.

## Build

### Option 1 — Using the provided Makefile

```bash
make all
```

Clean artifacts:

```bash
make clean
```

### Option 2 — Direct `gcc`

```bash
gcc -Wall -Werror main.c pangram.c -lcjson -o pangram_checker
```

> If your cJSON is not in default include/lib paths, add include and library flags, e.g.:  
> `-I/path/to/cjson/include -L/path/to/cjson/lib -lcjson`

## Run

Place **`list_of_1000_strings.json`** in the same directory as the binary and run:

```bash
./pangram_checker
```

## Expected Output

Example console log (informational messages + summary table):

```
[open_list]: File was opened successfully
[pan_str_init]: Memory for the strings was allocated successfully
[pan_str_init]: Strings' properties were initialized successfully
[load_strings_into_array]: JSON strings were extracted and stored succesfully
[pangram_checking_parser]: Strings' letters where counted successfully
[pangram_checking_parser]: All strings recieved a category value successfully

====================================
               Results
====================================
Non Pangram strings: 819
Pangram strings: 132
Perfect Pangram strings: 49
====================================
```

## How It Works

1. **Read JSON** → `open_list()` reads the entire `list_of_1000_strings.json` into memory. fileciteturn0file0  
2. **Init** → `pan_str_init()` allocates an array of 1,000 `pan_string_t` items, zeroes letter counts, and sets default category. fileciteturn0file0 fileciteturn0file1  
3. **Parse JSON** → `load_strings_into_array()` parses the JSON array and copies each element into the array. fileciteturn0file0  
4. **Classify** → `pangram_checking_parser()` walks each string, lowercases chars, filters non-letters, maps `'a'..'z'` to `0..25` via `map_letter()`, increments counts, and sets category:  
   - **NON_PANGRAM**: at least one letter missing  
   - **PANGRAM**: all letters present, some > 1  
   - **PERFECT_PANGRAM**: each letter appears exactly once  
   fileciteturn0file0 fileciteturn0file1
5. **Report** → `print_results()` totals per-category counts and prints a summary. fileciteturn0file0  
6. **Lifecycle** → `main()` orchestrates the flow and frees all allocated memory. fileciteturn0file2

## Design Notes & Edge Cases

- **Alphabet scope**: Only ASCII letters `a–z` are considered. All other characters are ignored before mapping. This ensures punctuation/whitespace/digits and non-letter Unicode do not affect counts. fileciteturn0file0  
- **Case-insensitive**: Characters are normalized to lowercase using `tolower()` prior to classification. fileciteturn0file0  
- **Strict mapping**: `map_letter()` requires `isalpha()` to have been checked; otherwise the program exits with an error (defensive programming). fileciteturn0file0  
- **Fixed size**: The program expects **exactly 1,000** strings (`JSON_STR_NUM`). Adjust this constant in `pangram.h` if your dataset size differs. fileciteturn0file1

## Testing Tips

- Quickly validate logic with classic pangrams in the JSON (e.g., “The quick brown fox…”). The dataset already includes many canonical/near-canonical pangrams. fileciteturn0file3
- Try adding custom strings to `list_of_1000_strings.json` to exercise edge cases (empty strings, only punctuation, repeated single letter, etc.).
- For performance sanity checks, scale `JSON_STR_NUM` and the input file to larger values.

## Troubleshooting

- **Linker errors for cJSON**: Ensure `-lcjson` and proper include/library paths.  
- **Invalid JSON errors**: Verify `list_of_1000_strings.json` is a **JSON array of strings**. fileciteturn0file0  
- **Non-ASCII letters not counted**: By design, only English letters are mapped (`a–z`). Extend `map_letter()` and classification logic if you need locale-specific alphabets. fileciteturn0file0

## License

This project is for an educational coding challenge. Use, modify, and adapt as needed.
