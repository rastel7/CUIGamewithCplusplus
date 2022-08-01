#include"Scene.h"
#include"Game.h"
Shop::Shop(SPtr<GameData> _gamedata) :Scene(_gamedata), m_defaultvalue({ 40,40,30,50,40,60 }), m_mul({ { 10,10,10,10,10,10 } }) {
	m_clerk = GetGamedataPtr()->m_character_alloc->Alloc();
	m_clerk->SetParameter(CharacterType::Clerk);
}

Shop::~Shop() {
	GetGamedataPtr()->m_character_alloc->Free(m_clerk);
	m_clerk = nullptr;
}

SceneType Shop::Update() {
	auto input = Scene::GetKey();
	int need_money = 0;
	
	switch (input)
	{
	case '1':
		need_money = GetGamedataPtr()->m_shopbuycount.hpup * m_mul[0] + m_defaultvalue[0];
		if (need_money <= GetGamedataPtr()->GetPlayerPtr()->GetMoney()) {
			log = "�ő�HP��25�A�b�v���܂����I";
			GetGamedataPtr()->GetPlayerPtr()->DecreaseMoney(need_money);
			GetGamedataPtr()->m_shopbuycount.hpup++;
			GetGamedataPtr()->GetPlayerPtr()->IncreaseMAXHP(25);
			ChangeClerkDialogue();
		}
		else {
			log = m_notenoguhmoney_log;
		}
		break;
	case '2':
		need_money = GetGamedataPtr()->m_shopbuycount.atkup * m_mul[1] + m_defaultvalue[1];
		if (need_money <= GetGamedataPtr()->GetPlayerPtr()->GetMoney()) {
			log = "ATK��10�A�b�v���܂����I";
			GetGamedataPtr()->GetPlayerPtr()->DecreaseMoney(need_money);
			GetGamedataPtr()->m_shopbuycount.atkup++;
			GetGamedataPtr()->GetPlayerPtr()->IncreaseATK(10);
			ChangeClerkDialogue();
		}
		else {
			log = m_notenoguhmoney_log;
		}
		break;
	case '3':
		need_money = GetGamedataPtr()->m_shopbuycount.healup * m_mul[2] + m_defaultvalue[2];
		if (need_money <= GetGamedataPtr()->GetPlayerPtr()->GetMoney()) {
			log = "HP�񕜃A�C�e������肵�܂����I";
			GetGamedataPtr()->GetPlayerPtr()->DecreaseMoney(need_money);
			GetGamedataPtr()->m_shopbuycount.healup++;
			GetGamedataPtr()->GetPlayerPtr()->IncreaseHEAL(1);
			ChangeClerkDialogue();
		}
		else {
			log = m_notenoguhmoney_log;
		}
		break;
	case '4':
		need_money = GetGamedataPtr()->m_shopbuycount.heal * m_mul[3] + m_defaultvalue[3];
		if (need_money <= GetGamedataPtr()->GetPlayerPtr()->GetMoney()) {
			log = "HP���S�񕜂����I";
			GetGamedataPtr()->GetPlayerPtr()->DecreaseMoney(need_money);
			GetGamedataPtr()->m_shopbuycount.heal++;
			GetGamedataPtr()->GetPlayerPtr()->RecoveryHP();
			ChangeClerkDialogue();
		}
		else {
			log = m_notenoguhmoney_log;
		}
		break;
	case '5':
		need_money = GetGamedataPtr()->m_shopbuycount.continueheal * m_mul[4] + m_defaultvalue[4];
		if (need_money <= GetGamedataPtr()->GetPlayerPtr()->GetMoney()) {
			GetGamedataPtr()->GetPlayerPtr()->DecreaseMoney(need_money);
			GetGamedataPtr()->m_shopbuycount.continueheal++;
			GetGamedataPtr()->GetPlayerPtr()->AddCHeal(5);
			log = "���^�[���ő�HP��" + std::to_string(GetGamedataPtr()->GetPlayerPtr()->GetCHeal()) + "�㏸����悤�ɂȂ����I";
			ChangeClerkDialogue();
		}
		else {
			log = m_notenoguhmoney_log;
		}
		break;
	case '6':
		need_money = GetGamedataPtr()->m_shopbuycount.continueheal * m_mul[5] + m_defaultvalue[5];
		if (need_money <= GetGamedataPtr()->GetPlayerPtr()->GetMoney()) {
			GetGamedataPtr()->GetPlayerPtr()->DecreaseMoney(need_money);
			GetGamedataPtr()->m_shopbuycount.continueatkup++;
			GetGamedataPtr()->GetPlayerPtr()->AddCAtk(1);
			log = "���^�[��ATK��" + std::to_string(GetGamedataPtr()->GetPlayerPtr()->GetCAtk()) + "�㏸����悤�ɂȂ����I";
			ChangeClerkDialogue();
		}
		else {
			log = m_notenoguhmoney_log;
		}
		break;
	case ' ':
		need_money = 0;
		GetGamedataPtr()->IncrementStageLevel();
		return SceneType::Stage;
		break;
	default:
		break;
	}
	GetGamedataPtr()->GetPlayerPtr()->Update();
	return SceneType::None;
}

