import re
tot=0
for i in open("data.txt","r"):
    tot+=max([eval(k) for k in re.findall(r"(\d+)(?=\sred)",i)])*max([eval(k) for k in re.findall(r"(\d+)(?=\sgreen)",i)])*max([eval(k) for k in re.findall(r"(\d+)(?=\sblue)",i)])
print(tot)