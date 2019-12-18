#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
typedef struct {
    char s1;
    int ni, P, F, b[100];
 
} nguon;
void doicho(nguon *a, nguon *b) {
    nguon c;
    c = *a;
    *a = *b;
    *b = c;
}
 
int main() {
    char *s;
    nguon *kitu;
    int i, j, n, k = 1, *a, ni, maxni;
     float I=0,t=0;
    s = (char *) malloc(100 * sizeof(char));
    a = (int *) malloc(100 * sizeof(int));
    kitu = (nguon *) malloc(100 * sizeof(nguon));
    printf("Enter the code sequence: ");
    gets(s);
    fflush(stdin);
    puts(s);
    n = strlen(s);//length of the string
    //Classification of characters
    //ASCII Table
    for (j = 1; j <= 256; j++) {
        a[k] = 0;
        for (i = 0; i <= n; i++)
            if ((int) s[i] == j) {
                a[k]++;
                kitu[k].s1 = s[i];
            }
        if (a[k] > 0) {
            kitu[k].P = a[k];
            k++;
        }
    }
    //
    printf("\nNumber of different code words d=%d",k-1);
    for (i = 1; i < k; i++)
        for (j = i; j < k; j++)
            if (kitu[i].P < kitu[j].P) 
                doicho(&kitu[i], &kitu[j]);
    //P(Xi)
 
    for (i = 1; i <= k; i++) {
        if (i == 1)
            kitu[1].F = 0;
        if (i > 1)
            kitu[i].F = kitu[i - 1].F + kitu[i - 1].P;
    }
 
    //ni
    for (i = 1; i < k; i++) {
        float j;
        j = n / kitu[i].P;
        if(n%kitu[i].P==0) ni = (int) (log(j) / log(2));
        else ni = (int) (log(j) / log(2)) + 1;
        kitu[i].ni = ni;
     
    }
    maxni = kitu[1].ni;
    for (i = 1; i < k; i++){
        if (kitu[i].ni > maxni)
            maxni = kitu[i].ni;
     	 for (j = i; j < k; j++){
            if (kitu[i].ni > kitu[j].ni) 
                doicho(&kitu[i], &kitu[j]);
			if (kitu[i].P < kitu[j].P) 
                doicho(&kitu[i], &kitu[j]);
			}
		printf("\nFrequency of code words x[%d]= %d",i,kitu[i].P);
		t=t+(float)(kitu[i].ni)*(kitu[i].P)/n;
		I=I+(float)(kitu[i].P)*(log10((float)n/kitu[i].P)*(float)log(10)/log(2))/n;
	}
	printf("\n\Average word length La=%10.2f",t);
	printf("\nAverage amount of infoamtion of I(X)=%10.2f (bit)",I);
	printf("\nMax Entropy  H(X)max=%10.2f (bit/sign)",(float)log10(k-1)*log(10)/log(2));
    //Tinh P(Xi) he 2 
    int l;
    float F;
    for (i = 1; i < k; i++) {
        l = 1;
        F = (float) kitu[i].F / n;
        while ((l <= maxni) && (F != 0)) {
            F = F * 2;
            kitu[i].b[l] = (int) F / 1;
            l++;
            F = F - (int) F;
        }
    }
 
    printf("\n\n%2s %5s %8s %12s %8s", "Num", "Xi", "P(Xi)", "P(Xj)", "length");
    for (i = 1; i <= maxni + 1; i++)
        printf(" ");
    printf("%10s", "Binary code");
    for (i = 1; i <= maxni; i++)
        printf(" ");
    printf("%10s", "Shannon Code");
    for (i = 1; i < k; i++) {
        ni = kitu[i].ni;
        printf("\n%2d %5c %7d/%d %7d/%d %7d",i, kitu[i].s1, kitu[i].P, n, kitu[i].F,
                n, kitu[i].ni);
        for (j = 1; j <= maxni - ni; j++)
            printf(" ");
        printf("%10s", "0.");
        for (j = 1; j <= ni; j++)
            printf("%d", kitu[i].b[j]);
        for (j = 1; j <= maxni - ni; j++)
            printf(" ");
        printf("%10s", " ");
        for (j = 1; j <= ni; j++)
            printf("%d", kitu[i].b[j]);
    }
    printf("\n");
    return 0;
}

