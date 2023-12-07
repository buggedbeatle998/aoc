import re
tot,counts,dict=0,[],{"2":2,"3":3,"4":4,"5":5,"6":6,"7":7,"8":8,"9":9,"T":10,"J":1,"Q":12,"K":13,"A":14}
for hand,bid in [i.split() for i in open("data.txt","r").read().splitlines()]:
    counted,cards,jokers=[],[],0
    for card in hand: counted,hand,cards,jokers=sorted(counted+[re.subn(card,"",hand)[1] if card!="J" else 0]),(re.subn(card,"",hand)[0]),cards+[dict[card]],(jokers+(1 if card=="J" else 0))
    counted[-1]+=jokers
    counts=sorted(counts+[sorted(counted)[::-1]+cards+[int(bid)]])
for i in range(len(counts)):
    tot+=counts[i][-1]*(i+1)
print(tot)