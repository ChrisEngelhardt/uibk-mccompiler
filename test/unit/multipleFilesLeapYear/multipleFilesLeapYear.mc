bool isLeapYear(int n)
{
  if ((modulo(n,4) == 0 && modulo(n,100) != 0) || (modulo(n,400) == 0)){
    return true;
  }
  return false;
}