#include <emscripten.h>
#include <string.h>

#define WEEKS 13

// 状態・エラーの定義
#define STATUS_UNSUBMITTED 0
#define STATUS_SUBMITTED   1
#define STATUS_NONE        2

#define ATTEND_UNDECIDED 0
#define ATTEND_PRESENT   1
#define ATTEND_ABSENT    2
#define ATTEND_LATE      3

#define ERROR_INVALID_WEEK -1
#define ERROR_INVALID_TEXT -2
#define ERROR_INVALID_DATE -3

// データの保持
int tasks[WEEKS] = {STATUS_UNSUBMITTED};
int attendance[WEEKS] = {ATTEND_UNDECIDED};
char classroom_name[32] = "未設定";

int base_year = 0;
int base_month = 0;
int base_day = 0;

// --- 既存のロジック ---
EMSCRIPTEN_KEEPALIVE
int get_task_status(int week_num) {
    if (week_num < 1 || week_num > WEEKS) return ERROR_INVALID_WEEK; 
    return tasks[week_num - 1];
}

EMSCRIPTEN_KEEPALIVE
int toggle_task(int week_num) {
    if (week_num < 1 || week_num > WEEKS) return ERROR_INVALID_WEEK; 
    int idx = week_num - 1;
    tasks[idx] = (tasks[idx] + 1) % 3;
    return tasks[idx];
}

EMSCRIPTEN_KEEPALIVE
int get_attendance_status(int week_num) {
    if (week_num < 1 || week_num > WEEKS) return ERROR_INVALID_WEEK;
    return attendance[week_num - 1];
}

EMSCRIPTEN_KEEPALIVE
int toggle_attendance(int week_num) {
    if (week_num < 1 || week_num > WEEKS) return ERROR_INVALID_WEEK;
    int idx = week_num - 1;
    attendance[idx] = (attendance[idx] + 1) % 4;
    return attendance[idx];
}

EMSCRIPTEN_KEEPALIVE
const char* get_classroom() {
    return classroom_name;
}

EMSCRIPTEN_KEEPALIVE
int update_classroom(const char* new_name) {
    if (!new_name || strlen(new_name) == 0 || strlen(new_name) >= 32) {
        return ERROR_INVALID_TEXT;
    }
    strcpy(classroom_name, new_name);
    return 0;
}

EMSCRIPTEN_KEEPALIVE
int set_base_date(int year, int month, int day) {
    if (year < 2000 || year > 2100 || month < 1 || month > 12 || day < 1 || day > 31) return ERROR_INVALID_DATE;
    base_year = year;
    base_month = month;
    base_day = day;
    return 0;
}

EMSCRIPTEN_KEEPALIVE
int get_base_year() { return base_year; }

EMSCRIPTEN_KEEPALIVE
int get_base_month() { return base_month; }

EMSCRIPTEN_KEEPALIVE
int get_base_day() { return base_day; }


// --- ★新機能：保存データ復元用ロジック ---
EMSCRIPTEN_KEEPALIVE
int set_task_status(int week_num, int status) {
    if (week_num < 1 || week_num > WEEKS) return ERROR_INVALID_WEEK;
    tasks[week_num - 1] = status;
    return 0;
}

EMSCRIPTEN_KEEPALIVE
int set_attendance_status(int week_num, int status) {
    if (week_num < 1 || week_num > WEEKS) return ERROR_INVALID_WEEK;
    attendance[week_num - 1] = status;
    return 0;
}