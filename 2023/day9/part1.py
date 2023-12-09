import numpy
for seqence in [[eval(n) for n in i.split()] for i in open("data.txt","r").read().splitlines()]:
    print(seqence)
    print(numpy.diff(seqence))