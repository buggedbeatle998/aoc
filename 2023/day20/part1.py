presses,modules,tot=[(i.strip(" "),False,"broadcaster") for i in open("data.txt","r").read().splitlines()[0].split("->")[1].split(",")],{i.split("->")[0][1:].strip(" "):[i[0],[k.strip(" ") for k in i.split("->")[1].split(",")],False if i[0]=="%" else {}] for i in open("data.txt","r").read().splitlines()[1:]},[0,0]
#while sum(tot)<=0 or any([modules[i][2] if type(modules[i][2])==type(True) else any([modules[i][2][n] for n in modules[i][2]]) for i in modules]):
tot[0]+=1
while presses:
    for dest,signal,source in presses.copy():
        presses.remove((dest,signal,source))
        tot[signal]+=1
        if dest in modules and modules[dest][0]=="&":
            modules[dest][2].__setitem__(source,signal)
            presses+=[(i,not all([modules[dest][2][n] for n in modules[dest][2]]),dest) for i in modules[dest][1] if dest in modules]
        elif dest in modules and not signal: presses,modules[dest][2]=presses+[(i,(not modules[dest][2]),dest) for i in modules[dest][1] if dest in modules],not modules[dest][2]
print(tot)