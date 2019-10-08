from matplotlib import pyplot as plt
import numpy as np

algos = []
algo_ix = {}

vals_x = []
vals_y = []

try:

    while True:

        line = input()
        fname, val = line.split()
        algo, _, S, A = fname.rstrip(".txt").split("-")

        S = int(S)
        A = int(A)
        # B = int(B)
        val = float(val)

        if algo not in algo_ix:

            algo_ix[algo] = len(algos)
            algos.append(algo)
            vals_x.append([])
            vals_y.append([])

        vals_x[algo_ix[algo]].append(S)
        vals_y[algo_ix[algo]].append(val)


except EOFError:

    pass

legendmap = {
    "greedyStateGreedyActionPI": "Greedy Howard's",
    "greedyStateRandomActionPI": "Randomised Howard's",
    "randomStateGreedyActionPI": "Greedy Mansour and Singh's",
    "randomStateRandomActionPI": "Randomised Mansour and Singh's",
    "randomPolicyPI": "Uniformly Randomised",
    "batchStateGreedyActionPI": "Batched Greedy Howard's",
    "batchStateRandomActionPI": "Batched Randomised Howard's",

    "batchRandomPolicyPI": "Batched Uniformly Randomised",
    "batchRandomStateGreedyActionPI": "Batched Greedy Mansour and Singh's",
    "batchRandomStateRandomActionPI": "Batched Randomised Mansour and Singh's",

}

fig, ax = plt.subplots()

for i, algo in enumerate(algos):

    x, y = list(zip(*sorted(zip(vals_x[i], vals_y[i]))))
    print(algo)
    # if algo.startswith("batch"):
    #     continue
    # y = list(y)
    # for i in range(1, len(y)):
    #     y[i] = max(y[i - 1], y[i])
    # y = tuple(y)
    # ax.plot(x, y, label=algo)
    ax.plot(x, y, label=legendmap[algo])

leg = plt.legend(framealpha=0.5, loc="upper left")
# plt.xscale("log", basex=2)

# for lh in leg.legendHandles:
#     lh._legmarker.set_alpha(10)

# plt.show()
inp = "variation-with-n"
plt.savefig(inp + ".png", bbox_inches='tight', dpi=400)
plt.savefig(inp + ".pdf", bbox_inches='tight', dpi=400)
print(inp)
# plt.show()
