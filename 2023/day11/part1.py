data,tot=[[*i] for i in open("data.txt","r").read().splitlines()],0
for i in range(len(data[0]))[::-1]:
    if all([False if data[n][i]=="#" else True for n in range(len(data))]):
        for n in range(len(data)): data[n].insert(i,".")
for i in range(len(data))[::-1]:
    if not "#" in data[i]: data.insert(i,data[i])
for source in [[(x,y) for x,i in enumerate(line) if i=="#"][0] for y,line in enumerate(data) if "#" in line]:
    data[source[1]][source[0]]="@"
    for i in data:
        print(i)
    print()
    for dest in [[(x,y) for x,i in enumerate(line) if i=="#"][0] for y,line in enumerate(data) if "#" in line]: tot+=(abs(source[0]-dest[0])+abs(source[1]-dest[1])) if source!=[] and dest!=[] else 0
    data[source[1]][source[0]]="."
print(tot)