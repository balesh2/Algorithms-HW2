#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Locker {
  int key;
  int ball;
  int open;
};

struct Table {
  int cost;
  struct Locker *locker;
};

int max(int a, int b) {
  if(a >= b) {
    return a;
  }
  return b;
}

int min(int a, int b) {
  if(a <= b) {
    return a;
  }
  else {
    return b;
  }
}

int up(struct Table *C, struct Table P, int N, int ck, int cr) {
  int x;
  int ball1 = -1;
  int ball2 = -1;
  for(x=0; x<N; x++) {
    C[0].locker[x].ball = P.locker[x].ball;
    C[0].locker[x].key = P.locker[x].key;
    C[0].locker[x].open = P.locker[x].open;
  }

  for(x=0; x<N; x++) {
    if(C[0].locker[x].ball == 1 && C[0].locker[x].open == 0) {
      ball1 = x;
      break;
    }
  }

  for(x=cr; x>=0; x--) {
    if(C[0].locker[x].ball == 1 && C[0].locker[x].open == 0) {
      ball2 = x;
    }
  }

  if(ball1 == -1) {
    return 0;
  }

  if(ck <= ball1) {
    ball1 = ck;
  } else if(ck > ball2) {
    ball2 = ck;
  }

  for(x=ball1; x<=ball2; x++) {
    if(C[0].locker[x].open == 0) {
      C[0].locker[x].open = 1;
    }
  }

  C[0].cost = 0;
  for(x=0; x<N; x++) {
    if(C[0].locker[x].open == 1) {
      C[0].cost++;
    }
  }

  return 0;
}

int upandover(struct Table *C, struct Table P, int N, int ck, int pk, int cr) {
  int x;
  int lb = 0;
  int ub = 0;
  struct Table temp1;
  struct Table temp2;
  temp1.cost = P.cost;
  temp2.cost = P.cost;
  temp1.locker = malloc(sizeof(struct Locker)*N);
  temp2.locker = malloc(sizeof(struct Locker)*N);

  for(x=0; x<N; x++) {
    temp1.locker[x].ball = P.locker[x].ball;
    temp1.locker[x].key = P.locker[x].key;
    temp1.locker[x].open = P.locker[x].open;

    temp2.locker[x].ball = P.locker[x].ball;
    temp2.locker[x].key = P.locker[x].key;
    temp2.locker[x].open = P.locker[x].open;
  }

  up(&temp1, P, N, ck, cr);
  up(&temp2, P, N, pk, cr);

  if(temp1.cost < temp2.cost) {
    C[0].cost = temp1.cost;
    for(x=0; x<N; x++) {
      C[0].locker[x].ball = temp1.locker[x].ball;
      C[0].locker[x].key = temp1.locker[x].key;
      C[0].locker[x].open = temp1.locker[x].open;
    }
    free(temp2.locker);
  } else {
    C[0].cost = temp2.cost;
    for(x=0; x<N; x++) {
      C[0].locker[x].ball = temp2.locker[x].ball;
      C[0].locker[x].key = temp2.locker[x].key;
      C[0].locker[x].open = temp2.locker[x].open;
    }
    free(temp1.locker);
  }
  if(C[0].locker[ck].open == 0) {
    C[0].locker[ck].open = 1;
    C[0].cost++;
  }

  return 0;
}

int over(struct Table *C, struct Table P, int N, int ck, int cr) {
  int x;
  for(x=0; x<N; x++) {
    C[0].locker[x].ball = P.locker[x].ball;
    C[0].locker[x].key = P.locker[x].key;
    C[0].locker[x].open = P.locker[x].open;
  }

  if(C[0].locker[ck].open == 0 && C[0].locker[ck].ball == 1){
    C[0].locker[ck].open = 1;
  }

  C[0].cost = 0;
  for(x=0; x<N; x++) {
    if(C[0].locker[x].open == 1) {
      C[0].cost++;
    }
  }

  return 0;
}

