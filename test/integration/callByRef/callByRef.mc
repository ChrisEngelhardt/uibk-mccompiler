void add(int[1] first, int[1] second){
	first[0] = first[0] + second[0];
}

int main()
{
	int[1] first;
	int[1] second;
	first[0] = 17;
	second[0] = 25;

	add(first,second);

	print_int(first[0]);
	print_nl();
	return 0;
}