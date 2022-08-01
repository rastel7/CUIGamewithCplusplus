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
			log = "最大HPが25アップしました！";
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
			log = "ATKが10アップしました！";
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
			log = "HP回復アイテムを入手しました！";
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
			log = "HPが全回復した！";
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
			log = "毎ターン最大HPが" + std::to_string(GetGamedataPtr()->GetPlayerPtr()->GetCHeal()) + "上昇するようになった！";
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
			log = "毎ターンATKが" + std::to_string(GetGamedataPtr()->GetPlayerPtr()->GetCAtk()) + "上昇するようになった！";
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
	printf("□お店");

	GetGamedataPtr()->GetPlayerPtr()->Draw(PLAYER_DEFAULT_Y, PLAYER_DEFAULT_X);
	m_clerk->Draw(PLAYER_DEFAULT_Y, OPPONENT_DEFAULT_X);
	const uint Y = 15,X=3;
	MoveCursor(Y-1, X-1);
	printf("・商品一覧");
	//各商品の名前と値段を書く
	MoveCursor(Y, X);
	EraseLine();
	printf("1:HPアップ(最大値25増加)                 :%d円", GetGamedataPtr()->m_shopbuycount.hpup*m_mul[0]+m_defaultvalue[0]);
	MoveCursor(Y+1, X);
	EraseLine();
	printf("2:ATKアップ(10増加)                      :%d円", GetGamedataPtr()->m_shopbuycount.atkup * m_mul[1] + m_defaultvalue[1]);
	MoveCursor(Y+2, X);
	EraseLine();
	printf("3:HP回復アイテム(1個増加)                :%d円", GetGamedataPtr()->m_shopbuycount.healup * m_mul[2] + m_defaultvalue[2]);
	MoveCursor(Y+3, X);
	EraseLine();
	printf("4:宿屋(HP全回復)                         :%d円", GetGamedataPtr()->m_shopbuycount.heal * m_mul[3] + m_defaultvalue[3]);
	MoveCursor(Y + 4, X);
	EraseLine();
	printf("5:継続回復(毎ターンごとに最大HPが5上昇)  :%d円", GetGamedataPtr()->m_shopbuycount.continueheal * m_mul[4] + m_defaultvalue[4]);
	MoveCursor(Y + 5, X);
	EraseLine();
	printf("6:継続強化(毎ターンごとにATKが1上昇)     :%d円", GetGamedataPtr()->m_shopbuycount.continueatkup * m_mul[5] + m_defaultvalue[5]);

	MoveCursor(Y + 7, X);
	EraseLine();
	printf("%s           \n", log.c_str());
	MoveCursor(Y + 9, X);
	EraseLine();
	printf("あなたの所持金:\033[33m %d円 \033[m",GetGamedataPtr()->GetPlayerPtr()->GetMoney());
	MoveCursor(Y + 10,X);
	EraseLine();
	printf("あなたの選択肢");
	MoveCursor(Y + 11, X);
	EraseLine();
	printf("1:HPアップ 2:ATKアップ 3:HP回復アイテム 4:宿屋 5:継続回復 6:継続強化 スペースキー:次の試合へ進む");
}

void Shop::ChangeClerkDialogue(const std::string& _dialog) {
	m_clerk->ChangeIcon("(～￣▽￣)～＜"+_dialog);
}
void Shop::ChangeClerkDialogue() {
	auto rand = GetRandomFloat();
	if (rand <= 0.3f) {
		ChangeClerkDialogue("ありがとうございました～            ");
	}
	else if (rand <= 0.6f) {
		ChangeClerkDialogue("もっと買ってくださいね～               ");
	}
	else {
		ChangeClerkDialogue("お金は使わないと紙束ですよ～           ");
	}
}