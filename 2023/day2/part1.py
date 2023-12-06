import re, functools
tot=0
for i in open("data.txt","r"):
    if functools.reduce(lambda a, b : False if int(b)>a else a,re.findall(r"(\d+)(?=\sred)",i),12) and functools.reduce(lambda a, b : False if int(b)>a else a,re.findall(r"(\d+)(?=\sgreen)",i),13) and functools.reduce(lambda a, b : False if int(b)>a else a,re.findall(r"(\d+)(?=\sblue)",i),14):
        tot+=int(re.findall(r"Game\s(\d+)",i)[0])
print(tot)