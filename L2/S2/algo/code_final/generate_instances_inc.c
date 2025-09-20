#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 6) {
        fprintf(stderr, "Usage: %s <minN> <maxN> <m> <maxDim> <outputFile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int minN    = atoi(argv[1]);
    int maxN    = atoi(argv[2]);
    int m       = atoi(argv[3]);
    /* int maxDim = atoi(argv[4]); */  // non utilisé ici
    const char *outputFile = argv[5];

    if (minN < 1 || maxN < minN || m < 1) {
        fprintf(stderr, "Error: invalid arguments. Ensure 1 ≤ minN ≤ maxN and m ≥ 1.\n");
        return EXIT_FAILURE;
    }

    int totalInstances = (maxN - minN + 1) * m;

    FILE *fp = fopen(outputFile, "w");
    if (!fp) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // 1) Nombre total d'instances
    fprintf(fp, "%d\n", totalInstances);

    // 2) Génération : pour chaque n, m fois, dimensions 1,2,...,n+1
    for (int n = minN; n <= maxN; n++) {
        for (int j = 0; j < m; j++) {
            fprintf(fp, "%d\n", n);
            for (int k = 0; k <= n; k++) {
                fprintf(fp, "%d", k + 1);
                if (k < n) fprintf(fp, " ");
            }
            fprintf(fp, "\n");
        }
    }

    fclose(fp);
    printf("Generated %d instances with increasing dims (1..n+1) in %s\n",
           totalInstances, outputFile);
    return EXIT_SUCCESS;
}

