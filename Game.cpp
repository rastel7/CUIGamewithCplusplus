#include"Game.h"
#include"Character.h"
GameData::GameData():m_character_alloc(std::make_unique<PoolAllocator<Character>>()),m_stagelevel(1), m_opponents_prof(), m_opponents_proof_top(0) {
	m_player = m_character_alloc->Alloc();
	m_player->SetParameter(CharacterType::Player);
}
GameData::~GameData() {
	m_character_alloc->Free(m_player);
	m_player = nullptr;
}

uint GameData::GetStageLevel() const {
	return m_stagelevel;
}
Character* GameData::GetPlayerPtr() const {
	return m_player;
}
void GameData::IncrementStageLevel() {
	m_stagelevel++;
}

void GameData::AddOpponent(std::string const& _name , std::string const& _icon) {
	if (m_opponents_proof_top >= m_opponents_prof.size())return;
	m_opponents_prof[m_opponents_proof_top].icon = _icon;
	m_opponents_prof[m_opponents_proof_top].name = _name;

	m_opponents_proof_top++;
}
int GameData::GetScore() const {
	return int(m_player->GetTotalMoney() + m_player->GetMoney() * 1.5);
}
void GameData::ResetData() {
	GetPlayerPtr()->SetParameter(CharacterType::Player);
	m_shopbuycount = ShopBuyCount();
	m_opponents_proof_top = 0;
	m_opponents_prof= std::array<OpponentNameandIcon, 16>();
	m_stagelevel = 1;

}
std::array<GameData::OpponentNameandIcon, 16> const* GameData::GetOpponentProf() const {
	auto ret = &m_opponents_prof;
	return ret;
}

void Game::Update() {
	do {
		m_scene->Draw();
		SceneType next_scene =  m_scene->Update();
		if (next_scene != SceneType::None) {
			LoadScene(next_scene);
		}
	} while (not(m_scene->IsEndGame()));
}

Game::Game():m_gamedata(std::make_shared<GameData>()){
	m_scene=std::make_unique<Title>(m_gamedata);
}

void Game::Wait() {
	std::this_thread::sleep_for(std::chrono::milliseconds(WAITTIME));
}
void Game::LoadScene(SceneType _scenetype) {
	std::system("cls");
	switch (_scenetype)
	{
	case SceneType::Title:
		m_scene = std::make_unique<Title>(m_gamedata);
		break;
	case SceneType::Stage:
		m_scene = std::make_unique<Stage>(m_gamedata);
		break;
	case SceneType::Shop:
		m_scene = std::make_unique<Shop>(m_gamedata);
		break;
	case SceneType::End:
		m_scene = std::make_unique<End>(m_gamedata);
		break;
	case SceneType::None:
		break;
	}
}