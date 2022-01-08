#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include "MusicPlayer.hpp"
#include "Player.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "StateStack.hpp"

class Application
{
public:
	Application();
	void Run();

private:
	void ProcessInput();
	void Update(sf::Time delta_time);
	void Render();
	void UpdateStatistics(sf::Time elapsed_time);
	void RegisterStates();

private:
	sf::RenderWindow m_window;
	Player m_player;

	TextureHolder m_textures;
	FontHolder m_fonts;

	MusicPlayer m_music;

	StateStack m_stack;

	sf::Text m_statistics_text;
	sf::Time m_statistics_updatetime;

	std::size_t m_statistics_numframes;
	static const sf::Time kTimePerFrame;
};

