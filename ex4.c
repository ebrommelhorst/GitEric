 
#include<stdio.h>
#include<string.h>
void main()
{
    int i=0;
    char arr1[ 15 ] = "Trumantiger";
    char arr2[ 15 ];
    while(i<15){
        arr2[ i ] = 'A';
	++i;
    }
	arr2[14] = '\0';
    strcpy( arr1 , arr2 );
    printf("%s",arr1);
}