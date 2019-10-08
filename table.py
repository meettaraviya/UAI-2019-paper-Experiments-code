algos = []
algo_ix = {}

sas = []
sas_ix = {}

vals = {}

try:

    while True:

        line = input()
        fname, val = line.split()
        algo, _, S, A = fname.rstrip(".txt").split("-")

        if algo not in algo_ix:

            algo_ix[algo] = len(algos)
            algos.append(algo)

        if (S, A) not in sas_ix:

            sas_ix[(S, A)] = len(sas)
            sas.append((S, A))

        vals[(sas_ix[(S, A)], algo_ix[algo])] = "{:.2f}".format(float(val))

except EOFError:

    pass

header = " & ".join(["n", "k"] + algos) + "\\\\ \\hline \n"
out = header

for (S, A) in sas:
    i = sas_ix[(S, A)]
    row = [S, A] + [vals[(i, j)] for j in range(len(algos))]
    out += " & ".join(row) + "\\\\ \\hline \n"

print("c".join("|" * (len(algos) + 3)))
print()
print(out)
