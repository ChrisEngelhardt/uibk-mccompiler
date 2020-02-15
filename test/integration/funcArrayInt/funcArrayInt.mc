void firstFunc(int[8] elem){
	elem[4] = 24;
}

int main()
{
	int[8] first;

	firstFunc(first);

	print_int(first[4]);
	print_nl();

	return 0;
}

