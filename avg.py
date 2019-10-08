from math import sqrt

estimates = []

try:

    while True:

        # total += int(input())
        estimates.append(int(input()))

except Exception:

    mean = sum(estimates)/len(estimates)
    # var = sqrt(sum([(e-mean)**2 for e in estimates])/(len(estimates)-1))
    var = sqrt(sum([(e-mean)**2 for e in estimates])/(len(estimates)-1))/sqrt(len(estimates))
    print(mean, var)
