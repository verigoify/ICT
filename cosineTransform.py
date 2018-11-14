from math import *

def discreteCosineTransform(inputSignal):
    N = len(inputSignal)
    outputSignal = []
    for k in range(N):
        if k == 0:
            outputSignal.append(sum(inputSignal)/sqrt(N))
        else:
            g = []
            for m in range(N):
                g.append(inputSignal[m]*cos(pi*k*(2*m+1)/(2*N)))
            outputSignal.append(sqrt(2/N)*sum(g))
    return outputSignal


def inverseDiscreteCosineTransform(inputSignal):
    N = len(inputSignal)
    outputSignal = []
    G0 = inputSignal[0]/(sqrt(N))
    for m in range(N):
        g = []
        for k in range(1, N):
            g.append(inputSignal[k]*cos(pi*k*(2*m+1)/(2*N)))
        outputSignal.append(sqrt(2/N)*sum(g) + G0)
    return outputSignal

