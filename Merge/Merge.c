#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int left, int mid, int right, int* comparisons, int* moves) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 임시 배열 생성
    int L[n1], R[n2];

    // 데이터를 임시 배열 L[]와 R[]로 복사
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // 정렬된 임시 배열을 다시 arr[left..right]로 복사
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        (*moves)++;
        k++;
    }

    // L[]에 남아 있는 요소를 복사
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        (*moves)++;
    }

    // R[]에 남아 있는 요소를 복사
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        (*moves)++;
    }
}

void mergeSort(int arr[], int left, int right, int* comparisons, int* moves) {
    if (left < right) {
        // (left+right)/2와 같지만 큰 left와 right에 대한 오버플로우를 피함
        int mid = left + (right - left) / 2;

        // 첫 번째 반과 두 번째 반을 정렬
        mergeSort(arr, left, mid, comparisons, moves);
        mergeSort(arr, mid + 1, right, comparisons, moves);

        // 정렬된 반들을 합침
        merge(arr, left, mid, right, comparisons, moves);
    }
}

int main() {
    // 난수 생성을 위한 시드
    srand(time(NULL));

    // 배열의 요소 수
    int n = 20;

    // 평균을 위한 반복 횟수
    int iterations = 20;

    // 각 반복에 대한 비교와 이동 횟수를 저장하는 배열
    int comparisons_array[iterations];
    int moves_array[iterations];

    // 다중 반복을 위한 루프
    for (int i = 0; i < iterations; i++) {
        // 0부터 99까지의 20개의 난수로 배열 생성
        int arr[n];
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 100;
        }

        // 각 반복에 대한 비교와 이동을 초기화
        int comparisons = 0;
        int moves = 0;

        // 정렬되지 않은 배열 출력
        printf("미정렬 배열 (반복 %d):\n", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");

        // 병합 정렬 수행
        mergeSort(arr, 0, n - 1, &comparisons, &moves);

        // 정렬된 배열 출력
        printf("정렬된 배열 (반복 %d):\n", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");

        // 각 반복에 대한 비교와 이동을 저장
        comparisons_array[i] = comparisons;
        moves_array[i] = moves;

        // 각 반복에 대한 정렬 과정 출력
        printf("비교 횟수: %d\n", comparisons);
        printf("이동 횟수: %d\n", moves);
        printf("=====================================\n");
    }

    // 평균 비교와 이동 횟수를 계산하고 출력
    int total_comparisons = 0;
    int total_moves = 0;
    for (int i = 0; i < iterations; i++) {
        total_comparisons += comparisons_array[i];
        total_moves += moves_array[i];
    }

    printf("평균 비교 횟수: %.2f\n", (float)total_comparisons / iterations);
    printf("평균 이동 횟수: %.2f\n", (float)total_moves / iterations);

    return 0;
}