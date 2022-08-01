#pragma once

#include <chrono>
#include <thread>
#include"Scene.h"
#include"Def.h"
#include"PoolAllocator.h"
//シーンを跨いで使用したいデータをまとめたクラス
class Character;
class GameData {
	uint m_stagelevel;//ゲームの進行度を保存
	Character* m_player;
	struct OpponentNameandIcon {
		std::string name;
		std::string icon;
		inline OpponentNameandIcon() {
			name.resize(16);
			icon.resize(16);
		}
	};
	int m_opponents_proof_top;
	std::array<OpponentNameandIcon,16> m_opponents_prof;
public:
	struct ShopBuyCount {
		int hpup = 0;
		int atkup = 0;
		int healup = 0;
		int heal = 0;
		int continueheal = 0;
		int continueatkup = 0;
	} m_shopbuycount;
	
	UPtr<PoolAllocator<Character>> m_character_alloc;
	GameData();
	~GameData();
	uint GetStageLevel() const;
	Character* GetPlayerPtr() const;
	void IncrementStageLevel();
	void AddOpponent( std::string const& _name,  std::string const& _icon);
	std::array<OpponentNameandIcon, 16> const* GetOpponentProf() const;
	int GetScore() const;
	void ResetData();
};
class Game {
	UPtr<Scene> m_scene;
	SPtr<GameData> m_gamedata;
	const int WAITTIME =16;
	void Wait();//1フレーム程度待機する
	void LoadScene(SceneType _scenetype);
public:
	Game();
	void Update();

};