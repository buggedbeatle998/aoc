tot=[0]*len(open("data.txt","r").read().splitlines())
for i in open("data.txt","r").read().splitlines():
    num,sec1,sec2=int(i.rstrip().split(":")[0].strip(" ").split("d")[1]),i.rstrip().replace("  "," ").split(":")[1].split("|")[0][1:-1].split(" "),i.rstrip().replace("  "," ").split(":")[1].split("|")[1][1:].split(" ")
    for n in sec1:
        if n in sec2: tot[num-1]=tot[num-1]*2 if tot[num-1]>0 else 1;continue
print(sum(tot))