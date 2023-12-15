from functools import reduce
data,boxes=[(i[:-1] if i[-1:]=="-" else i[:-2],"-" if i[-1:]=="-" else "=","" if i[-1:]=="-" else i[-1:]) for i in open("data.csv","r").read().split(",")],[[] for _ in range(256)]
for label,action,flength in data:
    hashmap=(reduce(lambda a,b: ((a+ord(b))*17)%256,[*label],0))%256
    if action=="-": boxes[hashmap]=[i for i in boxes[hashmap] if i[0]!=label]
    elif any([i[0]==label for i in boxes[hashmap]]): boxes[hashmap]=[i if i[0]!=label else [i[0],flength] for i in boxes[hashmap]]
    else: boxes[hashmap]+=[[label,flength]]
print(sum([sum([(n+1)*int(vals2[1]) for n,vals2 in enumerate(vals)])*(i+1) for i,vals in enumerate(boxes)]))