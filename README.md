# amzncpp

My MAT564 Combinatorial Game Theory final project

# Features
- Optimal play for tree of height three or less
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
  - \-.txt
- Conway notation
- JavaScript UI
  - Util
  - Load game
  - Print board to screen
  - Get a move

# Extra features
- Support for any board size (simply start your file with "-1 {width} {height}")
- User can play with left of right
- Input system supports invalid input, it asks multiple times until a valid input is provided
- Engine is able to identify disjoint games and list them
- In order to solve optimally for small games I implemented the concept of a canonical position, which is a position that has at least one amazon in the first row and column. A canonical position is mapped 1-1 to a number (i.e. the map function is reversible to go back to the position). Any position (whose amazons are fully contained in a 5x4 region) can be mapped to a canonical position by getting its canonical id, this mapping is n-1, as multiple positions can map to the same canonical id. In order to translate a position into a canonical id first you translate (0, 0) to the (minX, minY) of the position, then you pad with zeros up to the max supported size (5x4), and then you turn each tile into a digit of a base-3 number, each digit can be either 0, 1, or 2. The id will be the base-10 representation of this stream of digis. E.g.
Position:
0 0 0
0 0 2
0 1 1
After translating (0, 0) to (1, 1):
0 2
1 1
After padding with zeros to a 5x4 board:
0 2 0 0 0
1 1 0 0 0
0 0 0 0 0
0 0 0 0 0
This translates into the 1100020 (base-3)
Which is equivalent to 978 (base-10)
This id is equivalent to:
0 2
1 1
And:
0 0 0 2 0 0
0 0 1 1 0 0
Now that you know which canonical game this is, you can query for the best move to make using a pre-filled knowledge base (which I filled programmatically) :)
Note about the 5x4 limitation. I can extend this coverage by using arbitrary length numbers, right now I'm constrained to 20 base-3 digits (3^20 < 2^32 < 3^21), and I decided to use 4 and 5 as the dimensions. The caveat is that if the limitation changes, the knowledge base needs to be re-generated.

# TODO
