typedef struct{
  int N, M, P, Q;
  int X[100], Y[100];
  int b[100], e[100];
  char s[100], d[100];
  int k[100];
} inputdata;
void out(inputdata data){
  int i;
  printf("%d %d %d %d\n", data.N, data.M, data.P, data.Q);
  printf("-----N-----\n");
  for(i=0; i<data.N; i++){
    printf("%d %d\n", data.X[i], data.Y[i]);
  }
  printf("-----M-----\n");
  for(i=0; i<data.M; i++){
    printf("%d %d\n", data.b[i], data.e[i]);
  }
  printf("-----P-----\n");
  for(i=0; i<data.P; i++){
    printf("%d %d\n", data.X[data.N+i], data.Y[data.N+i]);
  }
}
void out_Q(inputdata data, int i){
  printf("%s %s %d\n", data.s, data.d, data.k[i]);
}
void out_G(int cnt, int N, double **G){
  int i, j;
  printf("   ");
  for(i=0; i<N+cnt; i++) printf("     [%2d]", i);
  printf("\n");
  for(i=0; i<N+cnt; i++){
    printf("[%2d]", i);
    for(j=0; j<N+cnt; j++){
      printf("%8.5f ", G[i][j]);
    }
    printf("\n");
  }
}
