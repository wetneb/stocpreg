import os
import sys

dct = dict()

mainFolder = 'statistics'

for tagline in open(mainFolder+'/types.2'):
    lst = tagline.strip().split(' ')
    if len(lst) == 2:
        dct[lst[1]] = dict()

for folder in os.listdir(mainFolder+'/'):
    if os.path.isdir(mainFolder+'/'+folder):
        for wsj_file in os.listdir(mainFolder+'/'+folder):
            for line in open(mainFolder+'/'+folder+'/'+wsj_file, 'r'):
                line = line.strip()
                lst = line.split('\t')
                if len(lst) == 3:
                    word = lst[0]
                    tag = lst[1]
                    if tag in dct:
                        if word in dct[tag]:
                            dct[tag][word] += 1
                        else:
                            dct[tag][word] = 1


for tagline in open(mainFolder+'/types.2'):
    lst = tagline.strip().split(' ')
    if len(lst) == 2:
        items = dct[lst[1]].items()
        items.sort(key = lambda pair: pair[1], reverse=True)
        print lst[0] + '\t' + lst[1] + '\t' + str(items[:10])


