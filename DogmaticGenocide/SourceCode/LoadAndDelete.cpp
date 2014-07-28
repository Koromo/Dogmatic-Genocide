#include "LoadAndDelete.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "ResourceID.h"
#include "DxLib.h"

void TitleLoad::operator()(){
	ImageMng.set(TITLE_BACKBOARD, "Resource\\Image\\Title\\BackBoard.jpg");
	ImageMng.set(TITLE_MASK, "Resource\\Image\\Title\\Mask.png");
	ImageMng.set(TITLE_TITLE, "Resource\\Image\\Title\\Title.png");
	ImageMng.set(TITLE_GAMESTART, "Resource\\Image\\Title\\GAMESTART.png");
	ImageMng.set(TITLE_OPTION, "Resource\\Image\\Title\\OPTION.png");
	ImageMng.set(TITLE_EXIT, "Resource\\Image\\Title\\EXIT.png");
	ImageMng.set(TITLE_BACK, "Resource\\Image\\Title\\Back.png");
	SoundMng.set(BGM_TITLE, "Resource\\Sound\\BGM\\t-till.ogg");
	SoundMng.set(SE_CHOISE, "Resource\\Sound\\SE\\ëIëâπ.ogg");
	Volume::getInstance().fit();
}

void GameLoad::operator()(){
	ImageMng.set(GAME_BOARD, "Resource\\Image\\Game\\Board.png");
	ImageMng.set(EBE_B, "Resource\\Image\\Game\\Effect\\EnemyBulletExplosionBlue.png");
	ImageMng.set(EBE_R, "Resource\\Image\\Game\\Effect\\EnemyBulletExplosionRed.png");
	ImageMng.set(EE_01, "Resource\\Image\\Game\\Effect\\EnemyExplosion01.png");
	ImageMng.set(EE_02, "Resource\\Image\\Game\\Effect\\EnemyExplosion02.png");
	ImageMng.set(PBE_01, "Resource\\Image\\Game\\Effect\\PlayerBulletExplosion01.png");
	ImageMng.set(PBE_B, "Resource\\Image\\Game\\Effect\\PlayerBulletExplosionBoost.png");
	ImageMng.set(PE_B, "Resource\\Image\\Game\\Effect\\PlayerExplosionBlue.png");
	ImageMng.set(PE_R, "Resource\\Image\\Game\\Effect\\PlayerExplosionRed.png");
	ImageMng.set(SBE_01, "Resource\\Image\\Game\\Effect\\SupporterBulletExplosion01.png");
	ImageMng.set(E_01, "Resource\\Image\\Game\\Enemy\\Enemy01.png");
	ImageMng.set(E_02, "Resource\\Image\\Game\\Enemy\\Enemy02.png");
	ImageMng.set(E_03, "Resource\\Image\\Game\\Enemy\\Enemy03.png");
	ImageMng.set(E_04, "Resource\\Image\\Game\\Enemy\\Enemy04.png");
	ImageMng.set(EB_01B, "Resource\\Image\\Game\\EnemyBullet\\EnemyBullet01Blue.png");
	ImageMng.set(EB_01R, "Resource\\Image\\Game\\EnemyBullet\\EnemyBullet01Red.png");
	ImageMng.set(EB_02B, "Resource\\Image\\Game\\EnemyBullet\\EnemyBullet02Blue.png");
	ImageMng.set(EB_02R, "Resource\\Image\\Game\\EnemyBullet\\EnemyBullet02Red.png");
	ImageMng.set(EB_03B, "Resource\\Image\\Game\\EnemyBullet\\EnemyBullet03Blue.png");
	ImageMng.set(EB_03R, "Resource\\Image\\Game\\EnemyBullet\\EnemyBullet03Red.png");
	ImageMng.set(EB_04B, "Resource\\Image\\Game\\EnemyBullet\\EnemyBullet04Blue.png");
	ImageMng.set(EB_04R, "Resource\\Image\\Game\\EnemyBullet\\EnemyBullet04Red.png");
	ImageMng.set(EB_04Y, "Resource\\Image\\Game\\EnemyBullet\\EnemyBullet04Yellow.png");
	ImageMng.set(UP1, "Resource\\Image\\Game\\Item\\1up.png");
	ImageMng.set(ENERGY_L, "Resource\\Image\\Game\\Item\\EnergyL.png");
	ImageMng.set(ENERGY_S, "Resource\\Image\\Game\\Item\\EnergyS.png");
	ImageMng.set(_POINT, "Resource\\Image\\Game\\Item\\Point.png");
	ImageMng.set(P_01, "Resource\\Image\\Game\\Player\\Player01.png");
	ImageMng.set(P_02, "Resource\\Image\\Game\\Player\\Player02.png");
	ImageMng.set(S_01, "Resource\\Image\\Game\\Player\\é©ã@Aéqã@.png");
	ImageMng.set(S_02, "Resource\\Image\\Game\\Player\\Supporter02.png");
	ImageMng.set(PB_01, "Resource\\Image\\Game\\PlayerBullet\\é©ã@íeñã01.png");
	ImageMng.set(PB_02, "Resource\\Image\\Game\\PlayerBullet\\PlayerBullet02.png");
	ImageMng.set(PB_B01, "Resource\\Image\\Game\\PlayerBullet\\é©ã@íeñãHê¬.png");
	ImageMng.set(PB_B02, "Resource\\Image\\Game\\PlayerBullet\\é©ã@íeñãHê‘.png");
	ImageMng.set(SB_01, "Resource\\Image\\Game\\PlayerBullet\\SupporterBullet01.png");
	ImageMng.set(SB_02, "Resource\\Image\\Game\\PlayerBullet\\SupporterBullet02.png");
	SoundMng.set(SE_EXPLOSION03, "Resource\\Sound\\SE\\îöîjâπ.ogg");
	SoundMng.set(SE_EXPLOSION01, "Resource\\Sound\\SE\\îöîjâπ3.ogg");
	SoundMng.set(SE_EXPLOSION02, "Resource\\Sound\\SE\\îöîjâπ2.ogg");
	SoundMng.set(SE_PE01, "Resource\\Sound\\SE\\îöîjâπ.ogg");
	SoundMng.set(SE_GETITEM, "Resource\\Sound\\SE\\ÉAÉCÉeÉÄéÊìæâπ.ogg");
	ImageMng.set(MAP_TIP, "Resource\\Image\\Game\\map.png");
	ImageMng.set(ICON_A, "Resource\\Image\\Game\\écã@A.png");
	ImageMng.set(ICON_B, "Resource\\Image\\Game\\écã@.png");
	Volume::getInstance().fit();
}

