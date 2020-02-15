int secondFunc(int first, int second){
	return (first*second) + (first+second);
}

int firstFunc(int first, int second){
	return secondFunc(secondFunc(first,second),secondFunc(first,second));
}

int main()
{
	int first;
	int second;
	first = 3;
	second = 4;

	print_int(firstFunc(first,second));
	print_nl();

	return 0;
}