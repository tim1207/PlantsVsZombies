#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
namespace game_framework {
bool YouWin = false;
CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}
//讀取音效檔
void CGameStateInit::LoadAudio() {
	CAudio::Instance()->Load(AUDIO_MENU, ".\\Sounds\\ZombiesOnYourLawn.wav");
	CAudio::Instance()->Load(AUDIO_EVIL_LAUGH, ".\\Sounds\\evillaugh.wav");
}
void CGameStateInit::OnInit()
{
	ShowInitProgress(0);
	menu.Load();
	conditionA = false;
	conditionB = false;
	LoadAudio();
	help.LoadBitmapA(".\\RES\\interface\\help.bmp", RGB(255, 255, 255));
}
void CGameStateInit::OnBeginState()
{
	menu.SetBeginState();                                     //設定選單的初始狀態
	play_Audio = false;
}
void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	if (nChar == KEY_ESC)								                      // Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	    // 關閉遊戲
}
void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 處理滑鼠和選單的互動
	bool conditionA1 = (point.y - 125 <= 35 * (point.x - 350) / 250);
	bool conditionA2 = (point.y - 68 >= -57 * (point.x - 351));
	bool conditionA3 = (point.y - 68 >= 17 * (point.x - 351) / 261);
	bool conditionA4 = (point.y - 160 <= -75 * (point.x - 600) / 12);
	bool conditionB1 = (point.y - 70 >= -20 * (point.x - 400) / 25);
	bool conditionB2 = (point.y >= 50);
	bool conditionB3 = (point.y - 50 >= 31 * (point.x - 520) / 26);
	bool conditionB4 = (point.y - 70 <= 11 * (point.x - 400) / 146);
	conditionA = (conditionA1 && conditionA2 && conditionA3 && conditionA4);
	conditionB = (conditionB1 && conditionB2 && conditionB3 && conditionB4);
	menu.SetHighLight(conditionA || conditionB);
}
//處理點選選單的動作
void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (conditionA || conditionB) {
		menu.Shine();
		CAudio::Instance()->Stop(AUDIO_MENU);
		CAudio::Instance()->Play(AUDIO_EVIL_LAUGH, false);
	}
}
void CGameStateInit::OnShow()
{
	// 撥放音樂
	if (play_Audio == false) {
		play_Audio = true;
		CAudio::Instance()->Play(AUDIO_MENU, true);
	}
	if (menu.isShineFinished() == true) {
		GotoGameState(GAME_STATE_RUN);		              // 切換至GAME_STATE_RUN
	}
	menu.OnShow();
	help.SetTopLeft(0, 0);
	help.ShowBitmap();
	CDC *pDC = CDDraw::GetBackCDC();			            // 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(120,"Times New Roman");	        // 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					                // 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(0, 414, "Press Alt-F4 or ESC to Quit.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(0,436,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(0,458,"Press Ctrl-F to switch in between window mode and full screen mode.");
	pDC->SelectObject(fp);						                // 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					                // 放掉 Back Plain 的 CDC
}								
CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}
 //讀取結果的圖檔
