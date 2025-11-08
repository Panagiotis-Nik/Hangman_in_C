#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMCAP 46
#define RED printf("\033[1;31m")
#define GREEN printf("\033[1;32m")
#define BLUE printf("\033[1;34m")
#define PURPLE printf("\033[1;35m")
#define YELLOW printf("\033[1;33m")
#define RESET printf("\033[0m")


//Function that chooses a random capital from the capitals array and place it in the rcapital array
void randcap(char capitals[][20], char rcapital[]) {
    int r = rand() % NUMCAP;
    int i = 0;
    while (capitals[r][i] != '\0') {
        rcapital[i] = capitals[r][i];
        i++;
    }
    rcapital[i] = '\0';
}

// Function that calculates the length of the rcapital array so that it can place the correct amount of _ latter in the screen
int lengthofword(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Function that checks if the letter exists inside the random capital
int checkletter(char letter, char rcapital[]) {
    int i = 0;
    while (rcapital[i] != '\0') {
        if (letter == rcapital[i] || letter == rcapital[i] + 32 || letter == rcapital[i] - 32) {
            return 1;
        }
        i++;
    }
    return 0;
}

// Function that replaces _ with the correct letter
void from_2letter(char letter, char rcapital[], char _array[]) {
    int i = 0;
    while (rcapital[i] != '\0') {
        if (letter == rcapital[i] || letter == rcapital[i] + 32 || letter == rcapital[i] - 32) {
            _array[i] = rcapital[i];
        }
        i++;
    }
}

// Function that checks if the letter has already been guessed
int alreadyguessed(char letter, char guessedLetters[], int numGuessedLetters) {
    for (int i = 0; i < numGuessedLetters; i++) {
        if (letter == guessedLetters[i] || letter == guessedLetters[i] + 32 || letter == guessedLetters[i] - 32) {
            return 1;
        }
    }
    return 0;
}

void printman(int attempts) {
    if(attempts==9){
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("____\n");
    }else if(attempts==8){
        printf("  |\n");
        printf("  |\n");
        printf("  |\n");
        printf("  |\n");
        printf("__|__\n");
    }else if(attempts==7){
        printf("  _________\n");
        printf("  |\n");
        printf("  |\n");
        printf("  |\n");
        printf("  |\n");
        printf("__|__\n");
    }else if(attempts==6){
        printf("  _________\n");
        printf("  |        |\n");
        printf("  |\n");
        printf("  |\n");
        printf("  |\n");
        printf("__|__\n");
    }else if(attempts==5){
        printf("  _________\n");
        printf("  |        |\n");
        printf("  |        O\n");
        printf("  |\n");
        printf("  |\n");
        printf("__|__\n");
    }else if(attempts==4){
        printf("  _________\n");
        printf("  |        |\n");
        printf("  |        O\n");
        printf("  |        |\n");
        printf("  |\n");
        printf("__|__\n");
    }else if(attempts==3){
        printf("  _________\n");
        printf("  |        |\n");
        printf("  |        O\n");
        printf("  |       /|\n");
        printf("  |\n");
        printf("__|__\n");
    }else if (attempts==2){
        printf("  _________\n");
        printf("  |        |\n");
        printf("  |        O\n");
        printf("  |       /|\\\n");
        printf("  |\n");
        printf("__|__\n");
    }else if(attempts==1){
        printf("  _________\n");
        printf("  |        |\n");
        printf("  |        O\n");
        printf("  |       /|\\\n");
        printf("  |       /\n");
        printf("__|__\n");
    }else if(attempts==0){
        printf("  _________\n");
        printf("  |        |\n");
        printf("  |        O\n");
        printf("  |       /|\\\n");
        printf("  |       / \\\n");
        printf("__|__\n");
    }
}

int main() {
    char capitals[NUMCAP][20] = {"Amsterdam", "Andorra", "Athens", "Belgrade", "Berlin", "Bern", "Bratislava", "Brussels", "Bucharest", "Budapest", "Chisinau",
                                 "Copenhagen", "Dublin", "Helsinki", "Kiev", "Lisbon", "Ljubljana", "London", "Luxembourg", "Madrid", "Minsk", "Monaco",
                                 "Moscow", "Nicosia", "Nuuk", "Oslo", "Paris", "Podgorica", "Prague", "Reykjavik", "Riga", "Rome", "SanMarino", "Sarajevo",
                                 "Skopje", "Sofia", "Stockholm", "Tallinn", "Tirana", "Vaduz", "Valletta", "Vatican", "Vienna", "Vilnius", "Warsaw", "Zagreb"};

    srand(time(NULL));

    char rcapital[20]; //the random capital
    int length; //length of the array rcapital
    int attempts=10;//the attempts the user has in order to guess the word each time
    char guessedalready[26]="\0";//array with the letters the user has already guessed
    int gl = 0;//an integer number to calculate the amount of letters that exist in the guessedalready array so that it can fill it corectly
    int rounds=1;
    char name[20];
    char guess;//the letter that the user provides as a guess

    printf("Please enter your name : ");
    do {
        if (scanf("%s", name) != 1) {
            printf("Error reading name, please try again: ");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);
    
    printf("Welcome to HANGMAN ");
    GREEN;
    printf("%s!!\n", name);
    PURPLE;
    printf("\nThe game rules are simple :\n  -Your goal is to guess the hiden word that will apear in your screen in order to save the litle man !\n");
    printf("  -You can provide one(1) letter each time, so make sure you feel comfident with your choice\n");
    printf("  -If you make ten(10) wrong guesses the game is over and the litle man dies :(\n");
    printf("  -Just to give you a hint, the thematic behind the words that you will be guessing is European Capitals !\n");
    RESET;
    GREEN;
    printf("Good luck, the fate of this litle man is in your hands!!\n");
    RESET;

    while(attempts>0 && rounds<=3){

      randcap(capitals, rcapital);
      length = lengthofword(rcapital);
      char _array[length + 1];//array tha contains the correct amount of _ for each capital

      int i;
      for (i = 0; i < length; i++) {
        _array[i] = '_';
      }
      _array[i] = '\0';
 
      attempts = 10;
      gl = 0;
      for (int i = 0; i < 26; i++) {
        guessedalready[i] = ' ';
      }

      printf("ROUND %d\n", rounds);

      while (attempts > 0) {
        BLUE;
        printf("\nGuessed Word: "); 
        RESET;  
        printf("%s\n", _array);
        PURPLE;
        printf("Attempts Remaining: "); 
        RESET; 
        printf("%d\n", attempts);
        YELLOW;
        printf("Letters you have already guessed :" ); 
        RESET;
        for(int i=0; i<=gl; i++){ 
           printf(" %c", guessedalready[i]);
        }

        printf("\nEnter your guess: ");
        scanf(" %c", &guess);

        
        if (!((guess >= 'a' && guess <= 'z') || (guess >= 'A' && guess <= 'Z'))) {
            printf("\nInvalid input. Please enter a letter.\n");
        }else if (alreadyguessed(guess, guessedalready, gl) == 1) {
            printf("\nYou have already guessed that letter. Please try again.\n");
        }else if (checkletter(guess, rcapital) == 1) {
            guessedalready[gl] = guess;
            gl++;
            from_2letter(guess, rcapital, _array);
            GREEN;
            printf("\nGood guess!\n");
            RESET;
        } else {
            guessedalready[gl] = guess;
            gl++;
            attempts--;
            RED;
            printf("\nWrong guess!\n");
            RESET;
        }

        printman(attempts);

        int fullyGuessed = 1;
        for (int i = 0; i < length; i++) {
            if (_array[i] == '_') {
                fullyGuessed = 0;
                break;
            }
        }

        if (fullyGuessed==1) {
            GREEN;
            printf("Congratulations! You guessed the capital correctly (%s).\n", rcapital);
            RESET;
            rounds++;
            break;
        }

        if (attempts == 0) {
            RED;
            printf("Game over! The capital was %s.\n", rcapital);
            RESET;
            return 0;
        }
      }  
    }

    return 0;
} 