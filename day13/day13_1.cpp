#include <stdio.h>
#include <vector>

int main() {
    FILE* input = fopen("testinput13.txt", "r");

    char c;
    int state = 0;
    int _state = 0;
    int tmpa, tmpb;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            if (state == 0) {

            }
            else if (state == 1) {

            }
            else if (state == 2) {

            }
        }
        else {
            if ()
        }
    }

    return 0;
}