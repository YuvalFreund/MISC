import random
from IPython.display import clear_output
class Player:
    def __init__(self,Hand=[], name='Player1', chips=0):
        self.name = name
        self.chips = chips
        self.Hand = []
    def empty_Hand(self):
        self.Hand = []
    def decChips(self, new_chips):
        self.chips -= new_chips
    def getChips (self):
        return self.chips
    def addChips(self, new_chips):
        self.chips += new_chips
    def  addCard(self,new_card):
        self.Hand.append(new_card)
    def printHand(self):
        for card in self.Hand:
            card_print(card)
    def sumCards (self):
        total= 0
        for card in self.Hand:
            value = card[0]
            if value == 'J' or value == 'Q' or value == 'K':
                value = 10
            total += value
        return total
    def __str__(self):
        return "Player's name: " + self.name  + "\nPlayer's chips count: " + str(self.chips)
    def cardCheck(self, card):
        return card in self.Hand
def card_print(card):
    print(" _________")
    spaces_num = int((10-len(card[1])) / 2)
    spaces_name= " "*spaces_num
    spaces_value = " "*4
    ten_value = " "*3
    print("|" + spaces_name + card[1] + spaces_name + "|")
    if card[0] != 10: 
        print("|" + spaces_value + str(card[0]) + spaces_value + "|")
    else:
        print("|" + spaces_value + str(card[0]) + ten_value + "|")
    print("|_________|")
def reset_deck(deck):
    for card in deck:
        card[2]=False

cardDeck = [[1,'Diamond',False],[2,'Diamond',False],[3,'Diamond',False],[4,'Diamond',False],[5,'Diamond',False],[6,'Diamond',False],[7,'Diamond',False],[8,'Diamond',False],[9,'Diamond',False],[10,'Diamond',False],['J','Diamond',False],['Q','Diamond',False],['K','Diamond',False],
            [1,'Spade',False],[2,'Spade',False],[3,'Spade',False],[4,'Spade',False],[5,'Spade',False],[6,'Spade',False],[7,'Spade',False],[8,'Spade',False],[9,'Spade',False],[10,'Spade',False],['J','Spade',False],['Q','Spade',False],['K','Spade',False],
            [1,'Heart',False],[2,'Heart',False],[3,'Heart',False],[4,'Heart',False],[5,'Heart',False],[6,'Heart',False],[7,'Heart',False],[8,'Heart',False],[9,'Heart',False],[10,'Heart',False],['J','Heart',False],['Q','Heart',False],['K','Heart',False],
            [1,'Clubs',False],[2,'Clubs',False],[3,'Clubs',False],[4,'Clubs',False],[5,'Clubs',False],[6,'Clubs',False],[7,'Clubs',False],[8,'Clubs',False],[9,'Clubs',False],[10,'Clubs',False],['J','Clubs',False],['Q','Clubs',False],['K','Clubs',False]]
Dealer = Player([],'Dealer',10000)
Player_name = input("Hello and welcome to BlackJack! What's your name? ")
req = "With how many chips would you like to start? "
req2 = "How many chips would you like to bet? "
round_num = 0
keep_playing = 'Y'
while keep_playing:
    try:
        player_starting_chips = int(input(req))
    except ValueError:
        print("Illegal value. Please enter a positive number:")
        continue
    if player_starting_chips > 0:
        break
    else:
        print("Illegal value. Please enter a positive number:")
