"""seeds=[([int(open("data.txt","r").read().splitlines()[0].split(" ")[1::2][i]),int(open("data.txt","r").read().splitlines()[0].split(" ")[1::2][i])+int(open("data.txt","r").read().splitlines()[0].split(" ")[2::2][i])]) for i in range(int(len(open("data.txt","r").read().splitlines()[0].split(" ")[1:])/2))]
for section in open("data.txt","r").read().split(":")[2:]:
    for dest,source,ran in [(int(k) for k in n.split(" ")) for n in [i for i in (section.split("\n")[:-2] if (section.splitlines()[-1][-1].isalpha()) else section.split("\n"))][1:]]:
        for i in range(len(seeds)):
            if source > seeds[i][0] and source < seeds[i][1]:
                seeds.append([source+(dest-source if (source+ran>=seeds[i][1]) else 0),seeds[i][0]+seeds[i][1]+(dest-source if (source+ran>=seeds[i][1]) else 0)])
                seeds[i][1]=source
            elif source+ran<seeds[i][1] and source+ran>seeds[i][0]:
                seeds.append([seeds[i][0]+(dest-source if (source<=seeds[i][0]) else 0),source+ran+(dest-source if (source<=seeds[i][0]) else 0)])
                seeds[i][0]=source+ran
            elif source<=seeds[i][0] and source+ran>=seeds[i][1]: seeds[i]=[seeds[i][0]-source+dest,seeds[i][1]-source+dest]
    print(sorted(seeds))"""

answer = 46
seeds=[([int(open("data.txt","r").read().splitlines()[0].split(" ")[1::2][i]),int(open("data.txt","r").read().splitlines()[0].split(" ")[1::2][i])+int(open("data.txt","r").read().splitlines()[0].split(" ")[2::2][i])]) for i in range(int(len(open("data.txt","r").read().splitlines()[0].split(" ")[1:])/2))]
while True:
    answered=answer
    for section in open("data.txt","r").read().split(":")[:2:-1]:
        answer=answered
        for dest,source,ran in [(int(k) for k in n.split(" ")) for n in [i for i in (section.split("\n")[1:-2] if (section.splitlines()[-1][-1].isalpha()) else section.split("\n"))][1:]]:
            if answer>=dest and answer<dest+ran:
                answered=answer+source-dest
    for seed in seeds:
        if answered>=seed[0] and answered<seed[1]:
            break
    answer+=1
print(answered)