#pragma once
namespace game_framework {
	class Sun {
	public:
		Sun();
		Sun(int,int,bool);		        // �Ӷ�����l��
		void LoadBitmap();		        // Ū���һݹ���
		void OnMove();			          // �B�z�Ӷ�������
		void MoveAnime();		          // �B�z�Ӷ����ʵe
		void OnShow();			          // ��ܦb�e����
		void drop();			            // ���Ӷ��q�Ť����U��
		void fly();				            // ���Ӷ��H�ߪ��u���覡����
		int GetX();				            // �^��X�y��
		int GetY();				            // �^��Y�y��
		int GetHeight();		          // �^�ǹϪ�����
		int GetWidth();			          // �^�ǹϪ��e��
		void PickUp();			          // ���Ӷ��Q�߰_
		bool isFinished();		        // �ˬd���ʬO�_�w����
	private:
		int x, y;				              // X, Y�y��
		int desy;				              // �Ӷ��̲ת�Y�y��
		int vx, vy;				            // X��V���t�שMY��V���t��
		bool picked;			            // �O�_�w�Q���
		int MoveCounter;		          // ���ʪ��p�ɾ�
		int stepX, stepY;		          // ���ʹL�{���C�@�����ʪ��Z��
		bool finished;			          // ���ʬO�_�w����
		bool CallFromSunFlower;	      // �O�_�O�q�V�鸪������
	};
}