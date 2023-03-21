##  Baum-Welch Algorithm

This is the practice of Baum-Welch Algorithm.
we assumed that the HMM parameters were given during the practice time. However In a real world scenario, this will rarely be the case. Instead, the initial distribution and transition and observation matrices must be approximated with help of data samples. This can be done efficiently with help of the Baum-Welch algorithm.

### Input
Three matrices are provided: transition matrix, emission matrix, and initial state probability distribution followed by the number of emissions and the sequence of emissions itself. 

The example input is stored in hmm_c_N100.in, hmm4_01.in, hmm4_02.in, hmm4_03.in

### Expected Output
The program will output the estimated transition matrix and emission matrix
The example output answer is stored inhmm_c_N100.ans, hmm4_01.ans, hmm4_02.ans, hmm4_03.ans

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
