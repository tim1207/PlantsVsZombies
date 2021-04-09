#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Selector.h"
namespace game_framework {
	Selector::Selector() {			          // 初始化
		highlight = false;
		SetBeginState();
	}
	void Selector::Load() {			          // 準備所需的圖檔
		background.LoadBitmap(".\\RES\\interface\\selector\\SelectorScreen_background.bmp");
		land.LoadBitmap(".\\RES\\interface\\selector\\SelectorScreen_land.bmp",RGB(255, 255, 255));
		leaves.LoadBitmap(".\\RES\\interface\\selector\\SelectorScreen_Leaves.bmp", RGB(255, 255, 255));
		tree.LoadBitmap(".\\RES\\interface\\selector\\SelectorScreen_Tree.bmp", RGB(255, 255, 255));
		tomb.LoadBitmap(".\\RES\\interface\\selector\\SelectorScreen_Tomb.bmp", RGB(255, 255, 255));
		Start.LoadBitmap(".\\RES\\interface\\selector\\SelectorScreen_StartAdventure_Button1.bmp", RGB(255, 255, 255));
		Start_highlight.LoadBitmap(".\\RES\\interface\\selector\\SelectorScreen_StartAdventure_Highlight.bmp", RGB(255, 255, 255));
		mini_games.LoadBitmap(".\\RES\\interface\\selector\\SelectorScreen_MiniGames_button.bmp", RGB(255, 255, 255));
		puzzle.LoadBitmap(".\\RES\\interface\\selector\\SelectorScreen_Puzzle_button.bmp", RGB(255, 255, 255));
		survival.LoadBitmap(".\\RES\\interface\\selector\\SelectorScreen_Survival_button.bmp", RGB(255, 255, 255));
		SetXY();
	}
	void Selector::SetBeginState() {		  // 設定初始狀態
		shine_counter = 0;
		shine_finished = false;
	}
	void Selector::Shine() {				      // 讓按鈕開始閃爍
		shine_counter = 90;
	}
	bool Selector::isShineFinished() {		// 檢查閃爍是否已結束
		return shine_finished;
	}
	void Selector::OnShow() {				      // 顯示畫面
		background.ShowBitmap();
		land.ShowBitmap();
		tomb.ShowBitmap();
		tree.ShowBitmap();
		leaves.ShowBitmap();
		if (shine_counter <= 0) {
			// 當游標碰到按鈕時按鈕會亮起來
			if (highlight == false) {
				Start.ShowBitmap();
			}
			else {
				Start_highlight.ShowBitmap();
			}
		}
		else {
			// 控制按鈕的閃爍
			if (shine_counter % 10 < 5) {
				Start.ShowBitmap();
			}
			else {
				Start_highlight.ShowBitmap();
			}
			shine_counter--;
			if (shine_counter == 0) {
				shine_finished = true;
			}
		}
		mini_games.ShowBitmap();
		puzzle.ShowBitmap();
		survival.ShowBitmap();
	}
	void Selector::SetXY() {					    // 設定每張圖片的XY座標
		background.SetTopLeft(0, 0);
		land.SetTopLeft(0, 165);
		tree.SetTopLeft(0, 0);
		leaves.SetTopLeft(0, 418);
		tomb.SetTopLeft(80, 32);
		Start.SetTopLeft(350, 50);
		Start_highlight.SetTopLeft(350, 50);
		mini_games.SetTopLeft(350, 130);
		puzzle.SetTopLeft(353, 198);
		survival.SetTopLeft(350, 250);
	}
	void Selector::SetHighLight(bool a) {	// 讓按鈕亮起來
		highlight = a;
	}
}