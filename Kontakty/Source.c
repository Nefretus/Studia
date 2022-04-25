#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#define numberOfLetters 30

#include <crtdbg.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
#include <stdbool.h>

struct contact {
    char name[numberOfLetters];
    char surname[numberOfLetters];
    char number[numberOfLetters];
    char group[numberOfLetters];
};

struct list {
    struct list* previous;
    struct contact data;
    struct list* next;
};

int sizeOfList(struct list** firstElement) {
    struct list* temp = *firstElement;
    int size = 0;
    while (temp != NULL) {
        size++;
        temp = temp->next;
    }
    return size;
}

int pushBack(struct list** activeElement, struct contact* loadedContact, struct list** firstElement) {
    struct list* newElement = malloc(sizeof(struct list));
    if (newElement == NULL) {
        printf("Blad alokacji\n");
        return 3;
    }
    if (*activeElement == NULL) {
        newElement->previous = NULL;
        newElement->next = NULL;
        memcpy(&newElement->data, loadedContact, sizeof(struct contact));
        *activeElement = newElement;
        *firstElement = newElement;
    }
    else {
        newElement->previous = *activeElement;
        newElement->next = NULL;
        memcpy(&newElement->data, loadedContact, sizeof(struct contact));
        (*activeElement)->next = newElement;
        *activeElement = newElement;
    }
    return 0;
}

void getText(char* holdText, int arraySize) {
    char* findEndline;
    if (fgets(holdText, arraySize, stdin) != NULL) {
        findEndline = strchr(holdText, '\n');
        if (findEndline != NULL) {
            *findEndline = '\0';
        }
    }
}

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

void clearList(struct list** firstElement) {
    struct list* temp;
    while (*firstElement) {
        temp = (*firstElement)->next;
        free(*firstElement);
        *firstElement = temp;
    }
}

int loadFile(struct list** activeElement, struct list** firstElement, char* filename) {
    FILE* file;
    int fileLenght = 0;
    struct contact loadContact;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Plik nie zostal otworzony\n");
        return 2;
    }
    fseek(file, 0, SEEK_END);
    fileLenght = ftell(file);
    rewind(file);
    if (*activeElement != NULL) {
        struct list* temp = *firstElement;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        *activeElement = temp;
    }
    while (fscanf(file, "%[^;]", loadContact.name) != EOF) {
        fscanf(file, "%*c");
        fscanf(file, "%[^;]", loadContact.surname);
        fscanf(file, "%*c");
        fscanf(file, "%[^;]", loadContact.number);
        fscanf(file, "%*c");
        fscanf(file, "%[^;\n]", loadContact.group);
        if (fileLenght != ftell(file)) {
            fscanf(file, "%*c");
        }
        if (pushBack(activeElement, &loadContact, firstElement) == 3) {
            printf("Blad alokacji, zamykam!\n");
            fclose(file);
            return 3;
        }
    }
    fclose(file);
    return 0;
}

void printList(struct list* firstElement) {
    struct list* temp = firstElement;
    while (temp != NULL) {
        printf("%s   %s   %s   %s  \n", temp->data.name, temp->data.surname, temp->data.number, temp->data.group);
        temp = temp->next;
    }
}

void replace(struct list** activeElement) {
    struct list* replacedElement = (*activeElement)->next;
    struct list* ptrToPrevious = (*activeElement)->previous;
    if (ptrToPrevious != NULL) {
        ptrToPrevious->next = replacedElement;
    }
    replacedElement->previous = (*activeElement)->previous;
    (*activeElement)->next = replacedElement->next;
    ptrToPrevious = replacedElement->next;
    if (ptrToPrevious != NULL) {
        ptrToPrevious->previous = *activeElement;
    }
    (*activeElement)->previous = replacedElement;
    replacedElement->next = *activeElement;
}

int compare(struct list** activeElement, struct list** ptrToNext, int sortBy) {
    if (sortBy == 1) {
        if (strcoll((*ptrToNext)->data.name, (*activeElement)->data.name) == -1) {
            return 1;
        }
        else
            return 0;
    }
    else if (sortBy == 2) {
        if (strcoll((*ptrToNext)->data.surname, (*activeElement)->data.surname) == -1) {
            return 1;
        }
        else
            return 0;
    }
    else if (sortBy == 3) {
        if (strcoll((*ptrToNext)->data.group, (*activeElement)->data.group) == -1) {
            return 1;
        }
        else
            return 0;
    }
    return 0;
}

int sort(struct list** activeElement, struct list** firstElement, int sortBy) {
    int n = sizeOfList(firstElement);
    *activeElement = *firstElement;
    struct list* tempPtr = (*activeElement)->next;
    do {
        for (int i = 0; i < n - 1; i++) {
            if (tempPtr != NULL) {
                if (compare(activeElement, &tempPtr, sortBy) == 1) {
                    replace(activeElement);
                    if (*activeElement == *firstElement) {
                        *firstElement = tempPtr;
                    }
                    tempPtr = (*activeElement)->next;
                }
                else {
                    *activeElement = tempPtr;
                    tempPtr = (*activeElement)->next;
                }
            }
        }
        *activeElement = *firstElement;
        tempPtr = (*activeElement)->next;
        n = n - 1;
    } while (n > 1);
    return 0;
}

