class HangmanGame: #any object of this class can run the hangman game.
    wordsList = None; 
    currentWordIndex = 0; 
    def __init__(self, testingWords = None) -> None:
        self.wordsList = testingWords; 
        if(self.wordsList is None):
            text_file = open("words_250000_train.txt","r"); 
            self.wordsList = text_file.read().splitlines()[200000:]; 
            text_file.close(); 
        self.currentWordIndex = 0; # Index of the current word being used in the game

    #so what we will output will just be the word, and keep count of guesses left ourself.

    def InputPlay(self):
        guess = input("Guess a letter: "); 
        return guess; 


    def play(self, playingFunction = InputPlay):
        curWord = self.wordsList[self.currentWordIndex]; 
        self.currentWordIndex += 1;
        curWord = [x for x in curWord]; 
        hiddenWord = ['_' for x in curWord]; 
        tries_left = 6; 
        while(tries_left > 0 and hiddenWord != curWord):
            print(" ".join(hiddenWord));  
            guess = playingFunction(hiddenWord); 
            if(guess in curWord):
                for i in range(len(curWord)):
                    if(curWord[i] == guess):
                        hiddenWord[i] = guess; 
            else:
                tries_left -= 1; 
                print("Incorrect guess. You have " + str(tries_left) + " tries left.");
        if(tries_left == 0):
            print("You lose. The word was " + " ".join(curWord));
    def getInput(self):
        return 


    #def play(self): # Runs the game
        #this algorithm should return some stuff

game = HangmanGame();
game.play();
        