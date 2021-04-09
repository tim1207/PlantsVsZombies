#pragma once
namespace game_framework {
	class Selector {
	public:
		Selector();					      // 初始化
		void Load();				      // 讀取資源
		void OnShow();				    // 顯示在畫面上	
		void SetHighLight(bool);	// 讓按鈕亮起來
		void SetXY();				      // 設定每張圖片的座標
		void Shine();				      // 讓按鈕開始閃爍
		void SetBeginState();		  // 設定初始化面的初始狀態
		bool isShineFinished();		// 檢查閃爍是否已經結束
	private:
		bool highlight;				    // 按鈕發亮的狀態
		int shine_counter;			  // 按鈕閃爍的計時器
		bool shine_finished;		  // 儲存閃爍使否已經結束
		CMovingBitmap background;
		CMovingBitmap land;
		CMovingBitmap tree;
		CMovingBitmap leaves;
		CMovingBitmap tomb;
		CMovingBitmap Start;
		CMovingBitmap Start_highlight;
		CMovingBitmap mini_games;
		CMovingBitmap puzzle;
		CMovingBitmap survival;
	};
}