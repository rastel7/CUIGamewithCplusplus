#pragma once
#include"Def.h"
#include<string>
enum class CharacterType{
	Player,
	Clerk,
	Enemy1,
	Enemy2,
	Enemy3,
	Enemy4,
	Enemy5,
	Enemy6,
	Enemy7,
};
class Character {
	int m_maxhp,m_hp, m_attack,m_healitem,m_prevhp,m_hpchange,m_money,m_totalmoney,m_cheal,m_catk;
	std::string m_name,m_icon;
	void UpdateContinueSkiil();//毎ターン毎にステータス変更を行うスキルの処理
public:
	inline Character():m_attack(0),m_hp(0),m_maxhp(0), m_healitem(0), m_prevhp(0), m_hpchange(0), m_money(0),m_totalmoney(0),m_cheal(0),m_catk(0) {}
	inline ~Character(){}
	// CharacterTypeからパラメータを設定
	void SetParameter(CharacterType _ctype);
	//ステージナンバーを与えることで相手のパラメータを設定する
	void SetParameter(uint _stagenum);
	//左上座標を渡すとキャラクター諸々を描画する
	void Draw(uint y,uint x)  const;
	void Update();//HP変動などのステータス変更によって，アイコンの変動を行う
	int DoHeal();//回復できた場合は回復したHPの数値を,回復できなかった場合は-1を返す
	std::string DoAttack(Character* _target);//ログの文字列を返す
	//ゲッター
	std::string GetName() const;
	std::string GetIcon() const;
	int GetHP() const;
	int GetMoney() const;
	int GetTotalMoney() const;
	int GetCHeal() const;
	int GetCAtk() const;
	//セッター
	void DecreaseHP(int _num);
	void IncreaseMAXHP(int _hp);
	void DecreaseMoney(int _money);
	void IncreaseATK(int _atk);
	void IncreaseHEAL(int _heal);
	void AddMoney(int _money);
	void RecoveryHP();//お店でのみ使用
	void ChangeIcon(const std::string & _icon);
	void ResetPrevHP();
	void AddCHeal(int _n);
	void AddCAtk(int _n);
};