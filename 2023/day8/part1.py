import re
dirs,mapped,place,tot=open("data.txt","r").read().splitlines()[0],[re.findall(r"\w{3}",i) for i in open("data.txt","r").read().splitlines()[2:]],"AAA",0
while True:
    for i in mapped:
        if i[0]==place: place=i[1 if dirs[tot%len(dirs)]=="L" else 2];break;
    tot+=1
    if place=="ZZZ": break
print(tot)