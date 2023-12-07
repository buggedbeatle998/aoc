import math
tot,data=1,["".join(open("data.txt","r").read().split(" ")).split(":")[1].split()[:-1],"".join(open("data.txt","r").read().split(" ")).split(":")[2].split()]
for i in range(len(data[0])):
    tot*=math.floor(((-int(data[0][i])-math.sqrt(int(data[0][i])**2-(4*int(data[1][i]))))/-2)-0.000000000001)-math.floor((-int(data[0][i])+math.sqrt(int(data[0][i])**2-(4*int(data[1][i]))))/-2)
print(tot)