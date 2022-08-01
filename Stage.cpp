#include"Scene.h"
#include"Game.h"
Stage::Stage(SPtr<GameData> _gamedata) :Scene(_gamedata), m_turn(0) {
	m_enemy = GetGamedataPtr()->m_character_alloc->Alloc();
	m_enemy->SetParameter(GetGamedataPtr()->GetStageLevel());
	GetGamedataPtr()->AddOpponent(m_enemy->GetName(),m_enemy->GetIcon());
	m_log[0] = "�퓬�J�n�I";
	GetPlayer()->ResetPrevHP();
}

Stage::~Stage() {
	GetGamedataPtr()->m_character_alloc->Free(m_enemy);
	m_enemy = nullptr;
}

Character* Stage::GetPlayer() const {
	return GetGamedataPtr()->GetPlayerPtr();
}
Character* Stage::GetEnemy() const {
	return m_enemy;
}

void Stage::Draw()const {
	const uint DEFAULT_X = 10;
	MoveCursor(PLAYER_DEFAULT_Y-3, DEFAULT_X);
	EraseLine();
	printf("��");
	int stagelevel = GetGamedataPtr()->GetStageLevel();
	if (stagelevel == 3) {
		printf("��������");
	}
	else if (stagelevel == 4) {
		printf("������");
	}
	else if (stagelevel == 5) {
		printf("�^�E������");
	}else{
		printf("��%d���", stagelevel);
	}
	GetGamedataPtr()->GetPlayerPtr()->Draw(PLAYER_DEFAULT_Y, PLAYER_DEFAULT_X );
	m_enemy->Draw(PLAYER_DEFAULT_Y, OPPONENT_DEFAULT_X);
	if (IsPlayerTurn()) {
		DrawChoices();
	}
	DrawLog();
	if (GetPlayer()->GetHP() <= 0) {
		MoveCursor(PLAYER_DEFAULT_Y+14, DEFAULT_X-7);
		printf("\033[34m �����Ă��܂����c  \033[m");
		MoveCursor(PLAYER_DEFAULT_Y+15, DEFAULT_X-7);
		printf("�X�y�[�X�L�[�Ń^�C�g����ʂ֖߂�");
	}
	if (GetEnemy()->GetHP() <= 0) {
		MoveCursor(PLAYER_DEFAULT_Y+14, DEFAULT_X-7);
		printf("\033[33m �������� \033[m");
		MoveCursor(PLAYER_DEFAULT_Y+15, DEFAULT_X-7);
		printf("%d�~��ɓ��ꂽ", CalcGetMoney());
		MoveCursor(PLAYER_DEFAULT_Y+16, DEFAULT_X-7);
		printf("�X�y�[�X�L�[�Ŏ��֐i��");
	}
}
bool Stage::IsPlayerTurn() const {
	return m_turn % 2==0;
}
SceneType Stage::Update() {
	MoveCursor(19, 3);
	if (GetPlayer()->GetHP() > 0 && GetEnemy()->GetHP() > 0) {
		if (IsPlayerTurn()) {
			auto input = Scene::GetKey();
			switch (input) {
			case '1':
				//�U��
			{
				auto log_str = GetPlayer()->DoAttack(GetEnemy());
				UpdateLog(log_str);
			}
			break;
			case '2':
				//��
			{
				auto healnum = GetPlayer()->DoHeal();
				if (healnum == -1) {
					UpdateLog("�񕜃A�C�e��������܂���I");
					m_turn--;
				}
				else {
					UpdateLog(GetPlayer()->GetName() + " ��HP�� " + std::to_string(healnum) + " �񕜂����I");
				}
			}
			break;
			default:
				UpdateLog("�L�[���͂��s���ł��I");
				m_turn--;
				break;
			}
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			auto log_str = GetEnemy()->DoAttack(GetPlayer());
			UpdateLog(log_str);
		}
		m_turn++;
	}
	else {
		auto input = Scene::GetKey();
		if (input == ' ') {
			if (GetPlayer()->GetHP() <= 0) {
				return SceneType::Title;
			}
			else {
				GetPlayer()->AddMoney(CalcGetMoney());
				int stagelevel = GetGamedataPtr()->GetStageLevel();
				if (stagelevel >= 4) {
					//�N���A��ʂֈڍs
					return SceneType::End;
				}
				return SceneType::Shop;
			}
		}
	}
	GetPlayer()->Update();
	GetEnemy()->Update();
	return SceneType::None;
}

void Stage::DrawChoices() const {
	const uint INIT_Y = 17, INIT_X = 2;
	MoveCursor(INIT_Y, INIT_X);
	printf("�E���Ȃ��̑I����");
	MoveCursor(INIT_Y+1, INIT_X+1);
	printf("1:�U�� 2:��");
}

void Stage::DrawLog() const {
	const uint INIT_Y = 13, INIT_X = 3;
	MoveCursor(INIT_Y - 1, INIT_X - 1);
	EraseLine();
	printf("�E�퓬���ʃ��O");
	for (size_t i = 0; i < m_log.size(); ++i) {
		MoveCursor(INIT_Y+(uint)i, INIT_X);
		EraseLine();
		printf("%s", m_log[i].c_str());
	}
}

void Stage::UpdateLog(const std::string& _message) {
	m_log[2] = m_log[1];
	m_log[1] = m_log[0];
	m_log[0] = _message;
}

int Stage::CalcGetMoney() const{
	int enemy_money = GetEnemy()->GetMoney();
	return std::max<int>(enemy_money, (int)(enemy_money*(2.0f-float(m_turn+1)/ 16.0f)));
}