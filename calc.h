double calc_G(double x, double y){
  return x*x+y*y;
}
int calc_A(int mat[4][2]){
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
void sort(double C[500][2], int Cp[500][6], int cnt){
  int i, j;
  double tmp[2]={};
  int tmp_i[6]={};
  for(i=0; i<cnt-1; i++){
    for(j=cnt-1; j>i; j--){
      if(C[j-1][0] > C[j][0]){
        tmp[0] = C[j-1][0];
        tmp[1] = C[j-1][1];
        tmp_i[2] = Cp[j-1][2];
        tmp_i[3] = Cp[j-1][3];
        tmp_i[4] = Cp[j-1][4];
        tmp_i[5] = Cp[j-1][5];
        C[j-1][0] = C[j][0];
        C[j-1][1] = C[j][1];
        Cp[j-1][2] = Cp[j][2];
        Cp[j-1][3] = Cp[j][3];
        Cp[j-1][4] = Cp[j][4];
        Cp[j-1][5] = Cp[j][5];
        C[j][0] = tmp[0];
        C[j][1] = tmp[1];
        Cp[j][2] = tmp_i[2];
        Cp[j][3] = tmp_i[3];
        Cp[j][4] = tmp_i[4];
        Cp[j][5] = tmp_i[5];
      }
    }
  }
}
void rm(int cnt, int N, double **G){
  int i, j;
  for(i=0; i<N+cnt; i++){
    for(j=0; j<N+cnt; j++){
      if(G[i][j] <= 0) G[i][j] = 0;
    }
  }
}
