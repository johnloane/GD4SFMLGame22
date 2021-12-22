#include "Player.hpp"
#include "Aircraft.hpp"
#include <algorithm>

struct AircraftMover
{
	AircraftMover(float vx, float vy) : velocity(vx, vy)
	{
		
	}

	void operator()(Aircraft& aircraft, sf::Time) const
	{
		aircraft.Accelerate(velocity * aircraft.GetMaxSpeed());
	}

	sf::Vector2f velocity;
};

Player::Player() : m_current_mission_status(MissionStatus::kMissionRunning)
{
	//Set initial key bindings
	m_key_binding[sf::Keyboard::A] = PlayerAction::kMoveLeft;
	m_key_binding[sf::Keyboard::D] = PlayerAction::kMoveRight;
	m_key_binding[sf::Keyboard::W] = PlayerAction::kMoveUp;
	m_key_binding[sf::Keyboard::S] = PlayerAction::kMoveDown;
	m_key_binding[sf::Keyboard::Space] = PlayerAction::kFire;
	m_key_binding[sf::Keyboard::M] = PlayerAction::kLaunchMissile;

	//Set initial action bindings
	InitialiseActions();

	//Assign all categories to the player's aircraft
	for(auto& pair : m_action_binding)
	{
		pair.second.category = Category::kPlayerAircraft;
	}
}


void Player::HandleEvent(const sf::Event& event, CommandQueue& commands)
{
	if(event.type == sf::Event::KeyPressed)
	{
		auto found = m_key_binding.find(event.key.code);
		if(found != m_key_binding.end() && !IsRealtimeAction(found->second))
		{
			commands.Push(m_action_binding[found->second]);
		}
	}
}

void Player::HandleRealtimeInput(CommandQueue& commands)
{
	//Check if any keybinding keys are pressed
	for(auto pair: m_key_binding)
	{
		if(sf::Keyboard::isKeyPressed(pair.first) && IsRealtimeAction(pair.second))
		{
			commands.Push(m_action_binding[pair.second]);
		}
	}
}

void Player::AssignKey(PlayerAction action, sf::Keyboard::Key key)
{
	//Remove all keys that are already bound to action
	for(auto itr = m_key_binding.begin(); itr != m_key_binding.end();)
	{
		if(itr->second == action)
		{
			m_key_binding.erase(itr++);
		}
		else
		{
			++itr;
		}
	}
	m_key_binding[key] = action;
}

sf::Keyboard::Key Player::GetAssignedKey(PlayerAction action) const
{
	for(auto pair : m_key_binding)
	{
		if(pair.second == action)
		{
			return pair.first;
		}
	}
	return sf::Keyboard::Unknown;
}

void Player::SetMissionStatus(MissionStatus status)
{
	m_current_mission_status = status;
}

MissionStatus Player::GetMissionStatus() const
{
	return m_current_mission_status;
}

void Player::InitialiseActions()
{
	const float player_speed = 200.f;

	m_action_binding[PlayerAction::kMoveLeft].action = DerivedAction<Aircraft>(AircraftMover(-1, 0.f));
	m_action_binding[PlayerAction::kMoveRight].action = DerivedAction<Aircraft>(AircraftMover(+1, 0.f));
	m_action_binding[PlayerAction::kMoveUp].action = DerivedAction<Aircraft>(AircraftMover(0.f, -1));
	m_action_binding[PlayerAction::kMoveDown].action = DerivedAction<Aircraft>(AircraftMover(0, 1));

	m_action_binding[PlayerAction::kFire].action = DerivedAction<Aircraft>([](Aircraft& a, sf::Time
		)
	{
		a.Fire();
	});

	m_action_binding[PlayerAction::kLaunchMissile].action = DerivedAction<Aircraft>([](Aircraft& a, sf::Time
		)
	{
		a.LaunchMissile();
	});
}

bool Player::IsRealtimeAction(PlayerAction action)
{
	switch(action)
	{
	case PlayerAction::kMoveLeft:
	case PlayerAction::kMoveRight:
	case PlayerAction::kMoveUp:
	case PlayerAction::kMoveDown:
	case PlayerAction::kFire:
		return true;
	default:
		return false;
	}
}
