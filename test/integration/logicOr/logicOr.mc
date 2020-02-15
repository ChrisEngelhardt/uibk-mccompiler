int main()
{
	bool first;
	bool second;
	first = true;
	second = false;

	if(first || first){
		print("first");
		print_nl();
	}
	if(first || second){
		print("second");
		print_nl();
	}
	if(second || second){
		print("third");
		print_nl();
	}
	
	return 0;
}

