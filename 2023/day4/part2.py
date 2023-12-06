cards,file,fileorig=[1]*(len(open("data.txt","r").read().splitlines())),open("data.txt","r").read().splitlines(),open("data.txt","r").read().splitlines()
for i in file:
    t,num,sec1,sec2=0,int(i.rstrip().split(":")[0].strip(" ").split("d")[1]),i.rstrip().replace("  "," ").split(":")[1].split("|")[0][1:-1].split(" "),i.rstrip().replace("  "," ").split(":")[1].split("|")[1][1:].split(" ")
    for n in sec1:
        if n in sec2:
            if len(cards)>num+t: cards[num+t]+=1*cards[num-1]
            t+=1;continue
print(sum(cards))