#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <string>

bool ValidEquasion(u_int64_t res, std::vector<int>* nums);

int main() {
    FILE *input;
    input = fopen("input7.txt", "r");

    char c;
    u_int64_t answer = 0;
    u_int64_t cur_res = 0;
    std::vector<int> cur_numbers;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            if (ValidEquasion(cur_res, &cur_numbers)) {
                answer += cur_res;
            }

            cur_res = 0;
            cur_numbers.clear();
        }
        else {
            fseek(input, -1, SEEK_CUR);
            if (cur_res == 0) {
                fscanf(input, "%ld:", &cur_res);
            }
            else {
                long tmp;
                fscanf(input, " %ld", &tmp);
                cur_numbers.push_back(tmp);
            }
        }
    }

    std::cout << answer << std::endl;

    fclose(input);
    
    return 0;
}

bool ValidEquasion(u_int64_t res, std::vector<int>* nums) {
    for (int i = 0;i < std::pow(3, nums->size() - 1);i++) {
        std::vector<char> ops(nums->size() - 1);

        u_int64_t tmp = i;
        for (int j = 0;j < ops.size();j++) {
            if (tmp % 3 == 0) {
                ops[ops.size() - 1 - j] = '+';
            }
            else if (tmp % 3 == 1) {
                ops[ops.size() - 1 - j] = '*';
            }
            else {
                ops[ops.size() - 1 - j] = '|';
            }
            tmp = tmp / 3;
        }

        tmp = (*nums)[0];
        int current_op = 0;
        for (int j = 1;j < nums->size();j++) {
            if (ops[current_op] == '+') {
                tmp += (*nums)[j];
            }
            else if (ops[current_op] == '*') {
                tmp *= (*nums)[j];
            }
            else {
                std::string tmp_s = std::to_string(tmp);
                tmp_s.append(std::to_string((*nums)[j]));
                // tmp = static_cast<u_int64_t>(atoi(tmp_s.c_str()));
                tmp = std::stol(tmp_s);
            }
            current_op++;
        }
        if (tmp == res) {
            return true;
        }
    }
    return false;
}