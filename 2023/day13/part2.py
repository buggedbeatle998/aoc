tot=0
for section in [i.splitlines() for i in open("data.txt","r").read().split("\n\n")]:
    for y in range(1,len(section)):
        if len([item for sublist in [[n for n in range(len(section[0])) if section[max(0,y-(len(section)-y)):y][i][n]!=section[y:min(len(section),y*2):][::-1][i][n]] for i in range(y-max(0,y-(len(section)-y)))] for item in sublist])==1: tot+=y*100;break
    else:
        for x in range(1,len(section[0])):
            if len([item for sublist in [[n for n in range(len(section[0][max(0,x-(len(section[0])-x)):x])) if [k[max(0,x-(len(section[0])-x)):x] for k in section][i][n]!=[k[x:min(len(section[0]),x*2):][::-1] for k in section][i][n]] for i in range(len(section))] for item in sublist])==1: tot+=x;break
print(tot)