void Stage01Load::operator()(){
	ImageMng.set(BOSS_01, "Resource\\Image\\Game\\Boss\\Boss01.png");
	ImageMng.set(MINIBOSS_01, "Resource\\Image\\Game\\Boss\\MiniBoss01.png");
	SoundMng.set(BGM_STAGE1, "Resource\\Sound\\BGM\\The1stShot(ver2).ogg");
	SoundMng.set(BGM_BOSS01, "Resource\\Sound\\BGM\\FrontLine.ogg");
	Volume::getInstance().fit();
}

void TitleDelete::operator()(){
	ImageMng.remove(TITLE_BACKBOARD);
	ImageMng.remove(TITLE_MASK);
	ImageMng.remove(TITLE_TITLE);
	ImageMng.remove(TITLE_GAMESTART);
	ImageMng.remove(TITLE_OPTION);
	ImageMng.remove(TITLE_EXIT);
	ImageMng.remove(TITLE_BACK);
	SoundMng.remove(BGM_TITLE);
	SoundMng.remove(SE_CHOISE);
}

void GameDelete::operator()(){
	ImageMng.remove(MAP_TIP);
	ImageMng.remove(GAME_BOARD);
	ImageMng.remove(EBE_B);
	ImageMng.remove(EBE_R);
	ImageMng.remove(EE_01);
	ImageMng.remove(EE_02);
	ImageMng.remove(PBE_01);
	ImageMng.remove(PBE_B);
	ImageMng.remove(PE_B);
	ImageMng.remove(PE_R);
	ImageMng.remove(SBE_01);
	ImageMng.remove(E_01);
	ImageMng.remove(E_02);
	ImageMng.remove(E_03);
	ImageMng.remove(E_04);
	ImageMng.remove(EB_01B);
	ImageMng.remove(EB_01R);
	ImageMng.remove(EB_02B);
	ImageMng.remove(EB_02R);
	ImageMng.remove(EB_03B);
	ImageMng.remove(EB_03R);
	ImageMng.remove(EB_04B);
	ImageMng.remove(EB_04R);
	ImageMng.remove(EB_04Y);
	ImageMng.remove(UP1);
	ImageMng.remove(ENERGY_L);
	ImageMng.remove(ENERGY_S);
	ImageMng.remove(_POINT);
	ImageMng.remove(P_01);
	ImageMng.remove(P_02);
	ImageMng.remove(S_01);
	ImageMng.remove(S_02);
	ImageMng.remove(PB_01);
	ImageMng.remove(PB_02);
	ImageMng.remove(PB_B01);
	ImageMng.remove(PB_B02);
	ImageMng.remove(SB_01);
	ImageMng.remove(SB_02);
	ImageMng.remove(ICON_A);
	ImageMng.remove(ICON_B);
	SoundMng.remove(SE_EXPLOSION01);
	SoundMng.remove(SE_EXPLOSION02);
	SoundMng.remove(SE_EXPLOSION03);
	SoundMng.remove(SE_PE01);
	SoundMng.remove(SE_GETITEM);
}

void Stage01Delete::operator()(){
	ImageMng.remove(BOSS_01);
	ImageMng.remove(MINIBOSS_01);
	SoundMng.remove(BGM_STAGE1);
	SoundMng.remove(BGM_BOSS01);
}