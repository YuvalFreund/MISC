
def game_start():
    print("Hello and welcome to TicTacToe!")
    player1=''
    while not (player1 == 'X' or player1 == 'O'):
        choice = input("Player 1, please choose either X or O: ")
        if choice == 'X' or choice == 'O':
            player1 = choice
            break
        else: 
            print("Illegal value. Please try again")
    if player1 == 'X':
    	player2 = 'O'
    	print("Player 1 is X and Player 2 is O. Let's play!")
    else:
    	print("Player 1 is O and Player 2 is X. Let's play!")
    return player1
def end_game(board,result):
	board_print(board)
	if result == player1:
		print("Player1 won!")
	elif result=='D':
		print("It's a draw!")
	else:
		print("Player2 won!")

def board_print(board):
    print(board[7]+"|"+board[8]+"|"+board[9])
    print(board[4]+"|"+board[5]+"|"+board[6])
    print(board[1]+"|"+board[2]+"|"+board[3])

def board_check(board):
    signs= ['X','O']
    for sign in signs:
        if (
            board[7]==sign and board[8]==sign and board[9]==sign or 
            board[4]==sign and board[5]==sign and board[6]==sign or 
            board[1]==sign and board[2]==sign and board[3]==sign or 
            board[3]==sign and board[5]==sign and board[7]==sign or 
            board[1]==sign and board[5]==sign and board[9]==sign or 
            board[9]==sign and board[6]==sign and board[3]==sign or 
            board[8]==sign and board[5]==sign and board[2]==sign or 
            board[7]==sign and board[4]==sign and board[1]==sign
        ):
                return sign
    return 'D'

def board_play(board):
	if move_count % 2 == 0:
		req = "Player1, choose where you want to put " + player1 +":"
		while True:
			try:
				choice = int(input(req))
			except ValueError:
				print("Please enter a number and not just random bullshit")
				continue
			if board[choice]==' ':
				board[choice] = player1
				break
			else:
				print("That place is not empty you cunt")
	else:
		req = "Player2, choose where you want to put " + player2 +":"
		while True:
			try:
				choice = int(input(req))
			except ValueError:
				print("Please enter a number and not just random bullshit")
				continue
			if board[choice]==' ':
				board[choice] = player2
				break
			else:
				print("That place is not empty you cunt")

board = ['#',' ',' ',' ',' ',' ',' ',' ',' ',' ']
result = 'D'
player1='X'
player2='O'
move_count = 0
player1 = game_start()
if player1==player2:
	player2='X'	
while result=='D' and move_count < 9:
	board_print(board)
	board_play(board)
	result = board_check(board)
	move_count+=1
end_game(board,result)
