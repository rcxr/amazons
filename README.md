# amazons

My MAT564 Combinatorial Game Theory final project

# Features
- Optimal play for tree of height three or less.
- Scope
- Max/Min
- Mix/Max
- Board
  - 10x10
  - Values: blank (0), black (1), white (2), void(3)
  - Coordinate system: (row, column), values from 0 to 9, (0, 0) is the top left corner
- Move
  - Player (1 or 2)
  - Start (r, c)
  - End (r, c)
  - Target (r, c)
  - Previous state
  - Current state
- APIs
  - bool validateMove(move)
  - move nextMove(board, player)
  - vector<move> listMoves(board, player)
- Input
  - \*.txt
- Conway notation
- JavaScript UI
