
// Julian-Justin Djoum
// 4.16.18
// Large Program 3 (HANGMAN)

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>


//Function Prototypes:
//*This function provides instructions to the user on how to play the game
void HangmanRules();
//*This funciton asks the user if they want to play another game (y or n?)
void PlayAgain(char *againPtr);
//*This function runs one game, input: character from the file, void return type
void PlayOneGame(char solution[]);
//*This function changes a character array to all uppercase letters
void UpperCaseWord(char word[]);
//*This function creates the starword array
void CreateStarword(char starword[], int length);
//*This function gets the users guess letter and adds it to the lettersGuessed array, return the letter from the user
char GetTheLetterGuess(char letterGuessed[], int *numPtr);
//*This function replaces any asterik in the starword with the current character entered by the user
int ReplaceStars(char solution[], char starword[], char letter);
//*This function gets the guess word, compares the solution and the guess word, tells the user if they won and returns a 1, otherwise returns a 0
int DidYouWin(char solution[]);



int main()
{
	FILE *inPtr;
	FILE *outPtr;

	char solution[50];
	char starword[50];
	char userGuess[50];
	char guesses[50];
	char again;
	inPtr = fopen("hangmanWords.txt", "r");

	HangmanRules();
	//PlayAgain(again);
	do {
		//Get Word from File
		fscanf(inPtr, " %s", solution);
		//Change solution word to all uppercase
		UpperCaseWord(solution);
		//Print solution on screen (TEST)
		//printf("\nSolution is: %s", solution);

		//Play One Game
		PlayOneGame(solution);
		//Play Again?
		PlayAgain(&again);
	} while (again == 'y');

	fclose(inPtr);
	return 0;
}

//Function Defintions:
//*This function provides instructions to the user on how to play the game
void HangmanRules()
{
	printf("--WELCOME TO HANGMAN!--\n");
	printf("\nHangman Instructions:\n");
	printf("\n~You will be presented with a word to be guessed, in the form of [*'s]\n");
	printf("~You should guess letters one at a time\n");
	printf("~You can have up to [6] incorrect letter guesses\n");
	printf("~You can only guess the solution word, when you have made a correct letter guess");
	printf("~Hangman will be OVER when you have guessed the word correctly (YOU WIN!)\nOR\nwhen you have made 6 incorrect letter guesses (YOU LOSE!)\n\n");
	printf("--HAVE FUN PLAYING HANGMAN!--\n");


}

//*This funciton asks the user if they want to play another game (y or n?)
void PlayAgain(char *againPtr)
{
	printf("\n\nUser, would you like to play another game? (y or n?):\n");
	scanf(" %c", againPtr);
	*againPtr = tolower(*againPtr);
	//printf("The letter is: %c\n", *againPtr);
}

//*This function runs one game, input: character from the file, void return type
void PlayOneGame(char solution[])
{
	char starword[30] = "";
	char guessedletters[30] = "";
	char letter;
	int len = strlen(solution);
	int count = 0;
	int win = 0;
	int numG = 0;
	int test = 0;
	//Create the starword (w/ loop)
	CreateStarword(starword, len);
	while (win == 0 && numG < 6)
	{
		//Print the starword*

		//*printf("MAIN: The starword is: %s", starword);
		//Print the guessed letters
		//printf("\nThe letters that you've guessed are: %s", guessedletters);
		//Ask and Get letter guess
		letter = GetTheLetterGuess(guessedletters, &count);
		printf("\n~The letter you guessed is: %c, and the total guess count is now: %d.", letter, count);
		printf("\n~The letter(s) you've guessed so far are: %s.", guessedletters);
		//Check if letter matches
		// if match, Guess the word
		test = ReplaceStars(solution, starword, letter);
		//printf("\nThe test integer is: %d", test);
		printf("\nThe starword is: %s", starword);
		if (test == 1)
		{
			//Call the DidYouWin Function
			//Guess
			printf("\nUser, you made the right guess!");
			win = DidYouWin(solution);
		}
		else if (test == 0)
		{
			//Add 1 to numG
			printf("\nUser, you made the wrong guess.");
			//printf("\nThe number of wrong guesses is now: %d", count);
			numG++;
		}
		// else if not, numG++
	}
	//Printf the starword to make sure that it's working
	// Will: present starword, will present lettersguessed so far, get a character guess, if char is in solution/ replace in starword, allow the user to guess the word

	if (numG == 6)
	{
		printf("\n\n(YOU LOSE!)");
	}
	printf("\n\n~The solution word that round was: %s.", solution);

}

//*This function changes a character array to all uppercase letters
void UpperCaseWord(char word[])
{
	int i;
	int len;
	len = strlen(word);
	//printf("length is %d", len);
	for (i = 0; i < len; i++)
	{
		word[i] = toupper(word[i]);
	}
}

//*This function creates the starword array
void CreateStarword(char starword[], int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		starword[i] = '*';
	}
	starword[length] = '\0';
	printf("\nThe starword is: %s", starword);
}

//*This function gets the users guess letter and adds it to the lettersGuessed array, return the letter from the user
char GetTheLetterGuess(char letterGuessed[], int *numPtr)
{
	char temp;
	printf("\n\nUser, please make a letter guess:\n");
	scanf(" %c", &temp);
	temp = toupper(temp);
	letterGuessed[*numPtr] = temp;
	*numPtr = *numPtr + 1;
	letterGuessed[*numPtr] = '\0';
	return temp;
	//Ask, get, and change temp to uppercase
}

//*This function replaces any asterik in the starword with the current character entered by the user
int ReplaceStars(char solution[], char starword[], char letter)
{
	int len;
	int i;
	int rV = 0;
	len = strlen(solution);

	for (i = 0; i < len; i++)
	{
		if (solution[i] == letter)
		{
			starword[i] = letter;
			rV = 1;
		}
	}
	return rV;
}

//*This function gets the guess word, compares the solution and the guess word, tells the user if they won and returns a 1, otherwise returns a 0'
int DidYouWin(char solution[])
{
	int rV = 0;
	char guess[30];
	printf("\n\nUser, please enter a guess for the solution word: ");
	scanf("%s", guess);
	UpperCaseWord(guess);
	printf("The guess word is: %s", guess);
	int res = strcmp(solution, guess);
	if (res == 0)
	{

		printf("\n\n~The guess word entered matches the solution word and the strings are equal.");
		printf("\n\n(YOU WIN!)");
		rV = 1;
	}
	else
	{
		printf("\n\n~The guess word entered does not match the solution word and the strings are \nunequal.");
	}
	return rV;
}
