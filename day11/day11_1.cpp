#include <stdio.h>
#include <vector>
#include <math.h>

int NumDigitsCnt(unsigned long long num);

int main() {
    FILE* input = fopen("input11.txt", "r");

    std::vector<unsigned long long> data;

    char c;
    unsigned long long num = 0;
    while ((c = fgetc(input)) != EOF) {
        if (c == ' ') {
            data.push_back(num);
            num = 0;
        }
        else {
            num *= 10;
            num += c - '0';
        }
    }
    data.push_back(num);

    for (int lapse = 0;lapse < 75;lapse++) {
        // for (std::size_t j = 0;j < data.size();j++) {
        //     printf("%lld ", data[j]);
        // }
        // printf("\n");
        for (std::size_t i = 0;i < data.size();i++) {
            int digit_cnt;
            if (data[i] == 0) {
                data[i] = 1;
            }
            else if ((digit_cnt = NumDigitsCnt(data[i])) % 2 == 0) {
                unsigned long long left_half = data[i] / pow(10, digit_cnt / 2);
                unsigned long long right_half = data[i] % static_cast<long>(pow(10, digit_cnt / 2));
                
                data[i] = left_half;
                data.insert(std::next(data.begin(), i + 1), right_half);
                i++;
            }
            else {
                data[i] *= 2024;
            }
        }
        printf("%d %ld\n", lapse, data.size());
    }
    for (std::size_t j = 0;j < data.size();j++) {
        printf("%lld ", data[j]);
    }
    printf("\n");

    printf("%ld\n", data.size());

    return 0;
}

int NumDigitsCnt(unsigned long long num) {
    int cnt = 0;
    while (num) {
        cnt++;
        num /= 10;
    }
    return cnt;
}