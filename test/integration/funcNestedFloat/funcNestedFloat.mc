float secondFunc(float elem){
	return elem + 1.2;
}

float firstFunc(float elem){
	return secondFunc(elem) + 0.19;
}

int main()
{
	float elem;
	elem = 4.72;

	print_float(firstFunc(elem));
	print_nl();

	return 0;
}