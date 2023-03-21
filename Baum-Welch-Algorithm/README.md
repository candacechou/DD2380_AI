##  Baum-Welch Algorithm

This is the practice of Baum-Welch Algorithm with more empirical investigations.

### Input
You will be given the test files (hmm_c_N1000.in and hmm_c_N10000.in) that contains a data sequence (T = 1000, 10000) generated from the following HMM dynamics:

A = [[0.7 0.05 0.25],[0.1 0.8 0.1],[0.2 0.3 0.5]]

B = [[0.7 0.2 0.1 0],[0.1 0.4 0.3 0.2],[0 0.1 0.2 0.7]]

pi = [1 0 0]

### Expected Output

### Compile

please run 

```
g++ -o main.out main.cpp
```

This will compile and return an execution file `main.out`

### Test

please run

```
main.out<sample.in
```

The result should be shown on the terminal.
