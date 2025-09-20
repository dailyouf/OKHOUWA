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
	
	
static void algo_glouton1(int n, char * res) {
	
	int i, j=n, best_i;
	long long curr_i_cost, best_i_cost;
	
	int d_tmp[MAXN+1];	
	memcpy(d_tmp, d, sizeof(int) * (n+1));
    	
    	char chain[MAXN][MAXREPR];
    	for (int i = 0; i < n; i++) {
        	sprintf(chain[i], "M%d", i+1);
    	}
    		
	char tmp[MAXREPR];
	
	while (j > 1) {
		
		best_i = 1;
		best_i_cost = d_tmp[best_i-1] * d_tmp[best_i] * d_tmp[best_i+1];
		
		for (i=2; i<j; i++) {	
			
			curr_i_cost = d_tmp[i-1] * d_tmp[i] * d_tmp[i+1];
					
			if (curr_i_cost < best_i_cost) {
				best_i = i; 
				best_i_cost = d_tmp[best_i-1] * d_tmp[best_i] * d_tmp[best_i+1];
			}
		}
		
		
		bestCost += best_i_cost;

        	
        	sprintf(tmp, "(%s %s)", chain[best_i - 1], chain[best_i]);
		strcpy(chain[best_i - 1], tmp);
		
		
		for (i=best_i; i<j; i++){
		    strcpy(chain[i], chain[i+1]);
		    d_tmp[i] = d_tmp[i+1];
		}
		
			
		j--;
			
	}
	
    	strcpy(res, chain[0]);
	
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
        algo_glouton1(n, res);
        
        
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
