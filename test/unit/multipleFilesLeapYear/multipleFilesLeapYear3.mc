int main()
{
  print("Please enter a year: ");
  print_nl();

  int n;
  n = read_int();

  print_int(n);
  if (isLeapYear(n)){
    print(" is a leap year.");
  }
  else
  {
    print(" is not a leap year.");
  }
  print_nl();

  return 0;
}
