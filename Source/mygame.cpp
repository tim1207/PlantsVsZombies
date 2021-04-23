#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"


namespace game_framework {
	bool YouWin = false;
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	//Ū��������
	void CGameStateInit::LoadAudio() {

	}

	// is finished 
	void CGameStateInit::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(0); // �@�}�l��loading�i�׬�0%
		//
		// �}�l���J���
		//
		logo.LoadBitmap(Background);
		adventure_block.LoadBitmap(Adventure, RGB(255, 255, 255));
		//Sleep(300);    // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
		//
	}

	void CGameStateInit::OnBeginState()
	{
	}

	// is finsihed
	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_SPACE)
			GotoGameState(GAME_STATE_RUN);      // ������GAME_STATE_RUN
		else if (nChar == KEY_ESC)        // Demo �����C������k
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0); // �����C��
	}


	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		// �B�z�ƹ��M��檺����
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		GotoGameState(GAME_STATE_RUN);  // ������GAME_STATE_RUN
	}

	// is finish
	void CGameStateInit::OnShow()
	{
		logo.ShowBitmap();
		adventure_block.SetTopLeft(480, 100);
		adventure_block.ShowBitmap();

		//   //
		//   // Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
		//   //
		//   CDC *pDC = CDDraw::GetBackCDC();   // ���o Back Plain �� CDC 
		//   CFont f, *fp;
		//   f.CreatePointFont(160, "Times New Roman"); // ���� font f; 160���16 point���r
		//   fp = pDC->SelectObject(&f);     // ��� font f
		//   pDC->SetBkColor(RGB(0, 0, 0));
		//   pDC->SetTextColor(RGB(255, 255, 0));
		//   pDC->TextOut(120, 220, "Please click mouse or press SPACE to begin.");
		//   pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");
		//   if (ENABLE_GAME_PAUSE)
		//    pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
		//   pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");
		//   pDC->SelectObject(fp);      // �� font f (�d�U���n�|�F��)
		//   CDDraw::ReleaseBackCDC();     // �� Back Plain �� CDC
	}

	// Init is over 




	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}
	//Ū�����G������
	void CGameStateOver::LoadBitmap() {
		ZombiesWon.LoadBitmap(".\\BMP_RES\\image\\interface\\ZombiesWon.bmp");
		//TODO:	need to be set 
		ZombiesWon.SetTopLeft(0, 0);
		ZombieNote.LoadBitmap(".\\BMP_RES\\image\\interface\\trophy.bmp");
		//TODO:	need to be set 
		ZombieNote.SetTopLeft(0, 0);
	}

	// is finished
	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}
	// is finished 
	void CGameStateOver::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(66); // ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
		//
		// �}�l���J���
		//
		Sleep(300);    // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// �̲׶i�׬�100%
		//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		if (YouWin == false) {
			ZombiesWon.ShowBitmap();
		}
		else {
			ZombieNote.ShowBitmap();
		}

		//teacher's code
		// 	CDC *pDC = CDDraw::GetBackCDC();   // ���o Back Plain �� CDC 
		// 	CFont f, *fp;
		// 	f.CreatePointFont(160, "Times New Roman"); // ���� font f; 160���16 point���r
		// 	fp = pDC->SelectObject(&f);     // ��� font f
		// 	pDC->SetBkColor(RGB(0, 0, 0));
		// 	pDC->SetTextColor(RGB(255, 255, 0));
		// 	char str[80];        // Demo �Ʀr��r�ꪺ�ഫ
		// 	sprintf(str, "Game Over ! (%d)", counter / 30);
		// 	pDC->TextOut(240, 210, str);
		// 	pDC->SelectObject(fp);      // �� font f (�d�U���n�|�F��)
		// 	CDDraw::ReleaseBackCDC();     // �� Back Plain �� CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g)
	{
		srand((unsigned)time(NULL));
	}

	CGameStateRun::~CGameStateRun()
	{

	}

	void CGameStateRun::OnBeginState()
	{
		background.SetTopLeft(-500, 0);    				// �]�w�I�����_�l�y��
		//help.SetTopLeft(0, SIZE_Y - help.Height());   // �]�w�����Ϫ��_�l�y��
		
		sunback.SetTopLeft(-400, 10);
		zombiesone[0].SetTopLeft(640, 150);
		zombiesone[1].SetTopLeft(660, 200);
		zombiesone[2].SetTopLeft(640, 250);
		zombiesone[3].SetTopLeft(660, 300);
		zombiesone[4].SetTopLeft(640, 350);

		//�]�w�M�ƹ��������ܼ�
		SunCounter = 0;                                   //�q�Ť������Ӷ����p�ɾ�
		selected = false;
		ChoosedCard = -1;
		ChoosedPlant = -1;
		//���]���W���Ӫ�

		 for (int i = 0; i < 5; i++) {
		 	for (int j = 0; j < 9; j++) {
		 		PlantManager[i][j] = 0;
		 	}
		 }
		 flow = 0;
		//�T�O�Ҧ���vector�M��

		// zombies.clear();
		// plants.clear();
		// peas.clear();
		suns.clear();
		seed.Reset();

		//���]�����
		// for (int i = 0; i < 5; i++) {
		// 	LawnMower[i].Reset();
		// }
		// wave = 0;

		//CAudio::Instance()->Play(AUDIO_LAKE, true);   // ���� WAVE
		//CAudio::Instance()->Play(AUDIO_DING, false);  // ���� WAVE
		//CAudio::Instance()->Play(AUDIO_NTUT, true);   // ���� MIDI
	}

	void CGameStateRun::OnInit()          // �C������Ȥιϧγ]�w
	{	
		int temp[] = { 1,2,3 };
		seed.Load(3, temp);//�i���
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(33); // ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
		background.LoadBitmap(Background1row);     // ���J�I�����ϧ�
		//
		// ��������Loading�ʧ@�A�����i��
		//
		ShowInitProgress(50);
		Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		for (int i = 0; i < 5; i++)						//���J�L��
			zombiesone[i].LoadBitmap(zombies, RGB(0, 0, 0));

		
		//plants.push_back(Plants(1, 3, 2));
		//testp[0]= Plants(1, 3, 1);
		cursor.LoadBitmap();
		sunback.LoadBitmap("BMP_RES/image/interface/SunBack.bmp", RGB(0, 0, 0));

		
		// �~����J��L���

		//CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav"); // ���J�s��0���n��ding.wav
		//CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3"); // ���J�s��1���n��lake.mp3
		//CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\ntut.mid"); // ���J�s��2���n��ntut.mid
		//
		// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
		//

	}

	void CGameStateRun::OnMove()       // ���ʹC������
	{
		//  �}�l�����ʵe��
		if (background.Left() < -80)
			background.SetTopLeft(background.Left() + 10, 0);
		if (sunback.Left() <100)
			sunback.SetTopLeft(sunback.Left()+ 10, 10);
		// TODO: ��m�L�� (right)
	

		//

		for (int i = 0; i < 5; i++) {
			if (zombiesone[i].Left() < 1040)
				zombiesone[i].SetTopLeft(zombiesone[i].Left() + 10, 150 + i * 50);
		}

		//�C�j7��q�Ť����ͤ@�ӤӶ�
		SunCounter++;
		if (SunCounter == 210) {
			SunCounter = 0;
			suns.push_back(Sun(rand() % 400 + 100, rand() % 300 + 100, false));
		}

		// maybe now don't need it  
		vector<Sun>::iterator itss;
		bool EraseSun = false;
		//�B�z�Ҧ��Ӷ����ʧ@
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

	}



	//�i�JGameStateOver�A�ñNvector�M�šA�_�h�ĤG�����|���Ϳ��~
	void CGameStateRun::GameOver() {
		// zombies.swap(vector<Zombies>());
		// plants.swap(vector<Plants>());
		suns.swap(vector<Sun>());
		// peas.swap(vector<Pea>());
		// CAudio::Instance()->Stop(AUDIO_MAIN_MUSIC);
		GotoGameState(GAME_STATE_OVER);
	}


	//�K��
	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y

		if (nChar == KEY_UP) {
			/*
			for (vector<Zombies>::iterator itz = zombies.begin(); itz != zombies.end(); itz++) {
				itz->GoToDie();
			}
			*/
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
		// const char KEY_LEFT = 0x25; // keyboard���b�Y
		// const char KEY_UP = 0x26; // keyboard�W�b�Y
		// const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		// const char KEY_DOWN = 0x28; // keyboard�U�b�Y

		// if (nChar == KEY_LEFT)
		// 	eraser.SetMovingLeft(false);
		// if (nChar == KEY_RIGHT)
		// 	eraser.SetMovingRight(false);
		// if (nChar == KEY_UP)
		// 	eraser.SetMovingUp(false);
		// if (nChar == KEY_DOWN)
		// 	eraser.SetMovingDown(false);

		// gamemap.OnKeyDown(nChar);
	}

	// TODO:
	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		if (!selected) {
			//�B�z�I���Ӷ����ʧ@
			bool GotSun = false;
			for (vector<Sun>::iterator its = suns.begin(); its != suns.end(); its++) {
				if (point.x >= its->GetX() && point.x <= its->GetX() + its->GetWidth() && point.y >= its->GetY() && point.y <= its->GetY() + its->GetHeight()) {
					its->PickUp();
					//CAudio::Instance()->Play(AUDIO_COLLECT_SUN, false);
					seed.GotSun();
					GotSun = true;
					break;
				}
			}
			//�B�z��ܥd�����ʧ@
			if (point.x >= 0 && point.x <= 95 && point.y >= 50 && point.y <= 230 && GotSun == false) {
				ChoosedCard = (point.y - 50) / 60;
				ChoosedPlant = seed.GetCardID(ChoosedCard);
				if (seed.isCardAvailible(ChoosedCard)) {
					//CAudio::Instance()->Play(AUDIO_CHOOSE_CARD, false);
					selected = true;
					cursor.SetXY(point.x, point.y);
					cursor.SetWhich(ChoosedPlant); //����Ъ��ˤl�ܦ��ǳƺشӪ��Ӫ�
					
				}
			}
			//�B�z�I�����l���ʧ@
			if (point.x >= 115 && point.x <= 191 && point.y >= 10 && point.y <= 44 && GotSun == false) {
				if (shovel.isChoosed() == false) {
					//CAudio::Instance()->Play(AUDIO_SHOVEL, false);
					shovel.SetChoosed(true);
					selected = true;
					cursor.SetWhich(8); //����Ъ��ˤl�ܦ���l
				}
			}

		}
		else if (selected) {
			if (point.x >= 172 && point.x <= 900 && point.y >= 80 && point.y <= 580) {
				//��{����l�����Ӫ����\��
				/*
				if (shovel.isChoosed() == true) {
					PlantManager[(point.y - 80) / 98][(point.x - 172) / 80] = 0;
					bool ErasePlant = false;
					testp[(point.y - 80) / 98][(point.x - 172) / 80].SetID(0);
					/*
					vector<Plants>::iterator itpp;
					for (vector<Plants>::iterator itp = plants.begin(); itp != plants.end(); itp++) {
						if (itp->GetRow() == (point.y - 75) / 75 && itp->GetColumn() == (point.x - 46) / 66) {
							itpp = itp;
							ErasePlant = true;
						}
					}
					

				}
				*/
				if (shovel.isChoosed() == false) {
					//�Ӫ��\��
					if (PlantManager[(point.y - 80) / 98][(point.x - 172) / 80] == 0) {
						PlantManager[(point.y - 80) / 98][(point.x - 172) / 80] = ChoosedPlant;
						testp[(point.y - 80) / 98][(point.x - 172) / 80] = Plants(ChoosedPlant, (point.x - 172) / 80, (point.y - 80) / 98);
						
						//plants.push_back(Plants(ChoosedPlant, (point.x - 172) / 80, (point.y - 80) / 98));
						//CAudio::Instance()->Play(AUDIO_PLANT, false);
						//seed.ResetCardCounter(ChoosedCard);//�N�o
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

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
	{

	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
	{
		 if (selected) {
		 	cursor.SetXY(point.x, point.y);
		 }
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
	{
		// for (int i = 0; i < 5; i++) {
		// zombies.push_back(Zombies(1, i, 590));
		// for (int j = 0; j < 10; j++) {
		// 	zombies.back().Faster();
		// }
	}


void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//
	
	background.ShowBitmap();   // �K�W�I����
	seed.OnShow();
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			testp[i][j].OnShow();
		}	
	}
	
	
	/*
	for (int row = 0; row < 5; row++) {
		vector<Plants>::iterator itp;
		bool ErasePlant = false;
		for (vector<Plants>::iterator it = plants.begin(); it != plants.end(); it++) {
			if (it->GetRow() == row)	
				it->OnShow();

			if (it->isFinished() == true) {             //���Ӫ��b���`��άO�ʧ@������(��Ī�M���)�Q�Ѻc
				itp = it;
				ErasePlant = true;
				PlantManager[itp->GetRow()][itp->GetColumn()] = 0;
				continue;
			}
			if (ErasePlant == true) {
				plants.erase(itp);
				ErasePlant = false;
			}
		}
	}
	*/
	///
	for (int i = 0; i < 5; i++)
		zombiesone[i].ShowBitmap();
	//peacard.ShowBitmap();
	//sunflowercard.ShowBitmap();
	//wallnutcard.ShowBitmap();
	//sunback.ShowBitmap();
	// map.OnShow();
	// seed.OnShow();
	// shovel.OnShow();
	/*
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f, *fp;
	f.CreatePointFont(100, "Times New Roman");	// ���� font f; 160���16 point���r
	fp = pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(238, 230, 170));
	pDC->SetTextColor(RGB(0, 0, 0));

	pDC->TextOut(165, 18, "50");
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	*/
	///sun drop
	for (vector<Sun>::iterator its = suns.begin(); its != suns.end(); its++) {
		its->OnShow();
	}
	if (selected) {

		cursor.OnShow();
	}
}

}