/*	stackapp.c: Stack application. */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string
	pre: s is not null
*/
char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s+i);
	if ( c == '\0' )
		return '\0';
	else
		return c;
}
/* Checks whether b is the complementary opening bracket to a
	 param: a, b chars
	 pre: a is ), }, or ]
	 			b is (, {, [
	 Returns: 1 if complementary
	 					0 if not complementary
					 -1 by default

*/
int IsComplement(char a, char b)
{
	assert( (a == ')' || a == '}' || a == ']')
				&&(b == '(' || b == '{' || b == '[' || b == 0)	);

	if(b==0)
	{
		return 0;
	}

	switch(a)
	{
		case(')'):
			if(b == '(')
				return 1;
			else if(b == '{' || b == '[')
				return 0;

		case('}'):
			if(b == '{')
				return 1;
			else if(b == '(' || b == '[')
				return 0;

		case(']'):
			if(b == '[')
				return 1;
			else if(b == '(' || b == '{')
				return 0;
	}
	return -1;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string
	pre: s is not null
	post:
*/
int isBalanced(char* s)
{
	char ch;  /*stores the current character from the input string*/
	char ts;  /*stores the top element of the stack*/
	int b=1;  /*Boolean variable b=1 means balanced; b=0 means unbalanced string*/
	DynArr *stack;
	stack = newDynArr(5);/*initialize stack with capacity = 5*/

	if (s && strlen(s))
		while(1)
		{
			ch=nextChar(s);

			if(ch==0 || ch=='\0')
				break;

			if(ch=='(' || ch=='[' || ch=='{' )
			{
				pushDynArr(stack,ch);
				ts = ch;
			}
			else if(ch == ')' || (ch == ']') || (ch == '}'))
			/* FIXME: You will write this part of the function */
			{
				if(IsComplement(ch,ts))
				{
					popDynArr(stack);
					if(stack->size > 0)
						ts = (char)topDynArr(stack);
					else
						ts = 0;
				}
				else
				{
					freeDynArr(stack);
					return b = 0;
				}
			}
		}

	if(stack->size > 0)
	{
		freeDynArr(stack);
		return b = 0;
	}
  /* Free the memory allocated to stack, and return b=1 or b=0 */
	/* FIXME: You will write this part of the function */
	freeDynArr(stack);
	return b;
}


int main(int argc, char* argv[]){

	char* s=argv[1];
/*
	char s[]="()+x+r*{{{((--{{[()[]]}}))}}}";
*/

	int res;

	printf("Assignment 2\n");

	if(argc==2)
	{
		res = isBalanced(s);

		if (res)
			printf("The string %s is balanced\n",s);
		else
			printf("The string %s is not balanced\n",s);
	}
	else
		printf("Please enter a string to be evaluated.\n");


	return 0;
}
