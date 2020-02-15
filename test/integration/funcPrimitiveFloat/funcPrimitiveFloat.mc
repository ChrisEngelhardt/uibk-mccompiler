float firstFunc(float first, float second, float third){
	return (first*second) + first - (third/first);
}

int main()
{
	print_float(firstFunc(10.12,7.11,40.9));
	print_nl();

	return 0;
}

