## PROBABILITY OF THE OBSERVATION SEQUENCE

This is the practice of calculating the probability of the observation sequence. 
We can make use of the so called forward algorithm or $\alpha$-pass algorithm.

### Input
Three matrices will be provided: transition matrix, emission matrix, and initial state probability distribution followed by the number of emissions and the sequence of emissions itself.

The example input is stored in hmm2_01.in

### Expected Output
The output the probability of the given sequence as a single scalar
The example output answer is stored in hmm2_01.ans

### Compile

please run 

```
g++ -o main.out main.cpp
```

This will compile and return an execution file `main.out`

### Test

please run

```
main.out<hmm2_01.in
```

The result should be shown on the terminal.
