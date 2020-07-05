from typing import List
from collections import defaultdict, deque


class Solution:
    def findLadders(self, beginWord: str, endWord: str, wordList: List[str]) -> List[List[str]]:
        if endWord not in wordList or beginWord == endWord or not wordList:
            return []
        length = len(beginWord)

        # creat defaultdict
        d = defaultdict(list)
        for word in wordList:
            for i in range(length):
                d[word[:i] + '*' + word[i + 1:]].append(word)

        # BFS
        # shortest path
        queue = deque([(beginWord, [beginWord])])
        visited = set(beginWord)
        res = []

        while queue and not res:
            size = len(queue)
            local_visited = set()

            for _ in range(size):
                current_word, path = queue.popleft()
                for i in range(length):
                    intermediate_word = current_word[:i] + '*' + current_word[i + 1:]
                    for next_word in d[intermediate_word]:
                        if next_word == endWord:
                            res.append(path + [next_word])
                        if next_word not in visited:
                            local_visited.add(next_word)
                            queue.append((next_word, path + [next_word]))
            visited = visited.union(local_visited)
        return res