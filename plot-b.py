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
        # fname, val = line.split()
        algo, _, S, A, B = fname.rstrip(".txt").split("-")

        S = int(S)
        A = int(A)
        B = int(B)
        val = float(val)
        err = float(err)

        if algo not in algo_ix:

            algo_ix[algo] = len(algos)
            algos.append(algo)
            vals_x.append([])
            vals_y.append([])
            vals_err.append([])

        vals_x[algo_ix[algo]].append(B)
        vals_y[algo_ix[algo]].append(val)
        vals_err[algo_ix[algo]].append(err)


except EOFError:

    pass

legendmap = {
    "greedyStateGreedyActionPI": "Greedy Howard's",
    "greedyStateRandomActionPI": "Randomised Howard's",
    "randomStateGreedyActionPI": "Greedy Mansour and Singh's",
    "randomStateRandomActionPI": "Randomised Mansour and Singh's",
    "randomPolicyPI": "Uniformly Randomised",

    "batchStateRandomActionPI": "Batched Randomised Howard's",
    "batchRandomStateGreedyActionPI": "Batched Greedy Mansour and Singh's",
    "batchRandomStateRandomActionPI": "Batched Randomised Mansour and Singh's",

    "batchStateGreedyActionPI": "BSPI (HPI)",
    "batchRandomPolicyPI": "BSPI (RPI)",

}

fig, ax = plt.subplots()

for i, algo in enumerate(algos):

    x, y, err = list(zip(*sorted(zip(vals_x[i], vals_y[i], vals_err[i]))))
    # x, y = list(zip(*sorted(zip(vals_x[i], vals_y[i]))))
    print(algo)
    # if algo.startswith("batch"):
    #     continue
    if algo not in ["batchRandomPolicyPI", "batchStateGreedyActionPI"]:
        continue
    y = list(y)
    # for i in range(1, len(y)):
        # y[i] = y[i] + np.random.randn() / 10
        # y[i] = max(y[i - 1], y[i])
    y = tuple(y)
    # ax.plot(x, y, label=algo)
    # ax.plot(x, y, label=legendmap[algo])
    ax.errorbar(x, y, err, label=legendmap[algo], solid_capstyle='projecting', capsize=2)


leg = plt.legend(framealpha=0.5, loc="upper right")
# plt.xscale("log", basex=2)

# for lh in leg.legendHandles:
#     lh._legmarker.set_alpha(10)

# plt.show()
# inp = "variation-with-k-logscale"
# inp = "variation-with-k"
inp = "variation-with-b"
plt.savefig(inp + ".png", bbox_inches='tight', dpi=400)
plt.savefig(inp + ".pdf", bbox_inches='tight', dpi=400)
plt.savefig(inp + ".ps", bbox_inches='tight', dpi=400)
print(inp)
# plt.show()
