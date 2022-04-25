#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
#include <stdbool.h>
#include<time.h>

struct word {
	char* letters;
	int lenght;
};

int safeScanf() {
	int number = 0;
	while (1) {
		if (!scanf("%d", &number)) {
			while (getchar() != '\n');
			printf("Zle dane\n");
		}
		else return number;
	}
}

int changeArraySize(struct word** wordArray, int* arraySize) {
	struct word* tempArray;
	tempArray = realloc(*wordArray, *arraySize * sizeof(*(*wordArray)));
	if (tempArray != NULL) {
		*wordArray = tempArray;
	}
	else {
		printf("Bladk realokacji\n");
		return 3;
	}
	return 0;
}

int allocateMemory(struct word* Word) {
	Word->letters = malloc(Word->lenght * sizeof(char));
	if (Word->letters == NULL) {
		return 3;
	}
	return 0;
}

int loadFile(struct word** wordArray, int* wordArraySize, char* filename) {
	FILE* file;
	file = fopen(filename, "r");
	if (file == NULL) {
		printf("Nie znalazlem pliku\n");
		return 2;
	}
	int fileLenght;
	int result;
	fseek(file, 0, SEEK_END);
	fileLenght = ftell(file);
	rewind(file);
	char loadWord[20];
	int n = *wordArraySize;
	while (fscanf(file, "%s", loadWord) != EOF) {
		if (ftell(file) != fileLenght) {
			fscanf(file, "%*c");
		}
		(*wordArraySize)++;
		result = changeArraySize(wordArray, wordArraySize);
		if (result == 3) {
			(*wordArraySize)--;
			fclose(file);
			return 3;
		}
		((*wordArray)[n]).lenght = strlen(loadWord) + 1;
		result = allocateMemory(&(*wordArray)[n]);
		if (result == 3) {
			fclose(file);
			return 3;
		}
		strcpy((*wordArray)[n].letters, loadWord);
		n++;
	}
	fclose(file);
	return 0;
}

void moveArray(struct word* wordArray, int* arraySize, int selectedWord) {
	for (int i = 0; i < *arraySize - selectedWord; i++) {
		wordArray[selectedWord + i] = wordArray[selectedWord + i + 1];
	}
}

int pickWord(int* wordArraySize) {
	int result;
	result = rand() % (*wordArraySize);
	return result;
}

int shuffleLetters(struct word* selectedWord, struct word** mixedWord) {
	(*mixedWord)->lenght = selectedWord->lenght;
	(*mixedWord)->letters = malloc((*mixedWord)->lenght * sizeof(char));
	if ((*mixedWord)->letters == NULL) {
		printf("Blad alokacji!\n");
		return 3;
	}
	strcpy((*mixedWord)->letters, selectedWord->letters);
	do {
		if ((*mixedWord)->lenght > 1) {
			for (int i = 0; i < (*mixedWord)->lenght - 1; i++) {
				int j = i + rand() / (RAND_MAX / ((*mixedWord)->lenght - 1 - i) + 1);
				char t = (*mixedWord)->letters[j];
				(*mixedWord)->letters[j] = (*mixedWord)->letters[i];
				(*mixedWord)->letters[i] = t;
			}
		}
	} while (!strcmp((*mixedWord)->letters, selectedWord->letters));
	return 0;
}

void getUserInput(char* holdText, int arraySize) {
	char* replaceEndLine;
	if (fgets(holdText, arraySize, stdin) != NULL) {
		replaceEndLine = strchr(holdText, '\n');
		if (replaceEndLine != NULL) {
			*replaceEndLine = '\0';
		}
	}
}

void toHigher(char* userInput) {
	int lenght = strlen(userInput);
	for (int i = 0; i < lenght; i++) {
		if (userInput[i] >= 97 && userInput[i] <= 122) {
			userInput[i] = userInput[i] - 32;
		}
	}
}

int addWord(struct word** wordArray, int* wordArraySize) {
	char newWord[20];
	while (getchar() != '\n');
	getUserInput(newWord, sizeof(newWord));
	if (strlen(newWord) <= 1) {
		return 2;
	}
	toHigher(newWord);
	(*wordArraySize)++;
	if (changeArraySize(wordArray, wordArraySize) == 3) {
		return 3;
	}
	((*wordArray)[(*wordArraySize) - 1]).lenght = strlen(newWord) + 1;
	if (allocateMemory(&(*wordArray)[(*wordArraySize) - 1]) == 3) {
		return 3;
	}
	strcpy((*wordArray)[(*wordArraySize) - 1].letters, newWord);
	return 0;
}

