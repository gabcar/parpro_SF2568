"""
Pseudocode for broadcast operation using only
point-to-point operations.

Note that the elif statement triggers before the
if statement for every process except for process 0.
"""

x; #allocate memory for x: 1t_a
for d = 0->D-1:
    dest = bitflip(rank,d) #send or recieve destination: 1t_a
    if (rank < 2^d): #if rank is less than 2^d we send to dest
        send(x, dest) # 1t_startup + w*t_data
    elif (rank < 2^(d+1)): #elif rank is less than 2^(d+1) we recieve: 1t_a
        recieve(x, dest) #overwrite x:  1t_startup + w*t_data

#total time: t_a + log(P)*(t_startup + w*t_data + 3t_a)
