# mc Compiler


# Prerequisites

- `time`, typically located at `/usr/bin/time`
- `flex` for generating the lexer
- `bison` for generating the parser
- `gcc`
- `meson`
- `build-essential`
- `cmake`
- `gcc-multilib`
- `pkg-config `
- `git`
- `google test` for running the unit tests (included build script requires cmake)
- `doxygen` for generating the documentation (already generated under /doc)
- `gcovr & lcov` for generating the coverage reports


## Docker
Two scripts are provided which can be used to build and start the a docker container. This container has already all necessary dependencies preinstalled:
- `./buildDocker.sh` Build the docker container which should be used for testing and compiling.
- `./startDocker.sh` Which spins up the docker container in interactive mode.


## Build instructions

First, generate the build directory.

    $ meson builddir
    $ cd builddir

Meson creates Ninja build files.
Let's build.

    $ ninja

## Unit Tests
Unit tests can be started with:

    $ ninja test

## Integration tests:
1. `cd scripts` (from project root)
2. `./run_IntegrationTests.sh` (make sure you have exec permissions)


## Generate documentation
This command will genereate the documentation and save it under /doc/doc

  `doxygen doxygen.config` (from project root)

## Generate coverage report
1. `meson builddir -Db_coverage=true` (from project root)
2. `cd builddir`
3. `ninja test`
4. `ninja coverage`

## Project structure
The following directory layout is used.

	mcc/
	├── app/                                # Each C file in this directory corresponds to one executable.
	│   ├── mc_ast_to_dot.c
	│   ├── mcc.c
	│   └── …
	├── docs/                               # Additional documentation goes here.
	│   └── …
	├── include/                            # All public headers live here, note the `mcc` subdirectory.
	│   └── mcc/
	│       ├── ast.h
	│       ├── ast_print.h
	│       ├── ast_visit.h
	│       ├── parser.h
	│       └── …
	├── src/                                # The actual implementation; may also contain private headers and so on.
	│   ├── ast.c
	│   ├── ast_print.c
	│   ├── ast_visit.c
	│   ├── parser.y
	│   ├── scanner.l
	│   └── …
	├── test/
	│   ├── integration/                    # Example inputs for integration testing.
	│   │   ├── fib/
	│   │   │   ├── fib.mc
	│   │   │   ├── fib.stdin.txt
	│   │   │   └── fib.stdout.txt
	│   │   └── …
	│   └── unit/                           # Unit tests, typically one file per unit.
	│       ├── parser_test.c
	│       └── …
	├── subprojects/																# Subprojects used for meson
	└── README.md


## Known Issues
- Currently the builddir must be called `builddir` because with have a strong reference (`#include "../builddir/mcc@sha/parser.tab.hh"`
) to from the parser generated file. (See `include/mcDriver/mcDriver.cpp`)
