#include <math.h>

#include <raylib.h>
#include <stdlib.h>

#include "keys.h"

#define TITLE "rkey"

#define WIDTH GetScreenWidth()
#define HEIGHT GetScreenHeight()

#define FONT_SIZE 24

#define COLOR_BACKGROUND (Color) { 20, 20, 20, 255 }

#define LP_BUFFER 1
#define LPS_BUFFER 10

#define TEXT_LENGTH 27

#define KEYS_ALL 0

#define and &&
#define not !
#define or ||

bool has(int* list, int count, int value)
{
    for (int i = 0; i < count; i++) {
        if (list[i] == value) {
            return true;
        }
    }
    return false;
}

void text_reset(int mode, char* text)
{
    if (mode == KEYS_ALL) {
        for (int i = 0; i < TEXT_LENGTH; i++) {
            text[i] = 65 + i;
        }
        for (int i = 0; i < 10; i++) {
            int r1 = GetRandomValue(0, TEXT_LENGTH - 2);
            int r2 = GetRandomValue(0, TEXT_LENGTH - 2);
            char temp = text[r1];
            text[r1] = text[r2];
            text[r2] = temp;
        }
    } else {
        int count = 0;
        for (int i = 0; i < 10; i++) {
            char key = pos_keys[mode][i];
            if (key == 0) {
                break;
            }
            count++;
        }
        for (int i = 0; i < TEXT_LENGTH; i++) {
            int r1 = GetRandomValue(0, count - 1);
            text[i] = pos_keys[mode][r1];
        }
    }
    text[TEXT_LENGTH - 1] = 0;
}

