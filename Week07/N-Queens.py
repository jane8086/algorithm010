from typing import List


class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        if n < 1:
            return []

        self.result = []
        self.cols = set();
        self.hill = set();
        self.dale = set()
        self.dfs(n, 0, [])
        return self._generate_result(n)

    def dfs(self, n, row, cur_state):
        # terminator
        if row == n:
            return self.result.append(cur_state)

        # process
        for col in range(n):
            if col in self.cols or row + col in self.hill or row - col in self.dale:
                continue
            # valid col
            print(f'col is {col}')

            self.cols.add(col)
            self.hill.add(row + col)
            self.dale.add(row - col)

            # drill down
            self.dfs(n, row + 1, cur_state + [col])

            # reverse 回溯部分
            print(f'col is {col}, self.cols is {self.cols}')
            self.cols.remove(col)
            self.hill.remove(row + col)
            self.dale.remove(row - col)
            # when recursion stopped by the for loop traversal in col
        return print(f'recursion stop, row is {row}, start reverse')

    def _generate_result(self, n):
        checkerboard = []
        for res in self.result:
            for i in res:
                checkerboard.append('.' * i + 'Q' + '.' * (n - i - 1))

        print(checkerboard)

        return [checkerboard[i:i + n] for i in range(0, len(checkerboard), n)]
