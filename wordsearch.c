#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);
char lowerCase(char letter); 
char upperCase(char letter);
void horizontal(char** copy, int n, char* word);
void verticalTopToBottom(char** copy, int n, char* word);
void verticalBottomToTop(char** copy, int n, char* word);
void diagonalTopLeftBottomRight(char** copy, int n, char* word);
void diagonalBottomLeftTopRight(char** copy, int n, char* word);


// Main function, DO NOT MODIFY (except line 52 if your output is not as expected -- see the comment there)!!!	
int main(int argc, char **argv) {
    int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

	// Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
	fclose(fptr);

	// Open file for reading word list
	fptr = fopen("states.txt", "r");
	if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
	
	// Save words into arrays
	for(i = 0; i < 50; i++) {
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);		
	}
	
	// Remove newline characters from each word (except for the last word)
	for(i = 0; i < 49; i++) {
		*(*(words+i) + strlen(*(words+i))-1) = '\0'; // Change -2 to -1 if line 58 outputs words with the last character missing
	}
	
	// Print out word list
	printf("Printing list of words:\n");
	for(i = 0; i < 50; i++) {
		printf("%s\n", *(words + i));		
	}
	printf("\n");
	
	// Print out original puzzle grid
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
	printf("\n");

	// Call searchPuzzle to find all words in the puzzle
	searchPuzzle(block, bSize, words, 50);
	printf("\n");
	
	// Print out final puzzle grid with found words in lower case
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
	printf("\n");
	
    return 0;
}

void printPuzzle(char** arr, int n) {
	// This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
	// Your implementation here
	for(int i=0;i<n; i++){
	  for(int j=0;j<n; j++){
	    printf("%c ", *(*(arr + i) + j));
    }
	printf("\n");
  }


}

void searchPuzzle(char** arr, int n, char** list, int listSize) {
	// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
	// Your implementation here
	
	for(int i=0;i<listSize;i++){
		horizontal(arr, n, *(list+i));
		verticalTopToBottom(arr, n, *(list+i));
		verticalBottomToTop(arr, n, *(list+i));
		diagonalTopLeftBottomRight(arr, n, *(list+i));
		diagonalBottomLeftTopRight(arr, n, *(list+i));

	}

}

char lowerCase(char letter){
	if(letter>=97){
		return letter; //if meets conditional, letter is already lowercase
	}

	char lowercase = letter + 32;
	return lowercase;
}

char upperCase(char letter){
	if(letter<97){
		return letter; //if meets conditional, letter is already uppercase
	}
	char upper=letter-32;
	return upper;
}

void horizontal(char** arr, int n, char* word){ //Works Correctly (left to right search)
	int length=0;
	int begin=0;
	for(int i=0; i<n;i++){ //row
		for(int j=0;j<n;j++){ //column
			if(upperCase(*(word + length)) != *(*(arr + i) + j)){ //Uppercase all words since only first letter is uppercase
				length=0; //If the char does not match, then the built up length will reset till a match is found
			}else{
				if(length==0){//Resetting the length lets you know the previous char's were not a match in the row
					begin=j; // Updates current index
				}
				length+=1; //length of word will increase till a match is found or if there is a char that does not match
				if(length==strlen(word)){ //if match is found
					for(int q=begin;q<(begin + strlen(word));q++){ 
						*(*(arr + i) + q)  = lowerCase(*(*(arr + i) + q)); //sets letters in arr to lowercase in proper index
					}
					printf("Word found: %s\n", word); //prints matched words
				}
			}
		}
	}
}

void verticalTopToBottom(char** arr, int n, char* word){ //Finds all the vertical words, lowerCasing is the issue with this function
	int length=0;
	int begin=0;
	for(int j=0; j<n;j++){ //column
		for(int i=0;i<n;i++){ //row
			if(upperCase(*(word + length)) != upperCase(*(*(arr + i) + j))){ //Uppercase all words since only first letter is uppercase
				length=0; //If the char does not match, then the built up length will reset till a match is found
			}else{
				if(length==0){//Resetting the length lets you know the previous char's were not a match in the row
					begin=i; // Updates current index
				}
				length+=1; //length of word will increase till a match is found or if there is a char that does not match
				if(length==strlen(word)){ //if match is found
					for(int q=begin;q<(begin + strlen(word));q++){ 
						*(*(arr + q) + j)  = lowerCase(*(*(arr + q) + j)); //sets letters in arr to lowercase in proper index
					}
					printf("Word found: %s\n", word); //prints matched words
					//printf("Begin: %d\n", begin);
				}
			}	
		}
	}
}

