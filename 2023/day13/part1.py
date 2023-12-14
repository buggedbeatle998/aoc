tot=0
for section in [i.splitlines() for i in open("data.txt","r").read().split("\n\n")]:
    for y in range(1,len(section)):
        if section[max(0,y-(len(section)-y)):y]==section[y:min(len(section),y*2):][::-1]: tot+=y*100;break
    else:
        for x in range(1,len(section[0])):
            if [i[max(0,x-(len(section[0])-x)):x] for i in section]==[i[x:min(len(section[0]),x*2)][::-1] for i in section]: tot+=x;break
print(tot)