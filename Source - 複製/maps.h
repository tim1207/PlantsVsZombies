#pragma once

namespace game_framework {
	class Maps {
	public:
		Maps();
		void LoadBitmap();		// ���J�ϧ�
		void LoadBitmap(std::string path);		// ���J�ϧ�
		void OnShow(int, int);			  // �N�ϧζK��e��
	private:
		int x, y;				      // �ϧήy��
		CMovingBitmap bmp;
	};
}
