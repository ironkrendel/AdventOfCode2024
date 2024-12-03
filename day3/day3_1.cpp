#include <stdio.h>
#include <cctype>
#include <cstdlib>

int main() {
    FILE *input;
    input = fopen("input3.txt", "r");

    char c;
    int result = 0;
    int state = 0;
    char* num1_buf = new char[4];
    int num1_buf_size = 0;
    char* num2_buf = new char[4];
    int num2_buf_size = 0;
    const char* state_0_string = "mul(";
    int state_0_progress = 0;
    bool mul_status = true;
    int do_cmd_progress = 0;
    const char* do_string = "do()";
    const char* dont_string = "don't()";

    while ((c = fgetc(input)) != EOF) {
        if (state == 0) {
            if (do_cmd_progress <= 3) {
                if (do_cmd_progress == 3 && c == do_string[do_cmd_progress]) {
                    mul_status = true;
                    do_cmd_progress = 0;
                }
                else if (c == dont_string[do_cmd_progress] || c == do_string[do_cmd_progress]) {
                    do_cmd_progress++;
                }
                else {
                    do_cmd_progress = 0;
                }
            }
            else {
                if (do_cmd_progress == 6 && c == dont_string[do_cmd_progress]) {
                    mul_status = false;
                    do_cmd_progress = 0;
                }
                else if (do_cmd_progress > 6) {
                    do_cmd_progress = 0;
                }
                else {
                    do_cmd_progress++;
                }
            }
            if (c == state_0_string[state_0_progress] && state_0_progress >= 3) {
                state = 1;
                state_0_progress = 0;
            }
            else if (c == state_0_string[state_0_progress]) {
                state_0_progress++;
            }
            else {
                state_0_progress = 0;
            }
        }
        else if (state == 1) {
            if (c == ',') {
                if (num1_buf_size <= 3 && num1_buf_size != 0) {
                    num1_buf[num1_buf_size] = '\0';
                    num1_buf_size++;
                    state = 2;
                }
                else {
                    num1_buf_size = 0;
                    state = 0;
                }
            }
            else if (isdigit(c)) {
                if (num1_buf_size < 3) {
                    num1_buf[num1_buf_size] = c;
                    num1_buf_size++;
                }
                else {
                    num1_buf_size = 0;
                    state = 0;
                }
            }
            else {
                num1_buf_size = 0;
                state = 0;
            }
        }
        else if (state == 2) {
            if (c == ')') {
                if (num2_buf_size <= 3 && num2_buf_size != 0) {
                    num2_buf[num2_buf_size] = '\0';
                    num2_buf_size++;
                    if(mul_status) result += atoi(num1_buf) * atoi(num2_buf);
                    num1_buf_size = 0;
                    num2_buf_size = 0;
                    state = 0;
                }
                else {
                    num1_buf_size = 0;
                    num2_buf_size = 0;
                    state = 0;
                }
            }
            else if (isdigit(c)) {
                if (num2_buf_size < 3) {
                    num2_buf[num2_buf_size] = c;
                    num2_buf_size++;
                }
                else {
                    num1_buf_size = 0;
                    num2_buf_size = 0;
                    state = 0;
                }
            }
            else {
                num1_buf_size = 0;
                num2_buf_size = 0;
                state = 0;
            }
        }
    }

    printf("%d\n", result);

    fclose(input);
    
    return 0;
}