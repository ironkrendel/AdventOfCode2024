#include <stdio.h>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <map>

int NumDigitsCnt(unsigned long long num);

int main() {
    FILE* input = fopen("input11.txt", "r");

    std::map<u_int64_t, u_int64_t> data_map;

    char c;
    unsigned long long num = 0;
    while ((c = fgetc(input)) != EOF) {
        if (c == ' ') {
            data_map[num]++;
            num = 0;
        }
        else {
            num *= 10;
            num += c - '0';
        }
    }
    data_map[num]++;

    for (int lapse = 0;lapse < 75;lapse++) {
        std::map<u_int64_t, u_int64_t> new_map = data_map;
        for (std::map<u_int64_t, u_int64_t>::iterator it = data_map.begin();it != data_map.end();it++) {
            if (it->second <= 0) continue;
            int digit_cnt = NumDigitsCnt(it->first);
            if (it->first == 0) {
                new_map[0]-=it->second;
                new_map[1]+=it->second;
            }
            else if (digit_cnt % 2 == 0) {
                u_int64_t left_half = it->first / pow(10, digit_cnt / 2);
                u_int64_t right_half = it->first % static_cast<long>(pow(10, digit_cnt / 2));

                new_map[it->first]-=it->second;
                new_map[left_half]+=it->second;
                new_map[right_half]+=it->second;
            }
            else {
                u_int64_t new_num = it->first * 2024;
                new_map[it->first]-=it->second;
                new_map[new_num]+=it->second;
            }
        }
        data_map = new_map;

        u_int64_t tmp_res = 0;
        for (std::map<u_int64_t, u_int64_t>::iterator itt = data_map.begin();itt != data_map.end();itt++) {
            if (itt->second <= 0) continue;
            tmp_res += itt->second;
        }
        printf("%d - %ld\n", lapse, tmp_res);
    }

    u_int64_t result = 0;
    for (std::map<u_int64_t, u_int64_t>::iterator it = data_map.begin();it != data_map.end();it++) {
        if (it->second > 0) {
            result += it->second;
        }
    }

    printf("%ld\n", result);

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