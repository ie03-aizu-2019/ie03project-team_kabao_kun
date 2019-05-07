#include<stdio.h>
#include<stdlib.h>
#include"function.h"

#define MAX 100

int main(){
  int i, j, judge=0;
  double s, t;
  double x, y;
  int abs_A;
  int mat[4][2] = {};
  inputdata data;

  scanf("%d%d%d%d", &(data.N), &(data.M), &(data.Q), &(data.P));
  for(i=0; i<data.N; i++){
    scanf("%d%d", &(data.X[i]), &(data.Y[i]));
  }
  for(i=0; i<data.M; i++){
    scanf("%d%d", &(data.b[i]), &(data.e[i]));
  }

  printf("-----input data-----\n");
  out(data);
  printf("--------------------\n");

  //pick up Xp1,Yp1,...
  i=0;
  for(j=0; j<2; j++){
    mat[i][0] = data.X[data.b[j]-1];
    mat[i][1] = data.Y[data.b[j]-1];
    i++;
    mat[i][0] = data.X[data.e[j]-1];
    mat[i][1] = data.Y[data.e[j]-1];
    i++;
  }
  //finish pick up

  //calc |A|
  abs_A = abs(function1(mat));

  if(abs_A != 0){
    s = calc_S(mat, abs_A);
    t = calc_T(mat, abs_A);
    if((0<s && s<1) && (0<t && t<1)){
      x = mat[0][0]+(mat[1][0]-mat[0][0])*s;
      y = mat[2][1]+(mat[3][1]-mat[2][1])*t;
      judge = 1;
    }
  }

  if(judge == 1){
    printf("(x, y) = (%.5f, %.5f)\n", x, y);
  }else printf("(x, y) = NA\n");

  return 0;
}
