/**********************************
Data import/export demo code
Daniel Collins
EC 500 Spring 2011
**********************************/

#include <stdio.h>
#include <stdlib.h>

void print_ooc()
{
	int i,j,k;

	for(i=0;i<10;i++)
	for(j=0;j<i;j++)
	{
		//prints new line if new row, else prints separating comma
		j==0 ? printf("\n") : printf(",");

		k=i*j;
		printf("%d",k);
	}
}

void print_matlab()
{
	int i,j,k;

	for(i=0;i<10;i++)
	{
		for(j=0;j<i;j++)
		{
			//prints new line if new row, else prints separating comma
			j==0 ? printf("\n") : printf(",");

			k=i*j;
			printf("%d",k);
		}

		//Pads rows for MATLAB
		for(j=i;j<10;j++)
		{
			//prints new line if new row, else prints separating comma
			j==0 ? printf("\n") : printf(",");
			printf("NaN");
		}
	}
}



int main()
{
	//print_ooc();
	print_matlab();
	return 0;
}
