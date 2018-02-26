"""
Pseudocode for broadcast operation using only
point-to-point operations.

Note that the elif statement triggers before the
if statement for every process except for process 0.
"""

for d = 0->D-1:
    dest = bitflip(rank,d) #send or recieve destination
    if (rank < 2^d): #if rank is less than 2^d we send to dest
        send(dest)
    elif (rank < 2^(d+1)): #elif rank is less than 2^(d+1) we recieve.
        recieve(dest)
