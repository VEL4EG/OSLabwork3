#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define FIB_NUM_COUNT 100
#define THREADS_COUNT 10
#define DIGITS_COUNT 21

void* printFib(void *threadNumber);
// a += b
void plusAssignBigNum(char *a, char const *b, size_t digitsCount);
void printBigNum(const char *bN, size_t digitsCount);
// a = b
void assignBigNum(char *a, const char *b, size_t digitsCount);
void minusBigNum(char *result, const char *minuend, const char *subtrahend, size_t digitsCount);

int main()
{
	uint numbers[THREADS_COUNT];
	pthread_t threads[THREADS_COUNT];
	
	for (int i = 0; i < THREADS_COUNT; i++)
	{
		numbers[i] = i + 1;
		
		errno = pthread_create(threads + i, NULL, printFib, numbers + i);
		
		if (errno != 0)
		{
			printf("Error: %s\n", strerror(errno));
			return -1;
		}
	}
		
		for (int i = 0; i < THREADS_COUNT; i++)
		{
			errno = pthread_join(threads[i], NULL);
			if (errno != 0)
			{
				printf("Error: %s\n", strerror(errno));
				return -1;
			}
		}

	return 0;
}

// a += b
void plusAssignBigNum(char *a, char const *b, size_t digitsCount)
{
	for (int i = digitsCount - 1; i >= -1; i--)
	{
		a[i] += b[i];

		if (a[i] >= 10)
		{
			a[i] -= 10;

			if (i > 0)
			a[i-1]++;
		}
	}
}

void minusBigNum(char *result, const char *minuend, const char *subtrahend, size_t digitsCount)
{
	for (size_t i = 0; i < digitsCount; i++)
	result[i] = minuend[i];

	for (int i = digitsCount - 1; i >= -1; i--)
	{
		result[i] -= subtrahend[i];

		if (result[i] < 0)
		{
			result[i] += 10;

			if (i > 0)
			result[i-1]--;
		}
	}
}

// a = b
void assignBigNum(char *a, const char *b, size_t digitsCount)
{
	for (size_t i = 0; i < digitsCount; i++)
	a[i] = b[i];
}

void printBigNum(const char *bN, size_t digitsCount)
{
	size_t i = 0;
	
	for (; i < digitsCount - 1; i++)
	{
		if (bN[i] != 0)
		break;
	}

	for (; i < digitsCount; i++)
	printf("%d", bN[i]);

	printf("\n");
}

void* printFib(void *threadNumber)
{
	uint *num = (uint*) threadNumber;
	char next[DIGITS_COUNT], prev[DIGITS_COUNT], temp[DIGITS_COUNT];

	next[DIGITS_COUNT - 1] = 1;
	prev[DIGITS_COUNT - 1] = 0;
	
	for (size_t i = 0; i < DIGITS_COUNT - 1; i++)
	next[i] = prev[i] = 0;
	
	printf("Thread %d Num%d = ", *num, 1);
	printBigNum(prev, DIGITS_COUNT);
	
	printf("Thread %d Num%d = ", *num, 2);
	printBigNum(next, DIGITS_COUNT);
	
	for (int i = 3; i <= FIB_NUM_COUNT; i++)
	{
		assignBigNum(temp, next, DIGITS_COUNT);
		plusAssignBigNum(next, prev, DIGITS_COUNT);
		assignBigNum(prev, temp, DIGITS_COUNT);
		
		printf("Thread %d Num%d = ", *num, i);
		printBigNum(next, DIGITS_COUNT);
		
	}
	
	return 0;
}
