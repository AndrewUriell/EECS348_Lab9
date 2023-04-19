#include <stdio.h>
#include <stdlib.h>

#define MONTHS 12

void print_monthly_sales(char *months[], float *sales)
{
    printf("Monthly sales report for 2022:\n\n");
    printf("%-15s%-10s\n\n", "Month:", "Sales:");
    for (int i = 0; i < MONTHS; i++)
    {
        printf("%-15s$%.2f\n", months[i], sales[i]);
    }
    printf("\n");
}

void print_sales_summary(char *months[], float *sales)
{
    float min_value = 999999.99;
    float max_value = 0.0;
    char *max_month = "";
    char *min_month = "";
    float total;
    for (int i = 0; i < MONTHS; i++)
    {
        total += sales[i];
        // If the sales is less than min value, set sales to min value and month to min month
        if (sales[i] < min_value)
        {
            min_value = sales[i];
            min_month = months[i];
        }
        // If the sales is more than max value, set sales to max value and month to max month
        if (sales[i] > max_value)
        {
            max_value = sales[i];
            max_month = months[i];
        }
    }
    float avg = total / MONTHS;
    printf("Sales summary:\n\n");
    printf("Minimum sales:\t$%.2f\t(%s)\n", min_value, min_month);
    printf("Maximum sales:\t$%.2f\t(%s)\n", max_value, max_month);
    printf("Average sales:\t$%.2f\n", avg);
}

void print_six_months(char *months[], float *sales)
{
    printf("\nSix-Month Moving Average Report:\n\n");
    for (int i = 0; i <= MONTHS / 2; i++)
    {
        char *initial_month = months[i];
        char *advance_six_months = months[i + 5];
        float total = 0.0;

        for (int j = i; j < i + 6; j++)
        {
            // Adds all numbers within 6 indeces/months
            total += sales[j];
        }
        // Finds 6 month average
        float six_month_avg = total / 6;
        printf("%-15s - %-10s $%.2f\n", initial_month, advance_six_months, six_month_avg);
    }
}

void print_descending_report(char *months[], float *sales)
{
    printf("\nSales Report (Highest to Lowest):\n\n");
    printf("%-10s%-10s\n", "Month", "Sales");
    for (int i = 0; i < MONTHS; i++)
    {
        for (int j = i + 1; j < MONTHS; j++)
        {
            // Swaps indeces so they are in descending order
            if (sales[i] < sales[j])
            {
                float tmp_sales = sales[i];
                char *tmp_months = months[i];
                sales[i] = sales[j];
                months[i] = months[j];
                sales[j] = tmp_sales;
                months[j] = tmp_months;
            }
        }
        printf("%-10s$%-.2f\n", months[i], sales[i]);
    }
}

float *read_file(char *file_name)
{
    float *sales_data = (float *)malloc(sizeof(float) * MONTHS);

    FILE *pFile = fopen(file_name, "r");
    // If nothing in file print out cant open file
    if (NULL == pFile)
    {
        printf("Could Not Open File \n");
    }

    for (int i = 0; i < MONTHS; i++)
    {
        fscanf(pFile, "%f", &sales_data[i]);
    }
    fclose(pFile);
    // This is what *sales in main will be set to
    return sales_data;
}

int main()
{

    float *sales = read_file("test.txt");
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    print_monthly_sales(months, sales);
    print_sales_summary(months, sales);
    print_six_months(months, sales);
    print_descending_report(months, sales);

    return 0;
}
