# EDC20_Team_A_star_strategy_part
This is the strategy board source code for the EDC20, THU championship team A_star, mainly implemented by Ziyi Wu and Urkax.  
This part includes receiving the information from the host computer, making decisions about path-planning, communicating between two boards and also wiFi-control bluetooth output, etc.  
See the detailed implementation of our code in the repository.  
## Details
wifiControl.h/c and Decode.h/c is about receiving messages from the host computer and decode them to get the correct information about scores, positions, etc. Output.h/c is the implementation of bluetooth communication. Core.h/c is mainly the decision-making part about which passenger to pick up and the nearest path to do so. urkax.h/c and main.h/c is actually the real core of our strategy board (not Core.h/c hhh), which decides when to call all the functions to do path-search and send the movement board the next position to go to.


