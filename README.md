# cs143b-project1

How to run (c++):
1. Compile `main.cpp` by the following command: `g++ -Wall src/main.cpp src/helpers.cpp src/operations.cpp -Iincludes -o a.out`.
2. Execute the object file by redirecting the submission test file as stdin and redirect the output to output.txt with: `./a.out < submission-input.txt > output.txt`.
3. Or exeute the object file with `./a.out` and use the following set instructions in the table below:

| Shell command | Function    |
|---------------|-------------|
| cr            | create()    |
| de <i>        | destroy(i)  |
| rq <r>        | request(r)  |
| rl <r>        | release(r)  |
| to            | timeout()   |
| in            | init()      |