void toLower(char* text, int size) {
    for (int i = 0; i < size; i++) {
        if (text[i] >= 65 && text[i] <= 95) {
            text[i] += 32;
        }
    }
}

int findString(struct list** firstElement, char* input, char* whichContactDelete) {
    struct contact copyContact;
    struct list* activeElement = *firstElement;
    bool compareGroup = false;
    int count = 0;
    int listSize = sizeOfList(firstElement);
    for (int i = 0; i < listSize; i++) {
        memcpy(&copyContact, &activeElement->data, sizeof(struct contact));
        toLower(copyContact.name, sizeof(copyContact.name));
        toLower(copyContact.surname, sizeof(copyContact.surname));
        if (strstr(copyContact.name, input) != NULL || strstr(copyContact.surname, input) != NULL) {
            if (whichContactDelete != NULL) {
                whichContactDelete[i] = '1';
            }
            else {
                printf("%s   %s   %s   %s  \n", activeElement->data.name, activeElement->data.surname, activeElement->data.number, activeElement->data.group);
            }
            count++;
        }
        activeElement = activeElement->next;
    }
    if (count == 0) {
        printf("Nie znalazlem nic\n");
        return 1;
    }
    return 0;
}

int insert(struct list** activeElement, struct list** firstElement, int sortBy, bool isSorted) {
    struct contact newContact;
    printf("Wprowadz imie: \n");
    while (getchar() != '\n');
    getText(newContact.name, sizeof(newContact.name));
    printf("Wprowadz nazwisko: \n");
    getText(newContact.surname, sizeof(newContact.surname));
    printf("Wprowadz numer: \n");
    getText(newContact.number, sizeof(newContact.number));
    printf("Wprowadz grupe: \n");
    getText(newContact.group, sizeof(newContact.group));
    struct list* temp = *firstElement;
    if (temp != NULL) {
        while (temp->next != NULL) {
            temp = temp->next;
        }
    }
    *activeElement = temp;
    if (pushBack(activeElement, &newContact, firstElement) == 3) {
        return 3;
    }
    if (isSorted) {
        sort(activeElement, firstElement, sortBy);
        return 0;
    }
    return 0;
}

int searchGroup(struct list** firstElement, char* input, int sizeOfInput) {
    char copyGroup[numberOfLetters];
    char previousGroup[numberOfLetters];
    struct list* activeElement = *firstElement;
    bool oneMatch = true;
    bool foundAnyMatch = false;
    int count = 0;
    int listSize = sizeOfList(firstElement);
    printf("Znalezione kontakty: \n\n");
    while (1) {
        activeElement = *firstElement;
        oneMatch = true;
        count = 0;
        foundAnyMatch = false;
        for (int i = 0; i < listSize; i++) {
            strcpy(copyGroup, activeElement->data.group);
            toLower(copyGroup, sizeof(copyGroup));
            if (strstr(copyGroup, input) != NULL) {
                foundAnyMatch = true;
                printf("%s   %s   %s   %s  \n", activeElement->data.name, activeElement->data.surname, activeElement->data.number, activeElement->data.group);
                if (count == 0) {
                    strcpy(previousGroup, copyGroup);
                    count++;
                }
                if (strcmp(copyGroup, previousGroup) != 0) {
                    oneMatch = false;
                }
                strcpy(previousGroup, copyGroup);
            }
            activeElement = activeElement->next;
        }
        if (oneMatch == true && foundAnyMatch == true) {
            return 0;
        }
        if (foundAnyMatch == false) {
            printf("Nie znalazlem nic takiego, wprowadz inna grupe\n");
        }
        else {
            printf("Doprecyzuj jakiej grupy szukasz\n");
        }
        getText(input, sizeOfInput);
        toLower(input, sizeOfInput);
    }
    return 0;
}

