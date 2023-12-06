seeds=[([int(open("data.txt","r").read().splitlines()[0].split(" ")[1::2][i]),int(open("data.txt","r").read().splitlines()[0].split(" ")[1::2][i])+int(open("data.txt","r").read().splitlines()[0].split(" ")[2::2][i])]) for i in range(int(len(open("data.txt","r").read().splitlines()[0].split(" ")[1:])/2))]
for section in open("data.txt","r").read().split(":")[2:]:
    i=0
    other=[]
    while True:
        if i>=len(seeds): seeds+=other;break
        for dest,source,ran in [(int(k) for k in n.split(" ")) for n in (section.split("\n")[:-2] if (section.splitlines()[-1][-1].isalpha()) else section.split("\n"))][1:]:
            if source > seeds[i][0] and source < seeds[i][1]:
                other.append([source+(dest-source if (source+ran>=seeds[i][1]) else 0),seeds[i][1]+(dest-source if (source+ran>=seeds[i][1]) else 0)])
                seeds[i][1]=source
                if source+ran<other[-1][1] and source+ran>other[-1][0]:
                    seeds.append([source+ran,other[-1][1]])
                    other[-1]=[dest,dest+ran]
                break
            elif source+ran<seeds[i][1] and source+ran>seeds[i][0]:
                other.append([seeds[i][0]+(dest-source),dest+ran])
                seeds[i][0]=source+ran
                break
            elif source<=seeds[i][0] and source+ran>=seeds[i][1]:
                seeds[i]=[seeds[i][0]-source+dest,seeds[i][1]-source+dest];break
        i+=1
print(min(seeds))
"""answer = 12403039
seeds=sorted([([int(open("data.txt","r").read().splitlines()[0].split(" ")[1::2][i]),int(open("data.txt","r").read().splitlines()[0].split(" ")[1::2][i])+int(open("data.txt","r").read().splitlines()[0].split(" ")[2::2][i])]) for i in range(int(len(open("data.txt","r").read().splitlines()[0].split(" ")[1:])/2))])
while True:
    answered=answer
    for section in open("data.txt","r").read().split(":")[:1:-1]:
        for n in section.splitlines()[(section.splitlines()[0]==""):(len(section.splitlines())-2*(not section.splitlines()[0]==""))]:
            dest,source,ran=n.split()
            if answered>=int(dest) and answered<int(dest)+int(ran):answered+=int(source)-int(dest);break
    for seed in seeds:
        if answered>=seed[0] and answered<seed[1]:
            answered=-5
    if answered==-5: break
    answer+=1
print(answer)"""