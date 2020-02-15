void firstFunc(bool[8] elem){
	elem[4] = true;
}

int main()
{
	bool[8] first;
	first[4] = false;

	firstFunc(first);

	if(first[4]){
		print("true");
	}else{
		print("false");
	}
	print_nl();

	return 0;
}

