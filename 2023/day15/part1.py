import functools
print(sum([functools.reduce(lambda a,b: ((a+ord(b))*17)%256,[*i],0) for i in "rn".split(",")]))