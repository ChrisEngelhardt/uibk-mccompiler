int main()
{
	bool first;
	bool second;
	first = true;
	second = false;

	if(first != second){
		print("true");
		print_nl();
	}else{
		print("false");
		print_nl();
	}
	if(first != first){
		print("true");
		print_nl();
	}else{
		print("false");
		print_nl();
	}
	if(second != second){
		print("true");
		print_nl();
	}else{
		print("false");
		print_nl();
	}
	if(first != true){
		print("true");
		print_nl();
	}else{
		print("false");
		print_nl();
	}
	if(second != true){
		print("true");
		print_nl();
	}else{
		print("false");
		print_nl();
	}
	return 0;
}

