#include<stdio.h>
#include<math.h>
int sanjiaoxing(int *a,int *b,int *c,float *e)
{
    float q;
    q=(float)(*a + *b+ *c)/2;  //海伦公式
    *e=sqrt(q*(q- *a)*(q- *b)*(q- *c));  //海伦公式
    //printf("%f",e);
    return 0;
}
int main()
{
    int a,b,c;
    float square;
    scanf("%d",&a);  //第一个边
    scanf("%d",&b);  //第二个边
    scanf("%d",&c);  //第三个边
    sanjiaoxing(&a,&b,&c,&square);
    printf("%f\n", square);
    return 0;
}
