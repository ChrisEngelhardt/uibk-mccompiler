int main()
{
	float i;
	float j;
	i = 0.0;
	j = 0.0;

	while(i < 4.0){
		j = 0.0;
		while(j < 3.0){
			print_float(i);
			print_nl();
			print_float(j);
			print_nl();
			j = j + 1.0;
		}
		i = i + 1.0;
	}
	
	return 0;
}