player1 = Player([],Player_name,player_starting_chips)
while (player1.getChips() > 0 and keep_playing=='Y'):
    round_num += 1
    print("Round " + str(round_num) + ":")
    print(player1)
    round_bet = 0
    while True:
        try:
            round_bet = int(input(req2))
        except ValueError:
            print("Illegal value. Please enter a positive number:")
            continue
        if round_bet > 0 and player1.getChips() >= round_bet:
            break
        else:
            print("You don't have enough chips! Try again.")
    keep_getting = 'Y'
    while player1.sumCards() <= 21: 
        keep_getting = input("Would you like to recieve more cards? Y or N: ").upper()
        while keep_getting != 'N' and keep_getting != 'Y':
            keep_getting = input("Please enter Y or N: ").upper()
        if keep_getting=='N':
            break
        getCard = random.choice(cardDeck) 
        while (getCard[2]==True):
            getCard = random.choice(cardDeck) 
        edited_card = getCard
        edited_card[2] = True
        cardDeck[cardDeck.index(getCard)] = edited_card
        player1.addCard(getCard) 
        player1.printHand()
        print("Total sum: " + str(player1.sumCards()))  
    if player1.sumCards() > 21:
        print("BUST! you lose your bet.")
        player1.decChips(int(round_bet))
        reset_deck(cardDeck)
        player1.empty_Hand()
        keep_playing = input("Would you like to keep playing? Y or N: ").upper()
        if keep_playing == 'N' or keep_playing == 'Y':
            continue
        while keep_playing != 'N' and keep_getting != 'Y':
            keep_playing = input("Please enter Y or N: ").upper()
        continue
    Dealer_gets = 'H' 
    print("Now it's the Dealer's turn! Dealer keeps hitting until he reaches 17.")
    while Dealer.sumCards() <= 17:
        Dealer_gets = input("keep hitting the Dealer using H! ").upper()
        getCard = random.choice(cardDeck) 
        while (getCard[2]==True):
            getCard = random.choice(cardDeck) 
        edited_card = getCard
        edited_card[2] = True
        cardDeck[cardDeck.index(getCard)] = edited_card
        Dealer.addCard(getCard)
        Dealer.printHand()
        print("Total sum: " + str(Dealer.sumCards()))
    if Dealer.sumCards() > 21:
        print("Dealer BUST! player wins!")
        player1.addChips(round_bet)
        player1.empty_Hand()
        Dealer.empty_Hand()
        reset_deck(cardDeck)
        keep_playing = input("Would you like to keep playing? Y or N: ").upper()
        if keep_playing == 'N' or keep_playing == 'Y':
            continue
        while keep_playing != 'N' and keep_getting != 'Y':
            keep_playing = input("Please enter Y or N: ").upper()
        continue
    if Dealer.sumCards() < 22 and Dealer.sumCards() < player1.sumCards():
        print("You win the round!! doubled your bet")
        player1.addChips(round_bet)
        player1.empty_Hand()
        Dealer.empty_Hand()
        reset_deck(cardDeck)
        keep_playing = input("Would you like to keep playing? Y or N: ").upper()
        if keep_playing == 'N' or keep_playing == 'Y':
            continue
        while keep_playing != 'N' and keep_getting != 'Y':
            keep_playing = input("Please enter Y or N: ").upper()
        continue
    if Dealer.sumCards() < 22 and Dealer.sumCards() > player1.sumCards():
        print("Dealer wins the round!! you lose your bet")
        player1.decChips(round_bet)
        player1.empty_Hand()
        Dealer.empty_Hand()
        reset_deck(cardDeck)
        keep_playing = input("Would you like to keep playing? Y or N: ").upper()
        if keep_playing == 'N' or keep_playing == 'Y':
            continue
        while keep_playing != 'N' and keep_getting != 'Y':
            keep_playing = input("Please enter Y or N: ").upper()
        continue
    if Dealer.sumCards() < 22 and Dealer.sumCards() == player1.sumCards():
        print("it's a Draw!")
        player1.empty_Hand()
        Dealer.empty_Hand()
        reset_deck(cardDeck)
        keep_playing = input("Would you like to keep playing? Y or N: ").upper()
        if keep_playing == 'N' or keep_playing == 'Y':
            continue
        while keep_playing != 'N' and keep_getting != 'Y':
            keep_playing = input("Please enter Y or N: ").upper()
        continue
if player_starting_chips > player1.getChips():
    print("Game is over! you have lost " + str(player_starting_chips - player1.getChips()) + " chips. Bye Bye")
else:
    print("Game is over! you have gained " + str(player1.getChips()-player_starting_chips) + " chips. Bye Bye")


  


    