void CGameStateOver::LoadBitmap() {
	ZombiesWon.LoadBitmap(".\\RES\\interface\\ZombiesWon.bmp");
	ZombiesWon.SetTopLeft(38, 6);
	ZombieNote.LoadBitmap(".\\RES\\interface\\ZombieNote.bmp");
	ZombieNote.SetTopLeft(0, 0);
}
void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}
void CGameStateOver::OnBeginState()
{
	counter = 30 * 5;                                 // 5 seconds
	if (YouWin == false) {
		CAudio::Instance()->Play(AUDIO_LOSE_MUSIC, false);
	}
	else {
		CAudio::Instance()->Play(AUDIO_WIN_MUSIC, false);
	}
}
//讀取結束的音樂
void CGameStateOver::LoadAudio() {
	CAudio::Instance()->Load(AUDIO_LOSE_MUSIC, ".\\Sounds\\losemusic.wav");
	CAudio::Instance()->Load(AUDIO_WIN_MUSIC, ".\\Sounds\\winmusic.wav");
}
void CGameStateOver::OnInit()
{
	LoadAudio();

	ShowInitProgress(66);	                            // 接個前一個狀態的進度，此處進度視為66%
	LoadBitmap();
	ShowInitProgress(100);
}
void CGameStateOver::OnShow()
{
	if (YouWin == false) {
		ZombiesWon.ShowBitmap();
	}
	else {
		ZombieNote.ShowBitmap(1.2);
	}
}
CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g)
{
	srand((unsigned)time(NULL));
}
CGameStateRun::~CGameStateRun()
{
}
void CGameStateRun::OnBeginState()                  //設定遊戲的初始狀態
{

	awooga = false;                                   //awooga是第一批殭屍出現時會撥放的音效
	CAudio::Instance()->Play(AUDIO_MAIN_MUSIC, true); //撥放遊戲背景音樂
	//設定和滑鼠相關的變數
	selected = false;
	ChoosedCard = -1;
	ChoosedPlant = -1;
	isGameOver = false;
	SunCounter = 0;                                   //從空中掉落太陽的計時器
	ZombieCounter = 0;                                //產生僵屍的計時器
	//重設場上的植物
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			PlantManager[i][j] = 0;
		}
	}
	//確保所有的vector清空
	zombies.clear();
	plants.clear();
	peas.clear();
	suns.clear();
	seed.Reset();
	//重設除草機
	for (int i = 0; i < 5; i++) {
		LawnMower[i].Reset();
	}
	wave = 0;
}
//進入GameStateOver，並將vector清空，否則第二次完會產生錯誤
void CGameStateRun::GameOver() {
	zombies.swap(vector<Zombies>());
	plants.swap(vector<Plants>());
	suns.swap(vector<Sun>());
	peas.swap(vector<Pea>());
	CAudio::Instance()->Stop(AUDIO_MAIN_MUSIC);
	GotoGameState(GAME_STATE_OVER);
}
void CGameStateRun::OnMove()							        // 移動遊戲元素
{
	//每隔7秒從空中產生一個太陽
	SunCounter++;
	if (SunCounter == 210) {
		SunCounter = 0;
		suns.push_back(Sun(rand() % 400 + 100, rand() % 300 + 100,false));
	}
	if (wave < 9) {
		///每隔10秒產生1~3隻隨機種類的殭屍
		if (ZombieCounter == 450) {
			wave++;
			if (awooga == false) {
				CAudio::Instance()->Play(AUDIO_AWOOGA, false);
				awooga = true;
			}
			ZombieCounter = 0;
			int groan = rand() % 6;
			CAudio::Instance()->Play(AUDIO_GROAN_1 + groan, false);
			for (int i = 0; i <= (wave - 1) / 3; i++) {
				int id = i + 1;
				int r = (rand() % 5);
				zombies.push_back(Zombies(id,r,590 + i * 10));
			}
		}
	}
	else if (wave == 9 && ZombieCounter >= 450) {
		if (ZombieCounter == 450) {
			CAudio::Instance()->Play(AUDIO_FINALWAVE, false);
		}
		if (ZombieCounter >= 450 && ZombieCounter<=470) {
			if ((ZombieCounter - 450) % 10 == 0) {
				for (int i = 0; i < 5; i++) {
					int id = (rand() % 3) + 1;
					zombies.push_back(Zombies(id, i, 590));
				}
			}
		}
	}
	ZombieCounter++;
	if (zombies.size() == 0 && ZombieCounter > 450) {
		YouWin = true;
		isGameOver = true;
	}
	//處理所有殭屍的動作
	for (vector<Zombies>::iterator itz = zombies.begin(); itz != zombies.end(); itz++) {
		itz->OnMove();
		if (itz->GetX() < -150) {
			YouWin = false;
			isGameOver = true;                                         //如果殭屍跑進家裡，遊戲結束
		}
		//尋找殭屍可攻擊的第一隻植物
		int closest = 10;
		for (int i = (itz->GetX()+80)/75; i >= 0; i--) {
			if (PlantManager[itz->GetRow()][i] > 0) {
				closest = i;
				break;
			}
		}
		if (itz->isAlive() == true) {
			//如果殭屍被除草機撞到就馬上死亡
			if (LawnMower[itz->GetRow()].GetX() > itz->GetX() + 30 && LawnMower[itz->GetRow()].GetX() < itz->GetX() + 100) {
				LawnMower[itz->GetRow()].StartMove();
				CAudio::Instance()->Play(AUDIO_LAWN_MOWER, false);
				itz->GoToDie();
			}
			bool found = false;
			for (vector<Plants>::iterator itp = plants.begin(); itp != plants.end(); itp++) {
				if (itp->GetRow() == itz->GetRow() && itp->GetColumn() == closest) {
					if (itp->GetX() <= itz->GetX() + 80 && itp->GetX() >= itz->GetX() + 30) {
						itz->SetStatus(2);                                   //如果離殭屍最近的植物進入攻擊範圍就進入攻擊狀態
						found = true;
					}
					else {
						itz->SetStatus(1);
					}
					//如果殭屍正在攻擊狀態且攻擊冷卻時間結束，植物就受到攻擊
					if (itz->GetStatus() == 2 && itz->Attack() == true) {
						int chomp = rand() % 3;
						CAudio::Instance()->Play(AUDIO_CHOMP_1 + chomp, false);
						itp->BeingAttacked();
						if (itp->isAlive() == false) {
							itz->SetStatus(1);                                 //如果植物被殭屍吃掉了，殭屍馬上恢復普通狀態
						}
					}
				}
			}
			if (found == false) {
				itz->SetStatus(1);
			}
		}
	}
	//處理所有植物的動作
	vector<Plants>::iterator itpp;
	bool ErasePlant = false;
	for (vector<Plants>::iterator itp = plants.begin(); itp != plants.end(); itp++) {
		if (itp->isAlive() == false) {                               //如果植物的生命為零，設定植物的死亡
			itpp = itp;
			ErasePlant = true;
			PlantManager[itp->GetRow()][itp->GetColumn()] = 0;
			continue;
		}
		itp->OnMove();
		//處理向日葵的動作
		if (itp->GetID() == 1) {
			itp->SetCounterOn(true);
			if (itp->isAction() == true) {                             //時間到了就產生一個太陽
				suns.push_back(Sun(itp->GetX(), itp->GetY(), true));
			}
			continue;
		}
		//處理一般豌豆的動作
		if (itp->GetID() == 2) {
			bool FoundZombie = false;
			for (vector<Zombies>::iterator itz = zombies.begin(); itz != zombies.end(); itz++) {
				if (itz->GetRow() == itp->GetRow() && itz->GetX() + 50 >= itp->GetX()) {
					FoundZombie = true;
					if (itz->GetX() + 50 > itp->GetX()) {
						itp->SetCounterOn(true);                             //如果找到可攻擊的殭屍就進入攻擊狀態
					}
					else {
						itp->SetCounterOn(false);
					}
				}
			}
			if (itp->isAction() == true) {
				CAudio::Instance()->Play(AUDIO_SHOOT, false);
				peas.push_back(Pea(itp->GetX() + 50, itp->GetRow(), 0)); //如果攻擊冷卻時間到了就射出一顆豆子
			}
			if (FoundZombie == false) {
				itp->SetCounterOn(false);
			}
		}
		//處理葫蘆的動作
		if (itp->GetID() == 4) {

			if (itp->isCounterOn() == false) {
				for (vector<Zombies>::iterator itz = zombies.begin(); itz != zombies.end(); itz++) {
					if (itz->GetRow() == itp->GetRow() && itz->GetX() < itp->GetX() + 40 && itz->GetX() > itp->GetX() - 200) {
						itp->SetCounterOn(true);                             //如果有殭屍進入攻擊範圍，進入攻擊狀態
					}
				}
			}
			else if(itp->isAction() == true) {
				bool FoundZombie = false;
				vector<Zombies>::iterator itzz;
				for (vector<Zombies>::iterator itz = zombies.begin(); itz != zombies.end(); itz++) {
					if (itz->GetRow() == itp->GetRow() && itz->GetX() < itp->GetX() + 40 && itz->GetX() > itp->GetX() - 250) {
						if (itp->isFinished() == true) {
							itz->GoToDie();                                    //如果葫蘆的攻擊動畫結束，在葫蘆下面的殭屍立刻死亡
						}
						FoundZombie = true;
						itzz = itz;
					}
				}
				// 設定葫蘆移動的方向和位置
				if (itp->WhichAction() == 1 && FoundZombie == true) {
					if (itzz->GetX() - itp->GetX() + 60 > 0) {
						itp->SetTargetX(itzz->GetX() + 80);
					}
					else {
						itp->SetTargetX(itzz->GetX());
					}
				}
			}
		}
		//處理櫻桃的動作
		if (itp->GetID() == 5) {
			if (itp->WhichAction() == 2) {
				CAudio::Instance()->Play(AUDIO_CHERRY_BOMB, false);
				for (vector<Zombies>::iterator itz = zombies.begin(); itz != zombies.end(); itz++) {
					if (abs(itz->GetRow() - itp->GetRow()) <= 1 && itz->GetX() + 50 < itp->GetX() + 100 && itz->GetX() + 50 > itp->GetX() - 100) {
						itz->BoomToDie();                                    //如果殭屍在櫻桃的爆炸範圍內就會瞬間被炸死
					}
				}
			}
		}
		//處理冷凍豌豆的動作
		if (itp->GetID() == 6) {
			bool FoundZombie = false;
			for (vector<Zombies>::iterator itz = zombies.begin(); itz != zombies.end(); itz++) {
				if (itz->GetRow() == itp->GetRow() && itz->GetX() + 50 >= itp->GetX()) {
					FoundZombie = true;
					if (itz->GetX() + 50 > itp->GetX()) {
						itp->SetCounterOn(true);                             //如果有殭屍在攻擊範圍內就進入攻擊模式
					}
					else {
						itp->SetCounterOn(false);
					}
				}
			}
			if (itp->isAction() == true) {
				CAudio::Instance()->Play(AUDIO_SHOOT, false);
				peas.push_back(Pea(itp->GetX() + 50, itp->GetRow(), 1)); //如果攻擊冷卻時間到了就射出一顆豆子
			}
			if (FoundZombie == false) {
				itp->SetCounterOn(false);
			}
		}
		//處理連射豌豆的動作
		if (itp->GetID() == 7) {
			bool FoundZombie = false;
			for (vector<Zombies>::iterator itz = zombies.begin(); itz != zombies.end(); itz++) {
				if (itz->GetRow() == itp->GetRow() && itz->GetX() + 50 >= itp->GetX()) {
					FoundZombie = true;
					if (itz->GetX() + 50 > itp->GetX()) {
						itp->SetCounterOn(true);                             //如果有殭屍在攻擊範圍內就進入攻擊模式
					}
					else {
						itp->SetCounterOn(false);
					}
				}
			}
			if (itp->isAction() == true) {
				CAudio::Instance()->Play(AUDIO_SHOOT, false);
				peas.push_back(Pea(itp->GetX() + 50, itp->GetRow(), 0)); //如果攻擊冷卻時間到了就射出一顆豆子
			}
			if (FoundZombie == false) {
				itp->SetCounterOn(false);
			}
		}
	}	
	if (ErasePlant == true) {
		plants.erase(itpp);                                          //從vector裡刪掉死亡的殭屍
		ErasePlant = false;
	}
	//處理所有豆子的動作
	for (vector<Pea>::iterator itpea = peas.begin(); itpea != peas.end(); itpea++) {
		itpea->OnMove();
		//檢查豆子是否有擊中殭屍
		vector<Zombies>::iterator itzz;
		bool HitZombie = false;
		int mi = 1000;
		for (vector<Zombies>::iterator itz = zombies.begin(); itz != zombies.end(); itz++) {
			if (itpea->GetRow() == itz->GetRow() && itpea->GetX() > itz->GetX() + 75 && itpea->GetX() < itz->GetX() + 110) {
				if (mi > itz->GetX()) {
					mi = itz->GetX();
					itzz = itz;
					HitZombie = true;
				}
			}
			if (itpea->GetX() > 640) {
				itpea->SetHitZombie(true);
			}
		}
		//處理擊中殭屍後的動作
		if (HitZombie == true) {
			itpea->SetHitZombie(true);
			if (itzz->GetID() == 3 && itzz->GetLife() > 10) {
				int sound = rand() % 2;
				CAudio::Instance()->Play(AUDIO_HIT_BUCKET_1 + sound, false);
			}
			else {
				int sound = rand() % 3;
				CAudio::Instance()->Play(AUDIO_SPLAT_1 + sound, false);
			}
			itzz->Hitted(itpea->MyType());
		}
	}
	vector<Sun>::iterator itss;
	bool EraseSun = false;
	//處理所有太陽的動作
	for (vector<Sun>::iterator its = suns.begin(); its != suns.end(); its++) {
		if (its == suns.begin()) {
			its->MoveAnime();
		}
		its->OnMove();
		if (its->isFinished()) {
			itss = its;
			EraseSun = true;
		}
	}
	if (EraseSun == true) {
		suns.erase(itss);
		EraseSun = false;
	}
	seed.OnMove();
	//處理所有除草機的動作
	for (int i = 0; i < 5; i++) {
		LawnMower[i].OnMove();
	}
}

  //讀取所需的音效檔
