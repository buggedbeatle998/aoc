answer,answered,seeds = 12403039,12403039,sorted([([int(open("data.txt","r").read().splitlines()[0].split(" ")[1::2][i]),int(open("data.txt","r").read().splitlines()[0].split(" ")[1::2][i])+int(open("data.txt","r").read().splitlines()[0].split(" ")[2::2][i])]) for i in range(int(len(open("data.txt","r").read().splitlines()[0].split(" ")[1:])/2))])
while answered>=0:
    for section in open("data.txt","r").read().split(":")[:1:-1]:
        for n in section.splitlines()[(section.splitlines()[0]==""):(len(section.splitlines())-2*(not section.splitlines()[0]==""))]:
            dest,source,ran=n.split()
            if answered>=int(dest) and answered<int(dest)+int(ran):answered+=int(source)-int(dest);break
    for seed in seeds:
        if answered>=seed[0] and answered<seed[1]: answered=-5
    answered,answer=answer+1,answer+1
print(answer)