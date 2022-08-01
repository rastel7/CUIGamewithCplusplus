#include"Character.h"
#include<cmath>
void Character::SetParameter(CharacterType _ctype) {
	m_healitem = 0;
	m_money = 0;
	m_totalmoney = 0;
	m_hpchange = 0;
	m_cheal = 0;
	m_catk = 0;
	switch (_ctype)
	{
	case CharacterType::Player:
		m_maxhp = 100;
		m_attack = 30;
		m_name = "‚ ‚È‚½";
		m_icon = "( OÍOj";
		m_healitem = 3;
		break;
	case CharacterType::Clerk:
		m_maxhp = 999;
		m_attack = 120;
		m_name = "“Xˆõ";
		m_icon = "(`P¤P)`ƒ‚¢‚ç‚Á‚µ‚á‚¢‚Ü‚¹`";
		m_healitem = 0;
		m_money = 300;
		break;
	case CharacterType::Enemy1:
		m_maxhp = 70;
		m_attack = 30;
		m_money = 100;
		m_name = "‚´‚±‚«‚á‚ç‚P";
		m_icon = "(OƒÖ O)";
		break;
	case CharacterType::Enemy2:
		m_maxhp = 150;
		m_attack = 40;
		m_money = 260;
		m_name = "‚³‚¢‚½‚ÜƒAƒŠ[ƒi‚ğ‚Á‚Ä‚¢‚Ü‚·";
		m_icon = "ƒĞ(^_^)";
		break;
	case CharacterType::Enemy3:
		m_maxhp = 210;
		m_attack = 35;
		m_money = 280;
		m_name = "‚Í‚¿‚İ‚Â‚Ì‘ƒŒŠ";
		m_icon = "_:(L< `v Ú):";
		break;
	case CharacterType::Enemy4:
		m_maxhp = 250;
		m_attack = 55;
		m_money = 510;
		m_name = "O‚Âq";
		m_icon = "(@ƒÃ:)(@ƒÃ:)(@ƒÃ:)";
		break;
	case CharacterType::Enemy5:
		m_maxhp = 200;
		m_attack = 60;
		m_money = 500;
		m_name = "gccƒ}ƒ“";
		m_icon = "(gcc)";
		break;
	case CharacterType::Enemy6:
		m_maxhp = 450;
		m_attack = 35;
		m_money = 480;
		m_name = "7Š„‚ª‚â‚³‚µ‚³";
		m_icon = "S(—Ü[Ü—)ƒm";
		break;
	case CharacterType::Enemy7:
		m_maxhp = 500;
		m_attack = 70;
		m_money = 600;
		m_name = "‹†‹É‚Ìƒ‰ƒXƒ{ƒX";
		m_icon = "(LK„ƒ_KMœ)";
		break;
	default:
		m_maxhp = 70;
		m_attack = 30;
		m_money = 100;
		m_name = "‚´‚±‚«‚á‚ç‚P";
		m_icon = "(OƒÖ O)";
		break;
	}
	m_hpchange = 0;
	m_prevhp = m_maxhp;
	m_hp = m_maxhp;
}

void Character::SetParameter(uint _stagenum) {
	switch (_stagenum)
	{
	case 1:
		SetParameter(CharacterType::Enemy1);
		break;
	case 2:
		{
			float rand = GetRandomFloat();
			if (rand < 0.5f) {
				SetParameter(CharacterType::Enemy2);
			}
			else {
				SetParameter(CharacterType::Enemy3);
			}
		}
		break;
	case 3:
	{
		float rand = GetRandomFloat();
		if (rand <= 0.33f) {
			SetParameter(CharacterType::Enemy4);
		}
		else if(rand<=0.66f) {
			SetParameter(CharacterType::Enemy5);
		}
		else {
			SetParameter(CharacterType::Enemy6);
		}
	}
		break;
	case 4:
		SetParameter(CharacterType::Enemy7);
		break;
	case 5:
		SetParameter(CharacterType::Clerk);
		break;
	default:
		SetParameter(CharacterType::Enemy1);
		break;
	}
}

