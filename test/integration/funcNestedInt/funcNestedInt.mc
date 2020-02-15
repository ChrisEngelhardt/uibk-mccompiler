int secondFunc(int elem){
	return elem + 13;
}

int firstFunc(int elem){
	return secondFunc(elem) + 12;
}

int main()
{
	int elem;
	elem = 17;

	print_int(firstFunc(elem));
	print_nl();

	return 0;
}