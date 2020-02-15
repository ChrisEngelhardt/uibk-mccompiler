void firstFunc(string[8] elem){
	elem[4] = "success";
}

int main()
{
	string[8] first;

	firstFunc(first);

	print(first[4]);
	print_nl();

	return 0;
}

