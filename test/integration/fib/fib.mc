int fib(int n)
{
	if (n < 2) {
		return n;
	}

	return fib(n - 1) + fib(n - 2);
}

int main()
{
	int n;
	print("Please enter a number: ");
	n = read_int();

	int result;
	result = fib(n);

	print("fib(");
	print_int(n);
	print(") = ");
	print_int(result);
	print_nl();

	return 0;
}
