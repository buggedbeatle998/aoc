data,data_moves,path={(x[0],y):line.strip()[x[0]] for x in enumerate(open("data.txt","r").read().splitlines()[0].strip()) for y, line in enumerate(open("data.txt","r").read().splitlines())},{(x[0],y):{".": [],"|": [(x[0], y - 1), (x[0], y + 1)],"-": [(x[0] - 1, y), (x[0] + 1, y)],"L": [(x[0], y - 1), (x[0] + 1, y)],"J": [(x[0] - 1, y), (x[0], y - 1)],"7": [(x[0] - 1, y), (x[0], y + 1)],"F": [(x[0] + 1, y), (x[0], y + 1)],"S": [(x[0] - 1, y), (x[0] + 1, y), (x[0], y - 1), (x[0], y + 1)]}[line.strip()[x[0]]] for x in enumerate(open("data.txt","r").read().splitlines()[0].strip()) for y, line in enumerate(open("data.txt","r").read().splitlines())},[[(x[0],y[0]) for x in enumerate(y[1]) if x[1]=="S"] for y in enumerate(open("data.txt","r").read().splitlines()) if "S" in y[1]][0]
while path[-1] != path[0] or len(path) < 2: path.append([i for i in data_moves[path[-1]] if (path[-1] in data_moves[i]) and ((i not in path) or (i == path[0] and len(path) > 2))][0])
print(len(path)//2)