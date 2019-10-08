from matplotlib import pyplot as plt
import numpy as np

import matplotlib
matplotlib.rcParams['pdf.fonttype'] = 42
matplotlib.rcParams['ps.fonttype'] = 42


plt.rcParams.update({'font.size': 15})

algos = []
algo_ix = {}

vals_x = []
vals_y = []
vals_err = []

try:

    while True:

        line = input()
        fname, val, err = line.split()
        algo, S, A = fname.rstrip(".txt").split("-")

        S = int(S)
        A = int(A)
        # B = int(B)
        val = float(val)
        err = float(err)

        if algo not in algo_ix:

            algo_ix[algo] = len(algos)
            algos.append(algo)
            vals_x.append([])
            vals_y.append([])
            vals_err.append([])

        vals_x[algo_ix[algo]].append(A)
        vals_y[algo_ix[algo]].append(val)
        vals_err[algo_ix[algo]].append(err)


except EOFError:

    pass

legendmap = {
    "greedyStateGreedyActionPI": "HPI (GQ)",
    # "greedyStateGreedyActionPI": "Greedy Howard's",
    "greedyStateRandomActionPI": "HPI-R",
    # "greedyStateRandomActionPI": "Randomised Howard's",
    "randomStateGreedyActionPI": "RPI (GQ)",
    # "randomStateGreedyActionPI": "Greedy Mansour and Singh's",
    "randomStateRandomActionPI": "RPI (UIA)",
    # "randomStateRandomActionPI": "Randomised Mansour and Singh's",
    "randomPolicyPI": "RPI-UIP",
    # "randomPolicyPI": "Uniformly Randomised",

    "batchStateGreedyActionPI": "Batched Greedy Howard's",
    "batchStateRandomActionPI": "Batched Randomised Howard's",
    "batchRandomPolicyPI": "Batched Uniformly Randomised",
    "batchRandomStateGreedyActionPI": "Batched Greedy Mansour and Singh's",
    "batchRandomStateRandomActionPI": "Batched Randomised Mansour and Singh's",

}

fig, ax = plt.subplots()
# fig, ax = plt.subplots(1,5)

for i, algo in enumerate(algos):

    x, y, err = list(zip(*sorted(zip(vals_x[i], vals_y[i], vals_err[i]))))
    print(algo)
    # if not algo.startswith("batch"):
    #     continue
    # y = list(y)
    # for i in range(1, len(y)):
    #     y[i] = max(y[i - 1], y[i])
    # y = tuple(y)
    # ax.plot(x, y, label=algo)
    # ax.plot(x, y, label=legendmap[algo])
    # ax.errorbar(x, y, err, label=legendmap[algo], capsize=3)
    ax.errorbar(x, y, err, label=legendmap[algo], solid_capstyle='round', capsize=2)
    # ax[i].legend(framealpha=0.5, loc="upper left")
leg = ax.legend(framealpha=0.5, loc="upper left")
plt.xscale("log", basex=2)

# for lh in leg.legendHandles:
#     lh._legmarker.set_alpha(10)

# plt.show()
inp = "variation-with-k-logscale"
# inp = "variation-with-k"
# inp = "variation-with-k-monotonized"
plt.savefig(inp + ".png", bbox_inches='tight', dpi=400)
plt.savefig(inp + ".pdf", bbox_inches='tight', dpi=400)
plt.savefig(inp + ".ps", bbox_inches='tight', dpi=400)
print(inp)
# plt.show()
