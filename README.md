# lines-counter
Count the number of lines in directory tree with specific files extensions

## Why?

I was trying to count how many lines I've written while solving competitive programming problems.

## How to use it?

- Compile `main.cpp` file with `gcc` or any other compiler.
- Run the executable file with `FILE_NAME PATH EXT [EXT [EXT [...]]]`.
- `PATH` should be a directory path.
- `EXT` should be any file extension (without the dot `.`).

Example run:

```
$ g++ main.cpp -o main

$ ./main /home/aliosm/Repositories/CompetitiveProgramming cpp java
cpp extension:
Number of files: 1101
Number of lines: 47863

java extension:
Number of files: 1
Number of lines: 21

Total number of files is 1102
Total number of lines is 47884
```

## How it works?

When you run the compiled file and give it the `PATH` argument with some `EXT`'s, the code will open the directory in `PATH` and using `BFS` algorithm, it will try to reach all files that end with any `EXT` in the current directory and all other directories inside it.

## Contributing
Bug reports and pull requests are welcome on GitHub at https://github.com/AliOsm/lines-counter.

## License
The project is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
