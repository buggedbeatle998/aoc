import re
dirs,mapped,place,tot=open("data.txt","r").read().splitlines()[0],{},re.findall(r"(..A) =",open("data.txt","r").read()),0
for i in open("data.txt","r").read().splitlines()[2:]: mapped.update({re.findall(r"\w{3}",i)[0]:re.findall(r"\w{3}",i)[1:]})
while True:
    for i in range(len(place)):
        place[i]=mapped[place[i]][dirs[tot%len(dirs)]=="R"]
    tot+=1
    if all([i[-1]=="Z" for i in place]): print(place)
print(tot)