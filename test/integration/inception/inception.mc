int test(){
  if(true){
    if(false){
      return 0;
    } else {
      while (true){
        if(true){
          return 1;
        } else {
          return 0;
        }
      }
      return 0;
    }
  } else {
    return 0;
  }
}


int main() {
  print_int(test());
  print_nl();
  return 0;
}
