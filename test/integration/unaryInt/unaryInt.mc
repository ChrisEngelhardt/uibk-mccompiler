int simpleInt(){
	return -42;
}

int main()
{
	int first;
	int second;
	first = 42;
	second = -42;

	print_int(-first);
	print_nl();
	print_int(second);
	print_nl();
	print_int(simpleInt());
	print_nl();
	
	return 0;
}

