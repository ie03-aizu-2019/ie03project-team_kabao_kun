#include<stdio.h>
#include<stdlib.h>
#include"function.h"

#define MAX 100

int main(){
  int i, j, k, cnt=0, abs_A, judge=0;
  double s, t;
  double x, y, tmp;
  int mat[4][2] = {};
  double point[500][2];
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


  for(i=0; i<data.M-1; i++){
    for(j=i+1; j<data.M; j++){
      //pick up Xp1,Yp1,...
      mat[0][0] = data.X[data.b[i]-1];
      mat[0][1] = data.Y[data.b[i]-1];
      mat[1][0] = data.X[data.e[i]-1];
      mat[1][1] = data.Y[data.e[i]-1];
      mat[2][0] = data.X[data.b[j]-1];
      mat[2][1] = data.Y[data.b[j]-1];
      mat[3][0] = data.X[data.e[j]-1];
      mat[3][1] = data.Y[data.e[j]-1];
      //pick up finish
      
      //calc |A|
      abs_A = abs(function1(mat));

      //calc s, t
      if(abs_A != 0){
	s = calc_S(mat, abs_A);
	t = calc_T(mat, abs_A);
	if((0<s && s<1) && (0<t && t<1)){
	  x = mat[0][0]+(mat[1][0]-mat[0][0])*s;
	  y = mat[2][1]+(mat[3][1]-mat[2][1])*t;
	  judge = 1;
	}
      }

      //final judge
      if(judge == 1){
	point[cnt][0] = x;
	point[cnt][1] = y;
	cnt++;
      }
      judge = 0;
    }
  }

  sort(point, cnt);
  for(i=0; i<cnt; i++){
    printf("No.%d:(x, y) = (%.5f, %.5f)\n", i+1, point[i][0], point[i][1]);
  }

  return 0;
}
