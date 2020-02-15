float aa(){
	return 3.14;
}

int main(){
	float a;

	a = read_float();

	print_float(a);
	print_nl();

	print_float(aa());
	print_nl();

	return 0;
}
