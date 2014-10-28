#include <stdio.h>

void a_julia();
void a_cameras();


int main(int argc, char* argv[])
{
	printf("starting a_julia \n");
	//a_julia();
	printf("a_julia finished \n starting a_cameras \n");
    a_cameras();
    printf("finished a_cameras \n");
    return 0;
}
