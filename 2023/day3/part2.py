import re,functools
tot,data,listed=0,open("data.txt","r").read(),re.findall(r"(\*)",open("data.txt","r").read())
for i in listed:
    temp,temped,data=(re.search("\\"+i,data).start()),[],data[:(re.search("\\"+i,data).start())]+"."+data[(re.search("\\"+i,data).start())+1:]
    for n in [-len(data.splitlines()[0])-1-1,-len(data.splitlines()[0])-1,-len(data.splitlines()[0])-1+1,-1,1,len(data.splitlines()[0])+1-1,len(data.splitlines()[0])+1,len(data.splitlines()[0])+1+1]:
        if data[temp+n].isdigit():
            temped.append(int((data[temp+n-2] if data[temp+n-1].isdigit() and data[temp+n-2].isdigit() else "")+(data[temp+n-1] if data[temp+n-1].isdigit() else "")+data[temp+n]+(data[temp+n+1] if data[temp+n+1].isdigit() else "")+(data[temp+n+2] if data[temp+n+1].isdigit() and data[temp+n+2].isdigit() else "")))
            data=data[:temp+n-(2 if data[temp+n-1].isdigit() else 1)]+("." if data[temp+n-1].isdigit() else "")+"..."+("." if data[temp+n+1].isdigit() else "")+data[temp+n+(3 if data[temp+n+1].isdigit() else 2):]
    tot+=((functools.reduce(lambda a,b:a*b,temped)) if len(temped)>1 else 0)
print(tot)