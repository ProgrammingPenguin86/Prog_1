#include <iostream>
#include <string> // allows for use of strings + string functions
#include <random> // allows for use of random
using namespace std;

class Hand{
public:
    int cardvalues[5] = {0, 0, 0, 0, 0};
    int count = 0;
    int sum = 0;
    int Count_Hand(){
        for ( ; count < 5; count++){ // nothing in first run; nothing needed
            sum += cardvalues[count]; // adds up all the elements of cardvalues[]
        }
        return sum; // returns the sum number (used to scoring)
    }
};

void print_card(int *p){ // function for printing random cards
    char suit[4] = {'S', 'H', 'C', 'D'}; // initialization + definition of suit array
    int cardvalue[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10}; // initialization + definition of card numbers
    char spec_cards[4] = {'J', 'Q', 'K', 'A'}; // initialization + definition of face cards
    int card_val; // index variable *initialized*, not defined
    random_device rd; // creates random object "rd"
    mt19937 gen(rd()); // initializes a pseudo random number generator named "gen." The mt19937 takes a seed value initialized with value obtained through calling object rd
    uniform_int_distribution<int> dis(0, 12); // Define the range [0, 12]; uniform_int_distribution generates random numbers uniformly
    int card_placeholder = dis(gen); // generates random number
    card_val = card_placeholder; // sets *index* variable to random number
    if(card_val <= 8){
        cout << cardvalue[card_val]; // if statement that will print card value based on index
        *p = cardvalue[card_val];
    }
    else if (card_val < 13){
        cout << spec_cards[card_val - 9];// else if statement to print special card value
        if (spec_cards[card_val- 9] != 'A'){
            *p = 10;
        }
        else{
            *p = 11;
        }
    }
    else{
        cout << "oops!"; // safe-net else statement in case generator fails
    }
     random_device PT; // random device
     mt19937 generate(PT()); // random number generator
     uniform_int_distribution<int> distinction(0, 3); // Define the range [0, 3]
    int suit_placeholder = distinction(generate); // generate random number between 0 - 3
    int suitnum = suit_placeholder; // sets *index* variable 2 to random number generated
    cout << " of " << suit[suitnum]; // prints "of" the suit relative to the index

}
int main() {
    string move;
    string gamechoice;
    int temp; // temp number transferred between main and card function using '&' (*call by reference*)
    int Dealer_Sum, Player_Sum; // integers representing number for scoring
    int card_num = 2; // number for index of the class array 'cardvalue[]'
    Hand Player; // object for class 'Hand' - Player Data
    Hand Dealer; // object for class 'Hand' - Dealer Data
    bool choice = true; // boolean control variable for player's moves
    bool computer = true; // boolean control variable for computer's decisions

    cout << "The dealer's cards are: " << endl; // These next 8 lines print dealer's cards

    print_card(&temp); // first card
    cout << endl;
    Dealer.cardvalues[0] = temp; // sets first number in dealer card array to value of first card

    print_card(&temp); // second card
    cout << endl;
    Dealer.cardvalues[1] = temp; // sets second number in dealer card array to value of second card

    Dealer_Sum = Dealer.Count_Hand(); // initialize variable to be Dealer Count
    cout << "The Dealer is at " << Dealer_Sum << endl << endl; // prints dealer count
    if (Dealer_Sum == 21) { // test line for it cmputer has blackjack
        cout << "The Dealer has Blackjack!" << endl << endl;
        computer = false;
    }

    cout << "Your cards are: \n"; // these next 8 lines print player's cards

    print_card(&temp); // first card
    cout << endl;
    Player.cardvalues[0] = temp;

    print_card(&temp); // second card
    cout << endl;
    Player.cardvalues[1] = temp;

    Player_Sum = Player.Count_Hand(); // initialize variable to be Player Count
    cout << "You are at " << Player_Sum << endl; // prints player count
    if (Player_Sum == 21) {
        choice = false;
        cout << "You have Blackjack! Dealer's turn now... \n";
    }
if (choice) { // if player does not have blackjack
    while (choice) { // while player does not have 21 or higher
        cout << endl << "HIT or STAY?" << endl; // asks for player's next move
        cin >> move; // inputs it into *string* "move" variable
        if (move == "HIT" || move == "hit" || move == "Hit") { // if statement to print another card
            print_card(&temp); // prints another card
            cout << endl;
            Player.cardvalues[card_num] = temp; // sets new card value to 2nd card in hand
            Player_Sum += temp;
            cout << "You are now at " << Player_Sum << endl;

        } else if (move == "STAY" || move == "stay" || move == "Stay") {
            choice = false;
            cout << "OK. Dealer's turn now... \n"; // if player stays, program acknowledges player's choice
        }
        if (Player_Sum > 21) {
            choice = false;
            cout << "Bust! Dealer's turn now... \n";

        } else if (Player_Sum == 21) {
            choice = false;
            cout << "BlackJack! Dealer's turn now... \n";
        }
    }
}
else {
    cout << "Dealer's move now...\n";
}

    if (computer) { // if computer does not have blackjack off first cards
        while (computer) { // while dealer is < 17
            if (Dealer_Sum > 21) {
                cout << "Dealer busts!";
                computer = false;
            }
            if (Dealer_Sum == 21) {
                cout << "Dealer has Blackjack! ";
                computer = false;
            } else if (Dealer_Sum > 17) { // weak point **Even if a condition is met, every stage of loop will run through**
                computer = false;
                cout << "Dealer stays.";
            } else {
                cout << "Dealer hits. ";
                print_card(&temp); // prints another card
                cout << endl;
                Dealer_Sum += temp;
                cout << "Dealer is now at " << Dealer_Sum << endl;
            }
        }
    }
    else{
        cout << "The results: \n";
    }

    if ((Player_Sum > Dealer_Sum) && (Player_Sum <= 21) && (Dealer_Sum < 21)) { //if else statments to find winner
        cout << "\nYou Win! Would you like to play again? YES or NO?\n";
    } else if ((Player_Sum < Dealer_Sum) && (Dealer_Sum <= 21) && (Player_Sum < 21)) {
        cout << "\nDealer Wins! Would you like to play again? YES or NO?\n";
    } else if ((Player_Sum) > 21 && (Dealer_Sum > 21)) {
        cout << "\nBoth Busts! Draw! Would you like to play again? YES or NO?\n";
    } else if ((Player_Sum > 21) && (Dealer_Sum <= 21)) {
        cout << "\nDealer Wins! Would you like to play again? YES or NO?\n";
    } else if ((Dealer_Sum > 21) && (Player_Sum <= 21)) {
        cout << "\nYou Win! Would you like to play again? YES or NO?\n";
    }
    else{
        cout << "Weird ending... Play again?"; // asks player if wants to play again
    }
    cin >> gamechoice;
    if (gamechoice == "YES" || gamechoice == "yes" || gamechoice == "Yes"){
        main(); // calls main function if yes
    }
    else {
        return 0; // ends program and returns 0 if no
    }
}