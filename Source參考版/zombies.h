#pragma once
namespace game_framework {
	class Zombies {
	public:
		Zombies();
		Zombies(int,int,int);				  // �L�ͪ���l��
		void LoadBitmap();				    // Ū���һݪ�����
		void OnMove();					      // �B�z�L�ͪ��ʧ@
		void OnShow();					      // ��ܦb�e����
		int GetLife();					      // �^�ǥثe�ҳѪ��ͩR
		bool isAlive();					      // �ˬd�O�_�w���`
		void GiveLife();				      // �]�w�L�ͪ��ͩR
		string GetPath();				      // ���o���ɪ����|
		string GetPathWithStatus();		// �������ɪ����|
		void SetStatus(int);			    // �]�w�L�ͥثe�����A
		int GetStatus();				      // �^���L�ͥثe�����A
		void SetFrames();				      // �]�w�L�͹����`�q
		void Hitted(int);				      // �L�ͳQ����
		int GetRow();					        // �^���L�ͩҦb���C��
		int GetX();						        // �^�ǥثe��X�y��
		void SetID(int);				      // �]�w�L�ͪ�����
		int GetID();					        // �^���L�ͪ�����
		bool Attack();					      // ���L�͵o�ʧ���
		bool isFinished();				    // �ˬd���`�ʵe�O�_�w�g����
		void GoToDie();					      // ���L���������`
		void BoomToDie();				      // ���L�ͳQ����
		void MoveX();					        // ���L�ͦV�e����
		void SetSnowCounter();			  // �]�w�N��p�ɾ�
		void Faster();					      // ���L�ͥ[�t(�K�ޥ�)
	private:
		int x, y;						          // �y��
		int AttackCounter;				    // �������p�ɾ�
		int AttackClock;				      // �������N�o�ɶ�
		int SnowCounter;				      // �N�᪺�p�ɾ�
		int row;						          // �C��
		unsigned int life;				    // �ͩR
		int ID;							          // �L�ͪ�����
		/*
			0:none
			1:zombie
			2:cone head zombie
			3:bucket head zombie
		*/
		int status;						        // �L�ͪ����A�A1�O�����A2�O����
		int LastMove;					        // �x�s�W�@�B�����ʪ��A(�N�᪬�A��)
		int velocity;					        // �L�ͪ����ʳt��
		int WalkingFrames;				    // ���������ɪ��ƶq
		int AttackingFrames;			    // ���������ɪ��ƶq
		CAnimation AnimeWalking;
		CAnimation AnimeAttacking;
		CAnimation NormalWalking;
		CAnimation NormalAttacking;
		CAnimation AnimeDie;
		CAnimation Head;
		CAnimation BoomDie;
		bool Boom;						        // �O�_�O�Q����
		bool HeadFinished;				    // �Y���U�ӤF�ʵe�O�_�w����
		bool DieFinished;				      // ���`���ʵe�O�_�w����
		bool BoomFinished;				    // �z�����`���ʵe�O�_�w����
	};
}