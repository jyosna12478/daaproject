#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//////////////////////////////////////////////NAIVE////////////////////////////////////////////

int naive(char *text, char *pattern)
{
	int n=strlen(text);
	int m=strlen(pattern);
	if (n==0 || m==0){
		return -1;
	}
	for(int i = 0; i<=n-m; i++)
	{
		int j = 0;
		while(j<m && text[i+j] == pattern[j])
		{
			j++;
		}
		if(j==m)
		{
			//printf("%d\n", i+1);
			return i;
		}
	}
	//printf("%d\n",-1);
	return -1;
}


///////////////////////////////HORSPOOL//////////////////////////////////////////////////

int horspool(char *text, char *pattern)
{
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    int  i;
    int *table = (int*)malloc(sizeof(int)*300);
    table = shiftTable(pattern);
    i = pattern_len - 1 ;
    int j = 0 ;
    while(i < text_len)
    {
        j = 0;
        while(j<pattern_len && text[i-j] == pattern[pattern_len-1-j])
            j = j + 1;
        if(j == pattern_len)
            return i-(pattern_len-1);
        i = i + table[text[i]];    
    }
    return -1; 
}
int* shiftTable(char* pattern){
    int pattern_len = strlen(pattern);
    int *table = (int*)malloc(sizeof(int)*300);
    for(int i = 0 ; i<300; i++)
        table[i] = pattern_len;

    for(int i = 0 ; i<pattern_len-1 ; i++)
        table[pattern[i]] = pattern_len-1-i;
    return table;
}


//////////////////////////////////////////RABIN KARP///////////////////////////////////////


#define d 256 
  

int rabinkarp(char pattern[], char target[], int q) 
{ 
    int M = strlen(pattern); 
    int N = strlen(target); 
    int i, j; 
    int phash = 0; 
    int thash = 0;  
    int h = 1; 
   
    for (i = 0; i < M-1; i++) 
        h = (h*d)%q; //calculating base value
  
   
    for (i = 0; i < M; i++) //calculating hash value for pattern and for the first m characters in the text
    { 
        phash = (d*phash + pattern[i])%q; 
        thash = (d*thash + target[i])%q; 
    } 
  
     
    for (i = 0; i <= N - M; i++) 
    { 
   
        if ( phash == thash ) 
        { 
            for (j = 0; j < M; j++) 
            { 
                if (target[i+j] != pattern[j]) 
                    break; 
            }  
            if (j == M) 
            {    //printf("Pattern found at index %d \n", i); 
		return i;
	     }
        } 
  
        // Calculate hash value for the next block of m characters in the text 
        if ( i < N-M ) 
        { 
            thash = (d*(thash - target[i]*h) + target[i+M])%q; //deleting the hash value of the first chacter of previous block and add the 									hash value of the last character in the current block
 	    // Assigning the prime value to the text hash when its is less than zero 
            if (thash < 0) 
            thash = (thash + q); 
        } 
    } 
	return -1;
} 
  

int rabin_karp(char *target, char *pattern) 
{ 
    int q = 101; // A prime number 
    int pos=-1;
    pos = rabinkarp(pattern, target, q); 
    return pos; 
} 



 

//////////////////////////////////////////////KMP///////////////////////////////////////////////////


int *pi_table(char *pattern, int psize)
{
	int k = -1;
	int i = 1;
	int *pi = malloc(sizeof(int)*psize);
	if (!pi)
		return NULL;

	pi[0] = k;
	for (i = 1; i < psize; i++) {
		while (k > -1 && pattern[k+1] != pattern[i])
			k = pi[k];
		if (pattern[i] == pattern[k+1])
			k++;
		pi[i] = k;
	}
	return pi;
}

int kmp(char *target, char *pattern,int tsize, int psize)
{
	int i;
	int *pi = pi_table(pattern, psize);
	int k = -1;
	if (!pi)
		return -1;
	for (i = 0; i < tsize; i++) {
		while (k > -1 && pattern[k+1] != target[i])
			k = pi[k];
		if (target[i] == pattern[k+1])
			k++;
		if (k == psize - 1) {
			free(pi);
			return i-k;
		}
	}
	free(pi);
	return -1;
}