void CGameStateRun::LoadAudio() {
	CAudio::Instance()->Load(AUDIO_MAIN_MUSIC, ".\\Sounds\\mainmusic.wav");
	CAudio::Instance()->Load(AUDIO_AWOOGA, ".\\Sounds\\awooga.wav");
	for (int i = 1; i <= 6; i++) {
		char FILENAME[100];
		sprintf(FILENAME, ".\\Sounds\\groan%d.wav", i);
		CAudio::Instance()->Load(AUDIO_GROAN_1 + i - 1, FILENAME);
	}
	for (int i = 1; i <= 3; i++) {
		char FILENAME[100];
		sprintf(FILENAME, ".\\Sounds\\chomp%d.wav", i);
		CAudio::Instance()->Load(AUDIO_CHOMP_1 + i - 1, FILENAME);
	}
	CAudio::Instance()->Load(AUDIO_CHERRY_BOMB, ".\\Sounds\\cherrybomb.wav");
	CAudio::Instance()->Load(AUDIO_LAWN_MOWER, ".\\Sounds\\lawnmower.wav");
	CAudio::Instance()->Load(AUDIO_PLANT, ".\\Sounds\\plant.wav");
	CAudio::Instance()->Load(AUDIO_COLLECT_SUN, ".\\Sounds\\points.wav");
	CAudio::Instance()->Load(AUDIO_CHOOSE_CARD, ".\\Sounds\\seedlift.wav");
	CAudio::Instance()->Load(AUDIO_HIT_BUCKET_1, ".\\Sounds\\shieldhit1.wav");
	CAudio::Instance()->Load(AUDIO_HIT_BUCKET_2, ".\\Sounds\\shieldhit2.wav");
	CAudio::Instance()->Load(AUDIO_SHOVEL, ".\\Sounds\\shovel.wav");
	CAudio::Instance()->Load(AUDIO_SPLAT_1, ".\\Sounds\\splat.wav");
	CAudio::Instance()->Load(AUDIO_SPLAT_2, ".\\Sounds\\splat2.wav");
	CAudio::Instance()->Load(AUDIO_SPLAT_3, ".\\Sounds\\splat3.wav");
	CAudio::Instance()->Load(AUDIO_SHOOT, ".\\Sounds\\puff.wav");
	CAudio::Instance()->Load(AUDIO_FINALWAVE, ".\\Sounds\\finalwave.wav");
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//讀取所需的音效檔
	ShowInitProgress(33);	                                         // 接個前一個狀態的進度，此處進度視為33%
	LoadAudio();
	ShowInitProgress(50);
	int temp[] = { 1,2,3,4,5,6,7 };
	map.LoadBitmap();
	seed.Load(7,temp);
	cursor.LoadBitmap();
	shovel.LoadBitmap();
	for (int i = 0; i < 5; i++) {
		LawnMower[i].SetY(i);
		LawnMower[i].LoadBitmap();
	}
	FinalWave.LoadBitmap(".\\RES\\interface\\FinalWave.bmp", RGB(0, 0, 255));
	Wave.LoadBitmap(".\\RES\\interface\\wave.bmp", RGB(255, 255, 255));
	for (int i = 0; i < 10; i++) {
		char FILENAME[100];
		sprintf(FILENAME, ".\\RES\\interface\\%d.bmp", i);
		numbers[i].LoadBitmap(FILENAME, RGB(255, 255, 255));
	}
	slash.LoadBitmap(".\\RES\\interface\\slash.bmp", RGB(255, 255, 255));
}
//這裡有遊戲的密技功能
void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭

	if (nChar == KEY_UP) {
		for (vector<Zombies>::iterator itz = zombies.begin(); itz != zombies.end(); itz++) {
			itz->GoToDie();
		}
	}
	else if (nChar == KEY_DOWN) {
		for (int i = 0; i < 40; i++) {
			seed.GotSun();
		}
	}
	else if (nChar == KEY_LEFT) {
		seed.ResetCD();
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if (!selected) {
		//處理點擊太陽的動作
		bool GotSun = false;
		for (vector<Sun>::iterator its = suns.begin(); its != suns.end(); its++) {
			if (point.x >= its->GetX() && point.x <= its->GetX() + its->GetWidth() && point.y >= its->GetY() && point.y <= its->GetY() + its->GetHeight()) {
				its->PickUp();
				CAudio::Instance()->Play(AUDIO_COLLECT_SUN, false);
				seed.GotSun();
				GotSun = true;
				break;
			}
		}
		//處理選擇卡片的動作
		if (point.x >= 77 && point.x <= 427 && point.y >= 8 && point.y <= 78 && GotSun == false) {
			ChoosedCard = (point.x - 77) / 50;
			ChoosedPlant = seed.GetCardID(ChoosedCard);
			if (seed.isCardAvailible(ChoosedCard)) {
				CAudio::Instance()->Play(AUDIO_CHOOSE_CARD, false);
				cursor.SetWhich(ChoosedPlant); //讓游標的樣子變成準備種植的植物
				selected = true;
			}
		}
		//處理點擊產子的動作
		if (point.x >= 462 && point.x <= 538 && point.y >= 10 && point.y <= 44 && GotSun == false) {
			if (shovel.isChoosed() == false) {
				CAudio::Instance()->Play(AUDIO_SHOVEL, false);
				shovel.SetChoosed(true);
				selected = true;
				cursor.SetWhich(8); //讓游標的樣子變成鏟子
			}
		}
	}
	else if (selected) {
		if (point.x >= 46 && point.x <= 640 && point.y >= 75 && point.y <= 450) {
			//實現用鏟子移除植物的功能
			if (shovel.isChoosed() == true) {
				PlantManager[(point.y - 75) / 75][(point.x - 46) / 66] = 0;
				bool ErasePlant = false;
				vector<Plants>::iterator itpp;
				for (vector<Plants>::iterator itp = plants.begin(); itp != plants.end(); itp++) {
					if (itp->GetRow() == (point.y - 75) / 75 && itp->GetColumn() == (point.x - 46) / 66) {
						itpp = itp;
						ErasePlant = true;
					}
				}
				if (ErasePlant == true) {
					plants.erase(itpp);
				}
			}
			//處理種植植物的動作
			else if(shovel.isChoosed() == false) {
				if (PlantManager[(point.y - 75) / 75][(point.x - 46) / 66] == 0) {
					PlantManager[(point.y - 75) / 75][(point.x - 46) / 66] = ChoosedPlant;
					plants.push_back(Plants(ChoosedPlant, (point.x - 46) / 66, (point.y - 75) / 75));
					CAudio::Instance()->Play(AUDIO_PLANT, false);
					seed.ResetCardCounter(ChoosedCard);
					seed.Buy(ChoosedCard);
				}
			}
		}
		cursor.SetWhich(0);
		selected = false;
		ChoosedCard = -1;
		shovel.SetChoosed(false);
	}
}
void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}
void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	if (selected) {
		cursor.SetXY(point.x, point.y);
	}
}
void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}
void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作，加速遊戲死亡用
{
	for (int i = 0; i < 5; i++) {
		zombies.push_back(Zombies(1, i, 590));
		for (int j = 0; j < 10; j++) {
			zombies.back().Faster();
		}
	}
}
void CGameStateRun::OnShow()
{
	map.OnShow();
	seed.OnShow();
	shovel.OnShow();
	for(int row = 0; row < 5; row++){               //讓圖片從最上面一排依序顯示到最下面一排，以免畫面不規則的重疊
		vector<Plants>::iterator itp;
		bool ErasePlant = false;
		for (vector<Plants>::iterator it = plants.begin(); it != plants.end(); it++) {
			if (it->GetRow() == row)	it->OnShow();
			if (it->isFinished() == true) {             //讓植物在死亡後或是動作結束後(葫蘆和櫻桃)被解構
				itp = it;
				ErasePlant = true;
				PlantManager[itp->GetRow()][itp->GetColumn()] = 0;
				continue;
			}
		}
		if (ErasePlant == true) {
			plants.erase(itp);
			ErasePlant = false;
		}
		vector<Zombies>::iterator itz;
		bool EraseZombie = false;
		for (vector<Zombies>::iterator it = zombies.begin(); it != zombies.end(); it++) {
			if (it->GetRow() == row)	it->OnShow();
			if (it->isFinished() == true) {             // 讓殭屍在死亡動畫顯示完畢後才會被解構
				itz = it;
				EraseZombie = true;
				continue;
			}
		}
		LawnMower[row].OnShow();
		if (EraseZombie == true) {
			zombies.erase(itz);
			EraseZombie = false;
		}
		vector<Pea>::iterator itpea;
		bool ErasePea = false;
		for (vector<Pea>::iterator it = peas.begin(); it != peas.end(); it++) {
			if (it->isFinished() == true) {             //讓豆子在擊中殭屍的動畫結束後才會被解構
				itpea = it;
				ErasePea = true;
				continue;
			}
			it->OnShow();
		}
		if (ErasePea == true) {
			peas.erase(itpea);
			ErasePea = false;
		}
	}
	for (vector<Sun>::iterator its = suns.begin(); its != suns.end(); its++) {
		its->OnShow();
	}
	if (selected) {
		cursor.OnShow();
	}
	Wave.SetTopLeft(570, 10);
	Wave.ShowBitmap();
	slash.SetTopLeft(590, 35);
	slash.ShowBitmap();
	numbers[1].SetTopLeft(605, 35);
	numbers[0].SetTopLeft(620, 35);
	numbers[0].ShowBitmap();
	numbers[1].ShowBitmap();
	if (wave == 9 && ZombieCounter >= 450) {
		numbers[1].SetTopLeft(560, 35);
		numbers[1].ShowBitmap();
		numbers[0].SetTopLeft(575, 35);
		numbers[0].ShowBitmap();
		if (ZombieCounter >= 450) {
			if (ZombieCounter <= 468) {
				FinalWave.SetTopLeft(int(150-170*(468-ZombieCounter)/2.0), int(200-40* (468 - ZombieCounter) / 2.0));
				FinalWave.ShowBitmap(1+(468 - ZombieCounter)/2.0);
			}
			else if (ZombieCounter < 500) {
				FinalWave.SetTopLeft(150, 200);
				FinalWave.ShowBitmap();
			}
		}
	}
	else {
		numbers[(wave) % 10].SetTopLeft(575, 35);
		numbers[(wave) % 10].ShowBitmap();
	}
	if (isGameOver == true) {
		GameOver();
	}
}
}