#include<stdio.h>
#include<stdlib.h>
#include"function.h"

#define MAX 100

int main(){
  int i, j, k;
  int abs_A;
  int mat[4][2];
  inputdata data;

  scanf("%d%d%d%d", &(data.N), &(data.M), &(data.Q), &(data.P));
  for(i=0; i<data.N; i++){
    scanf("%d%d", &(data.X[i]), &(data.Y[i]));
  }

  for(i=0; i<data.M; i++){
    scanf("%d%d", &(data.b[i]), &(data.e[i]));
  }
  printf("-----inputdata-----\n");
  out(data);
  printf("-------------------\n");

  i=0;
  for(j=0; j<2; j++){
    printf("i = %d\n", i);
    mat[i][0] = data.X[data.b[j]];
    mat[i][1] = data.Y[data.b[j]];
    i++;
    printf("i = %d\n", i);
    mat[i][0] = data.X[data.e[j]];
    mat[i][1] = data.Y[data.e[j]];
    i++;

    for(k=0; k<4; k++){
      printf("%d, %d\n", mat[k][0], mat[k][1]);
    }
    printf("%d loop\n", j);
  }


  printf("-----after change-----\n");
  for(i=0; i<4; i++){
    printf("%d, %d\n", mat[i][0], mat[i][1]);
  }

  //abs_A = abs(finction1(data));

  return 0;
}
