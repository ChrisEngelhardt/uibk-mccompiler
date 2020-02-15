int main()
{
	bool first;
	bool second; 
	first = true;
	second = false;

	if(first){
		if(second){
			print("wrong");
		}else{
			print("right");
		}
	}

	print_nl();

	if(first)
		if(second)
			print("wrong");
		else
			print("right");

	print_nl();
	return 0;
}

