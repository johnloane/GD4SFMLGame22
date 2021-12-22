#pragma once
#include "Command.hpp"
#include <SFML/Window/Event.hpp>
#include <map>
#include "CommandQueue.hpp"
#include "MissionStatus.hpp"
#include "PlayerAction.hpp"

class Player
{
public:
	Player();
	void HandleEvent(const sf::Event& event, CommandQueue& commands);
	void HandleRealtimeInput(CommandQueue& commands);

	void AssignKey(PlayerAction action, sf::Keyboard::Key key);
	sf::Keyboard::Key GetAssignedKey(PlayerAction action) const;
	void SetMissionStatus(MissionStatus status);
	MissionStatus GetMissionStatus() const;

private:
	void InitialiseActions();
	static bool IsRealtimeAction(PlayerAction action);

private:
	std::map<sf::Keyboard::Key, PlayerAction> m_key_binding;
	std::map<PlayerAction, Command> m_action_binding;
	MissionStatus m_current_mission_status;
};