void Character::Draw(uint y, uint x) const {
	//ƒJ[ƒ\ƒ‹‰ŠúˆÊ’u‚ÉˆÚ“®
	printf("\x1b[%d;%dH",y,x);
	{//Šç‚Æ–¼‘O‚ğ‹Lq
		if (m_hp <= 0) {
			printf("\x1b[%d;%dH", y - 1, x);
			printf("  ¼O½");
		}
		printf("\x1b[%d;%dH", y, x);
		printf("%s   ", m_icon.c_str());
		printf("\x1b[%d;%dH", y + 1, x);
		printf("%s   ", m_name.c_str()); 
	}
	{//HP‚È‚Ç‚ÌƒXƒe[ƒ^ƒX‚ğ•\¦
		if (m_hpchange != 0) {
			//HP‚Ì•Ï“®‚ª‚ ‚é‚È‚ç‚ÎC·•ª‚ğ•\¦
			printf("\x1b[%d;%dH", y + 2, x);
			std::string colorinit, colorerase;
			if (m_hpchange < 0) {
				colorinit = "\033[31m";
				colorerase = "\033[m";
			}
			else {
				colorinit = "\033[32m";
				colorerase = "\033[m";
			}
			printf("%s %d  %s",colorinit.c_str(), m_hpchange,colorerase.c_str());

		}
		if (m_hp <= 0) {
			printf("\033[31m");
		}
		printf("\x1b[%d;%dH", y+3, x);
		printf("HP:%d/%d   ", m_hp,m_maxhp);
		if (m_hp <= 0) {
			printf("\033[m");
		}
		printf("\x1b[%d;%dH", y + 4, x);
		printf("ATK:%d   ", m_attack);
		printf("\x1b[%d;%dH", y + 5, x);
		printf("HEAL:%d   ", m_healitem);
	}
}

void Character::Update() {
	if (m_hp <= 0) {
		m_hp = 0;
		m_name = "•‰‚¯‚¿‚á‚Á‚½";
	}
	if (m_prevhp != m_hp) {
		m_hpchange = m_hp - m_prevhp;
		m_prevhp = m_hp;
	}
}
int Character::DoHeal() {
	if (m_healitem <= 0)return -1;
	int healHP =std::abs(m_maxhp-m_hp);
	m_hp = m_maxhp;
	m_healitem--;
	UpdateContinueSkiil();
	return healHP;
}
std::string Character::GetName() const {
	return m_name;
}
std::string Character::GetIcon() const {
	return m_icon;
}
std::string Character::DoAttack(Character* _target) {
	auto random = GetRandomFloat();
	int damage = static_cast<int>(m_attack * (0.95f + random / 20.0f));
	_target->DecreaseHP(damage);
	UpdateContinueSkiil();
	std::string log = GetName() + " ‚Í " + _target->GetName() + " ‚É " + std::to_string(damage) + " ‚Ìƒ_ƒ[ƒW‚ğ—^‚¦‚½I";
	return log;
}
void Character::DecreaseHP(int _num) {
	m_hp -= _num;
}
int Character::GetHP() const {
	return m_hp;
}
int Character::GetMoney() const { 
	return m_money; 
}

void Character::AddMoney(int _money)
{
	m_totalmoney += _money;
	m_money += _money;
}
void Character::DecreaseMoney(int _money) {
	m_money -= _money;
}
void Character::IncreaseMAXHP(int _hp) {
	m_maxhp += _hp;
	m_hp += _hp;
}
void Character::IncreaseATK(int _atk) {
	m_attack += _atk;
}
void Character::IncreaseHEAL(int _heal) {
	m_healitem += _heal;
}
void Character::RecoveryHP() {
	m_hp = m_maxhp;
}

void Character::ChangeIcon(const std::string& _icon) {
	m_icon = _icon;
}
void Character::ResetPrevHP() {
	m_prevhp = m_hp;
	m_hpchange = 0;
}
void Character::AddCHeal(int _n) {
	m_cheal += _n;
}

void Character::AddCAtk(int _n) {
	m_catk += _n;
}
int Character::GetTotalMoney() const {
	return m_totalmoney;
}

void Character::UpdateContinueSkiil() {
	m_hp += m_cheal;
	m_maxhp += m_cheal;
	m_attack += m_catk;
}

int Character::GetCHeal() const {
	return m_cheal;
}

int Character::GetCAtk()const {
	return m_catk;
}