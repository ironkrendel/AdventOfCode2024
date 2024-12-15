// DOESN'T WORK!!!!

// #include <stdio.h>
// #include <vector>
// #include <chrono>
// #include <thread>

// struct Vector2D {
//     int x;
//     int y;
// };

// struct FVector2D {
//     float x;
//     float y;
// };

// inline void PrintData(char** data, int width, int height, float pos_x, float pos_y, std::vector<FVector2D> *boxes);
// #define PRINTDATA PrintData(data, width, height, pos_x, pos_y, &boxes)

// inline bool Collides(std::vector<FVector2D> *boxes, int index, float pos_x, float pos_y, float delta_x, float delta_y, bool first_move);

// template<typename T>
// bool VectorContains(std::vector<T> vec, T val) {
//     for (std::size_t i = 0;i < vec.size();i++) {
//         if (vec[i] == val)
//             return true;
//     }
//     return false;
// }

// int main() {
//     FILE* input = fopen("input15.txt", "r");

//     char c;
//     std::vector<char> moves;
//     int height = 0, width = 0;
//     int state = 0;
//     while ((c = fgetc(input)) != EOF) {
//         if (state == 0) {
//             if (c == '\n') {
//                 height++;
//                 if (fgetc(input) == '\n') {
//                     state = 1;
//                 }
//                 else {
//                     fseek(input, -1, SEEK_CUR);
//                 }
//             }
//             else {
//                 width++;
//             }
//         }
//         else if (state == 1) {
//             if (c == '\n') {

//             }
//             else {
//                 moves.push_back(c);
//             }
//         }
//     }
//     width = width / height;
//     width *= 2;
//     fseek(input, 0, SEEK_SET);

//     char** data = new char*[height];
//     float pos_x, pos_y;

//     std::vector<FVector2D> boxes;
//     for (int i = 0;i < height;i++) {
//         data[i] = new char[width * 2];
//         for (int j = 0;j < width;j+=2) {
//             data[i][j] = fgetc(input);
//             if (data[i][j] == '@') {
//                 pos_x = static_cast<float>(j) / 2;
//                 pos_y = static_cast<float>(i);
//                 data[i][j] = '.';
//                 data[i][j + 1] = '.';
//             }
//             else if (data[i][j] == 'O') {
//                 // data[i][j] = '[';
//                 // data[i][j + 1] = ']';
//                 data[i][j] = '.';
//                 data[i][j + 1] = '.';
//                 boxes.push_back(FVector2D{static_cast<float>(j) / 2, static_cast<float>(i)});
//             }
//             else {
//                 data[i][j + 1] = data[i][j];
//             }
//         }
//         fseek(input, 1, SEEK_CUR);
//     }

//     PRINTDATA;

//     for (std::size_t i = 0;i < moves.size();i++) {
//         float delta_x = 0, delta_y = 0;
//         if (moves[i] == '<') {
//             delta_x = -0.5;
//         }
//         else if (moves[i] == '^') {
//             delta_y = -1;
//         }
//         else if (moves[i] == '>') {
//             delta_x = 0.5;
//         }
//         else if (moves[i] == 'v') {
//             delta_y = 1;
//         }

//         if (data[static_cast<int>(pos_y + delta_y)][static_cast<int>(pos_x + delta_x) * 2] == '#') continue;

//         std::vector<int> push_list;
//         for (std::size_t b = 0;b < boxes.size();b++) {
//             // printf(" - %f %f\n", pos_x, pos_y);
//             if (Collides(&boxes, b, pos_x, pos_y, delta_x, delta_y, true)) {
//                 push_list.push_back(b);

//                 float _x = boxes[b].x;
//                 float _y = boxes[b].y;
//                 int _index = b;
//                 // printf(" | %ld | ", b);
//                 while (_x * 2 >= 0 && _x * 2 < width && _y >= 0 && _y < height) {
//                     bool flag = true;
//                     for (std::size_t _b = 0;_b < boxes.size();_b++) {
//                         if (_b == _index) continue;
//                         if (Collides(&boxes, _b, _x, _y, delta_x, delta_y, false)) {
//                             if (!VectorContains(push_list, static_cast<int>(_b))) {
//                                 push_list.push_back(_b);
//                                 flag = false;
//                             }
//                             // flag = false;
//                             // _x = boxes[_b].x;
//                             // _y = boxes[_b].y;
//                             // _index = _b;
//                         }
//                         if (Collides(&boxes, _b, _x + 0.5, _y, delta_x, delta_y, false)) {
//                             if (!VectorContains(push_list, static_cast<int>(_b))) {
//                                 push_list.push_back(_b);
//                                 flag = false;
//                             }
//                             // flag = false;
//                         }
//                         // if (delta_x > 0 && Collides(&boxes, _b, _x + 0.5, _y, delta_x, delta_y)) {
//                         //     push_list.push_back(_b);
//                         //     flag = false;
//                         // }
//                     }
//                     if (push_list.size() > 0) {
//                         int last_index = push_list[push_list.size() - 1];
//                         _x = boxes[last_index].x;
//                         _y = boxes[last_index].y;
//                         _index = last_index;
//                     }
//                     // int last_index = push_list[push_list.size() - 1];
//                     // _x = boxes[last_index].x;
//                     // _y = boxes[last_index].y;
//                     // _index = last_index;

