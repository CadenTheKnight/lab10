#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie* children = struct Trie[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    if(pTrie == NULL){
        pTrie = createTrie();
        return;
    }
    
    int wordIdx = 0;
    int wordLen = sizeof(word)/sizeof(char);
    struct Trie* tmp = pTrie;
    
    while(wordIdx < wordLen){
        char ch = word[wordIdx];
        if(tmp->children[ch - 'a'] == NULL){
            tmp->children[ch - 'a'] = createTrie();
            wordIdx++;
        } 
        else{
            wordIdx++;
            tmp = tmp->children[ch - 'a'];
        }
    }
    
    //reached the end
    char ch = word[wordIdx];
    if(tmp->children[ch - 'a'] == NULL){
        tmp->children[ch - 'a'] = createTrie();
        tmp = tmp->children[ch - 'a'];
        tmp->count = 1;
    }
    else {
        tmp = tmp->children[ch - 'a'];
        tmp->count += 1;
    }
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if(pTrie == NULL){
        return 0;
    }
    
    int wordIdx = 0;
    int wordLen = sizeof(word)/sizeof(char);
    struct Trie* tmp = pTrie;
    
    while(wordIdx < wordLen){
        char ch = word[wordIdx];
        if(tmp->children[ch - 'a'] == NULL){
            return 0;
        } 
        else{
            wordIdx++;
            tmp = tmp->children[ch - 'a'];
        }
    }
    
    //reached the end
    char ch = word[wordIdx];
    if(tmp->children[ch - 'a'] == NULL){
        return 0;
    }
    else {
        tmp = tmp->children[ch - 'a'];
        return tmp->count;
    }
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie == NULL) return NULL;
    
    for(int i = 0; i < 26; i++){
        deallocateTrie(pTrie->children[i]);
    }
    
    if(hasNoChildren(pTrie)) {
        free(pTrie);
        return NULL;
    }

    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* t = malloc(sizeof(struct Trie));
    t.count = 0;
    return t;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    
}

//helper function for deallocating the function
int hasNoChildren(struct Trie* node){
    if(node == NULL) return 1;
    for(int i = 0; i < 26; i++){
        if(node->children[i] != NULL){
            return 0;
        }
    }
    return 1;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}

