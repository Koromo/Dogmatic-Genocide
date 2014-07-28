#include "Stage.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "ResourceID.h"
#include "LoadAndDelete.h"
#include "MiniBoss01.h"
#include "Enemy01A.h"
#include "Enemy01B.h"
#include "Enemy03A.h"
#include "Enemy04A.h"
#include "Boss01.h"
#include "MapTip.h"

Stage1::Stage1(int level) :
level(level)
{ }

void Stage1::init(){
	Stage01Load load;
	load();
	for(int i = 0; i < 9; ++i){
		ary[i].position = getVector(static_cast<float>(GAME_SCREEN_LEFT + 42 * (i + 1)), -70.0f);
		ary[i].flag = false;
	}
}

void Stage1::end(){
	Stage01Delete del;
	StopSoundMem(SoundMng.get(BGM_STAGE1));
	StopSoundMem(BGM_BOSS01);
	del();
}

void Stage1::run(){
	if(stageCnt % 80 == 0){
		ObjectMng.set(MAP, new MapTip(ImageMng.get(MAP_TIP), getVector(0.0f, -40.0f)));
	}

	switch(stageCnt){
	case 0:
		SetLoopPosSoundMem(34909, SoundMng.get(BGM_STAGE1));
		SetLoopStartTimePosSoundMem(120000 + 2182, SoundMng.get(BGM_STAGE1));
		PlaySound(SoundMng.get(BGM_STAGE1), DX_PLAYTYPE_LOOP);

		stageCnt = 0;

		for (int i = 0; i < 3; ++i)
		{
			ObjectMng.set(MAP, new MapTip(ImageMng.get(MAP_TIP), getVector(0.0f, (i + 1.0f) * 200.0f - 40.0f)));
		}
		break;

	case 130:
		createEnemy01A(ImageMng.get(E_01), getVector(290.0f, -70.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(250.0f, -70.0f), ENEMY01_LIFE, level);
		break;
	case 140:
		createEnemy01A(ImageMng.get(E_01), getVector(210.0f, -90.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(180.0f, -70.0f), ENEMY01_LIFE, level);
		break;

	case 220:
		createEnemy01A(ImageMng.get(E_01), getVector(350.0f, -70.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(390.0f, -70.0f), ENEMY01_LIFE, level);
		break;
	case 230:
		createEnemy01A(ImageMng.get(E_01), getVector(430.0f, -90.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(460.0f, -70.0f), ENEMY01_LIFE, level);
		break;

	case 450:
		createEnemy01A(ImageMng.get(E_01), getVector(300.0f, -70.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(260.0f, -90.0f), ENEMY01_LIFE, level);
		break;
	case 460:
		createEnemy01A(ImageMng.get(E_01), getVector(210.0f, -90.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(180.0f, -70.0f), ENEMY01_LIFE, level);
		break;

	case 490:
		createEnemy03A(ImageMng.get(E_03), getVector(400, -70.0f), ENEMY03_LIFE, level);
		break;

	case 620:
		createEnemy01A(ImageMng.get(E_01), getVector(340.0f, -70.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(380.0f, -90.0f), ENEMY01_LIFE, level);
		break;
	case 630:
		createEnemy01A(ImageMng.get(E_01), getVector(430.0f, -90.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(460.0f, -70.0f), ENEMY01_LIFE, level);
		break;

	case 690:
		createEnemy03A(ImageMng.get(E_03), getVector(220.0f, -70.0f), ENEMY03_LIFE, level);
		break;
	case 750:
		createEnemy03A(ImageMng.get(E_03), getVector(320.0f, -70.0f), ENEMY03_LIFE, level);
		break;
	case 780:
		createEnemy03A(ImageMng.get(E_03), getVector(420.0f, -70.0f), ENEMY03_LIFE, level);
		break;

	case 860:
		createEnemy01B(ImageMng.get(E_01), getVector(550.0f, -40.0f), 0.37f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(510.0f, -40.0f), 0.37f, ENEMY01_LIFE, level);
		break;
	case 890:
		createEnemy01B(ImageMng.get(E_01), getVector(470.0f, -40.0f), 0.33f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(430.0f, -40.0f), 0.33f, ENEMY01_LIFE, level);
		break;
	case 920:
		createEnemy01B(ImageMng.get(E_01), getVector(390.0f, -40.0f), 0.29f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(450.0f, -40.0f), 0.29f, ENEMY01_LIFE, level);
		break;

	case 1000:
		createEnemy01A(ImageMng.get(E_01), getVector(300.0f, -70.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(340.0f, -70.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(260.0f, -90.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(380.0f, -90.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(230.0f, -70.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(410.0f, -70.0f), ENEMY01_LIFE, level);
		break;

	case 1100:
		createEnemy01B(ImageMng.get(E_01), getVector(570.0f, -40.0f), 0.37f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(530.0f, -40.0f), 0.37f, ENEMY01_LIFE, level);
		break;
	case 1120:
		createEnemy01B(ImageMng.get(E_01), getVector(490.0f, -40.0f), 0.33f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(450.0f, -40.0f), 0.33f, ENEMY01_LIFE, level);
		break;
	case 1140:
		createEnemy01B(ImageMng.get(E_01), getVector(410.0f, -40.0f), 0.29f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(370.0f, -40.0f), 0.29f, ENEMY01_LIFE, level);
		break;
	case 1160:
		createEnemy01B(ImageMng.get(E_01), getVector(330.0f, -40.0f), 0.25f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(290.0f, -40.0f), 0.25f, ENEMY01_LIFE, level);
		break;

	case 1280:
		createEnemy04A(ImageMng.get(E_04), getVector(50.0f, 150.0f), 0.97f, ENEMY04_LIFE, level);
		createEnemy04A(ImageMng.get(E_04), getVector(590.0f, 150.0f), 0.53f, ENEMY04_LIFE, level);
		break;

	case 1460:
		createEnemy01A(ImageMng.get(E_01), getVector(290.0f, -50.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(250.0f, -50.0f), ENEMY01_LIFE, level);
		break;
	case 1470:
		createEnemy01A(ImageMng.get(E_01), getVector(230.0f, -90.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(200.0f, -70.0f), ENEMY01_LIFE, level);
		break;

	case 1500:
		createEnemy03A(ImageMng.get(E_03), getVector(360.0f, -70.0f), ENEMY03_LIFE, level);
		break;
	case 1530:
		createEnemy03A(ImageMng.get(E_03), getVector(460.0f, -70.0f), ENEMY03_LIFE, level);
		break;
	case 1560:
		createEnemy03A(ImageMng.get(E_03), getVector(280.0f, -70.0f), ENEMY03_LIFE, level);
		break;
	case 1590:
		createEnemy03A(ImageMng.get(E_03), getVector(190.0f, -70.0f), ENEMY03_LIFE, level);
		break;

	case 1860:
		createMiniBoss01(ImageMng.get(MINIBOSS_01), getVector(620.0f, 230.0f), MINIBOSS01_LIFE, level);
		EnemyMng.setAlive(true);
		break;

	case 3200:
		createEnemy01A(ImageMng.get(E_01), getVector(340.0f, -70.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(380.0f, -90.0f), ENEMY01_LIFE, level);
		break;
	case 3210:
		createEnemy01A(ImageMng.get(E_01), getVector(430.0f, -90.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(460.0f, -70.0f), ENEMY01_LIFE, level);
		break;
	case 3240:
		createEnemy01A(ImageMng.get(E_01), getVector(300.0f, -70.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(260.0f, -90.0f), ENEMY01_LIFE, level);
		break;
	case 3250:
		createEnemy01A(ImageMng.get(E_01), getVector(210.0f, -90.0f), ENEMY01_LIFE, level);
		createEnemy01A(ImageMng.get(E_01), getVector(180.0f, -70.0f), ENEMY01_LIFE, level);
		break;

	case 3300:
		createEnemy03A(ImageMng.get(E_03), getVector(340.0f, -70.0f), ENEMY03_LIFE, level);
		break;
	case 3330:
		createEnemy03A(ImageMng.get(E_03), getVector(410.0f, -70.0f), ENEMY03_LIFE, level);
		break;
	case 3360:
		createEnemy03A(ImageMng.get(E_03), getVector(490.0f, -70.0f), ENEMY03_LIFE, level);
		break;
	case 3420:
		createEnemy03A(ImageMng.get(E_03), getVector(250.0f, -70.0f), ENEMY03_LIFE, level);
		break;
	case 3450:
		createEnemy03A(ImageMng.get(E_03), getVector(170.0f, -70.0f), ENEMY03_LIFE, level);
		break;

	case 3550:
		createEnemy01B(ImageMng.get(E_01), getVector(90.0f, -40.0f), 0.13f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(130.0f, -40.0f), 0.13f, ENEMY01_LIFE, level);
		break;
	case 3570:
		createEnemy01B(ImageMng.get(E_01), getVector(170.0f, -40.0f), 0.17f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(210.0f, -40.0f), 0.17f, ENEMY01_LIFE, level);
		break;
	case 3590:
		createEnemy01B(ImageMng.get(E_01), getVector(250.0f, -40.0f), 0.21f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(290.0f, -40.0f), 0.21f, ENEMY01_LIFE, level);
		break;

	case 3620:
		createEnemy01B(ImageMng.get(E_01), getVector(550.0f, -40.0f), 0.37f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(510.0f, -40.0f), 0.37f, ENEMY01_LIFE, level);
		break;
	case 3640:
		createEnemy01B(ImageMng.get(E_01), getVector(470.0f, -40.0f), 0.33f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(430.0f, -40.0f), 0.33f, ENEMY01_LIFE, level);
		break;
	case 3660:
		createEnemy01B(ImageMng.get(E_01), getVector(390.0f, -40.0f), 0.29f, ENEMY01_LIFE, level);
		createEnemy01B(ImageMng.get(E_01), getVector(350.0f, -40.0f), 0.29f, ENEMY01_LIFE, level);
		break;

	case 3960:
		StopSoundMem(SoundMng.get(BGM_STAGE1));
		SetLoopPosSoundMem(42667, SoundMng.get(BGM_BOSS01));
		SetLoopStartTimePosSoundMem(120000 + 18667, SoundMng.get(BGM_BOSS01));
		PlaySound(SoundMng.get(BGM_BOSS01), DX_PLAYTYPE_LOOP);
		break;

	case 4000:
		createBoss01(ImageMng.get(BOSS_01), getVector(320.0f, -100.0f), BOSS01_LIFE, level);
		EnemyMng.setAlive(true);
		break;

	default:
		break;
	}

	if(stageCnt > 1860 && stageCnt < 3060 && ! EnemyMng.aliveBoss()){
		if(cnt % 30 == 20){
			bool crte = true;

			for(int i = 1; i < 8 && ary[i].flag; ++i){
				if(i == 8 - 1){
					crte = false;
				}
			}

			if(crte){
				int i;

				do{
					i = GetRand(6) + 1;
				}while(ary[i].flag);

				createEnemy01Aex(ImageMng.get(E_01), ary[i].position, ENEMY01_LIFE, ary[i].flag, level);
				ary[i].flag = true;
			}
		}
		++cnt;
	}

	if(stageCnt > 3460 && CheckSoundMem(SoundMng.get(BGM_STAGE1))){
		float n = Volume::getInstance().getBgmVolume() / 500.0f;

		ChangeVolumeSoundMem((3960 - stageCnt) * n, SoundMng.get(BGM_STAGE1));
	}

	++stageCnt;
}