#pragma once
namespace game_framework {
	class Plants {
	public:
		Plants();
		Plants(int,int,int);		  // �Ӫ�����l��
		void SetID(int);			    // �]�w�Ӫ�������
		void SetLife();				    // �]�w�ͩR
		int GetLife();				    // �^�ǥثe�Ѿl���ͩR
		bool isAlive();				    // �ˬd�O�_���`
		void LoadBitmap();			  // Ū���һݹ���
		void OnMove();			  	  // ����ʧ@
		void OnShow();			  	  // ��ܦb�ù��W
		string GetPath();		  	  // ���o���ɪ����|
		void SetFrames();		  	  // �ھڴӪ��������]�w���ɪ��ƶq
		int GetRow();				      // �^�ǩҦb���C��
		int GetColumn();			    // �^�ǩҦb�����
		int GetX();					      // �^��X�y��
		int GetY();					      // �^��Y�y��
		int GetWidth();				    // �^�ǹ��ɪ��e��
		void SetX(int);				    // �]�wX�y��
		void SetY(int);				    // �]�wY�y��
		void BeingAttacked();		  // ���Ӫ��Q����
		int GetID();				      // �^�ǴӪ�������
		void ResetCounter();		  // ���]�N�o�ɶ�
		void SetCounterOn(bool);	// ���Ӫ��}�l�ʧ@
		bool isCounterOn();			  // �ˬd�O�_�w�Ұʰʧ@�p�ɾ�
		bool isAction();			    // �ˬd�O�_���b�ʧ@
		int CounterLeft();			  // �^���٭n�h�[�~�|�ʧ@
		void StartAction();			  // �}�l�ʧ@
		int WhichAction();			  // �^�ǥثe�����A
		void SetTargetX(int);		  // �]�w�ؼЩҦb��X�y��(��Ī��)
		bool isFinished();			  // �ˬd�ʵe�O�_�w�g����
	private:
		int x, y;					        // X,Y�y��
		int Counter;				      // �N�o�ɶ����p�ɾ�
		int ActionCounter;			  // �x�s�N�o�ɶ�����
		int MovingCounter;			  // �x�s���ʪ��N�o�ɶ�����(��Ī��)
		int anime2Counter;			  // �z���ɶ��p�ɾ�(����)
		int velocity;				      // ���ʪ��t��(��Ī��)
		bool CounterOn;			     	// �p�ɾ����ҰʻP�_
		bool Action;				      // �ʧ@���A
		int status;					      // �������A
		int TargetX;				      // �ؼЪ�X�y��(��Ī��)
		int row, column;			    // ��C�y��
		int life;					        // �ͩR
		int ID;						        // �Ӫ�����
		/*
			0 : empty
			1 : SunFlower
			2 : PeaShooter
			3 : WallNut
			31: WallNut_cracked1
			32: WallNut_cracked2
			4 : Squash
			41: SquashAttack
			5 : CherryBomb
			6 : SnowPea
			7 : Repeater
		*/
		int frames;					      // ���ɼƶq
		CAnimation anime;
		CAnimation anime2;
		CAnimation anime3;
		CMovingBitmap Boom;
	};
}