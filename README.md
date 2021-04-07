# WordSearch
- Project 1 for CSE31 Course at University of California, Merced
- Entire program is done in C
- How it works:
   - Program searches in 5 directions: Horizontal (Left to Right) , Vertical (top to bottom) , Vertical (bottom to top) , Diagonal (top left to bottom right) , Diagonal (bottom left to top right)
   - There are separate sub functions to search in these 5 directions
   - The grid of letters is starts off as all uppercase letters
   - The word bank is filled with the 50 states of the US and only the first letter is uppercase (keep this in mind during the character comparisons)
   - After a word is found in the grid, the letters in the grid that matched will be lowercased
   - When the program is done, it will print the original grid but with the appropriate loweercased letters 
