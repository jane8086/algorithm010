from typing import List
from collections import defaultdict, deque


class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        if endWord not in wordList:
            return 0

        d = defaultdict(list)
        for word in wordList:
            for i in range(len(beginWord)):
                d[word[:i] + '*' + word[i + 1:]].append(word)

        queue = deque([(beginWord, 1)])
        visited = set(beginWord)

        while queue:
            current_word, level = queue.popleft()
            for i in range(len(beginWord)):
                intermediate_word = current_word[:i] + '*' + current_word[i + 1:]
                for word in d[intermediate_word]:
                    if word == endWord:
                        return level + 1
                    if word not in visited:
                        visited.add(word)
                        queue.append((word, level + 1))
        return 0