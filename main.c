#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"print.h"
#include"calc.h"

#define max 500
#define inf 10000000

int main(){
  int i, j, cnt=0, abs_A, judge=0, check1=0, check2=0;
  double s, t, x, y;      //stxyは交差地点計算用
  double weight=0;
  int mat[4][2] = {};     //Xp1, Yp1, ...
  double C[max][2] = {};  //intersection(交差点)[x][y]
  int Cp[max][6] = {};    //↑の[bi][ei][bj][ej]
  double **G;             //重み付き隣接行列
  inputdata data;

  //input until before s, d, k
  scanf("%d%d%d%d", &(data.N), &(data.M), &(data.P), &(data.Q));

  //initialization G[][]
  G = malloc(sizeof(double *)*((data.N+data.P)*2));
  for(i=0; i<((data.N+data.P)*2); i++){
    G[i] = malloc(sizeof(double)*((data.N+data.P)*2));
  }
  for(i=0; i<data.N; i++){
    for(j=0; j<data.N; j++){
      G[i][j] = 0;
    }
  }

  //それぞれのデータ入力
  for(i=0; i<data.N; i++){
    scanf("%d%d", &(data.X[i]), &(data.Y[i]));
  }
  for(i=0; i<data.M; i++){
    scanf("%d%d", &(data.b[i]), &(data.e[i]));
    //距離計算してグラフにぶち込む
    weight = sqrt(calc_G(abs((data.X[data.b[i]-1])-(data.X[data.e[i]-1])), abs((data.Y[data.b[i]-1])-(data.Y[data.e[i]-1]))));
    G[data.b[i]-1][data.e[i]-1] = weight;
    G[data.e[i]-1][data.b[i]-1] = weight;
  }
  for(i=0; i<data.P; i++){
    scanf("%d%d", &(data.X[data.N+i]), &(data.Y[data.N+i]));
  }

  //交差地点の判定、記録
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

      //calculation |A|
      abs_A = abs(calc_A(mat));

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
        C[cnt][0] = x;
        C[cnt][1] = y;
        //交差地点があった時の２線分を記録
        Cp[cnt][2] = data.b[i]-1;
        Cp[cnt][3] = data.e[i]-1;
        Cp[cnt][4] = data.b[j]-1;
        Cp[cnt][5] = data.e[j]-1;
        cnt++;
      }
      judge = 0;
    }
  }

  //交差地点をX昇順でソート
  sort(C, Cp, cnt);

  //ここで交差地点をグラフに追加(※与えられた線分が昇順になっている時のみ作用します。)
  for(i=0; i<cnt; i++){
    if(i==0){
      weight = sqrt(calc_G(fabs(C[i][0]-data.X[Cp[i][2]]), fabs(C[i][1]-data.Y[Cp[i][2]])));
      G[Cp[i][2]][data.N+i] = weight;
      G[data.N+i][Cp[i][2]] = weight;
      weight = G[Cp[i][2]][Cp[i][3]] - weight;
      G[Cp[i][3]][data.N+i] = weight;
      G[data.N+i][Cp[i][3]] = weight;
      G[Cp[i][2]][Cp[i][3]] *= -1;
      G[Cp[i][3]][Cp[i][2]] *= -1;
      weight = sqrt(calc_G(fabs(C[i][0]-data.X[Cp[i][4]]), fabs(C[i][1]-data.Y[Cp[i][4]])));
      G[Cp[i][4]][data.N+i] = weight;
      G[data.N+i][Cp[i][4]] = weight;
      weight = G[Cp[i][4]][Cp[i][5]] - weight;
      G[Cp[i][5]][data.N+i] = weight;
      G[data.N+i][Cp[i][5]] = weight;
      G[Cp[i][4]][Cp[i][5]] *= -1;
      G[Cp[i][5]][Cp[i][4]] *= -1;
    }
    else{
      for(j=i-1; j>=0; j--){
        if(Cp[i][2]==Cp[j][2] && Cp[i][3]==Cp[j][3]){
          weight = sqrt(calc_G(fabs(C[i][0]-C[j][0]), fabs(C[i][1]-C[j][1])));
          G[data.N+j][data.N+i] = weight;
          G[data.N+i][data.N+j] = weight;
          G[data.N+j][Cp[j][3]] = 0;
          G[Cp[j][3]][data.N+j] = 0;
          weight = sqrt(calc_G(fabs(data.X[Cp[i][3]]-C[i][0]), fabs(data.Y[Cp[i][3]]-C[i][1])));
          G[Cp[i][3]][data.N+i] = weight;
          G[data.N+i][Cp[i][3]] = weight;
          G[Cp[j][2]][Cp[j][3]] = 0;
          G[Cp[j][3]][Cp[j][2]] = 0;
          G[Cp[i][2]][Cp[i][3]] *= -1;
          G[Cp[i][3]][Cp[i][2]] *= -1;
          check1 = 1;
        }
        else if(Cp[i][2]==Cp[j][4] && Cp[i][3]==Cp[j][5]){
          weight = sqrt(calc_G(fabs(C[i][0]-C[j][0]), fabs(C[i][1]-C[j][1])));
          G[data.N+j][data.N+i] = weight;
          G[data.N+i][data.N+j] = weight;
          G[data.N+j][Cp[j][5]] = 0;
          G[Cp[j][5]][data.N+j] = 0;
          weight = sqrt(calc_G(fabs(data.X[Cp[i][3]]-C[i][0]), fabs(data.Y[Cp[i][3]]-C[i][1])));
          G[Cp[i][3]][data.N+i] = weight;
          G[data.N+i][Cp[i][3]] = weight;
          G[Cp[j][4]][Cp[j][5]] = 0;
          G[Cp[j][5]][Cp[j][4]] = 0;
          G[Cp[i][2]][Cp[i][3]] *= -1;
          G[Cp[i][3]][Cp[i][2]] *= -1;
          check1 = 1;
        }
        if(Cp[i][4]==Cp[j][2] && Cp[i][5]==Cp[j][3]){
          weight = sqrt(calc_G(fabs(C[i][0]-C[j][0]), fabs(C[i][1]-C[j][1])));
          G[data.N+j][data.N+i] = weight;
          G[data.N+i][data.N+j] = weight;
          G[data.N+j][Cp[j][3]] = 0;
          G[Cp[j][3]][data.N+j] = 0;
          weight = sqrt(calc_G(fabs(data.X[Cp[i][5]]-C[i][0]), fabs(data.Y[Cp[i][5]]-C[i][1])));
          G[Cp[i][5]][data.N+i] = weight;
          G[data.N+i][Cp[i][5]] = weight;
          G[Cp[j][2]][Cp[j][3]] = 0;
          G[Cp[j][3]][Cp[j][2]] = 0;
          G[Cp[i][4]][Cp[i][5]] *= -1;
          G[Cp[i][5]][Cp[i][4]] *= -1;
          check2 = 1;
        }
        else if(Cp[i][4]==Cp[j][4] && Cp[i][5]==Cp[j][5]){
          weight = sqrt(calc_G(fabs(C[i][0]-C[j][0]), fabs(C[i][1]-C[j][1])));
          G[data.N+j][data.N+i] = weight;
          G[data.N+i][data.N+j] = weight;
          G[data.N+j][Cp[j][5]] = 0;
          G[Cp[j][5]][data.N+j] = 0;
          weight = sqrt(calc_G(fabs(data.X[Cp[i][5]]-C[i][0]), fabs(data.Y[Cp[i][5]]-C[i][1])));
          G[Cp[i][5]][data.N+i] = weight;
          G[data.N+i][Cp[i][5]] = weight;
          G[Cp[j][4]][Cp[j][5]] = 0;
          G[Cp[j][5]][Cp[j][4]] = 0;
          G[Cp[i][4]][Cp[i][5]] *= -1;
          G[Cp[i][5]][Cp[i][4]] *= -1;
          check2 = 1;
        }

        //２点がかすってもなかったら飛ばす
        if(check1==0 && check2==0) continue;

        //交差地点Cpi[2]-Cpi[3]、Cpi[4]-Cpi[5]どちらかが同線上にいない方を以下で作成
        if(check1==0){
          weight = sqrt(calc_G(fabs(C[i][0]-data.X[Cp[i][2]]), fabs(C[i][1]-data.Y[Cp[i][2]])));
          G[Cp[i][2]][data.N+i] = weight;
          G[data.N+i][Cp[i][2]] = weight;
          weight = fabs(G[Cp[i][2]][Cp[i][3]] - weight);
          G[Cp[i][3]][data.N+i] = weight;
          G[data.N+i][Cp[i][3]] = weight;
          G[Cp[i][2]][Cp[i][3]] *= -1;
          G[Cp[i][3]][Cp[i][2]] *= -1;
        }
        if(check2==0){
          weight = sqrt(calc_G(fabs(C[i][0]-data.X[Cp[i][4]]), fabs(C[i][1]-data.Y[Cp[i][4]])));
          G[Cp[i][4]][data.N+i] = weight;
          G[data.N+i][Cp[i][4]] = weight;
          weight = fabs(G[Cp[i][4]][Cp[i][5]] - weight);
          G[Cp[i][5]][data.N+i] = weight;
          G[data.N+i][Cp[i][5]] = weight;
          G[Cp[i][4]][Cp[i][5]] *= -1;
          G[Cp[i][5]][Cp[i][4]] *= -1;
        }
        check1 = 0;
        check2 = 0;
      }
    }
  }
  //余計な重み削除
  rm(cnt, data.N, G);

  //s, d, k...入力
  for(i=0; i<data.Q; i++){
    scanf("%s%s%d", data.s, data.d, &(data.k[i]));

    //最短距離計算
  }

  //グラフの出力
  out_G(cnt, data.N, G);

  for(i=0; i<((data.N+data.P)*2); i++){
    free(G[i]);
  } free(G);
  return 0;
}
