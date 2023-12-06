import re
tot,data=0,open("data.txt","r").read()
for i in re.findall(r"([^\w\.\n])",data):
    temp,data=(re.search(r"([^\w\.\n])",data).start()),data[:re.search(r"([^\w\.\n])",data).start()]+"."+data[re.search(r"([^\w\.\n])",data).start()+1:]
    for n in [-len(data.splitlines()[0])-1-1,-len(data.splitlines()[0])-1,-len(data.splitlines()[0])-1+1,-1,1,len(data.splitlines()[0])+1-1,len(data.splitlines()[0])+1,len(data.splitlines()[0])+1+1]:
        if data[temp+n].isdigit():
            tot+=int((data[temp+n-2] if data[temp+n-1].isdigit() and data[temp+n-2].isdigit() else "")+(data[temp+n-1] if data[temp+n-1].isdigit() else "")+data[temp+n]+(data[temp+n+1] if data[temp+n+1].isdigit() else "")+(data[temp+n+2] if data[temp+n+1].isdigit() and data[temp+n+2].isdigit() else ""))
            data=data[:temp+n-(2 if data[temp+n-1].isdigit() else 1)]+("." if data[temp+n-1].isdigit() else "")+"..."+("." if data[temp+n+1].isdigit() else "")+data[temp+n+(3 if data[temp+n+1].isdigit() else 2):]
print(tot)