#pragma once
enum Scene { //シーンID
	DEBUG,
	TITLE,
	INFO,
	STAGE1,
	STAGE2,
	STAGE3,
	CLEAR,
	GAMEOVER,
};

enum PHASE { // フェーズ
	MOVE,
	ATTACK,
};

enum TURN {
	OWN,
	ENEMY
};

struct ActionData {
	PHASE phase;
	TURN turn;
};