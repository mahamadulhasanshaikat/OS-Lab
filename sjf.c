#include <stdio.h>

int main()
{
    int count, n;
    int time = 0;
    printf("\n\nEnter the Total number of Process: ");
    scanf("%d", &n);

    int arrival_time[n], cpu_time[n], rt[n], t[n];
    int gantt_chart[n][2];

    for (count = 0; count < n; count++)
    {
        printf("Enter Arrival Time and CPU Time for Process Process Number %d :", count + 1);
        scanf("%d", &arrival_time[count]);
        scanf("%d", &cpu_time[count]);
        rt[count] = cpu_time[count];
    }

    printf("\n\nProcess\t  Arrival Time  |  CPU Time    |Turnaround Time | Waiting Time\n\n");

    int i, flag = 0, gc_index = 0;

    for (count = 0; count < n; count++)
    {
        int a;
        int min = 100, min2 = 100;
        for (i = 0; i < n; i++)
        {
            if (time != 0)
            {
                if (rt[i] <= min && rt[i] != 0 && arrival_time[i] <= time)
                {
                    a = i;
                    min = rt[i];
                }
            }
            else
            {
                if (arrival_time[i] <= min)
                {
                    a = i;
                    min = arrival_time[i];
                }
            }
        }

        if (time == 0)
        {
            for (i = 0; i < n; i++)
            {
                if (min == arrival_time[i])
                    flag++;
            }
        }

        if (flag > 1)
        {
            for (i = 0; i < n; i++)
            {
                if (arrival_time[i] <= min && rt[i] <= min2)
                {
                    a = i;
                    min = arrival_time[i];
                    min2 = rt[i];
                }
                flag = 0;
            }
        }

        if (arrival_time[a] > time)
        {
            time = arrival_time[a] + rt[a];
            rt[a] = 0;
            t[a] = time;

            gantt_chart[gc_index][0] = a + 1;
            gantt_chart[gc_index][1] = time;
            gc_index++;
        }
        else
        {
            time = time + rt[a];
            rt[a] = 0;
            t[a] = time;

            gantt_chart[gc_index][0] = a + 1;
            gantt_chart[gc_index][1] = time;
            gc_index++;
        }
    }

    for (count = 0; count < n; count++)
    {
        printf("P[%d]\t|\t%d\t|\t%d\t|\t%d\t|\t%d\n", count + 1, arrival_time[count], cpu_time[count], t[count] - arrival_time[count], t[count] - arrival_time[count] - cpu_time[count]);
    }

    printf("\nGantt Chart:\n");
    for (i = 0; i < gc_index; i++)
    {
        printf("| P%d ", gantt_chart[i][0]);
    }
    printf("|\n");

    printf("0");
    for (i = 0; i < gc_index; i++)
    {
        printf("    %d", gantt_chart[i][1]);
    }
    printf("\n");

    return 0;
}
