#pragma once
#include "Game.h"
#include"Text.h"

class Font;
class Text;

class SpaceGame : public Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};



public:

	SpaceGame(Engine* engine) : Game{ engine } {};

	// Inherited via Game
	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;
	void OnPlayerDeath();



private:
	eState m_state{ eState::Title };
	float m_spawnTimer{ 0 };
	float m_spawnTime{ 0 };
	float m_stateTimer{ 0 };

	int m_roundCounter{ 0 };
	int m_enemyCount{ 0 };

	Font* m_font{ nullptr };
	Font* m_fontLarge{ nullptr };

	
	Text* m_textScore{ nullptr };
	Text* m_textLives{ nullptr };
	Text* m_textRound{ nullptr };
	Text* m_textTitle{ nullptr };
};