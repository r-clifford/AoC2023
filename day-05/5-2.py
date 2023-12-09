from typing import List
from collections import deque

class Map:
    def __init__(self, dst, src, length):
        self.dst = dst
        self.src = src
        self.length = length
    def __call__(self, start: int, end: int):
        offset = self.dst - self.src
        before = (start, min(end, self.src))
        within = (max(start, self.src)+offset, min(end, self.src + self.length) + offset)
        after = (max(start, self.src + self.length), end)
        unmapped = deque()
        mapped = deque()
        if (before[0] < before[1]):
            # keep trying to map
            unmapped.append(before)
        if (after[0] < after[1]):
            unmapped.append(after)
        if (within[0] < within[1]):
            mapped.append(within)
        return (unmapped, mapped)



class Mapping:
    def __init__(self, m: List[Map]):
        self.m = m.copy()
    def __call__(self, start: int, end: int)->deque[tuple[int,int]]:
        unmapped = deque([(start, end)])
        mapped = deque()
      
        for m in self.m:
            if len(unmapped) <= 0:
                break
            item = unmapped.pop()  
            (u, m) = m(item[0], item[1])
            unmapped.extend(u)
            mapped.extend(m)
        unmapped.extend(mapped)
        return unmapped

def parseLine(line: str):
    s = line.split()
    try:
        dst = int(s[0])
        src = int(s[1])
        length = int(s[2])
        return Map(dst, src, length)
    except Exception:
        return None

def parseSeeds(s: str) -> list[tuple[int,int]]:
    seeds = []
    tmp = s.split()[1:]
    for i in range(0, len(tmp), 2):
        start = int(tmp[i])
        end = start + int(tmp[i + 1])
        seeds.append((start, end))
    return seeds

levels = []
with open("5.txt") as f:
    seedLine = f.readline()
    f.readline()
    seeds = parseSeeds(seedLine)
    mappings: list[Mapping] = []
    current = []
    lines = f.readlines()
    lines.append("\n")
    for line in lines:
        if (line == "\n"):
            mappings.append(Mapping(current))
            current.clear()
        else:
            tmp = parseLine(line)
            if (tmp):
                current.append(tmp)
    result = []
    for seed in seeds:
        src = deque([seed])
        for mapping in mappings:
            next = deque()
            for item in src:
                next.extend(mapping(item[0], item[1]))
            src = next
            # print(src)
        result.append(min([i[0] for i in src]))
    print(min(result)) # 100165128