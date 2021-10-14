#include <iostream>
#include <string>
#include <ctime> // used as a timer for card shuffling

/* ------------------ ------------------ ------------------ */
/* ------------------ Classes and struct ------------------ */
enum Faces {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES,
};

enum Ranks {
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
};

static const char ranks_str[]{'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
static const std::string faces_str[]{"Hearts", "Diamonds", "Spades", "Clubs"};

// class player which saves the players victories, losses and name.
class Player {
    private:
        std::string m_name;
        int m_victories = 0;
        int m_losses = 0;

    public:
        Player(std::string name) {
            m_name = name;
        };
        Player() {};

        void won(){
            m_victories++;
        };
        int getVictories(){
            return m_victories;
        };

        void lost() {
            m_losses++;
        };
        int getLosses() {
            return m_losses;
        };

        void setName(std::string name) {
            m_name = name;
        };
        std::string getName() {
            return m_name;
        };
};

class Card{
    private:
        Faces m_face = (Faces)0;
        Ranks m_rank = (Ranks)0;
        int m_points = 0;

    public:
        Faces getFace() {
            return m_face;
        };
        Ranks getRank() {
            return m_rank;
        };
        void setFace(Faces face) {
            m_face = face;
            m_points = m_face + m_rank;
        };
        void setRank(Ranks rank) {
            m_rank = rank;
            m_points = m_rank + m_rank; 
        };
        
        void setPoints (int points) {
            m_points = points;
        };
        int getPoints() {
            return m_points;
        };


        void print(){
			std::cout << faces_str[m_face] << " of " << ranks_str[m_rank] << std::endl;
		};

        bool isEqual(Card card) {
            if (card.getFace() != m_face) return false; 
            if (card.getRank() != m_rank) return false; 
            return true;
        };
};

class Deck {
    private:
        Card m_deck[52];

    public:
        // constractor
        Deck() {
            // initialisation of the deck
            int l = 0;
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 13; j++){
                    m_deck[l].setFace((Faces)i);
                    m_deck[l].setRank((Ranks)j);
                    l++;
                };
            };
        };
        // prints the cards of deck if called upon
        void printcards() {
            for(int k = 0; k < 52; k++) {
                m_deck[k].print();
            };
        };
        // shufffles the deck
        void shuffle() {
            for(int n = 0; n < 52; n++) {
                int m = rand() % 52;
                
                Card temp = m_deck[n];
                m_deck[n] = m_deck[m];
                m_deck[m] = temp;
            };
        };

        Card getRandomCard() {
            return m_deck[rand() % 52];
        };

        Card getCard(int cardNumber) {
            return m_deck[cardNumber]; // Never try to pull number bigger then 52!
        };
};


int main(){
    srand(time(0));

    std::cout<< "\tWelcome to the legendary cardgame!\n";
    std::cout << "\tPlay a card game against your friend!\n ";

    std::cout << "First player please enter your name: ";
    std::string player1_name;
    std::cin >> player1_name;

    Player player1 = Player(player1_name);
    std::cout << "Hello " << player1.getName() << std::endl;

    
    std::cout<< "\tSecond player please enter your name: ";
    std::string player2_name;
    std::cin >> player2_name;

    Player player2 = Player(player2_name);
    std::cout << "Hello " << player2.getName() << std::endl;

    // create a deck
    Deck deck = Deck();
    deck.shuffle();
    // deck.printcards();
    bool continuePlay = true;
    while (continuePlay)
    {
        for (int i = 0; i < 3 ; i++) {
            std::cout << "---------------------------------" << std::endl;

            Card card1 = deck.getCard(rand() % 52);
            Card card2 = deck.getCard(rand() % 52);
            
            std::cout << player1.getName() << " you have a : ";
            card1.print();
            std::cout << "you have " << card1.getPoints() << " points" << std::endl;

            std::cout << player2.getName() << " you have a : ";
            card2.print();
            std::cout << "you have " << card2.getPoints() << " points" << std::endl;

            if (card1.getPoints() >card2.getPoints()) {
                player1.won();
                player2.lost();
                std::cout << "player " << player1.getName() << " won this game !" << std::endl;
            } else {
                player2.won();
                player1.lost();
                std::cout << "player " << player2.getName() << " won this game !" << std::endl;
            };
        };

        // Under this line shall the user have the option to exit or continue
        char confirmation;
        std::cout << std::endl;
        std::cout << "do you want to gamble again n/y ? (type n to exit / or y to play again)." << std::endl;
        std::cin >> confirmation;
        if (confirmation == 'n') {
            continuePlay = false;
            std::cout << "Thank you for playing the game! See you soon.";
        }
    }
    std::cout << "---------------------------------" << std::endl;
    std::cout << "player " << player1.getName() << " you have " << player1.getVictories() << " wins and " << player1.getLosses() << " losses." << std::endl;
    std::cout << "player " << player2.getName() << " you have " << player2.getVictories() << " wins and " << player2.getLosses() << " losses." << std::endl;

};