#include <stdio.h>
#include <string.h>

#define MAX_NUM_CLAUSES 505
#define MAX_NUM_GATES 100

#define AND 0
#define OR 1
#define NOT 2

/* Add clauses which correspond to a gate type and its input and output
 * to the output array of clauses */
void addClause(int *clauseNum, int clauses[][4], int extra,
               int gate, int input1, int input2, int output) {
    switch (gate) {
        case AND:
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = -output;
            clauses[*clauseNum][2] = input1;
            clauses[*clauseNum][3] = extra;
            (*clauseNum)++;
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = -output;
            clauses[*clauseNum][2] = input1;
            clauses[*clauseNum][3] = -extra;
            (*clauseNum)++;
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = -output;
            clauses[*clauseNum][2] = input2;
            clauses[*clauseNum][3] = extra;
            (*clauseNum)++;
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = -output;
            clauses[*clauseNum][2] = input2;
            clauses[*clauseNum][3] = -extra;
            (*clauseNum)++;
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = output;
            clauses[*clauseNum][2] = -input1;
            clauses[*clauseNum][3] = -input2;
            (*clauseNum)++;
            break;
        case OR:
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = output;
            clauses[*clauseNum][2] = -input1;
            clauses[*clauseNum][3] = extra;
            (*clauseNum)++;
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = output;
            clauses[*clauseNum][2] = -input1;
            clauses[*clauseNum][3] = -extra;
            (*clauseNum)++;
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = output;
            clauses[*clauseNum][2] = -input2;
            clauses[*clauseNum][3] = extra;
            (*clauseNum)++;
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = output;
            clauses[*clauseNum][2] = -input2;
            clauses[*clauseNum][3] = -extra;
            (*clauseNum)++;
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = -output;
            clauses[*clauseNum][2] = input1;
            clauses[*clauseNum][3] = input2;
            (*clauseNum)++;
            break;
        case NOT:
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = output;
            clauses[*clauseNum][2] = input1;
            clauses[*clauseNum][3] = extra;
            (*clauseNum)++;
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = output;
            clauses[*clauseNum][2] = input1;
            clauses[*clauseNum][3] = -extra;
            (*clauseNum)++;
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = -output;
            clauses[*clauseNum][2] = -input1;
            clauses[*clauseNum][3] = extra;
            (*clauseNum)++;
            clauses[*clauseNum][0] = 3;
            clauses[*clauseNum][1] = -output;
            clauses[*clauseNum][2] = -input1;
            clauses[*clauseNum][3] = -extra;
            (*clauseNum)++;
            break;
    }
}

int main() {
    int t;
    int m, n, extra; // number of logic gates, number of variables

    scanf("%d", &t);
    while (t--) {
        int c = 0; // number of output clauses
        int clauses[MAX_NUM_CLAUSES][4] = {{0}};

        scanf("%d %d", &m, &n);

        extra = n + m + 1;
        char gate[4];
        int input1, input2;

        for (int i = 1; i <= m; i++) {
            scanf("%3s", gate);

            if (strcmp(gate, "AND") == 0) {
                scanf("%d %d", &input1, &input2);
                addClause(&c, clauses, extra, AND, input1, input2, i+n);
            } else if (strcmp(gate, "OR") == 0) {
                scanf("%d %d", &input1, &input2);
                addClause(&c, clauses, extra, OR, input1, input2, i+n);
            } else if (strcmp(gate, "NOT") == 0) {
                scanf("%d", &input1);
                addClause(&c, clauses, extra, NOT, input1, 0, i+n);
            }
        }

        /* The m + n gate is the final value of the circuit */
        clauses[c][0] = 3;
        clauses[c][1] = m + n;
        clauses[c][2] = extra;
        clauses[c][3] = extra + 1;
        c++;
        clauses[c][0] = 3;
        clauses[c][1] = m + n;
        clauses[c][2] = extra;
        clauses[c][3] = -(extra + 1);
        c++;
        clauses[c][0] = 3;
        clauses[c][1] = m + n;
        clauses[c][2] = -extra;
        clauses[c][3] = extra + 1;
        c++;
        clauses[c][0] = 3;
        clauses[c][1] = m + n;
        clauses[c][2] = -extra;
        clauses[c][3] = -(extra + 1);
        c++;

        printf("%d\n", c);
        for (int i = 0; i < c; i++) {
            printf("%d", clauses[i][0]);
            for (int j = 1; j <= clauses[i][0]; j++) {
                printf(" %d", clauses[i][j]);
            }
            printf("\n");
        }
    }
}