bool simpleTrue(){
	return true;
}

bool simpleFalse(){
	return false;
}

int main()
{
	if(simpleTrue()){
		print("first");
		print_nl();
	}else{
		print("second");
		print_nl();
	}
	if(simpleFalse()){
		print("third");
		print_nl();
	}else{
		print("fourth");
		print_nl();
	}

	return 0;
}

