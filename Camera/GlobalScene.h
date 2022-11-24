#pragma once
enum Scene { //シーンID
	DEBUG,
	TITLE,
	INFO,
	TUTORIAL,
	SELECT,
	STAGE1,
	STAGE2,
	STAGE3,
	CLEAR,
	GAMEOVER,
};

enum PHASE { // フェーズ
	POP,
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