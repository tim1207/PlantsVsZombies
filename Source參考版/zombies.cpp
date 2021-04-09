#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "zombies.h"
#include <cstring>
#include <sstream>
#include <stdio.h>
namespace game_framework{
	Zombies::Zombies() {
	}
	// �L�ͪ���l��
	Zombies::Zombies(int a, int b, int c):status(1) {
		ID = a;
		x = c;
		y = b * 75;
		row = b;
		LastMove = 0;
		AttackCounter = 0;
		AttackClock = 30;
		SnowCounter = 0;
		HeadFinished = false;
		DieFinished = false;
		BoomFinished = false;
		Boom = false;
		velocity = 1;
		AnimeWalking.SetDelayCount(7);
		NormalWalking.SetDelayCount(7);
		AnimeAttacking.SetDelayCount(3);
		NormalAttacking.SetDelayCount(3);
		AnimeDie.SetDelayCount(4);
		Head.SetDelayCount(4);
		BoomDie.SetDelayCount(4);
		GiveLife();
		LoadBitmap();
	}
	//	�]�w�L�ͪ�����
	void Zombies::SetID(int a) {
		ID = a;
	}
	//	�^���L�ͪ�����
	int Zombies::GetID() {
		return ID;
	}
	//	�]�w�L�ͪ��ͩR
	void Zombies::GiveLife() {
		switch (ID) {
		case 1:life = 10; break;
		case 2:life = 20; break;
		case 3:life = 30; break;
		default:	        break;
		}
	}
	//	�^�ǥثe�ѤU���ͩR
	int Zombies::GetLife() {
		return life;
	}
	//	�^�ǬO�_�w�g���`
	bool Zombies::isAlive() {
		if (GetLife() > 0)	return true;
		return false;
	}
	//	���L���������`
	void Zombies::GoToDie() {
		life = 0;
	}
	//	���L�ͳQ����
	void Zombies::BoomToDie() {
		Boom = true;
		life = 0;
	}
	// �]�w�L�ͪ����A
	void Zombies::SetStatus(int now) {
		status = now;
	}
	//	�^�ǥثe�����A
	int Zombies::GetStatus() {
		return status;
	}
	//	�ھ��L�ͪ������M�w�Ϥ����ƶq
	void Zombies::SetFrames()
	{
		switch (ID) {
		case 1: WalkingFrames = 17;	AttackingFrames = 20; break;
		case 2: WalkingFrames = 20; AttackingFrames = 10; break;
		case 3:	WalkingFrames = 14;	AttackingFrames = 10; break;
		default:	                                        break;
		}
	}
	//	Ū���һݪ�����
	void Zombies::LoadBitmap() {
		SetStatus(1);
		SetFrames();
		for (int i = 0; i <= WalkingFrames; i++) {
			char FILENAME[100];
			sprintf(FILENAME, "%s%s%02d.bmp",GetPath().c_str(),GetPathWithStatus().c_str(),i);
			AnimeWalking.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		SetStatus(2);
		for (int i = 0; i <= AttackingFrames; i++) {
			char FILENAME[100];
			sprintf(FILENAME, "%s%s%02d.bmp", GetPath().c_str(), GetPathWithStatus().c_str(), i);
			AnimeAttacking.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		for (int i = 0; i <= 17; i++) {
			char FILENAME[100];
			sprintf(FILENAME, ".\\RES\\Zombies\\Zombie\\Zombie_%02d.bmp", i);
			NormalWalking.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		for (int i = 0; i <= 20; i++) {
			char FILENAME[100];
			sprintf(FILENAME, ".\\RES\\Zombies\\Zombie\\ZombieAttack_%02d.bmp", i);
			NormalAttacking.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		SetStatus(1);
		for (int i = 0; i <= 9; i++) {
			char FILENAME[100];
			sprintf(FILENAME,"%s%02d.bmp",".\\RES\\Zombies\\Zombie\\ZombieDie_",i);
			AnimeDie.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		for (int i = 0; i <= 11; i++) {
			char FILENAME[100];
			sprintf(FILENAME, "%s%02d.bmp", ".\\RES\\Zombies\\Zombie\\ZombieHead_", i);
			Head.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		for (int i = 0; i <= 19; i++) {
			char FILENAME[100];
			sprintf(FILENAME, ".\\RES\\Zombies\\BoomDie\\BoomDie_%02d.bmp", i);
			BoomDie.AddBitmap(FILENAME, RGB(0, 0, 255));
		}
	}
	//	�^���L�ͩҦb���C��
	int Zombies::GetRow()
	{
		return row;
	}
	//	�^��X�y��
	int Zombies::GetX() {
		return x;
	}
	//	�ˬd�L�ͬO�_�n����
	bool Zombies::Attack() {
		if (AttackCounter == AttackClock) {
			AttackCounter = 0;
			return true;
		}
		return false;
	}
	//	���L�ͥ[�t(�K�ޥ�)
	void Zombies::Faster() {
		velocity++;
	}
	// ���L�ͦV�e����
	void Zombies::MoveX() {
		if (SnowCounter == 0) {
			x -= velocity;
		}
		else if (SnowCounter != 0) {
			//	�p�G�L�ͳB��N�᪬�A�h���ʳt�״�b
			SnowCounter--;
			if (LastMove == 0) {
				x -= velocity;
				LastMove = 1;
			}
			else if (LastMove == 1) {
				LastMove = 0;
			}
		}
	 }
	//	�B�z�L�ͪ��ʧ@
	void Zombies::OnMove() {
		if (SnowCounter == 1) {
			AttackClock = 30;
		}
		if (isAlive() == false && Boom == false) {
			AnimeDie.OnMove();
			Head.OnMove();
		}
		else if (isAlive() == false && Boom == true) {
			BoomDie.OnMove();
		}
		else if (GetStatus()==1) {
			AnimeWalking.OnMove();
			NormalWalking.OnMove();
			MoveX();
		}
		else if (GetStatus() == 2) {
			AttackCounter++;
			AnimeAttacking.OnMove();
			NormalAttacking.OnMove();
		}
	}
	// �B�z�L�ͪ��ʵe
	void Zombies::OnShow() {
		if (isAlive() == false) {
			if (Boom == false) {
				if (DieFinished == false) {
					AnimeDie.SetTopLeft(x, y);
					AnimeDie.OnShow();
					if (AnimeDie.IsFinalBitmap() == true) {
						DieFinished = true;
					}
				}
				if (HeadFinished == false) {
					Head.SetTopLeft(x, y);
					Head.OnShow();
					if (Head.IsFinalBitmap() == true) {
						HeadFinished = true;
					}
				}
			}
			else if (Boom == true) {
				if (BoomFinished == false) {
					BoomDie.SetTopLeft(x, y);
					BoomDie.OnShow();
					if (BoomDie.IsFinalBitmap() == true) {
						BoomFinished = true;
					}
				}
			}
		}
		else if (GetStatus() == 1) {
			if (GetLife() > 10) {
				AnimeWalking.SetTopLeft(x, y);
				AnimeWalking.OnShow();
			}
			else {
				NormalWalking.SetTopLeft(x, y);
				NormalWalking.OnShow();
			}
		}
		else if (GetStatus() == 2) {
			if (GetLife() > 10) {
				AnimeAttacking.SetTopLeft(x, y);
				AnimeAttacking.OnShow();
			}
			else {
				NormalAttacking.SetTopLeft(x, y);
				NormalAttacking.OnShow();
			}
		}
	}
	//	���͹��ɸ��|
	string Zombies::GetPathWithStatus() {

		if (status == 2)	return "Attack_"; 
		return "_";
	}
	//	���͹��ɸ��|
	string Zombies::GetPath() {
		stringstream ss;
		switch (ID) {
		case 1: ss << ".\\RES\\Zombies\\Zombie\\Zombie";						          break;
		case 2: ss << ".\\RES\\Zombies\\ConeHeadZombie\\ConeHeadZombie";		  break;
		case 3: ss << ".\\RES\\Zombies\\BucketHeadZombie\\BucketHeadZombie";	break;
		default:ss << "";                                                     break;
		}
		return ss.str();
	}
	//	�]�w�L�Ͷi�J�N�᪬�A
	void Zombies::SetSnowCounter() {
		SnowCounter = 150;
	}
	//	�L�ͳQ����
	void Zombies::Hitted(int type)
	{
		life--;
		if (type == 1) {
			SetSnowCounter();
			AttackClock = 60;
			AnimeAttacking.SetDelayCount(5);
			NormalAttacking.SetDelayCount(5);
			AnimeWalking.SetDelayCount(10);
			NormalWalking.SetDelayCount(10);
		}
	}
	//	�ˬd���`���ʵe�O�_�w�g����
	bool Zombies::isFinished() {
		if (DieFinished == true && HeadFinished == true || BoomFinished == true) {
			return true;
		}
		return false;
	}
}