int main()
{
	int i;
	int j;
	i = 0;
	j = 0;

	while(i < 4){
		j = 0;
		while(j < 3){
			print_int(i);
			print_nl();
			print_int(j);
			print_nl();
			j = j + 1;
		}
		i = i + 1;
	}
	
	return 0;
}

