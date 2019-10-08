from math import sqrt

estimates = []

k = 20

try:

    while True:

        # total += int(input())
        estimates.append(int(input()))

except Exception:

    mean = sum(estimates)/len(estimates)
    n = len(estimates)/k
    # var = sqrt(sum([(e-mean)**2 for e in estimates])/(len(estimates)-1))
    var = 3*sqrt(sum([(e-mean)**2 for e in estimates])/(k*(n-1)))/sqrt(n)
    print(mean, var)
