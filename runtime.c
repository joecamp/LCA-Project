#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void function(){
	for (int i = 0; i < 2000000000; i++) {
		int sum = i;


	}
}

// Eventually the main function will take
// an algorithm as it's parameter
int main(){
clock_t begin, end;
double time_spent;

begin = clock();

function();

end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("The time to run the function is %.02f\n",time_spent);

return 0;
}