int main(int argc, char** argv)
{
    int text_mode = KEYS_ALL;
    if (argc == 2) {
        int selected_mode = atoi(argv[1]);
        if (has(keys_pos, KP_COUNT, selected_mode)) {
            text_mode = selected_mode;
        }
    }

    SetRandomSeed(0);

    InitAudioDevice();
    Sound sound_hit = LoadSound("assets/hit-sound.mp3");
    Sound sound_miss = LoadSound("assets/miss-sound.mp3");
    SetSoundVolume(sound_hit, 1.0);
    SetSoundVolume(sound_miss, 0.5);

    SetTargetFPS(48);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1000, 450, TITLE);

    Vector2 margin_kb = { 0 };

    Vector2 size_key = { 50, 50 };
    int kb_skew = 20;
    int padding_key = 10;

    double row_count = 14;

    int key_last_pressed[LP_BUFFER] = { 0 };
    int key_last_pressed_pos = 0;

    char key_last_pressed_str[LPS_BUFFER + 2] = { 0 };
    int key_last_pressed_str_pos = 0;

    char text[TEXT_LENGTH] = { 0 };
    text_reset(text_mode, text);
    text[TEXT_LENGTH - 1] = 0;

    int current_key_to_press_pos = 0;

    double time_combo_start = 0.0;
    int combo = 0;

    while (not WindowShouldClose()) {

        {
            int keyboard_width = row_count * (size_key.x + padding_key) + kb_skew * 2;
            margin_kb.x = (WIDTH - keyboard_width) / 2.0;

            margin_kb.y = HEIGHT - (5 * (size_key.y + padding_key));
        }

        BeginDrawing();

        ClearBackground(IsSoundReady(sound_miss) and IsSoundReady(sound_hit) ? COLOR_BACKGROUND : GRAY);

        int row = 0;
        int row_key_count = 0;
        int row_key_width = 0;
        int bonus_size = 0;

        char current_key_to_press = text[current_key_to_press_pos];

        Vector2 start, end;

        for (int i = 0; i < KEY_COUNT; i++) {
            int current_row = floor(i / row_count);

            if (current_row == 3 and row_key_count == 12) {
                current_row += 1;
            }

            if (current_row < row) {
                current_row = row;
            }

            if (current_row > row) {
                row = current_row;
                row_key_count = 0;
                row_key_width = 0;
            }

            double x = margin_kb.x + row_key_width + (current_row * kb_skew);
            double y = margin_kb.y + (current_row * (size_key.y + padding_key));

            row_key_count += 1;

            int key = keys[i];

            if (key == KEY_RIGHT_SHIFT) {
                bonus_size = size_key.x * 2;
            } else if (key == KEY_BACKSPACE) {
                bonus_size = size_key.x * .8;
            } else if (key == KEY_SPACE) {
                bonus_size = size_key.x * 5;
            } else {
                bonus_size = 0;
            }

            int width = size_key.x + bonus_size;
            row_key_width += width + padding_key;

            if (IsKeyPressed(key)) {

                if (key == current_key_to_press) {

                    current_key_to_press_pos += 1;

                    if (current_key_to_press_pos == TEXT_LENGTH - 1) {
                        text_reset(text_mode, text);
                    }

                    current_key_to_press_pos %= TEXT_LENGTH - 1;

                    if (combo == 0) {
                        time_combo_start = GetTime();
                    }
                    combo += 1;

                    if (IsSoundReady(sound_hit)) {
                        PlaySound(sound_hit);
                    }

                } else {
                    if (combo > 10 and IsSoundReady(sound_miss)) {
                        PlaySound(sound_miss);
                    }
                    combo = 0;
                }

                key_last_pressed[key_last_pressed_pos] = key;
                key_last_pressed_pos += 1;
                key_last_pressed_pos %= LP_BUFFER;

                key_last_pressed_str[key_last_pressed_str_pos] = key;
                key_last_pressed_str_pos += 1;
                key_last_pressed_str_pos %= LPS_BUFFER;
            }

            if (IsKeyDown(key)) {

                DrawRectangle(x, y, width, size_key.y, GREEN);

            } else {

                if (has(key_last_pressed, LP_BUFFER, key)) {
                    DrawRectangle(x, y, width, size_key.y, BLUE);
                }

                else if (key == KEY_F or key == KEY_J) {
                    DrawRectangle(x, y, width, size_key.y, ORANGE);
                }

                else if (has(keys_pos, KP_COUNT, key)) {
                    DrawRectangle(x, y, width, size_key.y, BROWN);
                }

                else {
                    DrawRectangle(x, y, width, size_key.y, DARKGRAY);
                }
            }

            DrawText((const char*)&key, x + 5, y + 5, FONT_SIZE, WHITE);

            if (has(keys_pos, KP_COUNT, key) and has(pos_keys[key], 10, current_key_to_press)) {
                start = (Vector2) { x + size_key.x / 2.0, y + size_key.y / 2.0 };
            }

            if (key == current_key_to_press) {
                end = (Vector2) { x + size_key.x / 2.0, y + size_key.y / 2.0 };
            }
        }

        // DrawCircle(start.x, start.y, 8, ORANGE);
        DrawCircle(end.x, end.y, 8, RED);
        DrawLineEx(start, end, 4, RED);

        Rectangle bound = { 10, 10, WIDTH - 20, margin_kb.y - 20 };

        DrawRectangleRec(bound, DARKGRAY);

        const char* buf = TextFormat("%.*s%.*s", LPS_BUFFER - key_last_pressed_str_pos, key_last_pressed_str_pos + key_last_pressed_str, key_last_pressed_str_pos, key_last_pressed_str);
        const char* combo_str = TextFormat("Combo: %dx | CPS: %.2lf", combo, (combo / (GetTime() - time_combo_start)));
        int buf_w = MeasureText(buf, FONT_SIZE);
        int text_w = MeasureText((const char*)&current_key_to_press, FONT_SIZE);
        int combo_w = MeasureText(combo_str, FONT_SIZE);

        int buf_bound_w = FONT_SIZE * 20;
        DrawRectangleRec((Rectangle) { (bound.width + bound.x - buf_bound_w) / 2.0, bound.y + bound.height - FONT_SIZE - 10, buf_bound_w, FONT_SIZE + 10 }, COLOR_BACKGROUND);
        DrawRectangleRec((Rectangle) { (bound.width + bound.x - buf_bound_w) / 2.0, bound.y, buf_bound_w, FONT_SIZE + 10 }, combo > 10 ? DARKGREEN : COLOR_BACKGROUND);

        DrawText(
            combo_str,
            (bound.width + bound.x - combo_w) / 2.0, bound.y + 5, FONT_SIZE, WHITE);

        DrawText(buf, ((bound.width + bound.x) - buf_w) / 2.0, bound.y + bound.height - FONT_SIZE, FONT_SIZE, WHITE);

        DrawText(
            TextFormat("%s", text + current_key_to_press_pos),
            (bound.width + bound.x - text_w) / 2.0, bound.y + (bound.height - FONT_SIZE) / 2.0, FONT_SIZE, WHITE);

        DrawRectangleRec((Rectangle) { 0, bound.y, bound.x + (bound.width - buf_bound_w) / 2.0, bound.height }, COLOR_BACKGROUND);
        DrawRectangleRec((Rectangle) { (bound.width - buf_bound_w) / 2.0 + buf_bound_w, bound.y, bound.x + (bound.width - buf_bound_w) / 2.0, bound.height }, COLOR_BACKGROUND);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
