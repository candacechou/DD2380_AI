## Next Observation Distribution

This is the practice of calculating next observation distribution of a hidden Markov Model.

### Input
Three matrices, in this order, will be provided:transition matrix, emission matrix, and initial state probability distribution. The initial state probability distribution is a row vector encoded as a matrix with only one row. Each matrix is given on a separate line with the number of rows and columns followed by the matrix elements (ordered row by row). 

The example input is stored in sample_00.in

### Expected Output

The emission probability distribution.
The example output answer is stored in sample_00.ans

### Compile

please run 

```
g++ -o main.out main.cpp
```

This will compile and return an execution file `main.out`

### Test

please run

```
main.out<sample_00.in
```

The result should be shown on the terminal.
