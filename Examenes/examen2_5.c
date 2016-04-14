#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define N 6

int main()
{
    srand(time(NULL));
    int * num = (int*)malloc(N*sizeof(int));
    int sum = 0;
	int j = 0;
	#pragma omp parallel shared(sum) private(j)
	{
    	#pragma omp sections
        {
            #pragma omp section
            {
                #pragma omp parallel for
                for (j=0; j < N; j++){
                    *(num+j) = rand() % 10;
                    printf("num %d-->%d\n", j,*(num+j));
                    sum += *(num+j);
                }
            }
			#pragma omp section
            {
				int i = 0;
            	omp_set_nested(1);
                #pragma omp parallel num_threads(4) shared(i)
                {
                    #pragma omp critical
                    {
                        printf("thread--->%d\n", i);
                        i++;
                    }
                }
            }
        }
    }

    printf("SUM :: %d\n", sum);

    return 0;

}
