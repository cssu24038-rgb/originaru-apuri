#include <stdio.h>

#define WEEKS 13

// 状態の定義
#define STATUS_UNSUBMITTED 0 // 未提出
#define STATUS_SUBMITTED   1 // 提出済
#define STATUS_NONE        2 // 課題なし

// 関数のプロトタイプ宣言
void display_status(const int tasks[]);
void clear_input_buffer(void);

int main(void) {
    // 13週分の課題状態を「未提出(0)」で初期化
    int tasks[WEEKS] = {STATUS_UNSUBMITTED};
    int choice = -1;

    printf("=== 課題提出管理アプリ (概要機能版) ===\n");

    while (1) {
        printf("\n--- メニュー ---\n");
        printf("1: 課題状態の一覧表示\n");
        printf("2: 課題状態の変更（トグル）\n");
        printf("0: アプリを終了\n");
        printf("選択してください (0-2): ");

        // 入力検証：数値以外が入力された場合の対策
        if (scanf("%d", &choice) != 1) {
            printf("[エラー] 数値を入力してください。\n");
            clear_input_buffer();
            continue;
        }

        if (choice == 0) {
            printf("アプリを終了します。お疲れ様でした！\n");
            break;
        }

        switch (choice) {
            case 1:
                display_status(tasks);
                break;

            case 2: {
                int week_num = 0;
                printf("変更したい週の番号を入力してください (1-%d): ", WEEKS);
                
                // 入力検証：週番号のチェック
                if (scanf("%d", &week_num) != 1) {
                    printf("[エラー] 有効な数値を入力してください。\n");
                    clear_input_buffer();
                    break;
                }

                // 範囲外のエラーチェック
                if (week_num < 1 || week_num > WEEKS) {
                    printf("[エラー] 1から%dの範囲で入力してください。\n", WEEKS);
                    break;
                }

                // 配列のインデックス用にデクリメント (1〜13 -> 0〜12)
                int idx = week_num - 1;

                // 状態のトグル切り替え (未提出(0) -> 提出済(1) -> 課題なし(2) -> 未提出(0))
                tasks[idx] = (tasks[idx] + 1) % 3;

                printf("%d回目の課題状態を更新しました。\n", week_num);
                break;
            }

            default:
                printf("[エラー] 0から2の間で選択してください。\n");
                break;
        }
    }

    return 0;
}

/**
 * 13週分の課題状態を一覧表示する関数
 */
void display_status(const int tasks[]) {
    printf("\n==== 課題提出状況一覧 ====\n");
    for (int i = 0; i < WEEKS; i++) {
        printf("%2d回目: ", i + 1);
        switch (tasks[i]) {
            case STATUS_UNSUBMITTED:
                printf("[ 未提出 ]\n");
                break;
            case STATUS_SUBMITTED:
                printf("[ 提出済 ]\n");
                break;
            case STATUS_NONE:
                printf("[ 課題なし ]\n");
                break;
            default:
                printf("[ 不明な状態 ]\n");
                break;
        }
    }
    printf("==========================\n");
}

/**
 * 不正入力時に文字バッファをクリアする関数
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}