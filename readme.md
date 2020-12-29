# Full Build

git-bash command line:
```
cmake -G "CodeBlocks - MinGW Makefiles" -S . -B build
cmake --build build --target all -- -j 3
```

# Full Test

git-bash command line:
```
cmake -G "CodeBlocks - MinGW Makefiles" -S . -B build
cmake --build build --target all -- -j 3
cmake --build build --target test -- -j 3
```

# Full Install

git-bash command line:
```
cmake -G "CodeBlocks - MinGW Makefiles" -S . -B build
cmake --build build --target all -- -j 3
cmake --build build --target test -- -j 3
cmake --build build --target install -- -j 3
```

##### Configure

git-bash command line:
```
cmake -G "CodeBlocks - MinGW Makefiles" -S . -B build
```

##### Clean

git-bash command line:
```
cmake --build build --target clean -- -j 3
```

##### Build

git-bash command line:
```
cmake --build build --target all -- -j 3
```

##### Test

git-bash command line:
```
cmake --build build --target test -- -j 3
```

##### Install

git-bash command line:
```
cmake --build build --target install -- -j 3
```
