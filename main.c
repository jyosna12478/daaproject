#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"header.h"
#include"string_matching.c"
#define MAX_LIMIT 3000

char *input_string();
double time_elapsed(struct timespec *start, struct timespec *end) {
    double t;
    t = (end->tv_sec - start->tv_sec); 
    t += (end->tv_nsec - start->tv_nsec) * 0.000000001;
    return t;
}


void main()
{
	struct timespec s,e;
	int ch=-1,pos=-1;
	char *text;
	char *pat = (char*)malloc(sizeof(char)*100);
	printf("\nEnter Text: ");
	text = input_string();
	printf("Enter pattern : ");
	pat = input_string();	
	printf("\nSTRING MATCHING LIBRARY MENU\n");
	printf("1.Naive\n");
	printf("2.Horspool\n");
	printf("3.Rabin Karp\n");
	printf("4.Knuth Morris prath\n");
	printf("5.EXIT\n");
	printf("\n\n");
	printf("Enter your option:\t");
	scanf("%d",&ch);
	
	
	switch(ch)
	{
		case 1:  clock_gettime(CLOCK_REALTIME,&s); 
			 pos = naive(text,pat);
			 clock_gettime(CLOCK_REALTIME,&e);
			 printf("The pos is : %d\n",pos);
    			 printf("%lf sec\n",time_elapsed(&s, &e));
			 break;
		
		case 2:  clock_gettime(CLOCK_REALTIME,&s); 
			 pos = horspool(text,pat);
			 printf("The position is:%d\n",pos);
			 clock_gettime(CLOCK_REALTIME,&e);
    			 printf("%lf sec\n",time_elapsed(&s, &e));
			 break;
		
		case 3:  clock_gettime(CLOCK_REALTIME,&s);
			 pos = rabin_karp(text,pat);
			 clock_gettime(CLOCK_REALTIME,&e);
 			 printf("The position is:%d\n",pos);
    			 printf("%lf sec\n",time_elapsed(&s, &e));
			 break;
		
		case 4:  clock_gettime(CLOCK_REALTIME,&s);
			 int n = strlen(text);
			 int m = strlen(pat);
			 pos=kmp(text,pat,n,m);
			 clock_gettime(CLOCK_REALTIME,&e);
			 printf("The position is:%d\n",pos);
    			 printf("%lf sec\n",time_elapsed(&s, &e));
			 break;
		
		case 5:  exit(0);
			 break;
		
		default: printf("You have entered wrong choice!! Enter again.");
			 main();
	}
	
	printf("\n\n");
	//main();
}

char *input_string()
{
	char str[MAX_LIMIT + 1] = {0};
	char *text = NULL, *temp_text = NULL;
	int length = 0, temp_length = 0;
	while(strlen(str) % MAX_LIMIT == 0)	//Go until max limit
	{
	    temp_length = length;		
	    temp_text = text;
	    scanf("%3000[^\t^\n]%*c", str);		//buffer 3000 characters

	// Reallocate 128 bytes more for the currently read buffer until the end of input and till out of memory bound
	    if(text = realloc(text, (length = length + strlen(str)) + 128))
	    {
		strcpy(text + temp_length, str);  //append the current buffer to "text"
		continue;
	    }
	    free(temp_text);
	    printf("Out of memory");
	    return NULL;
	}
	printf("\n");
	return text;
}


