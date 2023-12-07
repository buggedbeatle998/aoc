import re
tot,counts,dict=0,[],{"2":2,"3":3,"4":4,"5":5,"6":6,"7":7,"8":8,"9":9,"T":10,"J":11,"Q":12,"K":13,"A":14}
for hand,bid in [i.split() for i in open("data.txt","r").read().splitlines()]:
    counted,cards=[],[]
    for card in hand: counted,hand,cards=counted+[re.subn(card,"",hand)[1]],(re.subn(card,"",hand)[0]),cards+[dict[card]]
    counts=sorted(counts+[sorted(counted)[::-1]+cards+[int(bid)]])
for i in range(len(counts)):
    tot+=counts[i][-1]*(i+1)
print(tot)