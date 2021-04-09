#include "maps.h"
#include "zombies.h"
#include "Plants.h"
#include "Seed.h"
#include "Pea.h"
#include "cursor.h"
#include "Sun.h"
#include "Shovel.h"
#include "LawnMower.h"
#include <vector>
#include "Selector.h"
namespace game_framework {
	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_AWOOGA,
		AUDIO_CHERRY_BOMB,
		AUDIO_CHOMP_1,
		AUDIO_CHOMP_2,
		AUDIO_CHOMP_3,
		AUDIO_EVIL_LAUGH,
		AUDIO_FINALWAVE,
		AUDIO_GROAN_1,
		AUDIO_GROAN_2,
		AUDIO_GROAN_3,
		AUDIO_GROAN_4,
		AUDIO_GROAN_5,
		AUDIO_GROAN_6,
		AUDIO_LAWN_MOWER,
		AUDIO_LOSE_MUSIC,
		AUDIO_MAIN_MUSIC,
		AUDIO_MENU,
		AUDIO_PLANT,
		AUDIO_COLLECT_SUN,
		AUDIO_CHOOSE_CARD,
		AUDIO_HIT_BUCKET_1,
		AUDIO_HIT_BUCKET_2,
		AUDIO_SHOVEL,
		AUDIO_SPLAT_1,
		AUDIO_SPLAT_2,
		AUDIO_SPLAT_3,
		AUDIO_SHOOT,
		AUDIO_WIN_MUSIC
	};
	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								                // �C������Ȥιϧγ]�w
		void OnBeginState();							              // �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				        // �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	  // �B�z�ƹ����ʧ@
		void LoadAudio();								                // Ū���һݪ�������
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		Selector menu;
		bool conditionA;								// �ˬd��ЬO�_���I��}�l�C�������s
		bool conditionB;								// �ˬd��ЬO�_���I��}�l�C�������s
		bool play_Audio;								// �x�s�O�_�w�g�}�l����I�����֪�flag
		bool load_Audio;								// �x�s�O�_�w�gŪ�������ɪ�flag
		CMovingBitmap	help;							// help������
	};
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							              // �]�w�C�������һݪ��ܼ�
		void OnInit();  								                // �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	  // �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	  // �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	  // �B�z�ƹ����ʧ@
		void LoadAudio();
	protected:
		void OnMove();						        		        	// ���ʹC������
		void OnShow();						        		        	// ��ܳo�Ӫ��A���C���e��
	private:
		Maps			      map;					            	  	// �I����
		Seed		      	seed;					             	  	// �����W��޲z�d��������
		Cursor		    	cursor;						            	// �Ψ���ܥثe������F��
		Shovel		    	shovel;						            	// ��l
		LawnMower	     	LawnMower[5];			         	  	// �����
		vector<Zombies>	zombies;			    	      	  	// �x�s�Ҧ��L�ͪ�vector
		vector<Plants>	plants;					          	  	// �x�s�Ҧ��Ӫ���vector
		vector<Pea>		  peas;						              	// �x�s�Ҧ����l��vector
		vector<Sun>	  	suns;						              	// �x�s�Ҧ��Ӷ���vector
		bool		      	selected;						            // �P�_�ثe�O�_������F��
		int			      	ChoosedCard;					          // �ثe������d��
		int			      	ChoosedPlant;					          // �ثe������Ӫ�
		int			      	SunCounter;						          // �q�Ť������Ӷ����p�ɾ�
		int			      	PlantManager[5][9] = { 0 };	  	// �x�s���W�Ӫ�����m
		int			      	ZombieCounter;				        	// �����L�ͪ��p�ɾ�
		int			      	wave;						                // �ثe���i��
		void		      	GameOver();			        	      // ���C���i�JCGameStateOver
		bool		      	isGameOver;				              // �ˬd�C���ϧ_����
		bool		      	awooga;					                // �Ĥ@���L�ͥX�{�ɼ��񭵼֪�flag
		CMovingBitmap	  FinalWave;			    		    	  // �̫�@�i�L�ͪ��w�i��
		CMovingBitmap	  Wave;					        	    	  // ���wave
		CMovingBitmap	  numbers[10];	    			    	  // ��ܼƦr
		CMovingBitmap	  slash;					      	    	  // ��ܱ׽u
	};
	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void LoadBitmap();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
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