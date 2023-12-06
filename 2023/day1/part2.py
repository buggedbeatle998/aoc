import functools,num2words
tot=0
for i in functools.reduce(lambda a, kv: a.replace(num2words.num2words(kv),num2words.num2words(kv)+str(kv)+num2words.num2words(kv)), range(10), open("data.txt","r").read()).splitlines():
    for k in range(10,0,-9):
        for n in i:
            if n.isdigit(): tot+=int(n)*k;break
        i=i[::-1]
print(tot)