import math
data=[" ".join(open("data.txt","r").read().split()).split(":")[1].split()[:-1]," ".join(open("data.txt","r").read().split()).split(":")[2].split()]
print(data)

def poo(r,t):
    return math.floor((-t+math.sqrt(t**2-(4*r)))/-2)-math.floor(((-t-math.sqrt(t**2-(4*r)))/-2)-0.000000000001)

print(abs(poo(9,7)))