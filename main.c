#include <emscripten.h>

#define WEEKS 13

// 状態の定義
#define STATUS_UNSUBMITTED 0 // 未提出
#define STATUS_SUBMITTED   1 // 提出済
#define STATUS_NONE        2 // 課題なし
#define ERROR_INVALID_WEEK -1 // エラー：無効な週番号

// 13週分の課題状態を保持する配列（初期値はすべて未提出）
int tasks[WEEKS] = {STATUS_UNSUBMITTED};

/**
 * 指定された週の課題状態を取得する関数
 * 入力検証を含み、範囲外ならエラーコードを返す
 */
EMSCRIPTEN_KEEPALIVE
int get_task_status(int week_num) {
    // ユーザ入力（週番号）の検証
    if (week_num < 1 || week_num > WEEKS) {
        return ERROR_INVALID_WEEK; 
    }
    return tasks[week_num - 1];
}

/**
 * 指定された週の課題状態をトグル（切り替え）する関数
 * 未提出(0) -> 提出済(1) -> 課題なし(2) -> 未提出(0)
 */
EMSCRIPTEN_KEEPALIVE
int toggle_task(int week_num) {
    // ユーザ入力（週番号）の検証
    if (week_num < 1 || week_num > WEEKS) {
        return ERROR_INVALID_WEEK; 
    }
    
    int idx = week_num - 1;
    tasks[idx] = (tasks[idx] + 1) % 3;
    
    return tasks[idx]; // 更新後の状態を返す
}