void verticalBottomToTop(char** arr, int n, char* word){ // Finds the words in the horizontal search w/o lowercasing (not supposed to happen)
int length=0;
int begin=0;
for(int j=0;j<n;j++){
		for(int i=14; i>=0;i--){
			if(upperCase(*(word + length)) != upperCase(*(*(arr + i) + j))){ //Uppercase all words since only first letter is uppercase
				length=0; //If the char does not match, then the built up length will reset till a match is found
			}else{
				if(length==0){//Resetting the length lets you know the previous char's were not a match in the row
					begin=i; // Updates current index
				}
				length+=1; //length of word will increase till a match is found or if there is a char that does not match
				if(length==strlen(word)){ //if match is found
					for(int q=begin;q<(begin + strlen(word));q++){ 
						*(*(arr + q) + j)  = lowerCase(*(*(arr + q) + j)); //sets letters in arr to lowercase in proper index
					}
					printf("Word found: %s\n", word); //prints matched words
					printf("Begin: %d \n", begin);
				}
			}
			//printf("%c ", *(*(arr + i) + j));	
		}
	}
}

void diagonalTopLeftBottomRight(char** arr, int n, char* word){ 
	int length=0;
	int beginR=0;
	int beginC=0;
	for(int i=0; i<n;i++){ //row
		for(int j=0;j<n;j++){ //column
			if(upperCase(*(word + length)) != upperCase(*(*(arr + i) + j))){ //Uppercase all words since only first letter is uppercase
				length=0; //If the char does not match, then the built up length will reset till a match is found
			}else{
				if(length==0){//Resetting the length lets you know the previous char's were not a match in the row
					beginR=i; // Updates current index
					beginC=j;
				}
				length = 1;
				for(int k=1;k<strlen(word);k++){
					if(!((i+k)<n && (j + k)<n)){
						break;
					}
					if(upperCase(*(word + length)) != upperCase(*(*(arr + (i+k)) + (j + k)))){
						length = 0;
						break;
					}
					length++;
				}
				if(length==strlen(word)){ //if match is found
					for(int q=0;q<(strlen(word));q++){ 
						*(*(arr + (beginR+q)) + (beginC+q))  = lowerCase(*(*(arr + (beginR+q)) + (beginC+q))); //sets letters in arr to lowercase in proper index
					}
					printf("Word found: %s\n", word);
				}
			}		
		}
	}
}

void diagonalBottomLeftTopRight(char** arr, int n, char* word){
	int length=0;
	int beginR=0;
	int beginC=0;
	for(int i=0; i<n;i++){
		for(int j=0;j<n;j++){
			if(upperCase(*(word + length)) != upperCase(*(*(arr + i) + j))){ //Uppercase all words since only first letter is uppercase
				length=0; //If the char does not match, then the built up length will reset till a match is found
			}else{
				if(length==0){//Resetting the length lets you know the previous char's were not a match in the row
					beginR=i; // Updates current index
					beginC=j;
				}
				length = 1;
				for(int k=1;k<strlen(word);k++){
					if(!((i-k)>=0 && (j+k)<n)){ //Out of bounds
						break;
					}
					if(upperCase(*(word + length)) != upperCase(*(*(arr + (i-k)) + (j + k)))){
						length = 0;
						break;
					}
					length++;
				}
				if(length==strlen(word)){ //if match is found
					for(int q=0;q<(strlen(word));q++){ 
						*(*(arr + (beginR-q)) + (beginC+q))  = lowerCase(*(*(arr + (beginR-q)) + (beginC+q))); //sets letters in arr to lowercase in proper index
					}
					printf("Word found: %s\n", word);
				}
			}
		}
	}
}
