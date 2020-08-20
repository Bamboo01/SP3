#pragma once
#include <string>

struct Unit
{
	std::string Name;

	// Base stats
	int Level;			// Unit’s level will affect how much health, damage and defense a unit have
	int Health;			// The amount of damage a unit can take before it dies
	int Damage;			// The amount of damage a unit can inflict on the enemy units
	int Defense;		// Mitigates a percentage of the damage the unit takes
	float AttackSpeed;	// The interval between attacks for the unit

	enum UnitTypes // This is arrange in a way to know what is rendered out for each unit when selected
	{
		START = 0,

		// Units BELOW this category except for WALL, are able to attack, as such set all base stats

		NORMALUNIT,
		TANKUNIT,
		RANGEUNIT,
		TOWER,
		WALL,

		// Units BELOW this category are not able to attack, as such set base stats only for level, health, defense, set damage and attack speed as 0

		NEXUS,			// Player/enemy main base, produce units
		GENERATOR,		// Generate resources for player
		LAB,			// Level units up
		END
	};

	UnitTypes unittype;

	Unit()
		: Name("")
		, Level(0)
		, Health(0)
		, Damage(0)
		, Defense(0)
		, AttackSpeed(0)
		, unittype(Unit::START)
	{
	}

	// Max base health is 150
	// Max base damage and defense is 100
	// Calculation for health = (basehealth * 4 * level) / 100 + level + 10
	// Calculation for damage/defense = (basedamage/basedefense * 4 * level) / 100 + 5
	Unit(std::string name, int level, int basehealth, int damage, int defense, float attackspeed, UnitTypes type)
		: Name(name)
		, Level(level)
		, Health((basehealth * 4 * level) / 100 + level + 10)
		, Damage((damage * 4 * level) / 100 + 5)
		, Defense((defense * 4 * level) / 100 + 5)
		, AttackSpeed(attackspeed)
		, unittype(type)
	{
	}

	// Add functions for updating stats when taking damage

};