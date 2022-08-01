#pragma once
#include"PoolAllocator.h"
#include"Def.h"
#include<array>
#include<string>
enum class SceneType
{	
	None,//�V�[���J�ڗp�Ɏg�p
	Title,
	Stage,
	Shop,
	End
};
class GameData;
class Scene {
protected:
	const uint PLAYER_DEFAULT_Y = 6;
	const uint PLAYER_DEFAULT_X = 1, OPPONENT_DEFAULT_X = 18;
	char GetKey();
	WPtr<GameData> o_gamedata;
	SPtr<GameData> GetGamedataPtr() const;
	void MoveCursor(uint y, uint x) const;
public:
	Scene(SPtr<GameData> _gamedata);
	virtual ~Scene();
	void EraseLine() const;
	virtual SceneType Update()=0;
	virtual void Draw() const =0;
	//Title��Stage�ł͂����override����D
	//true���Ԃ��Ă�����Q�[���I���Ƃ���D
	virtual bool IsEndGame() const;
};

class Title : public Scene {
	bool isEnd;
public:
	Title(SPtr<GameData> _gamedata);
	virtual ~Title();
	SceneType Update() final override;
	void Draw() const final override;
	bool IsEndGame() const final override;
};

class Stage :public Scene {
	std::array<std::string, 3> m_log;
	int m_turn;
	Character* m_enemy;
	Character* GetPlayer() const;
	Character* GetEnemy() const;
	void DrawChoices() const;
	void DrawLog() const; 
	void UpdateLog(const std::string& _message);
	bool IsPlayerTurn() const;
	int CalcGetMoney() const; //���̓G��|�����Ƃ��ɓ����邨�����v�Z
public:
	Stage(SPtr<GameData> _gamedata);
	virtual ~Stage();
	SceneType Update() final override;
	void Draw() const final override;
};
class Shop :public Scene {
	std::string log;//�s���̌��ʃ��O��ۑ�����D
	const std::string  m_notenoguhmoney_log = "����������܂���I";
	Character* m_clerk;
	std::array<int, 6> m_defaultvalue,m_mul;
	void ChangeClerkDialogue(const std::string & _dialog);
	void ChangeClerkDialogue();//������U���Ă������̒�����I��
public:
	Shop(SPtr<GameData> _gamedata);
	virtual ~Shop();
	SceneType Update() final override;
	void Draw() const final override;
};

class End :public Scene {
	bool m_kakusibosu;//�B���{�X�֐i�߂邩�ۂ��̑J��
	int m_score;
	void DrawOpponent(uint _y,uint _x) const;
	void WinerDraw() const;//�D�����̕`��
	void DrawKakusibosu() const; //�B���{�X���o�Ă���Ƃ��̕`��
public:
	End(SPtr<GameData> _gamedata);
	virtual ~End();
	SceneType Update()final override;
	void Draw() const final override;

};