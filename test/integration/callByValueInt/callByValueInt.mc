int foo(int first){
	first = 5;
	return 5;
}

int main()
{
	int first;
	int second;
	first = 3;
	second = 0;

	second = foo(first);

	print_int(first);
	print_nl();
	print_int(second);
	print_nl();
	return 0;
}

