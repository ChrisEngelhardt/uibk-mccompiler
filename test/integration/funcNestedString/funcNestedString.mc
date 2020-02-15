string secondFunc(string elem){
	return elem;
}

string firstFunc(string elem){
	return secondFunc(elem);
}

int main()
{
	string elem;
	elem = "a";

	print(firstFunc(elem));
	print_nl();

	return 0;
}

