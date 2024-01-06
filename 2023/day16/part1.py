import functools;tot,objects,lengths=[],{"/":{(0,1):[[-1,0]],(-1,0):[[0,1]],(0,-1):[[1,0]],(1,0):[[0,-1]]},"\\":{(0,1):[[1,0]],(-1,0):[[0,-1]],(0,-1):[[-1,0]],(1,0):[[0,1]]},"|":{(0,1):[[0,1]],(-1,0):[[0,1],[0,-1]],(0,-1):[[0,-1]],(1,0):[[0,-1],[0,1]]},"-":{(0,1):[[-1,0],[1,0]],(-1,0):[[-1,0]],(0,-1):[[1,0],[-1,0]],(1,0):[[1,0]]},".":{(0,1):[[0,1]],(-1,0):[[-1,0]],(0,-1):[[0,-1]],(1,0):[[1,0]]}},(len(open("data.txt","r").read().splitlines()[0]),len(open("data.txt","r").read().splitlines()))
for start in [[[[i,0],[0,1]] for i in range(lengths[0])]+[[[i,lengths[1]-1],[0,-1]] for i in range(lengths[0])]+[[[0,i],[1,0]] for i in range(lengths[1])]+[[[lengths[0]-1,i],[-1,0]] for i in range(lengths[1])]][0]:
    data,beams,prev,tot=functools.reduce(lambda a,b : a|b,[{(x,y):[val,False] for x,val in enumerate(line)} for y,line in enumerate(open("data.txt","r").read().splitlines())]),[start],[],tot+[0]
    beams[0][1],data[tuple(start[0])][1]=objects[data[(0,0)][0]][tuple(beams[0][1])][0],True
    while beams:
        for beam in beams:
            if (beam[0][0]+beam[1][0]>=0 and beam[0][1]+beam[1][1]>=0 and beam[0][0]+beam[1][0]<lengths[0] and beam[0][1]+beam[1][1]<lengths[1]) and not beam in prev: data[(beam[0][0]+beam[1][0],beam[0][1]+beam[1][1])][1],prev,beams=True,prev+[beam],beams+[[[beam[0][0]+beam[1][0],beam[0][1]+beam[1][1]],n] for n in objects[data[(beam[0][0]+beam[1][0],beam[0][1]+beam[1][1])][0]][tuple(beam[1])]]
            beams.remove(beam)
    for i in data: tot[-1]+=data[i][1]
print(max(tot))