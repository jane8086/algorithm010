from typing import List
import string


class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        if not beginWord or not endWord or not wordList or endWord not in wordList:
            return 0

        front = {beginWord}
        back = {endWord}
        dist = 1
        word_len = len(beginWord)
        wordList = set(wordList)

        while front:
            next_front = set()
            dist += 1
            for word in front:
                for i in range(word_len):
                    for c in string.ascii_lowercase:
                        new_front = word[:i] + c + word[i + 1:]
                        if new_front in back:
                            return dist
                        if new_front in wordList:
                            next_front.add(new_front)
                            wordList.remove(new_front)
            front = next_front
            if len(front) < len(back):
                front, back = back, front

        return 0