int swap(struct word* correctWord, struct word* mixedWord, int firstLetter, int secondLetter, bool sameLetterOnce) {
	char temp;
	if (mixedWord->letters[firstLetter] == correctWord->letters[firstLetter]) {
		if (sameLetterOnce == true) {
			system("cls");
			printf("Da sie to zrobic inaczej...\n");
		}
		return 1;
	}
	else if (mixedWord->letters[secondLetter] == correctWord->letters[secondLetter]) {
		if (sameLetterOnce == true) {
			system("cls");
			printf("Da sie to zrobic inaczej...\n");
		}
		return 1;
	}
	else {
		temp = mixedWord->letters[firstLetter];
		mixedWord->letters[firstLetter] = mixedWord->letters[secondLetter];
		mixedWord->letters[secondLetter] = temp;
		if (mixedWord->letters[firstLetter] == correctWord->letters[firstLetter]) {
			if (strcmp(mixedWord->letters, correctWord->letters) == 0) {
				system("cls");
				printf("Wylosowane slowo: %s\n", correctWord->letters);
				printf("Pomiesznae slowo: %s\n", mixedWord->letters);
				printf("Gratulacje!\n\n");
				return 0;
			}
			system("cls");
			printf("Niezle, coraz blizej...\n");
			return 0;
		}
		else if (mixedWord->letters[secondLetter] == correctWord->letters[secondLetter]) {
			if (strcmp(mixedWord->letters, correctWord->letters) == 0) {
				system("cls");
				printf("Gratulacje!\n");
				return 0;
			}
			system("cls");
			printf("Niezle, coraz blizej...\n");
			return 0;
		}
		else {
			temp = mixedWord->letters[firstLetter];
			mixedWord->letters[firstLetter] = mixedWord->letters[secondLetter];
			mixedWord->letters[secondLetter] = temp;
			system("cls");
			printf("Da sie to zrobic inaczej...\n");
			return 1;
		}
	}
	return 1;
}

bool allChecked(int* markLetters, int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		if (markLetters[i] != 0) {
			return false;
		}
	}
	return true;
}

int findLetters(struct word* correctWord, struct word* mixedWord, int* markLetters, char* lettersToBeReplaced, bool* sameLetterOnce) {
	char* findChar;
	int firstLetterAppear = 0;
	int secondLetterAppear = 0;
	int n = 0;
	while (n != 2) {
		findChar = strchr(mixedWord->letters, lettersToBeReplaced[n]);
		while (findChar != NULL) {
			if (n == 0) {
				markLetters[findChar - mixedWord->letters] += 1; // 1 -> pierwsza literka
				firstLetterAppear++;
			}
			else {
				if (markLetters[findChar - mixedWord->letters] != 1) {
					markLetters[findChar - mixedWord->letters] += 2; // 2 -> druga literka
					printf("%d %d %d", findChar - mixedWord->letters);
					secondLetterAppear++;
				}
			}
			findChar = strchr(findChar + 1, lettersToBeReplaced[n]);
		}
		n++;
	}
	if (firstLetterAppear == 0 || secondLetterAppear == 0) {
		return 1;
	}
	if (firstLetterAppear > 1 || secondLetterAppear > 1) {
		*sameLetterOnce = false;
	}
	return 0;
}

int game(struct word* correctWord, struct word* mixedWord, bool* emptyBuffer) {
	char lettersToBeReplaced[7];
	int* markLetters = calloc(mixedWord->lenght - 1, sizeof(int));
	bool sameLetterOnce = true;
	if (markLetters == NULL) {
		printf("Blad alokacji!\n");
		return 3;
	}
	printf("Podaj litery do zamiany: \n");
	if (!(*emptyBuffer)) {
		while (getchar() != '\n');
		*emptyBuffer = true;
	}
	getUserInput(lettersToBeReplaced, sizeof(lettersToBeReplaced));
	if (strlen(lettersToBeReplaced) > 2) {
		if(!strcmp(lettersToBeReplaced, "poddaj")) {
			system("cls");
			printf("Oj slabiutko\n");
			free(markLetters);
			return 4;
		}
	}
	if (lettersToBeReplaced[0] == '\0' || lettersToBeReplaced[1] == '\0') {
		system("cls");
		printf("Potrzebuje dwoch literek!\n");
		free(markLetters);
		return 0;
	}
	toHigher(lettersToBeReplaced);
	if (findLetters(correctWord, mixedWord, markLetters, lettersToBeReplaced, &sameLetterOnce) == 1) {
		system("cls");
		printf("A moze jednak nie...\n");
		free(markLetters);
		return 0;
	}
	int temp = 0;
	int letterBeingChecked, result;
	do {
		for (int i = 0; i < mixedWord->lenght - 1; i++) {
			if (markLetters[i] == 1) {
				if (temp != 0) {
					if (temp == 1) {
						continue;
					}
					result = swap(correctWord, mixedWord, i, letterBeingChecked, sameLetterOnce);
					if (result == 0) {
						free(markLetters);
						return 0;
					}
				}
				else {
					temp = markLetters[i];
					letterBeingChecked = i; // jezeli markletters[i] = 1 <- pierwsza literka
					markLetters[i] = 0;		//... = 2 <- druga literka
				}							// ... = 0 <- inna lub juz sprawdzona literka
			}
			else if (markLetters[i] == 2) {
				if (temp != 0) {
					if (temp == 2) {
						continue;
					}
					result = swap(correctWord, mixedWord, i, letterBeingChecked, sameLetterOnce);
					if (result == 0) {
						free(markLetters);
						return 0;
					}
				}
				else {
					temp = markLetters[i];
					markLetters[i] = 0;
					letterBeingChecked = i;
				}
			}
			else
				continue;
		}
		temp = 0;
	} while (!allChecked(markLetters, mixedWord->lenght - 1));
	if (sameLetterOnce == false) {
		system("cls");
		printf("Da sie to zrobic inaczej...\n");
	}
	free(markLetters);
	return 0;
}

