float foo(float first){
	first = 7.2028;
	return 8.1213;
}

int main()
{
	float first;
	float second;
	first = 3.129;
	second = 0.0;

	second = foo(first);

	print_float(first);
	print_nl();
	print_float(second);
	print_nl();
	return 0;
}

