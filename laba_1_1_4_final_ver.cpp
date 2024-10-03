#include <stdio.h>
#define MAX_LINE_LENGTH 3
#include <assert.h>
#include <math.h>
#include <stdlib.h>


void sep_arr_by_tau(int *new_arr, int new_size, int *source_arr,  int source_size, int tau) {
    for (int i = 0, k = 0; i < source_size; i += tau, k++) {
        int counter = 0;
        for (int j = i; j < i + tau; j++) { //накинуть потом assert
            counter += source_arr[j];

        }
        assert(k >= 0 && k < new_size);
        new_arr[k] = counter;
        // printf("%d\n", new_arr[k]);

    }
}

int get_file_size(FILE *fp) {
    char line[3];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        count++;
    }
    rewind(fp); //устанавливаю указатель обратно на начало потока
    return count;

}



int summation(int *new_arr, int new_size) {
    int sum = 0;
    for (int i = 0; i < new_size; i++) {
        assert(i >= 0 && i < new_size);
        sum += new_arr[i];
    }
    return sum;
}
int summation_of_sq(int *new_arr, int new_size) {
    int sum_sq = 0;
    for (int i = 0; i < new_size; i++) {
        assert(i >= 0 && i < new_size);
        sum_sq += new_arr[i] * new_arr[i];
    }
    return sum_sq;
}

double standart_deviation(int* new_arr, int new_size) {
    int stdev = 0;
    int res_sum = summation(new_arr, new_size);
    int res_sum_of_sq = summation_of_sq(new_arr, new_size);
    stdev = (double) (res_sum_of_sq - (double) pow(res_sum, 2) / new_size) / (new_size);
    return sqrt(stdev);
}

void array_filling(FILE *file, int *arr, int size) { //передавать в качестве параметра массив numbers, который объявлет в мэйне
    char line[MAX_LINE_LENGTH];
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        assert(0 <= i && i < size);
        sscanf(line, "%d", &arr[i]); //scanf по строкам
        i++;
    }

    fclose(file);

}

int main() {
    FILE *file = fopen("exp_1.1.4.txt", "r");

    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    int file_length  = get_file_size(file);
    printf("Размер файла - %d чисел\n", file_length);
    int *numbers = (int *) calloc(file_length, sizeof(int));
    array_filling(file, numbers, file_length);
    printf("Введите tau: \n");
    int tau;
    // int tau_10 = 10;
    // int tau_40 = 40;
    // int tau_80 = 80;
    scanf("%d", &tau);
    int length = file_length / tau;
    int *sep_array = (int *) calloc(length, sizeof(int));
    sep_arr_by_tau(sep_array, length, numbers, file_length, tau);
    double stdev = standart_deviation(sep_array, length);
    printf("stdev = %lg", stdev);
    free(numbers);
    free(sep_array);
    return 0;
}
