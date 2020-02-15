float simpleFloat(){
	return -42.1337;
}

int main()
{
	float first;
	float second;
	first = 42.1337;
	second = -42.1337;

	print_float(-first);
	print_nl();
	print_float(second);
	print_nl();
	print_float(simpleFloat());
	print_nl();
	
	return 0;
}

