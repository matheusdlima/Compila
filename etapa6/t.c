#include <stdbool.h>
#include <stdio.h>
//float v[2] = { 1.2, 1.1};
float b = 2.0;
float c = 5.0;
float a;
int b2 = 0;
int c2 = 5;
int v[2] = { 1, 2};
 int i = 1;
 char ch;

int func(int a, int b, int c, int d, int f, int a2, int b2, int c2, int d2, int f2, int g, int h, int i, int j, int k, int f1, int g1, int h1, int i1, int j1, int k1, int jjj){
    return a+1;
}

int main (){
    
    b2 = func(c2, c2, c2, c2, c2, c2, c2, c2, c2, c2, b2, c2, c2, c2, c2, c2, b2, c2, c2, c2, c2, c2);

    printf("%d\n", b2);
}