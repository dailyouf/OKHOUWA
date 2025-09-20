#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define MAXN 100
#define MAXREPR 500


/* We'll store the current dimensions in d[] for the chain */
static int d[MAXN+1];
static int n; // number of matrices


/* Arrays for dynamic programming */
static long long dp[MAXN+1][MAXN+1]={0};
static int split[MAXN+1][MAXN+1];
	
/* Ordre de multiplication optiomal  */
static char res[MAXREPR];

	
static void remplissage_dp(int n) {
	
	
	int i, j, l, k, best_k;
	long long bestCost, tmpCost;
	
	// Cas de base : une seule matrice → coût 0
	for (i = 1; i <= n; i++) {
		dp[i][i] = 0;
	}
    
	// Pour chaque longueur de chaîne l = 2..n    
	for (l=2; l<=n; l++) {
		
		// On parcourt tous les i tels que j = i+l-1 ≤ n <=> i ≤ n-l+1
		for (i=1; i<=n-l+1; i++) {
		
			j = i + l - 1;
			
			best_k = INT_MAX;
			bestCost = LLONG_MAX;
			tmpCost = 0;
			
			for (k=i; k<j; k++) {
				
				tmpCost = dp[i][k] + dp[k+1][j] + (d[i-1] * d[k] * d[j]);
				
				if (tmpCost < bestCost) {
					
					best_k = k;
					bestCost = tmpCost;
				
				}
			
			}
			
			dp[i][j] = bestCost;
			split[i][j] = best_k; 	
			
		}
		
	}
	
}	


static char * construction_solution(int i, int j, char *p) {
	
	int k = split[i][j];    
	
	
	if (i == j) 
        	return p + sprintf(p, "M%d", i);
   
	
	*p++ = '(';                
		
	p = construction_solution(i, k, p);
		
		
	*p++ = ' ';
	

	p = construction_solution(k+1, j, p);
		
	*p++ = ')';
		
	return p;
		
}



int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <inputFile> <outputFile>\n", argv[0]);
        return 1;
    }
    const char *inFile  = argv[1];
    const char *outFile = argv[2];

    FILE *fin = fopen(inFile, "r");
    if (!fin) {
        fprintf(stderr, "Cannot open input file: %s\n", inFile);
        return 1;
    }
    FILE *fout = fopen(outFile, "w");
    if (!fout) {
        fprintf(stderr, "Cannot open output file: %s\n", outFile);
        fclose(fin);
        return 1;
    }

    // Read total number of instances T
    int T;
    fscanf(fin, "%d", &T);

    // We'll solve each instance, measure time, and record results.
    for (int inst = 0; inst < T; inst++) {
        
        // read n
        fscanf(fin, "%d", &n);
        // read n+1 dimensions
        for (int i = 0; i < n+1; i++) {
            fscanf(fin, "%d", &d[i]);
        }

        // measure time
        clock_t start = clock();

        // run dynamic programming
        remplissage_dp(n);
	
	char *p = construction_solution(1, n, res);
	*p = '\0'; 
        
        /* Pour tracer la table dp
        for (int i=1; i<=n; i++) {
        	for (int j=1; j<=n; j++)
        		printf("dp[%d][%d]=%lld \t\t\t", i, j, dp[i][j]);
		printf("\n");
        }
        */

        clock_t end = clock();
        double timeSec = (double)(end - start) / CLOCKS_PER_SEC;

        // Write result: n time bestCost res
        fprintf(fout, "%d %.6f %lld %s \n", n, timeSec, dp[1][n], res);	
        fflush(fout);

        // Print progress
        printf("[Progress] Solved instance %d / %d : n=%d, time=%.6f, bestCost=%lld\n",
               inst+1, T, n, timeSec, dp[1][n]);
    }

    fclose(fin);
    fclose(fout);
    printf("Processed %d instances. Results saved to %s\n", T, outFile);

    return 0;
}
