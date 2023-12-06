seeds=[([int(open("data.txt","r").read().splitlines()[0].split(" ")[1::2][i]),int(open("data.txt","r").read().splitlines()[0].split(" ")[1::2][i])+int(open("data.txt","r").read().splitlines()[0].split(" ")[2::2][i])]) for i in range(int(len(open("data.txt","r").read().splitlines()[0].split(" ")[1:])/2))]
for section in open("data.txt","r").read().split(":")[2:]:
    #temp,seeds=(([[(abs(int(seed))-int(nums.split(" ")[1])+int(nums.split(" ")[0]) if (abs(int(seed))>=int(nums.split(" ")[1]) and abs(int(seed))<int(nums.split(" ")[1])+int(nums.split(" ")[2])) else -abs(int(seed)))for seed in seeds] for nums in (section.splitlines()[1:-2] if (section.splitlines()[-1][-1].isalpha()) else section.splitlines()[1:])])),[]
    #for i in range(len(temp[0])): seeds.append(max(n[i] for n in temp))
    for dest,source,ran in [int(i) for i in (section.split()[:-2] if (section.splitlines()[-1][-1].isalpha()) else section.split())]:
        for i in range(len(seeds)):
            if source > seeds[i][0]:
                seeds.append([source,min(source+ran,seeds[i][0]+seeds[i][1])-source])
                seeds[i][1]=source-seeds[i][0]
            elif source+ran<=source-seeds[i][0]+seeds[i][1]:
                seeds.append([max(source,seeds[i][0]),source+ran-max(source,seeds[i][0])])
                seeds[i][0]=source
    print(seeds)