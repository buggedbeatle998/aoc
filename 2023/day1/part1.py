tot=0
for i in open("data.txt","r").read().splitlines():
    for k in [10,1]:
        for n in i:
            if n.isdigit(): tot+=int(n)*k;break
        i=i[::-1]
print(tot)


tot=0
for i in open("data.txt","r").read().splitlines():
    for n in i:
        if n.isdigit(): tot+=int(n)*10;break
    for n in i[::-1]:
        if n.isdigit(): tot+=int(n);break
print(tot)