int main() {
  int i, j, x, a, l, c;
  int bc = 0;
  int kc = 0;

  /*****************************************************************************
   * DEFINE ALL INPUTS HERE ****************************************************
   ****************************************************************************/

  /* SAMPLE INPUTS 1 **********************************************************/
  //int N = 3;
  //int M = 1;
  //int T = 1;
  //int m[1] = {1};
  //int b[1] = {3};

  //SAMPLE 1 OUTPUT: 3 
  /****************************************************************************/

  /* SAMPLE INPUTS 2 **********************************************************/
  //int N = 4;
  //int M = 2;
  //int T = 2;
  //int m[2] = {2, 3};
  //int b[2] = {1, 4};

  //SAMPLE 2 OUTPUT: 4 
  /****************************************************************************/

  /* SAMPLE INPUTS 3 **********************************************************/
  //int N = 8;
  //int M = 2;
  //int T = 2;
  //int m[2] = {1, 8};
  //int b[2] = {5, 4};

  //SAMPLE 3 OUTPUT: 5
  /****************************************************************************/

  /* SAMPLE INPUTS 4 **********************************************************/
  //int N = 13;
  //int M = 5;
  //int T = 6;
  //int m[5] = {6, 4, 2, 7, 5};
  //int b[6] = {13, 1, 6, 9, 4, 2};

  //SAMPLE 4 OUTPUT: 11
  /****************************************************************************/

  /* SAMPLE INPUTS 5 **********************************************************/
  //int N = 67;
  //int M = 16;
  //int T = 14;
  //int m[16] = {12, 53, 32, 18, 11, 48, 17, 63, 7, 54, 20, 4, 6, 8, 14, 56};
  //int b[14] = {66, 32, 38, 16, 8, 40, 19, 52, 53, 12, 21, 51, 22, 18};

  //SAMPLE OUTPUT: 25
  /****************************************************************************/

  /* SAMPLE INPUTS 6 **********************************************************/
  //int N = 139;
  //int M = 50;
  //int T = 56;
  //int m[50] = {8, 121, 112, 9, 28, 84, 82, 129, 31, 91, 138, 25, 59, 89, 52, 36, 33, 110, 54, 37, 79, 109, 55, 16, 96, 26, 93, 101, 76, 104, 113, 139, 118, 47, 63, 128, 123, 15, 136, 132, 44, 70, 49, 86, 11, 23, 22, 39, 69, 68};
  //int b[56] = {86, 33, 92, 19, 125, 41, 14, 60, 75, 135, 50, 61, 57, 28, 104, 43, 129, 128, 83, 48, 133, 65, 45, 114, 55, 11, 58, 97, 17, 42, 91, 138, 34, 127, 2, 35, 103, 49, 18, 118, 111, 74, 101, 124, 113, 47, 70, 52, 5, 139, 69, 93, 13, 29, 40, 12};

  //SAMPLE  OUTPUT: 73
  /****************************************************************************/

  /* SAMPLE INPUTS 7 **********************************************************/
  //int N = 201;
  //int M = 184;
  //int T = 74;
  //int m[184] = {131, 94, 181, 99, 138, 193, 17, 145, 161, 165, 25, 107, 36, 142, 171, 110, 188, 97, 154, 28, 173, 60, 183, 53, 71, 13, 43, 184, 5, 168, 73, 139, 106, 91, 18, 93, 192, 163, 29, 120, 62, 21, 96, 78, 149, 87, 81, 84, 47, 80, 167, 31, 14, 124, 151, 178, 162, 147, 101, 105, 123, 30, 113, 41, 121, 38, 72, 12, 68, 117, 129, 130, 46, 166, 35, 104, 74, 116, 108, 158, 44, 180, 100, 122, 182, 66, 136, 52, 55, 23, 194, 2, 42, 102, 160, 172, 50, 156, 51, 103, 195, 48, 8, 10, 137, 152, 98, 15, 143, 127, 176, 75, 89, 24, 70, 189, 144, 135, 76, 115, 77, 32, 164, 170, 153, 82, 196, 86, 20, 33, 85, 169, 83, 159, 57, 199, 174, 64, 134, 109, 95, 140, 191, 79, 67, 179, 197, 150, 37, 58, 119, 186, 27, 88, 111, 59, 4, 146, 1, 26, 34, 22, 201, 7, 16, 114, 65, 177, 63, 9, 19, 69, 157, 45, 49, 190, 112, 148, 118, 132, 133, 56, 61, 187};
  //int b[74] = {201, 146, 116, 189, 159, 71, 10, 21, 41, 35, 38, 106, 95, 7, 43, 135, 193, 175, 117, 186, 185, 93, 194, 191, 3, 176, 196, 5, 148, 177, 45, 11, 144, 152, 72, 187, 147, 182, 14, 51, 138, 94, 183, 114, 64, 47, 76, 198, 174, 49, 123, 20, 179, 118, 97, 34, 86, 2, 105, 75, 98, 134, 178, 190, 80, 92, 81, 112, 9, 110, 87, 107, 17, 160};

  //SAMPLE  OUTPUT: 75
  /****************************************************************************/

  /* SAMPLE INPUTS 8 **********************************************************/
  //int N = 399;
  //int M = 197;
  //int T = 90;
  //int m[197] = {319, 348, 155, 143, 160, 147, 165, 3, 91, 323, 58, 179, 9, 57, 309, 258, 332, 59, 196, 194, 110, 379, 158, 19, 238, 21, 305, 30, 355, 339, 259, 252, 88, 233, 245, 137, 135, 17, 236, 125, 7, 247, 78, 124, 69, 394, 311, 15, 276, 67, 266, 335, 157, 146, 28, 87, 269, 248, 39, 268, 142, 224, 74, 227, 301, 326, 280, 206, 112, 308, 24, 111, 290, 396, 82, 13, 398, 369, 230, 73, 72, 99, 171, 350, 22, 303, 362, 220, 246, 214, 81, 153, 231, 306, 232, 144, 325, 217, 283, 49, 31, 315, 304, 84, 47, 302, 185, 384, 86, 164, 120, 297, 363, 187, 166, 116, 317, 186, 318, 286, 212, 136, 288, 223, 382, 294, 287, 347, 260, 79, 209, 356, 345, 391, 210, 310, 383, 131, 284, 397, 381, 95, 254, 8, 291, 103, 395, 299, 113, 94, 393, 150, 48, 32, 239, 373, 195, 34, 18, 11, 2, 43, 174, 114, 215, 132, 235, 46, 41, 182, 278, 264, 334, 378, 328, 300, 267, 64, 193, 261, 340, 122, 85, 342, 152, 207, 368, 341, 16, 273, 126, 181, 117, 60, 241, 274, 51};
  //int b[90] = {345, 394, 138, 111, 98, 191, 254, 251, 180, 205, 137, 172, 243, 331, 306, 94, 311, 288, 294, 328, 253, 2, 303, 333, 176, 112, 10, 140, 88, 81, 295, 291, 124, 203, 58, 146, 101, 48, 14, 365, 47, 301, 376, 107, 18, 350, 255, 245, 347, 395, 25, 399, 280, 273, 65, 165, 310, 219, 96, 267, 171, 136, 357, 276, 197, 248, 237, 117, 247, 340, 249, 309, 187, 67, 156, 129, 262, 298, 261, 102, 164, 367, 145, 356, 393, 308, 5, 45, 396, 392};

  //SAMPLE  OUTPUT: 126
  /****************************************************************************/

  /****************************************************************************/

  struct Locker *L = malloc(sizeof(struct Locker)*N);
  struct Table **C = (struct Table **)malloc(sizeof(struct Table*)*M);

  for(x=0; x<M; x++) {
    C[x] = (struct Table *)malloc(sizeof(struct Table)*M);
  }

  /*****************************************************************************
   * INIT L[], m[], AND b[] ****************************************************
   ****************************************************************************/

  //init lockers to 0
  for(i=0; i<N; i++) {
    L[i].key = 0;
    L[i].ball = 0;
    L[i].open = 0;
  }

  //add all keys to array of lockers
  for(i=0; i<M; i++) {
    L[m[i]-1].key = 1;
  }

  //add all balls to array of lockers
  for(i=0; i<T; i++) {
    L[b[i]-1].ball = 1;
  }

  //iterate through array of lockers and copy each ball and key to the ball or
  //key array so that they are in ascending order
  for(i=0; i<N; i++) {
    L[i].ball = L[i].ball;
    L[i].key = L[i].key;
    if(L[i].key == 1) {
      m[kc] = i;
      kc++;
    }
    if(L[i].ball == 1) {
      b[bc] = i;
      bc++;
    }
  }


  /****************************************************************************/

  /*****************************************************************************
   * FILL IN TABLE *************************************************************
   ****************************************************************************/

  struct Table *Ca = malloc(sizeof(struct Table));
  struct Table *Cb = malloc(sizeof(struct Table));
  struct Table *Cc = malloc(sizeof(struct Table));

  for(i=0; i<M; i++) {
    for(j=0; j<M; j++) {
      if(i==0 && j==0) {
        C[0][0].cost = 0;
        C[0][0].locker = malloc(sizeof(struct Locker)*N);
        for(x=0; x<N; x++) {
          C[0][0].locker[x].ball = L[x].ball;
          C[0][0].locker[x].key = L[x].key;
          C[0][0].locker[x].open = L[x].open;
        }
        if(m[0] >= b[0]) {
          for(x=b[0]; x<=m[0]; x++) {
            C[0][0].locker[x].open = 1;
            C[0][0].cost++;
          }
        }
      } else if(i==0) {
        Ca[0].locker = malloc(sizeof(struct Locker)*N);
        over(Ca, C[0][j-1], N, m[j], m[i]);
        C[i][j].cost = Ca[0].cost;
        C[i][j].locker = Ca[0].locker;
      } else if(j==0) {
        Ca[0].locker = malloc(sizeof(struct Locker)*N);
        up(Ca, C[i-1][0], N, m[j], m[i]);
        C[i][j].cost = Ca[0].cost;
        C[i][j].locker = Ca[0].locker;
      } else {
        Ca[0].locker = malloc(sizeof(struct Locker)*N);
        Cb[0].locker = malloc(sizeof(struct Locker)*N);
        Cc[0].locker = malloc(sizeof(struct Locker)*N);
        up(Ca, C[i-1][j], N, m[j], m[i]);
        upandover(Cb, C[i-1][j-1], N, m[j], m[j-1], m[i]);
        over(Cc, C[i][j-1], N, m[j], m[i]);

        if(Ca[0].cost <= Cb[0].cost && Ca[0].cost <= Cc[0].cost) {
          C[i][j].cost = Ca[0].cost;
          C[i][j].locker = Ca[0].locker;
          free(Cb[0].locker);
          free(Cc[0].locker);
        } else if(Cb[0].cost <= Ca[0].cost && Cb[0].cost <= Cc[0].cost) {
          C[i][j].cost = Cb[0].cost;
          C[i][j].locker = Cb[0].locker;
          free(Ca[0].locker);
          free(Cc[0].locker);
        } else {
          C[i][j].cost = Cc[0].cost;
          C[i][j].locker = Cc[0].locker;
          free(Ca[0].locker);
          free(Cb[0].locker);
        }
      }
    }
  }

  a=0;
  if(b[T-1] >= m[M-1]) {
    a = b[T-1] - m[M-1];
  }

  l = 1000;
  for(x=0; x<M; x++) {
    if(C[M-1][x].locker[m[M-1]].open == 0) {
      if(l > C[M-1][x].cost+a+1) {
        l = C[M-1][x].cost + a + 1;
      }
    } else {
      if(l > C[M-1][x].cost+a) {
        l = C[M-1][x].cost + a;
      }
    }
  }


  printf("solution: %d\n", l);

  /****************************************************************************/

  /*****************************************************************************
   * FOR DEBUG *****************************************************************
   ****************************************************************************/

  //if(N < 30) {
  //  printf("|");
  //  for(i=0; i<N; i++) {
  //    printf(" %d |", L[i].key);
  //  }
  //  printf("\n|");
  //  for(i=0; i<N; i++) {
  //    printf(" %d |", L[i].ball);
  //  }
  //  printf("\n");
  //  printf("\n");
  //}
  //else {
  //  //for(i=0; i<M; i++) {
  //  //  printf("%d ", m[i]);
  //  //}
  //  //printf("\n");
  //}

  //if(M < 10) {
  //  for(i=0; i<M; i++) {
  //    printf("|");
  //    for(j=0; j<M; j++) {
  //      printf(" %d |", C[i][j].cost);
  //    }
  //    printf("\n");
  //  }
  //  printf("\n");
  //}

  /****************************************************************************/

  /*****************************************************************************
   * FREE **********************************************************************
   ****************************************************************************/

  for(i=0; i<M; i++) {
    for(j=0; j<M; j++) {
      free(C[i][j].locker);
    }
  }
  for(i=0; i<M; i++) {
    free(C[i]);
  }
  free(C);

  /****************************************************************************/

  return 0;
}

