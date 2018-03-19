"""
Builds on broadcast function from previous part.

Broadcasts values such as to transpose y.

Performs cyclic shift on all rows of each column such that the diagonal value is on the first row

Processes are distributed on a square matrix [P x P]

Each process will posses its location as location(p) = (row,col)

"""

#--------- Main change from last section-----
new_row = row - column #shift rows in process: 1t_a
if new_row < 0: # 1t_a
    new_row = new_row + P #if row is negative we need to adjust with P for cyclic shift: 1t_a

for d 0->D-1:
    dest = col + bitflip(new_row, d) #shifted bitflip: 1t_a
    if dest >= P: #1t_a
        dest = dest - P #adjust for cyclic shift: 1t_a
#--------------------------------------------
    if (new_row < 2^d): #if row is less than 2^d we send to dest: 1t_a
        send(x, dest, column) #t_statup + wt_data
    elif (new_row < 2^(d+1)): #elif row is less than 2^(d+1) we recieve: 1t_a
        recieve(x, dest, column) #t_statup + wt_data

#total time: 3t_a + log(P)*(t_statup + wt_data + 5t_a)
