bool firstFunc(bool first, bool second, bool third){
	return first && (second || third) && !second;
}

int main()
{
	if(firstFunc(true,false,true)){
		print("true");
	}else{
		print("false");
	}
	print_nl();

	return 0;
}

