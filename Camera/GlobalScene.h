#pragma once
enum Scene { //�V�[��ID
	DEBUG,
	TITLE,
	INFO,
	STAGE1,
	STAGE2,
	STAGE3,
	CLEAR,
	GAMEOVER,
};

enum PHASE { // �t�F�[�Y
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