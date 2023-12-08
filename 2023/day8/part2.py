import re,math
dirs,mapped,place,tot,mults=open("data.txt","r").read().splitlines()[0],{},re.findall(r"(..A) =",open("data.txt","r").read()),0,[]
for i in open("data.txt","r").read().splitlines()[2:]: mapped.update({re.findall(r"\w{3}",i)[0]:re.findall(r"\w{3}",i)[1:]})
while len(place)>0:
    for i in range(len(place)): place[i]=mapped[place[i]][dirs[tot%len(dirs)]=="R"]
    tot+=1
    for i in range(len(place)):
        if i>=len(place): break
        if place[i][-1]=="Z": mults.append(tot);place.pop(i)
print(math.lcm(*mults))