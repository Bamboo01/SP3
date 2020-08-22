#pragma once
#include <string>
#include "glm.hpp"

struct Unit
{
	enum UnitType // The Unit 
	{
		DEFAULT = 0,
		// Units BELOW this category except for WALL, are able to attack, as such set all base stats
		NORMAL = 1,
		TANK = 2,
		RANGE = 3,
		TOWER = 4,
		WALL = 5,
		// Units BELOW this category are not able to attack, as such set base stats only for level, health, defense, set damage and attack speed as 0
		NEXUS = 6,			// Player/enemy main base, produce units
		GENERATOR = 7,		// Generate resources for player
		LAB = 8,			// Level units up
		PROJECTILE = 9,
		NUM_TYPE
	};

	enum UnitFaction
	{
		UNDEFINED = 0,
		PLAYER = 1,
		ENEMY = 2,
	};

	std::string name; // Name of unit
	int level; // Level of Unit, other statistics will scale accordingly to level
	float health; // The maximum amount of net damage a unit can receive
	float damage; // The amount of damage the unit can inflict on enemy units
	float defense; // An amount that will mitigate the percentage of damage received
	float attackRange; // The minimum distance for the unit to attack
	float attackSpeed; // The interval between attacks for unit
	float mass; // Reference mass used in colliderSystem
	glm::vec3 colliderScale; // Reference colliderScale used in colliderSystem
	bool active; // A boolean to check whether the unit is active or not, if it isn't active it won't be rendered/updated
	double delay; // A double to keep track of attack resets
	Entity target; // Current targeted enemy
	UnitType unitType; // The type of unit
	UnitFaction unitFaction; // The side/faction which the unit belongs to

	Entity originUnit; // (PROJECTILE ONLY!) The unit that shot the projectile, it could be tower or ranged :D
	Entity targetUnit; // (PROJECTILE ONLY!) The unit that is being traced by the projectile

	int FlowFieldCost;	// Check the cost value of this unit
	int StandingGridCost; // Check the grid that the unit is at cost

	glm::vec2 nextGrid = glm::vec2(-1,-1);	//Store next grid here

	glm::vec3 velocity;	// Velocity of the unit

	Unit()
		: name("Default")
		, level(1)
		, health(0)
		, damage(0)
		, defense(0)
		, attackSpeed(0)
		, mass(1)
		, colliderScale(glm::vec3(1, 1, 1))
		, active(false)
		, target(UINT_MAX)
		, unitType(UnitType::DEFAULT)
		, unitFaction(UnitFaction::UNDEFINED)
		, originUnit(UINT_MAX)
		, targetUnit(UINT_MAX)
		, FlowFieldCost(0)
		, StandingGridCost(0)
		, velocity(0)
	{
	}

	Unit(std::string name, int level, int basehealth, int damage, int defense, float attackspeed, UnitType type, int flowfieldcost = 0, int StandingGridCost = 0, int vel = 0)
		: name(name)
		, level(level)
		, health((basehealth * 4 * level) / 100 + level + 10)
		, damage((damage * 4 * level) / 100 + 5)
		, defense((defense * 4 * level) / 100 + 5)
		, attackSpeed(attackspeed)
		, unitType(type)
		, FlowFieldCost(flowfieldcost)
		, StandingGridCost(StandingGridCost)
		,velocity(vel)

	{
	}

};