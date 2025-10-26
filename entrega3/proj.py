import sys
from pulp import *

def resolver(input):
    # Parse de input

    linhas = input.strip().split("\n")

    n, m, t = map(int, linhas[0].split())

    if n == 0: return -1
    if n == 0: return -1
    if t == 0: return 0

    fabs =[]
    for i in range(1, n+1):
        fi, j, fmax = map(int, linhas[i].split())

        if fmax < 0: return -1
        if fmax == 0: continue

        fabs.append((fi,j,fmax))

    paises = []
    for i in range(n+1, n+m+1):
        j, pmax, pmin = map(int, linhas[i].split())

        if (pmin < 0 or pmax < 0): return -1
        if pmax == pmin == 0: continue

        paises.append((j,pmax,pmin))

    pedidos = []
    for i in range(n+m+1, n+m+t+1):
        l = list(map(int, linhas[i].split()))
        k = l[0] # Identificador crianca
        j = l[1]
        f_pedidos = l[2:]

        if f_pedidos.len == 0: continue

        pedidos.append((k,j,f_pedidos))

    # Problema

    problema = LpProblem("Brinquedos", LpMaximize)

    x = {
        (k, fi): LpVariable(f"x_{k}_{fi}", 0, 1, cat="Binary")
        for k, _, f_pedidos in pedidos for fi in f_pedidos
    }

    problema += lpSum(x[k, fi] for k, _, f_pedidos in pedidos for fi in f_pedidos)

    for k, _, f_pedidos in pedidos:
        problema += lpSum(x[k, fi] for fi in f_pedidos) <= 1

    for fi, _, fmax in fabs:
        problema += lpSum(x[k, fi] for k, _, f_pedidos in pedidos if fi in f_pedidos) <= fmax

    for j, pmax, pmin in paises:
        j_fabs = [fi for fi, pais, _ in fabs if j == pais]
        j_crian = [k for k, pais, _ in pedidos if j == pais]
        problema += lpSum(x[k, fi] for k, _, f_pedidos in pedidos if not (k in j_crian) for fi in f_pedidos if fi in j_fabs) <= pmax
        problema += lpSum(x[k, fi] for k, _, f_pedidos in pedidos if k in j_crian for fi in f_pedidos) >= pmin

    # Avaliar o resultado
    if problema.solve(GLPK_CMD(msg=False)) == 1:
        return int(value(problema.objective))
    else:
        return -1

input = sys.stdin.read()
print(resolver(input))