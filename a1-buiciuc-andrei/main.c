#include <stdio.h>


void print_menu()
{
    printf_s("Hello and Welcome. Choose a command: ");
    printf_s("\n1. Read a vector of numbers");
    printf_s("\n2. Functionality A");
    printf_s("\n3. Functionality B");
    printf_s("\n4. Functionality C");
    printf_s("\n0. Exit");
}

void read_vector(int array[], int* n)
{
    /*
     * Function that reads an array of natural numbers.
     */

    int i;
    printf_s("Dimension: ");
    scanf("%d", n);

    printf_s("Elements: ");
    for(i = 0; i < *n; i ++)
        scanf("%d", &array[i]);

}

int gcd(int a, int b)
{
    /*
     * Function that finds recursively the greatest common divisor between two numbers.
     */

    if(a == 0)
        return b;
    return gcd(b % a, a);
}

int are_relatively_prime(int a, int b)
{
    /*
     * Function that checks if two numbers are relatively prime (the gcd is 1).
     * returns 1 if True
     * returns 0 if False
     */

    if(gcd(a, b) == 1)
        return 1;
    else
        return 0;
}

int is_prime(int x)
{
    /*
     * Function that checks if a number is prime.
     * returns 1 if True
     * return 0 if False
     *
     * Basic cases are treated in the beginning.
     */

    if(x < 2)
        return 0;
    else if(x == 2)
        return 1;
    else if(x % 2 == 0)
        return 0;
    else
    {
        int k = 3;
        while(k * k <= x && x % k != 0)
            k += 2;

        if(k * k > x)
            return 1;
        else
            return 0;
    }
}

void function_a(int numbers[])
{
    /*
     * Function responsible for the first functionality: prints the first and only 8 numbers greater than 2 with the
     * following property: all natural numbers smaller than xi that are relatively prime with xi except 1 are prime.
     *
     */

    int count = 8, number = 3, i, j = 0, okay;

    while(count != 0)
    {
        okay = 1;
        for(i=2; i < number; i++)
            if(are_relatively_prime(i, number))
                if(is_prime(i) == 0)
                {
                    okay = 0;
                    break;
                }

        if(okay == 1)
        {
            // printf_s("%d ", number);

            numbers[j] = number;
            j = j + 1;
            count = count - 1;
        }

        number = number + 1;
    }
}

int compare_digits(int a, int b)
{
    /*
     * Function that checks whether two numbers have the same digits or not.
     * We create two frequency arrays in which we mark the digits found in the two given numbers respectively.
     */

    int a_freq[10], b_freq[10], i;

    for(i = 0; i <= 9; i++)
    {
        a_freq[i] = 0;
        b_freq[i] = 0;
    }

    while(a != 0)
    {
        a_freq[a%10] = 1;
        a /= 10;
    }

    while(b != 0)
    {
        b_freq[b%10] = 1;
        b /= 10;
    }

    for(i = 0; i <= 9; i ++)
        if(a_freq[i] != b_freq[i])
            return 0;

    return 1;
}

void function_b(int array[], int* n, int* lmax, int* end_position)
{
    /*
     * Function responsible with the second functionality: finds the longest contiguous subsequence such that
     * any consecutive elements contain the same digits.
     */

    int length = 1, number_ant, number, i;
    *lmax = 0;
    number_ant = array[0];
    i = 1;

    while(i != *n)
    {
        number = array[i];
        if(compare_digits(number_ant, number) == 1)
            length = length + 1;
        else
        {
            if(length > *lmax)
            {
                *lmax = length;
                *end_position = i - 1;
            }

            length = 1;
        }

        number_ant = number;
        i = i + 1;
    }

    if(length > *lmax)
    {
        *lmax = length;
        *end_position = i - 1;
    }

}

int function_c(int array[], int* n, int* lmax, int* end_position, int* start_position)
{
    /*
     * Function that computes the longest subsequence with the maximum sum.
     */

    int max_sum = -100000;    // the maximum sum
    int subseq_sum = 0;       // the sum the current subsequence
    int start = 0;            // the index from where the subsequence starts

    for(int i = 0; i < *n; i ++){
        subseq_sum = subseq_sum + array[i];

        if(subseq_sum > max_sum){
            max_sum = subseq_sum;
            *end_position = i;  // mark the position where you are at -> end_position
            *start_position = start; // mark the position where you started from -> start_position
        }

        if(subseq_sum < 0){
            subseq_sum = 0; // reinitialize the current subsequence sum
            start = i + 1;
        }

    }

    *lmax = *end_position - max_sum + 1;    // longest subsequence with maximum sum
    return max_sum;
}

void function_a_ui(int numbers[])
{
    /*
     * UI function for the first functionality: prints the result.
     */
    function_a(numbers);
    for(int i = 0; i <= 7; i ++)
        printf("%d ", numbers[i]);
}


void function_b_ui(int array[], int *n, int *lmax, int *end_position)
{
    /*
     * UI function for the second functionality: prints the result.
     */
    int start_position;
    function_b(array, n, lmax, end_position);
    start_position = *end_position - *lmax + 1;
    for(int i = start_position; i <= *end_position; i ++)
        printf("%d ", array[i]);
}

void function_c_ui(int array[], int *n, int*lmax, int* end_position, int* start_position)
{
    /*
     * UI function for the third functionality: prints the result.
     */

    int max_sum;
    max_sum = function_c(array, n, lmax, end_position, start_position);

    printf("The maximum sum is: %d", max_sum);
    printf("\nThe longest subsequence: ");
    for(int i = *start_position; i <= *end_position; i ++)
        printf("%d ", array[i]);
}

int main()
{
    int done = 0;
    int array[100], n, lmax, end_position;
    int numbers[8];
    char option;
    int start_position;

    print_menu();
    while(!done)
    {
        printf("\nEnter your command: ");
        scanf(" %c", &option);

        if(option == '1')
            read_vector(array, &n);
        else if(option == '2')
            function_a_ui(numbers);
        else if(option == '3')
            function_b_ui(array, &n, &lmax, &end_position);
        else if(option == '4')
            function_c_ui(array, &n, &lmax, &end_position, &start_position);
        else if(option == '0')
            done = 1;
        else
            printf_s("Bad command.");
    }

    return 0;
}