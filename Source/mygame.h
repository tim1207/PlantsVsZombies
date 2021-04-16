#include "maps.h"
#include "plants.h"
#include "Sun.h"
//#include "zombies.h"
#include "Seed.h"
// #include "Pea.h"
#include "cursor.h"
// #include "Shovel.h"
// #include "LawnMower.h"
// #include <vector>
// #include "Selector.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								                // �C������Ȥιϧγ]�w
		void OnBeginState();							             	 // �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				        		// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  				// �B�z�ƹ����ʧ@
		//TODO:
		void OnMouseMove(UINT nFlags, CPoint point);	  				// �B�z�ƹ����ʧ@
		void LoadAudio();								                // Ū���һݪ�������
		//

	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap logo;								// �_�I�Ҧ��e��
		CMovingBitmap	adventure_block;				// �_�I�Ҧ� 
		// TODO:
		// Selector menu;
		// bool conditionA;								// �ˬd��ЬO�_���I��}�l�C�������s
		// bool conditionB;								// �ˬd��ЬO�_���I��}�l�C�������s
		// bool play_Audio;								// �x�s�O�_�w�g�}�l����I�����֪�flag
		// bool load_Audio;								// �x�s�O�_�w�gŪ�������ɪ�flag
		// CMovingBitmap	help;							// help������
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////




	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void GameOver();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		// finish
		CMovingBitmap	background;	// �I����
		CMovingBitmap zombiesone[5];	// �L��
		CMovingBitmap peacard;	// PEA
		CMovingBitmap sunflowercard;	// sunflower
		CMovingBitmap wallnutcard;	// wallnut
		CMovingBitmap sunback;
		// TODO:
		// Maps			        map;					            	  	// �I����
		Seed		      	    seed;					             	  	// �����W��޲z�d��������
		Cursor		    	cursor;						            	// �Ψ���ܥثe������F��
		// Shovel		    	shovel;						            	// ��l
		// LawnMower	     	LawnMower[5];			         	  		// �����
		// vector<Zombies>		zombies;			    	      			// �x�s�Ҧ��L�ͪ�vector
		vector<Plants>		plants;					          	  		// �x�s�Ҧ��Ӫ���vector
		// vector<Pea>		  	peas;						              	// �x�s�Ҧ����l��vector
		vector<Sun>	  		suns;						              	// �x�s�Ҧ��Ӷ���vector
		bool		      		selected;						            // �P�_�ثe�O�_������F��
		int			      	ChoosedCard;					          	// �ثe������d��
		int			      	ChoosedPlant;					          	// �ثe������Ӫ�
		int			      	SunCounter;						          	// �q�Ť������Ӷ����p�ɾ�
		 int			      	PlantManager[5][9] = { 0 };	  				// �x�s���W�Ӫ�����m
		// int			      	ZombieCounter;				        		// �����L�ͪ��p�ɾ�
		// int			      	wave;						                // �ثe���i��
		// void		      		GameOver();			        	      		// ���C���i�JCGameStateOver
		// bool		      		isGameOver;				              		// �ˬd�C���ϧ_����
		// bool		      		awooga;					                	// �Ĥ@���L�ͥX�{�ɼ��񭵼֪�flag
		// CMovingBitmap	  	FinalWave;			    		    	  	// �̫�@�i�L�ͪ��w�i��
		// CMovingBitmap	  	Wave;					        	    	// ���wave
		// CMovingBitmap	  	numbers[10];	    			    	 	// ��ܼƦr
		// CMovingBitmap	  	slash;					      	    	  	// ��ܱ׽u
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);

		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
		// TODO:
		void LoadBitmap();
		void LoadAudio();							  	// Ū���һݪ�������
	protected:
		void OnMove();								  	// ���ʹC������
		void OnShow();								  	// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	                    // �˼Ƥ��p�ƾ�
		CMovingBitmap ZombiesWon;					// �C�����Ѫ��e��
		CMovingBitmap ZombieNote;					// �C���ӧQ���e��
	};
}