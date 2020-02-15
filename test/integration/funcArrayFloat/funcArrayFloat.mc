void firstFunc(float[8] elem){
	elem[4] = 42.1337;
}

int main()
{
	float[8] first;

	firstFunc(first);

	print_float(first[4]);
	print_nl();

	return 0;
}

