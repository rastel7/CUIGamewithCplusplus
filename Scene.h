#pragma once
#include"PoolAllocator.h"
#include"Def.h"
#include<array>
#include<string>
enum class SceneType
{	
	None,//シーン遷移用に使用
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
	//TitleとStageではこれをoverrideする．
	//trueが返ってきたらゲーム終了とする．
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
	int CalcGetMoney() const; //今の敵を倒したときに得られるお金を計算
public:
	Stage(SPtr<GameData> _gamedata);
	virtual ~Stage();
	SceneType Update() final override;
	void Draw() const final override;
};
class Shop :public Scene {
	std::string log;//行動の結果ログを保存する．
	const std::string  m_notenoguhmoney_log = "お金が足りません！";
	Character* m_clerk;
	std::array<int, 6> m_defaultvalue,m_mul;
	void ChangeClerkDialogue(const std::string & _dialog);
	void ChangeClerkDialogue();//乱数を振っていくつかの中から選ぶ
public:
	Shop(SPtr<GameData> _gamedata);
	virtual ~Shop();
	SceneType Update() final override;
	void Draw() const final override;
};

class End :public Scene {
	bool m_kakusibosu;//隠しボスへ進めるか否かの遷移
	int m_score;
	void DrawOpponent(uint _y,uint _x) const;
	void WinerDraw() const;//優勝時の描画
	void DrawKakusibosu() const; //隠しボスが出ているときの描画
public:
	End(SPtr<GameData> _gamedata);
	virtual ~End();
	SceneType Update()final override;
	void Draw() const final override;

};