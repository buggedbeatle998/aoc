cache={}
def count(line,stuff):
    cache[(line,stuff)]=cache[(line,stuff)] if (line,stuff) in cache else (1 if (line=="" and stuff==()) or (stuff==() and not "#" in line) else 0 if line=="" or stuff==() else (count(line[1:], stuff) if line[0] in ".?" else 0)+((count(line[stuff[0]+1:], stuff[1:]) if line[0] in "#?" and (stuff[0]<=len(line) and "." not in line[:stuff[0]] and (stuff[0]==len(line) or line[stuff[0]]!="#")) else 0)))
    return cache[(line,stuff)]
print(sum(count("?".join([line]*5),tuple(map(int,stuff.split(",")))*5) for line,stuff in [i.split() for i in open("data.txt","r").read().splitlines()]))