void Shop::Draw() const {
	MoveCursor(PLAYER_DEFAULT_Y - 3, 10);
	EraseLine();
	printf("�����X");

	GetGamedataPtr()->GetPlayerPtr()->Draw(PLAYER_DEFAULT_Y, PLAYER_DEFAULT_X);
	m_clerk->Draw(PLAYER_DEFAULT_Y, OPPONENT_DEFAULT_X);
	const uint Y = 15,X=3;
	MoveCursor(Y-1, X-1);
	printf("�E���i�ꗗ");
	//�e���i�̖��O�ƒl�i������
	MoveCursor(Y, X);
	EraseLine();
	printf("1:HP�A�b�v(�ő�l25����)                 :%d�~", GetGamedataPtr()->m_shopbuycount.hpup*m_mul[0]+m_defaultvalue[0]);
	MoveCursor(Y+1, X);
	EraseLine();
	printf("2:ATK�A�b�v(10����)                      :%d�~", GetGamedataPtr()->m_shopbuycount.atkup * m_mul[1] + m_defaultvalue[1]);
	MoveCursor(Y+2, X);
	EraseLine();
	printf("3:HP�񕜃A�C�e��(1����)                :%d�~", GetGamedataPtr()->m_shopbuycount.healup * m_mul[2] + m_defaultvalue[2]);
	MoveCursor(Y+3, X);
	EraseLine();
	printf("4:�h��(HP�S��)                         :%d�~", GetGamedataPtr()->m_shopbuycount.heal * m_mul[3] + m_defaultvalue[3]);
	MoveCursor(Y + 4, X);
	EraseLine();
	printf("5:�p����(���^�[�����Ƃɍő�HP��5�㏸)  :%d�~", GetGamedataPtr()->m_shopbuycount.continueheal * m_mul[4] + m_defaultvalue[4]);
	MoveCursor(Y + 5, X);
	EraseLine();
	printf("6:�p������(���^�[�����Ƃ�ATK��1�㏸)     :%d�~", GetGamedataPtr()->m_shopbuycount.continueatkup * m_mul[5] + m_defaultvalue[5]);

	MoveCursor(Y + 7, X);
	EraseLine();
	printf("%s           \n", log.c_str());
	MoveCursor(Y + 9, X);
	EraseLine();
	printf("���Ȃ��̏�����:\033[33m %d�~ \033[m",GetGamedataPtr()->GetPlayerPtr()->GetMoney());
	MoveCursor(Y + 10,X);
	EraseLine();
	printf("���Ȃ��̑I����");
	MoveCursor(Y + 11, X);
	EraseLine();
	printf("1:HP�A�b�v 2:ATK�A�b�v 3:HP�񕜃A�C�e�� 4:�h�� 5:�p���� 6:�p������ �X�y�[�X�L�[:���̎����֐i��");
}

void Shop::ChangeClerkDialogue(const std::string& _dialog) {
	m_clerk->ChangeIcon("(�`�P���P)�`��"+_dialog);
}
void Shop::ChangeClerkDialogue() {
	auto rand = GetRandomFloat();
	if (rand <= 0.3f) {
		ChangeClerkDialogue("���肪�Ƃ��������܂����`            ");
	}
	else if (rand <= 0.6f) {
		ChangeClerkDialogue("�����Ɣ����Ă��������ˁ`               ");
	}
	else {
		ChangeClerkDialogue("�����͎g��Ȃ��Ǝ����ł���`           ");
	}
}