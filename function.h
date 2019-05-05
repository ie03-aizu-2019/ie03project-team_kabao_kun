typedef struct{
  int N;
  int M;
  int Q;
  int P;
  int X[100];
  int Y[100];
  int b[100];
  int e[100];
} inputdata;

void out(inputdata data){
  int i;
  printf("%d %d %d %d\n", data.N, data.M, data.Q, data.P);
  for(i=0; i<data.N; i++){
    printf("%d %d\n", data.X[i], data.Y[i]);
  }
  for(i=0; i<data.M; i++){
    printf("%d %d\n", data.b[i], data.e[i]);
  }
}

/*
int function1(inputdata data){
  return 
}
*/
