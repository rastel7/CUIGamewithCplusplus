#include"Scene.h"
#include"Game.h"
#include<memory>

End::End(SPtr<GameData> _gamedata)
	:Scene(_gamedata),
	m_score(_gamedata->GetScore()),
	m_kakusibosu(_gamedata->GetPlayerPtr()->GetTotalMoney()>1500&&_gamedata->GetStageLevel()<=4)
{
	
}

End::~End() {

}
SceneType End::Update() {
	if (m_kakusibosu) {
		auto input = GetKey();
		switch (input)
		{
		case '1':
			return SceneType::Shop;
			break;
		case '2':
			m_kakusibosu = false;
			std::system("cls");
			break;
		default:
			break;
		}
	}
	else {
		auto input = GetKey();
		switch (input)
		{
		case ' ':
			return SceneType::Title;
			break;
		default:
			break;
		}
	}
	return SceneType::None;
}

void End::Draw() const {
	if (m_kakusibosu) {
		DrawKakusibosu();
	}
	else {
		WinerDraw();
	}
}
void End::WinerDraw() const {
	MoveCursor(5, 3);
	printf("優勝おめでとうございます！");
	MoveCursor(7, 5);
	printf("あなたのスコア : %d\n",m_score);
	MoveCursor(9, 3);
	printf("スペースキーでタイトルに戻る");
	DrawOpponent(3, 40);

}

void End::DrawOpponent(uint _y, uint _x) const {
	MoveCursor(_y-1, _x-1);
	printf("対戦相手たち");
	auto opponent = GetGamedataPtr()->GetOpponentProf();
	for (uint i = 0; i < opponent->size(); ++i) {
		if (opponent->at(i).icon == "") {
			break;
		}
		MoveCursor(_y + i*3, _x);
		printf("%s", opponent->at(i).icon.c_str());
		MoveCursor(_y + i*3+1, _x+1);
		printf("%s", opponent->at(i).name.c_str());
	}
}

void End::DrawKakusibosu()  const{
	MoveCursor(5, 6);
	printf("(～￣▽￣)～＜やんのか");
	MoveCursor(6, 3);
	printf("店員さんがあなたに話があるようです");
	MoveCursor(8, 3);
	printf("1:戦う 2:戦わない");
}