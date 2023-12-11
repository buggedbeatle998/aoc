data,tot,width=[[[n,1] for n in i] for i in open("data.txt","r").read().splitlines()],0,1000000
for i in range(len(data[0]))[::-1]:
    if all([False if data[n][i][0]=="#" else True for n in range(len(data))]):
        for n in range(len(data)): data[n][i][1]=width
for i in range(len(data))[::-1]:
    if not ["#",1] in data[i] and not ["#",width] in data[i]: data[i]=[[".",width]]*len(data[i])
for spos,source in [item for sublist in [[((x,y),(sum([data[y][xx][1] for xx in range(x)]),sum([data[yy][x][1] for yy in range(y)]))) for x,i in enumerate(line) if i[0]=="#"] for y,line in enumerate(data) if ["#",1] in line or ["#",width] in line] for item in sublist]:
    data[spos[1]][spos[0]][0]="."
    for dpos,dest in [item for sublist in [[((x,y),(sum([data[y][xx][1] for xx in range(x)]),sum([data[yy][x][1] for yy in range(y)]))) for x,i in enumerate(line) if i[0]=="#"] for y,line in enumerate(data) if ["#",1] in line or ["#",width] in line] for item in sublist]: tot+=(abs(source[0]-dest[0])+abs(source[1]-dest[1])) if source!=[] and dest!=[] else 0
print(tot)