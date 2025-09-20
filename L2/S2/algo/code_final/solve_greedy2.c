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

static long long bestCost=0;
	
/* Ordre de multiplication optiomal  */
static char res[MAXREPR];
	
	
static char * algo_glouton2(int i, int j, char * p) {
		
	int k, min=i;
	long long curr_cost, best_cost;
	
	
	if (i==j)
		return p + sprintf(p, "M%d", i);
	
	best_cost = d[i-1] * d[i] * d[i+1];
	
	for (k=i+1; k<j; k++) {
		
		curr_cost = d[k-1] * d[k] * d[k+1];
					
		if (curr_cost < best_cost) {
			min = k; 
			best_cost = d[k-1] * d[k] * d[k+1];
		}
		
	}	
	
	k = min;
	bestCost += best_cost;
		
	*p++ = '(';
	
	p = algo_glouton2(i, k, p);

	*p++ = ' ';
	
	p = algo_glouton2(k+1, j, p);
	
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

	bestCost = 0;

        // run algo glouton 1
        char * p = algo_glouton2(1, n, res);
        *p = '\0';
        
        clock_t end = clock();
        double timeSec = (double)(end - start) / CLOCKS_PER_SEC;


        // Write result: n time bestCost res
        fprintf(fout, "%d %.6f %lld %s \n", n, timeSec, bestCost, res);	
        fflush(fout);

        // Print progress
        printf("[Progress] Solved instance %d / %d : n=%d, time=%.6f, bestCost=%lld\n",
               inst+1, T, n, timeSec, bestCost);

    
    }

    fclose(fin);
    fclose(fout);
    printf("Processed %d instances. Results saved to %s\n", T, outFile);

    return 0;
}
