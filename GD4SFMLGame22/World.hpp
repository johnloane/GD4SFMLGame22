#pragma once
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Aircraft.hpp"
#include "Layers.hpp"
#include "AircraftType.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <array>
#include <SFML/Graphics/RenderWindow.hpp>

#include "BloomEffect.hpp"
#include "CommandQueue.hpp"


class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderTarget& output_target, FontHolder& font);
	void Update(sf::Time dt);
	void Draw();
	CommandQueue& getCommandQueue();
	bool HasAlivePlayer() const;
	bool HasPlayerReachedEnd() const;

private:
	void LoadTextures();
	void BuildScene();
	void AdaptPlayerPosition();
	void AdaptPlayerVelocity();

	sf::FloatRect GetViewBounds() const;
	sf::FloatRect GetBattlefieldBounds() const;
	void SpawnEnemies();
	void AddEnemy(AircraftType type, float relX, float relY);
	void AddEnemies();
	void GuideMissiles();
	void HandleCollisions();
	void DestroyEntitiesOutsideView();

private:
	struct SpawnPoint
	{
		SpawnPoint(AircraftType type, float x, float y) : m_type(type), m_x(x), m_y(y)
		{
			
		}
		AircraftType m_type;
		float m_x;
		float m_y;
	};
	

private:
	sf::RenderTarget& m_target;
	sf::RenderTexture m_scene_texture;
	sf::View m_camera;
	TextureHolder m_textures;
	FontHolder& m_fonts;
	SceneNode m_scenegraph;
	std::array<SceneNode*, static_cast<int>(Layers::kLayerCount)> m_scene_layers;
	CommandQueue m_command_queue;

	sf::FloatRect m_world_bounds;
	sf::Vector2f m_spawn_position;
	float m_scrollspeed;
	Aircraft* m_player_aircraft;
	std::vector<SpawnPoint> m_enemy_spawn_points;
	std::vector<Aircraft*>	m_active_enemies;

	BloomEffect m_bloom_effect;
};

