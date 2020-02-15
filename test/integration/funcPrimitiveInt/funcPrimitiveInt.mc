int firstFunc(int first, int second, int third){
	return (first*second) + first - (third/first);
}

int main()
{
	print_int(firstFunc(10,7,40));
	print_nl();

	return 0;
}