void printMenu(int* choice) {
	printf("1.Graj\n2.Wczytaj liste z pliku\n3.Dodaj wyraz z konsoli\n4.Usun wyraz z bazy\n5.Wyswietl dostepne wyrazy\n6.Koniec\n");
	*choice = safeScanf();
	system("cls");
}

int deleteWord(struct word** wordArray, int* wordArraySize, int selectedWord) {
	if (*wordArraySize > 1) {
		(*wordArraySize)--;
		free((*wordArray)[selectedWord].letters);
		moveArray(*wordArray, wordArraySize, selectedWord);
		if (changeArraySize(wordArray, wordArraySize) == 3) {
			return 3;
		}
	}
	else {
		free((*wordArray)[selectedWord].letters);
		free(*wordArray);
		(*wordArraySize)--;
		*wordArray = NULL;
	}
	return 0;
}

void printArray(struct word* wordArray, int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		printf("%d.%s\n", i + 1, (wordArray + i)->letters);
	}
	printf("\n");
}

int main() {
	srand((unsigned int)time(NULL));
	struct word* wordArray = NULL;
	struct word* mixedWord = malloc(sizeof(struct word));
	if (mixedWord == NULL) {
		return 3;
	}
	mixedWord->letters = NULL;
	int wordArraySize = 0;
	int choice, selectedWord, result;
	char fileName[25];
	bool error = false;
	bool emptyBuffer = false;
	bool surrender = false;
	printMenu(&choice);
	bool isFinish = false;
	while (!isFinish) {
		switch (choice) {
		case 1:
			if (wordArraySize != 0) {
				selectedWord = pickWord(&wordArraySize);
				if (shuffleLetters(&wordArray[selectedWord], &mixedWord) == 3) {
					printf("Zamykam!\n");
					isFinish = true;
					break;
				}
				surrender = false;
				printf("Pamietaj ze mozesz zrezgnowac wpisujac - poddaj!\n");
				while (strcmp(mixedWord->letters, wordArray[selectedWord].letters) != 0) {
					printf("Wylosowane slowo: %s\n", wordArray[selectedWord].letters);
					printf("Pomieszane slowo: %s\n", mixedWord->letters);
					result = game(&wordArray[selectedWord], mixedWord, &emptyBuffer);
					if (result == 3) {
						printf("Zamykam!\n");
						isFinish = true;
						error = true;
						break;
					}
					else if (result == 4) {
						surrender = true;
						break;
					}
					else
						continue;
				}
				emptyBuffer = false;
				if (error == true)
					break;
				free(mixedWord->letters);
				mixedWord->letters = NULL;
				if (!surrender) {
					if (deleteWord(&wordArray, &wordArraySize, selectedWord) == 3) {
						printf("Zamykam!\n");
						isFinish = true;
						break;
					}
				}
			}
			else {
				printf("Zacznij od dodania wyrazu do bazy\n");
			}
			printMenu(&choice);
			break;
		case 2:
			printf("Podaj nazwe pliku (bez .txt)\n");
			while (getchar() != '\n');
			getUserInput(fileName, sizeof(fileName));
			strcat(fileName, ".txt");
			if (loadFile(&wordArray, &wordArraySize, fileName) == 3) {
				printf("Zamykam\n");
				isFinish = true;
				break;
			}
			printMenu(&choice);
			break;
		case 3:
			result = addWord(&wordArray, &wordArraySize);
			if (result == 3) {
				printf("Zamykam\n");
				isFinish = true;
				break;
			}
			else if (result == 2) {
				printf("Niewlasciwy format!\n");
			}
			printMenu(&choice);
			break;
		case 4:
			if (wordArraySize != 0) {
				system("cls");
				printArray(wordArray, wordArraySize);
				selectedWord = safeScanf();
				if (selectedWord >= 1 && selectedWord <= wordArraySize) {
					if (deleteWord(&wordArray, &wordArraySize, selectedWord - 1) == 3) {
						printf("Zamykam\n");
						isFinish = true;
						break;
					}
					printf("Sukces!\n");
				}
				else {
					printf("Nie ma takiej opcji\n");
				}
			}
			else {
				printf("Zacznij od dodania wyrazu\n");
			}
			printMenu(&choice);
			break;
		case 5:
			printArray(wordArray, wordArraySize);
			printMenu(&choice);
			break;
		case 6:
			isFinish = true;
			break;
		default:
			printMenu(&choice);
			break;
		}
	}
	if (mixedWord->letters) {
		free(mixedWord->letters);
	}
	free(mixedWord);
	if (wordArray) {
		for (int i = 0; i < wordArraySize; i++) {
			if ((wordArray + i)->letters) {
				free((wordArray + i)->letters);
			}
		}
		free(wordArray);
	}
	return 0;
}