int deleteContact(struct list** firstElement, struct list** activeElement, char* input) {
    struct list* tempPtr = *firstElement;
    int count = 0;
    int choice;
    int listSize = sizeOfList(firstElement);
    char* whichContactDelete = malloc(listSize * sizeof(char));
    if (whichContactDelete == NULL) {
        printf("Blad alokacji\n");
        return 3;
    }
    for (int i = 0; i < listSize; i++)
        whichContactDelete[i] = '0';
    while (1337) {
        if (!findString(firstElement, input, whichContactDelete)) {
            printf("Znaleziono nastepujace kontakty: \n");
        }
        for (int i = 0; i < listSize; i++) {
            if (whichContactDelete[i] == '1') {
                count++;
                printf("%d. %s   %s   %s   %s  \n", count, tempPtr->data.name, tempPtr->data.surname, tempPtr->data.number, tempPtr->data.group);
            }
            tempPtr = tempPtr->next;
        }
        if (count != 0) {
            break;
        }
        tempPtr = *firstElement;
        getText(input, numberOfLetters);
    }
    printf("Wybierz z listy ktory kontakt chcesz usunac: \n");
    choice = safeScanf();
    tempPtr = *firstElement;
    count = 0;
    if (choice >= 1 && choice <= listSize) {
        for (int i = 0; i < listSize; i++) {
            if (whichContactDelete[i] == '1') {
                count++;
                if (count == choice) {
                    *activeElement = tempPtr->previous;
                    if (*activeElement == NULL) {
                        *firstElement = tempPtr->next;
                    }
                    else {
                        (*activeElement)->next = tempPtr->next;
                    }
                    *activeElement = tempPtr->next;
                    if (*activeElement != NULL) {
                        (*activeElement)->previous = tempPtr->previous;
                    }
                    free(tempPtr);
                    free(whichContactDelete);
                    return 0;
                }
            }
            tempPtr = tempPtr->next;
        }
    }
    else {
        printf("Nie ma takiej opcji\n");
    }
    free(whichContactDelete);
    return 0;
}

void printMenu(int* choice) {
    printf("1.Wczytaj kontakty z pliku\n2.Wyswietl liste\n3.Sortuj liste\n4.Wyszukaj kontakt\n5.Wyszukaj kontakty z tej samej grupy\n6.Dodaj kontakt\n7.Usun kontakt\n8.Koniec\n");
    *choice = safeScanf();
    system("cls");
}

int main() {
    setlocale(LC_ALL, "polish_poland");
    struct list* activeElement = NULL;
    struct list* firstElement = NULL;
    bool isSorted = false;
    bool isFinish = false;
    char input[30];
    char fileName[25];
    int sortBy = 0;
    int choice, result;
    printMenu(&choice);
    while (!isFinish) {
        switch (choice) {
        case 1:
            printf("Jaki plik otwieramy? (bez .csv) \n");
            while (getchar() != '\n');
            getText(fileName, sizeof(fileName));
            strcat(fileName, ".csv");
            result = loadFile(&activeElement, &firstElement, fileName);
            if (result == 3) {
                clearList(&firstElement);
                return 3;
            }
            if (result != 2)
                printf("Sukces!\n");
            printMenu(&choice);
            break;
        case 2:
            printList(firstElement);
            printf("Sukces!\n");
            printMenu(&choice);
            break;
        case 3:
            if (sizeOfList(&firstElement)) {
                printf("Wedlug: \n1.Imienia\n2.Nazwiska\n3.Grupy\n(Podaj numer)\n");
                sortBy = safeScanf();
                if (sortBy >= 1 && sortBy <= 3) {
                    if (sort(&activeElement, &firstElement, sortBy) == 0) {
                        isSorted = true;
                    }
                    printf("Sukces!\n");
                }
                else {
                    printf("Nie ma takiej opcji\n");
                }
            }
            else {
                printf("Zacznij od dodania kontaktow!\n");
            }
            printMenu(&choice);
            break;
        case 4:
            if (sizeOfList(&firstElement)) {
                printf("Podaj ciag znakow do wyszukania: \n");
                while (getchar() != '\n');
                getText(input, sizeof(input));
                toLower(input, sizeof(input));
                findString(&firstElement, input, NULL);
            }
            else {
                printf("Lista jest pusta!\n");
            }
            printMenu(&choice);
            break;
        case 5:
            if (sizeOfList(&firstElement)) {
                printf("Wprowadz nazwe grupy\n");
                while (getchar() != '\n');
                int size = sizeof(input);
                getText(input, size);
                toLower(input, size);
                searchGroup(&firstElement, input, size);
            }
            else {
                printf("Zacznij od dodania kontaktow!\n");
            }
            printMenu(&choice);
            break;
        case 6:
            if (insert(&activeElement, &firstElement, sortBy, isSorted) == 3) {
                clearList(&firstElement);
                return 3;
            }
            printMenu(&choice);
            break;
        case 7:
            if (sizeOfList(&firstElement)) {
                printf("Wyszukaj po nazwie lub nazwisku\n");
                while (getchar() != '\n');
                getText(input, sizeof(input));
                if (deleteContact(&firstElement, &activeElement, input) == 3) {
                    clearList(&firstElement);
                    return 3;
                }
            }
            else {
                printf("Zacznij od dodania kontaktu!\n");
            }
            printMenu(&choice);
            break;
        case 8:
            isFinish = true;
            break;
        default:
            printMenu(&choice);
            break;
        }
    }
    clearList(&firstElement);
    _CrtDumpMemoryLeaks();
    return 0;
}