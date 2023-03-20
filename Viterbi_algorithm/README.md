## Viterbi Algorithm

Instead of assuming that any state has led to the current estimate,we only take the most likely predecessor into account. The most likely hidden state sequence can be valuable information when estimating the actual dynamics underlying our noisy observations. The problem is solved with the help of Viterbi Algorithm,

### Input
You will be given three matrices; transition matrix, emission matrix, and initial state probability distribution followed by the number of emissions and the sequence of emissions itself.

The example input is stored in hmm3_01.in

### Expected Output
The output the probability of the given sequence as a single scalar
The example output answer is stored in hmm3_01.ans

### Compile

please run 

```
g++ -o main.out main.cpp
```

This will compile and return an execution file `main.out`

### Test

please run

```
main.out<hmm3_01.in
```

The result should be shown on the terminal.