#include<iostream>
#include <conio.h>
#include <stdexcept>
#include"Scene.h"
#include"Game.h"
#include<Windows.h>
//Title,End�͂��̃t�@�C���ɋL�q
Scene::Scene(SPtr<GameData> _gamedata):o_gamedata(_gamedata) {

}
Scene::~Scene() {

}
void Scene::MoveCursor(uint y, uint x)  const{
	printf("\x1b[%d;%dH", y, x);
}
void Scene::EraseLine() const {
	printf("\033[2K");
}
SPtr<GameData> Scene::GetGamedataPtr() const{
	if (auto ptr = o_gamedata.lock()) {
		return ptr;
	}
	throw std::exception("�Q�[���f�[�^���擾�ł��܂���ł���");
}
bool Scene::IsEndGame() const { return false; }
char Scene::GetKey() {
	int i = _getch();
	return (char)i;
}

Title::Title(SPtr<GameData> _gamedata):Scene(_gamedata), isEnd(false) {

}
Title::~Title() {

}
SceneType Title::Update() {
	auto c = Scene::GetKey();
	if (c=='q') {
		isEnd = true;
	}
	if (c == ' ') {
		GetGamedataPtr()->ResetData();
		return SceneType::Stage;
	}
	std::system("cls");
	return SceneType::None;
}
void Title::Draw() const {
	const uint INIT_Y = 4, INIT_X = 3;
	MoveCursor(INIT_Y, INIT_X);
	printf("----------------------------");
	MoveCursor(INIT_Y+1, INIT_X);
	std::cout << "|�u���Ȃ��v�̐킢          |" << std::endl;
	MoveCursor(INIT_Y+2, INIT_X);
	std::cout << "|q�L�[�ŏI�����܂�         |" << std::endl;
	MoveCursor(INIT_Y+3, INIT_X);
	std::cout << "|�X�y�[�X�L�[�ŊJ�n���܂�  |" << std::endl;
	MoveCursor(INIT_Y+4, INIT_X);
	printf("----------------------------");
}

bool Title::IsEndGame() const {
	return isEnd;
}