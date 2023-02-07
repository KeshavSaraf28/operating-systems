// Banker's Algorithm
#include <stdio.h>
#include <stdlib.h>
int main()
{

    FILE *myFile;
    myFile = fopen("somenumbers.txt", "r");
    int n, m;
    printf("Enter the Number of processes: ");
    scanf("%d", &n);
    int finish[n];
    printf("Enter the Number of Resources: ");
    scanf("%d", &m);
    int alloc[n][m];
    printf("Enter the Number of instances for resource of each process.\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fscanf(myFile, "%d", &alloc[i][j]);
            printf("%d ", alloc[i][j]);
        }
        printf("\n");
    }

    int max[n][m];
    printf("Enter the Max Number of instances for resource of each process.\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fscanf(myFile, "%d", &max[i][j]);
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    int avail[3] = {3, 3, 2}; // Available Resources
    printf("Enter the Available Instances of each resource with spaces:");
    for (int i = 0; i < m; i++)
    {
        fscanf(myFile, "%d", &avail[i]);
        printf("%d ", avail[i]);
    }
    printf("\n");
    int f[n], ans[n], ind = 0;
    for (int k = 0; k < n; k++)
    {
        f[k] = 0;
    }
    int need[n][m];
    printf("Need MAtrix\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    while (1)
    {
        printf("\nEnter 1 for Allocation Request and 0 to Exit:");
        int choice;
        int p;
        int r[m];
        scanf("%d", &choice);
        int runAlgo = 1;
        if (choice == 1)
        {
            printf("Available resources: ");
            for (int i = 0; i < m; i++)
                printf("%d ", avail[i]);
            printf("\nEnter the Process Number:");

            scanf("%d", &p);
            printf("Enter the Requested resources:");

            for (int i = 0; i < m; i++)
            {
                scanf("%d", &r[i]);
            }
            for (int i = 0; i < m; i++)
            {
                if (r[i] > avail[i])
                {
                    printf("Not Enough Available Resources.\n");
                    runAlgo = 0;
                    break;
                }
                if (r[i] > need[p][i])
                {
                    printf("Requesting Resources more than Process's Max.\n");
                    runAlgo = 0;
                    break;
                }
            }
        }
        else if (choice == 0)
        {
            exit(0);
        }
        else
        {
            printf("Invalid Choice.\n");
            continue;
        }
        if (runAlgo == 0)
        {

            continue;
        }
        else
        {
            for (int i = 0; i < m; i++)
            {
                alloc[p][i] += r[i];
                need[p][i] -= r[i];
                avail[i] -= r[i];
            }
        }
        for (int k = 0; k < n; k++)
        {
            f[k] = 0;
        }
        int y = 0;
        int Tempavail[m];
        for (int i = 0; i < m; i++)
            Tempavail[i] = avail[i];
        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                if (f[i] == 0)
                {

                    int flag = 0;
                    for (int j = 0; j < m; j++)
                    {
                        if (need[i][j] > Tempavail[j])
                        {
                            flag = 1;
                            break;
                        }
                    }

                    if (flag == 0)
                    {
                        ans[ind++] = i;
                        for (y = 0; y < m; y++)
                            Tempavail[y] += alloc[i][y];
                        f[i] = 1;
                    }
                }
            }
        }

        int flag = 1;

        for (int i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {
                flag = 0;
                printf("The following system is not safe");
                for (int i = 0; i < m; i++)
                {
                    alloc[p][i] -= r[i];
                    need[p][i] += r[i];
                    avail[i] += r[i];
                }

                break;
            }
        }

        if (flag == 1)
        {
            printf("Following is the SAFE Sequence\n");
            for (int i = 0; i < n - 1; i++)
                printf(" P%d ->", ans[i]);
            printf(" P%d", ans[n - 1]);
            int allmax = 0;
            int process = -1;
            for (int i = 0; i < n; i++)
            {
                if (allmax == m)
                {
                    finish[i - 1] = 1;
                    printf("\nProcess %d is Completed,Releasing it's Resources.\n", i - 1);
                    for (int j = 0; j < m; j++)
                    {
                        avail[j] += alloc[i - 1][j];
                        alloc[i - 1][j] = 0;
                        max[i - 1][j] = 0;
                    }
                }
                allmax = 0;
                for (int j = 0; j < m; j++)
                    if (need[i][j] == 0 && finish[i] != 1)
                        allmax++;
            }
            printf("\nAllocation Table.\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                    printf("%d ", alloc[i][j]);
                printf("\n");
            }
            printf("Max Allocation Table.\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                    printf("%d ", max[i][j]);
                printf("\n");
            }
            printf("Need MAtrix\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    need[i][j] = max[i][j] - alloc[i][j];
                    printf("%d ", need[i][j]);
                }
                printf("\n");
            }
            printf("Availables Resources:\n");
            for (int i = 0; i < m; i++)
            {
                printf("%d ", avail[i]);
            }
            printf("\n");
        }
    }
    return (0);
}
