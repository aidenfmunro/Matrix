## Build

Create a virtual environment and install conan:

```
python3 -m venv .venv && source .venv/bin/activate && pip3 install conan
```

Install dependencies via conan:

```
conan install . --build=missing --output-folder=conan
```

Build the project:

```
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=./conan/conan_toolchain.cmake

cmake --build build
```

## Run tests

```
cd build
```

Unit tests:

```
./tests
```

Test from stdin:

```
./matrix
```
