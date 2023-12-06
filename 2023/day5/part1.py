seeds=open("data.txt","r").read().splitlines()[0].split(" ")[1:]
for section in open("data.txt","r").read().split(":")[2:]:
    temp,seeds=(([[(abs(int(seed))-int(nums.split(" ")[1])+int(nums.split(" ")[0]) if (abs(int(seed))>=int(nums.split(" ")[1]) and abs(int(seed))<int(nums.split(" ")[1])+int(nums.split(" ")[2])) else -abs(int(seed)))for seed in seeds] for nums in (section.splitlines()[1:-2] if (section.splitlines()[-1][-1].isalpha()) else section.splitlines()[1:])])),[]
    for i in range(len(temp[0])): seeds.append(max(n[i] for n in temp))
print(min(abs(i) for i in seeds))