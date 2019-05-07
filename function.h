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

int function1(int mat[4][2]){
  return ((mat[1][0]-mat[0][0])*(mat[2][1]-mat[3][1])+(mat[3][0]-mat[2][0])*(mat[1][1]-mat[0][1]));
}

double calc_S(int mat[4][2], int abs_A){
  double s;
  s = ((mat[2][1]-mat[3][1])*(mat[2][0]-mat[0][0])+(mat[3][0]-mat[2][0])*(mat[2][1]-mat[0][1]));
  return s/abs_A;
}

double calc_T(int mat[4][2], int abs_A){
  double t;
  t = ((mat[0][1]-mat[1][1])*(mat[2][0]-mat[0][0])+(mat[1][0]-mat[0][0])*(mat[2][1]-mat[0][1]));
  return t/abs_A;
}
