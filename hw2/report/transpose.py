"""
Builds on broadcast function from previous part.

Broadcasts values such as to transpose y.

Performs cyclic shift on all rows of each column such that the diagonal value is on the first row

Processes are distributed on a square matrix [P x P]

Each process will posses its location as location(p) = (row,col)

"""

new_row = row - column

if new_row < 0:
    new_row = new_row + P

for d 0->D-1:
    #--------- Main change from last section-----
    if new < 2^d:
        dest = col + bitflip(new_row, d)

    if dest >= P:
        dest = dest - P
    #--------------------------------------------

    if (new_row < 2^d): #if row is less than 2^d we send to dest
        send(dest, column)
    elif (new_row < 2^(d+1)): #elif row is less than 2^(d+1) we recieve.
        recieve(dest, column)
