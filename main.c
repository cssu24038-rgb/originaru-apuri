#include <emscripten.h>
#include <string.h>

#define WEEKS 13

// 課題状態の定義
#define STATUS_UNSUBMITTED 0
#define STATUS_SUBMITTED   1
#define STATUS_NONE        2

// 出席状態の定義
#define ATTEND_UNDECIDED 0 // 未定
#define ATTEND_PRESENT   1 // 出席
#define ATTEND_ABSENT    2 // 欠席
#define ATTEND_LATE      3 // 遅刻

// エラーコードの定義
#define ERROR_INVALID_WEEK -1
#define ERROR_INVALID_TEXT -2

// データの保持
int tasks[WEEKS] = {STATUS_UNSUBMITTED};
int attendance[WEEKS] = {ATTEND_UNDECIDED};
char classroom_name[32] = "未設定"; // 教室の場所（初期値）

// --- 課題管理ロジック ---
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

// --- サブ機能1: 出席確認ロジック ---
EMSCRIPTEN_KEEPALIVE
int get_attendance_status(int week_num) {
    if (week_num < 1 || week_num > WEEKS) return ERROR_INVALID_WEEK;
    return attendance[week_num - 1];
}

EMSCRIPTEN_KEEPALIVE
int toggle_attendance(int week_num) {
    if (week_num < 1 || week_num > WEEKS) return ERROR_INVALID_WEEK;
    int idx = week_num - 1;
    // 未定(0) -> 出席(1) -> 欠席(2) -> 遅刻(3) -> 未定(0) のループ
    attendance[idx] = (attendance[idx] + 1) % 4;
    return attendance[idx];
}

// --- サブ機能3: 教室の場所表記（手動入力・入力検証） ---
EMSCRIPTEN_KEEPALIVE
const char* get_classroom() {
    return classroom_name;
}

EMSCRIPTEN_KEEPALIVE
int update_classroom(const char* new_name) {
    // 【入力検証】空欄（ポインタがヌル、または最初の文字が終端文字）のチェック
    if (!new_name || strlen(new_name) == 0) {
        return ERROR_INVALID_TEXT;
    }
    // 【入力検証】文字数オーバー（安全のため配列サイズ32文字未満、実質31文字まで）のチェック
    if (strlen(new_name) >= 32) {
        return ERROR_INVALID_TEXT;
    }

    // 検証を通過したら安全にコピー
    strcpy(classroom_name, new_name);
    return 0; // 成功
}