//                     // printf("%d %d\n", _x, _y);
//                     // for (std::size_t k = 0;k < push_list.size();k++) {
//                     //     printf("%d %f %f\n", push_list[k], boxes[push_list[k]].x, boxes[push_list[k]].y);
//                     // }
//                     // printf("---------------------------------------\n");

//                     if (flag) break;
//                 }
//             }
//         }

//         bool flag = false;
//         for (std::size_t b = 0;b < push_list.size();b++) {
//             if (data[static_cast<int>(boxes[push_list[b]].y + delta_y)][static_cast<int>((boxes[push_list[b]].x + delta_x) * 2)] == '#') {
//                 flag = true;
//                 break;
//             }
//             if (data[static_cast<int>(boxes[push_list[b]].y + delta_y)][static_cast<int>((boxes[push_list[b]].x + delta_x) * 2) + 1] == '#') {
//                 flag = true;
//                 break;
//             }
//         }
//         printf("%ld %ld\n", i, moves.size());
//         if (flag) continue;

//         for (std::size_t b = 0;b < push_list.size();b++) {
//             // printf("- %d ", push_list[b]);
//             boxes[push_list[b]].x += delta_x;
//             boxes[push_list[b]].y += delta_y;
//         }
//         // printf("\n");

//         pos_x += delta_x;
//         pos_y += delta_y;

//         // PRINTDATA;
//     }

//     int answer = 0;
//     // for (int i = 0;i < height;i++) {
//     //     for (int j = 0;j < width;j++) {
//     //         if (data[i][j] == '[') {
//     //             printf("%d %d\n", j, i);
//     //             answer += i * 100 + j;
//     //         }
//     //     }
//     // }

//     PRINTDATA;

//     for (std::size_t i = 0;i < boxes.size();i++) {
//         answer += static_cast<int>(boxes[i].y) * 100 + static_cast<int>(boxes[i].x * 2);
//         // printf("%d\n", static_cast<int>(boxes[i].y) * 100 + static_cast<int>(boxes[i].x * 2));
//     }
//     printf("%d\n", answer);

//     return 0;
// }

// inline void PrintData(char** data, int width, int height, float pos_x, float pos_y, std::vector<FVector2D> *boxes) {
//     int p_y = static_cast<int>(pos_y);
//     int p_x = static_cast<int>(pos_x * 2);
//     for (int i = 0;i < height;i++) {
//         for (int j = 0;j < width;j++) {
//             if (i == p_y && j == p_x) {
//                 printf("@");
//             }
//             else {
//                 bool flag = false;
//                 for (std::size_t b = 0;b < boxes->size();b++) {
//                     if (i == (*boxes)[b].y && static_cast<float>(j)/2 == (*boxes)[b].x) {
//                         flag = true;
//                         break;
//                     }
//                 }
//                 if (flag) {
//                     printf("[]");
//                     j++;
//                 }
//                 else {
//                     printf("%c", data[i][j]);
//                 }
//             }
//         }
//         printf("\n");
//     }
//     printf("\n");

//     // for (std::size_t i = 0;i < boxes->size();i++) {
//     //     printf("%f %f\n", (*boxes)[i].x, (*boxes)[i].y);
//     // }
//     // printf("\n");

//     // std::this_thread::sleep_for(std::chrono::milliseconds(10));
// }

// inline bool Collides(std::vector<FVector2D> *boxes, int index, float pos_x, float pos_y, float delta_x, float delta_y, bool first_move) {
//     // printf(" | %f %f %f\n", (*boxes)[index].x, (pos_x + delta_x * 2), pos_x);
//     if ((*boxes)[index].x == pos_x + delta_x && (*boxes)[index].y == pos_y + delta_y) {
//         return true;
//     }
//     else if (((*boxes)[index].x + 0.5) == pos_x + delta_x && (*boxes)[index].y == pos_y + delta_y) {
//         return true;
//     }
//     // else if ((*boxes)[index].x == (pos_x + delta_x * 2) && (*boxes)[index].y == pos_y + delta_y && delta_x < 0) {
//     //     return true;
//     // }
//     // else if (!first_move && (*boxes)[index].x == pos_x + 0.5 && (*boxes)[index].y == pos_y + delta_y) {
//     //     return true;
//     // }
//     // else if ((*boxes)[index].x == pos_x - 0.5 && (*boxes)[index].y == pos_y + delta_y) {
//     //     return true;
//     // }
//     return false;
// }