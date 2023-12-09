import numpy,more_itertools
tot=0
for sequence in [[[eval(n) for n in i.split()]] for i in open("data.txt","r").read().splitlines()]:
    while not more_itertools.all_equal(sequence[-1]):
        sequence.append(list(numpy.diff(sequence[-1])))
    for i in range(len(sequence)-1):
        sequence[-(i+2)].insert(0,sequence[-(i+2)][0]-sequence[-(i+1)][0])
    tot+=sequence[0][0]
print(tot)