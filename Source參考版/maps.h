#pragma once
namespace game_framework {
	class Maps {
	public:
		Maps();
		void LoadBitmap();		// ���J�ϧ�
		void OnShow();			  // �N�ϧζK��e��
	private:
		int x, y;				      // �ϧήy��
		CMovingBitmap bmp;
	};
}