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
	void UpdateContinueSkiil();//���^�[�����ɃX�e�[�^�X�ύX���s���X�L���̏���
public:
	inline Character():m_attack(0),m_hp(0),m_maxhp(0), m_healitem(0), m_prevhp(0), m_hpchange(0), m_money(0),m_totalmoney(0),m_cheal(0),m_catk(0) {}
	inline ~Character(){}
	// CharacterType����p�����[�^��ݒ�
	void SetParameter(CharacterType _ctype);
	//�X�e�[�W�i���o�[��^���邱�Ƃő���̃p�����[�^��ݒ肷��
	void SetParameter(uint _stagenum);
	//������W��n���ƃL�����N�^�[���X��`�悷��
	void Draw(uint y,uint x)  const;
	void Update();//HP�ϓ��Ȃǂ̃X�e�[�^�X�ύX�ɂ���āC�A�C�R���̕ϓ����s��
	int DoHeal();//�񕜂ł����ꍇ�͉񕜂���HP�̐��l��,�񕜂ł��Ȃ������ꍇ��-1��Ԃ�
	std::string DoAttack(Character* _target);//���O�̕������Ԃ�
	//�Q�b�^�[
	std::string GetName() const;
	std::string GetIcon() const;
	int GetHP() const;
	int GetMoney() const;
	int GetTotalMoney() const;
	int GetCHeal() const;
	int GetCAtk() const;
	//�Z�b�^�[
	void DecreaseHP(int _num);
	void IncreaseMAXHP(int _hp);
	void DecreaseMoney(int _money);
	void IncreaseATK(int _atk);
	void IncreaseHEAL(int _heal);
	void AddMoney(int _money);
	void RecoveryHP();//���X�ł̂ݎg�p
	void ChangeIcon(const std::string & _icon);
	void ResetPrevHP();
	void AddCHeal(int _n);
	void AddCAtk(int _n);
};