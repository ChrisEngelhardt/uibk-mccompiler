#include <stdio.h>

void print(const char *msg);
void print_nl(void);
void print_int(long x);
void print_float(float x);
long read_int(void);
float read_float(void);

void print(const char *msg)
{
	printf("%s", msg);
}

void print_nl(void)
{
	printf("\n");
}

void print_int(long x)
{
	printf("%ld", x);
}

void print_float(float x)
{
	printf("%f", x);
}

long read_int(void)
{
	long ret = 0;
	scanf("%ld", &ret);
	return ret;
}

float read_float(void)
{
	float ret = 0.0f;
	scanf("%f", &ret);
	return ret;
}
