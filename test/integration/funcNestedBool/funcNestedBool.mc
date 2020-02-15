bool secondFunc(bool elem){
	return elem || true;
}

bool firstFunc(bool elem){
	return elem || secondFunc(elem);
}

int main()
{
	bool elem;
	elem = false;

	elem = firstFunc(elem);
	if(elem){
		print("true");
	}else{
		print("false");
	}
	print_nl();

	return 0;
}

