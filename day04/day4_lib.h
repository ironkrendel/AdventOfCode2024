#pragma once

struct Vector2D
{
    int x;
    int y;
};

bool check_right(char* data, Vector2D data_size, Vector2D pos) {
    if (data_size.x - pos.x <= 3) return false;
    if (data[pos.y * data_size.x + pos.x + 1] == 'M' && data[pos.y * data_size.x + pos.x + 2] == 'A' && data[pos.y * data_size.x + pos.x + 3] == 'S') return true;
    return false;
}

bool check_left(char* data, Vector2D data_size, Vector2D pos) {
    if (pos.x <= 2) return false;
    if (data[pos.y * data_size.x + pos.x - 1] == 'M' && data[pos.y * data_size.x + pos.x - 2] == 'A' && data[pos.y * data_size.x + pos.x - 3] == 'S') return true;
    return false;
}

bool check_down(char* data, Vector2D data_size, Vector2D pos) {
    if (data_size.y - pos.y <= 3) return false;
    if (data[(pos.y + 1) * data_size.x + pos.x] == 'M' && data[(pos.y + 2) * data_size.x + pos.x] == 'A' && data[(pos.y + 3) * data_size.x + pos.x] == 'S') return true;
    return false;
}

bool check_up(char* data, Vector2D data_size, Vector2D pos) {
    if (pos.y <= 2) return false;
    if (data[(pos.y - 1) * data_size.x + pos.x] == 'M' && data[(pos.y - 2) * data_size.x + pos.x] == 'A' && data[(pos.y - 3) * data_size.x + pos.x] == 'S') return true;
    return false;
}

bool check_up_right(char* data, Vector2D data_size, Vector2D pos) {
    if (data_size.x - pos.x <= 3 || pos.y <= 2) return false;
    if (data[(pos.y - 1) * data_size.x + (pos.x + 1)] == 'M' && data[(pos.y - 2) * data_size.x + (pos.x + 2)] == 'A' && data[(pos.y - 3) * data_size.x + (pos.x + 3)] == 'S') return true;
    return false;
}

bool check_up_left(char* data, Vector2D data_size, Vector2D pos) {
    if (pos.x <= 2 || pos.y <= 2) return false;
    if (data[(pos.y - 1) * data_size.x + (pos.x - 1)] == 'M' && data[(pos.y - 2) * data_size.x + (pos.x - 2)] == 'A' && data[(pos.y - 3) * data_size.x + (pos.x - 3)] == 'S') return true;
    return false;
}

bool check_down_right(char* data, Vector2D data_size, Vector2D pos) {
    if (data_size.x - pos.x <= 3 || data_size.y - pos.y <= 3) return false;
    if (data[(pos.y + 1) * data_size.x + (pos.x + 1)] == 'M' && data[(pos.y + 2) * data_size.x + (pos.x + 2)] == 'A' && data[(pos.y + 3) * data_size.x + (pos.x + 3)] == 'S') return true;
    return false;
}

bool check_down_left(char* data, Vector2D data_size, Vector2D pos) {
    if (pos.x <= 2 || data_size.y - pos.y <= 3) return false;
    if (data[(pos.y + 1) * data_size.x + (pos.x - 1)] == 'M' && data[(pos.y + 2) * data_size.x + (pos.x - 2)] == 'A' && data[(pos.y + 3) * data_size.x + (pos.x - 3)] == 'S') return true;
    return false;
}

bool check_mas(char* data, Vector2D data_size, Vector2D pos) {
    if (pos.x <= 0 || pos.y <= 0 || data_size.x - pos.x <= 1 || data_size.y - pos.y <= 1) return false;
    if (data[(pos.y - 1) * data_size.x + (pos.x - 1)] == 'M' && data[(pos.y + 1) * data_size.x + (pos.x - 1)] == 'M' && data[(pos.y - 1) * data_size.x + (pos.x + 1)] == 'S' && data[(pos.y + 1) * data_size.x + (pos.x + 1)] == 'S') return true;
    if (data[(pos.y - 1) * data_size.x + (pos.x + 1)] == 'M' && data[(pos.y + 1) * data_size.x + (pos.x + 1)] == 'M' && data[(pos.y - 1) * data_size.x + (pos.x - 1)] == 'S' && data[(pos.y + 1) * data_size.x + (pos.x - 1)] == 'S') return true;
    if (data[(pos.y - 1) * data_size.x + (pos.x - 1)] == 'M' && data[(pos.y - 1) * data_size.x + (pos.x + 1)] == 'M' && data[(pos.y + 1) * data_size.x + (pos.x - 1)] == 'S' && data[(pos.y + 1) * data_size.x + (pos.x + 1)] == 'S') return true;
    if (data[(pos.y + 1) * data_size.x + (pos.x - 1)] == 'M' && data[(pos.y + 1) * data_size.x + (pos.x + 1)] == 'M' && data[(pos.y - 1) * data_size.x + (pos.x - 1)] == 'S' && data[(pos.y - 1) * data_size.x + (pos.x + 1)] == 'S') return true;
    return false;
}