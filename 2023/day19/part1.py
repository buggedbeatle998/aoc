rules,parts={i.split("{")[0]:i.split("{")[1] for i in open("data.txt","r").read().split("\n\n")[0].splitlines()},open("data.txt","r").read().split("\n\n")[1].splitlines()
print(rules)