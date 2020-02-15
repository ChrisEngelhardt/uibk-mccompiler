int main()
{
	float first;
	float second;
	float third;

	first = 5.45;
	second = 7.1;
	third = 5.450;

	if(first < second){
		print("true");
		print_nl();
	}else{
		print("false");
		print_nl();
	}
	if(second < first){
		print("true");
		print_nl();
	}else{
		print("false");
		print_nl();
	}
	if(first < third){
		print("true");
		print_nl();
	}else{
		print("false");
		print_nl();
	}

	return 0;
}

