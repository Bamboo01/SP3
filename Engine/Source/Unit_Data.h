#pragma once

#include "Unit.h"
#include <string>

// How the statistics are calculated
// Statistic Growth Formula = base statistic + growth statistic x (level - 1) x (additional value + small multiplier x (level - 1))
// To change any unit statistics, just edit the initiated variables such as baseHealth, healthGrowth.. etc
// Refrain from touching the rest

class UNormal : public Unit
{
public:
	UNormal() {}

	UNormal(int unitLevel, UnitFaction unitFact)
	{
		std::string unitName = "Normal";

		float baseHealth = 100;
		float healthGrowth = 20;
		float additionalHealthOffset = 0.7025;
		float multiplierHealthOffset = 0.0175;

		float baseDefense = 8;
		float defenseGrowth = 6.6;
		float additionalDefenseOffset = 0.7025;
		float multiplierDefenseOffset = 0.0175;

		float baseDamage = 10;
		float damageGrowth = 8.6;
		float additionalDamageOffset = 0.7025;
		float multiplierDamageOffset = 0.0175;

		float baseAttackSpeed = 1.0;
		float baseAttackRange = 15.0;
		float unitMass = 1;
		glm::vec3 collisionScale = glm::vec3(4, 4, 4);

		name = unitName;
		level = unitLevel;
		health = baseHealth + healthGrowth * (unitLevel - 1) * (additionalHealthOffset + multiplierHealthOffset * (unitLevel - 1));
		defense = baseDefense + defenseGrowth * (unitLevel - 1) * (additionalDefenseOffset + multiplierDefenseOffset * (unitLevel - 1));
		damage = baseDamage + damageGrowth * (unitLevel - 1) * (additionalDamageOffset + multiplierDamageOffset * (unitLevel - 1));
		attackRange = baseAttackRange;
		attackSpeed = baseAttackSpeed;
		delay = 0.0;
		mass = unitMass;
		colliderScale = collisionScale;
		target = UINT_MAX;
		unitType = NORMAL;
		unitFaction = unitFact;
		originUnit = UINT_MAX;
		targetUnit = UINT_MAX;
		FlowFieldCost = 0;
		StandingGridCost = 0;
		nextGrid = glm::vec2(-1, -1);
		velocity = glm::vec3(0, 0, 0);
		resourcesgenerated = 0.f;
		timeforgeneration = 0.f;
		generationdelay = 0;
	}

	~UNormal() {}
};

class URange : public Unit
{
public:
	URange() {}

	URange(int unitLevel, UnitFaction unitFact)
	{
		std::string unitName = "Range";

		float baseHealth = 65;
		float healthGrowth = 15.4;
		float additionalHealthOffset = 0.7025;
		float multiplierHealthOffset = 0.0175;

		float baseDefense = 6;
		float defenseGrowth = 5.8;
		float additionalDefenseOffset = 0.7025;
		float multiplierDefenseOffset = 0.0175;

		float baseDamage = 15;
		float damageGrowth = 20.6;
		float additionalDamageOffset = 0.7025;
		float multiplierDamageOffset = 0.0175;

		float baseAttackSpeed = 1.5;
		float baseAttackRange = 30.0;
		float unitMass = 1;
		glm::vec3 collisionScale = glm::vec3(4.5, 4, 5);

		name = unitName;
		level = unitLevel;
		health = baseHealth + healthGrowth * (unitLevel - 1) * (additionalHealthOffset + multiplierHealthOffset * (unitLevel - 1));
		defense = baseDefense + defenseGrowth * (unitLevel - 1) * (additionalDefenseOffset + multiplierDefenseOffset * (unitLevel - 1));
		damage = baseDamage + damageGrowth * (unitLevel - 1) * (additionalDamageOffset + multiplierDamageOffset * (unitLevel - 1));
		attackRange = baseAttackRange;
		attackSpeed = baseAttackSpeed;
		delay = 0.0;
		mass = unitMass;
		colliderScale = collisionScale;
		target = UINT_MAX;
		unitType = RANGE;
		unitFaction = unitFact;
		originUnit = UINT_MAX;
		targetUnit = UINT_MAX;
		FlowFieldCost = 0;
		StandingGridCost = 0;
		nextGrid = glm::vec2(-1, -1);
		velocity = glm::vec3(0, 0, 0);
		resourcesgenerated = 0.f;
		timeforgeneration = 0.f;
		generationdelay = 0;
	}

	~URange() {}
};

class UTank : public Unit
{
public:
	UTank() {}

	UTank(int unitLevel, UnitFaction unitFact)
	{
		std::string unitName = "Tank";

		float baseHealth = 200;
		float healthGrowth = 30;
		float additionalHealthOffset = 0.7025;
		float multiplierHealthOffset = 0.0175;

		float baseDefense = 15;
		float defenseGrowth = 20.0;
		float additionalDefenseOffset = 0.7025;
		float multiplierDefenseOffset = 0.0175;

		float baseDamage = 5;
		float damageGrowth = 10.0;
		float additionalDamageOffset = 0.7025;
		float multiplierDamageOffset = 0.0175;

		float baseAttackSpeed = 1.0;
		float baseAttackRange = 15.0;
		float unitMass = 1;
		glm::vec3 collisionScale = glm::vec3(4, 9, 4);

		name = unitName;
		level = unitLevel;
		health = baseHealth + healthGrowth * (unitLevel - 1) * (additionalHealthOffset + multiplierHealthOffset * (unitLevel - 1));
		defense = baseDefense + defenseGrowth * (unitLevel - 1) * (additionalDefenseOffset + multiplierDefenseOffset * (unitLevel - 1));
		damage = baseDamage + damageGrowth * (unitLevel - 1) * (additionalDamageOffset + multiplierDamageOffset * (unitLevel - 1));
		attackRange = baseAttackRange;
		attackSpeed = baseAttackSpeed;
		delay = 0.0;
		mass = unitMass;
		colliderScale = collisionScale;
		target = UINT_MAX;
		unitType = TANK;
		unitFaction = unitFact;
		originUnit = UINT_MAX;
		targetUnit = UINT_MAX;
		FlowFieldCost = 0;
		StandingGridCost = 0;
		nextGrid = glm::vec2(-1, -1);
		velocity = glm::vec3(0, 0, 0);
		resourcesgenerated = 0.f;
		timeforgeneration = 0.f;
		generationdelay = 0;
	}

	~UTank() {}
};

class UTower : public Unit
{
public:
	UTower() {}

	UTower(int unitLevel, UnitFaction unitFact)
	{
		std::string unitName = "Tower";

		float baseHealth = 700;
		float healthGrowth = 100;
		float additionalHealthOffset = 0.7025;
		float multiplierHealthOffset = 0.0175;

		float baseDefense = 0;
		float defenseGrowth = 0;
		float additionalDefenseOffset = 0.7025;
		float multiplierDefenseOffset = 0.0175;

		float baseDamage = 70;
		float damageGrowth = 50;
		float additionalDamageOffset = 0.7025;
		float multiplierDamageOffset = 0.0175;

		float baseAttackSpeed = 1.0;
		float baseAttackRange = 60.0;
		float unitMass = -1;
		glm::vec3 collisionScale = glm::vec3(10, 24, 12);

		name = unitName;
		level = unitLevel;
		health = baseHealth + healthGrowth * (unitLevel - 1) * (additionalHealthOffset + multiplierHealthOffset * (unitLevel - 1));
		defense = baseDefense + defenseGrowth * (unitLevel - 1) * (additionalDefenseOffset + multiplierDefenseOffset * (unitLevel - 1));
		damage = baseDamage + damageGrowth * (unitLevel - 1) * (additionalDamageOffset + multiplierDamageOffset * (unitLevel - 1));
		attackRange = baseAttackRange;
		attackSpeed = baseAttackSpeed;
		delay = 0.0;
		mass = unitMass;
		colliderScale = collisionScale;
		target = UINT_MAX;
		unitType = TOWER;
		unitFaction = unitFact;
		originUnit = UINT_MAX;
		targetUnit = UINT_MAX;
		FlowFieldCost = 500;
		StandingGridCost = 0;
		nextGrid = glm::vec2(-1, -1);
		velocity = glm::vec3(0, 0, 0);
		resourcesgenerated = 0.f;
		timeforgeneration = 0.f;
		generationdelay = 0;
	}

	~UTower() {}
};

class UWall : public Unit
{
public:
	UWall() {}

	UWall(int unitLevel, UnitFaction unitFact)
	{
		std::string unitName = "Wall";

		float baseHealth = 1000;
		float healthGrowth = 100;
		float additionalHealthOffset = 0.7025;
		float multiplierHealthOffset = 0.0175;

		float baseDefense = 0;
		float defenseGrowth = 0;
		float additionalDefenseOffset = 0.7025;
		float multiplierDefenseOffset = 0.0175;

		float baseDamage = 0;
		float damageGrowth = 0;
		float additionalDamageOffset = 0.7025;
		float multiplierDamageOffset = 0.0175;

		float baseAttackSpeed = 1.0;
		float baseAttackRange = 1.0;
		float unitMass = -1;
		glm::vec3 collisionScale = glm::vec3(20, 24, 20);

		name = unitName;
		level = unitLevel;
		health = baseHealth + healthGrowth * (unitLevel - 1) * (additionalHealthOffset + multiplierHealthOffset * (unitLevel - 1));
		defense = baseDefense + defenseGrowth * (unitLevel - 1) * (additionalDefenseOffset + multiplierDefenseOffset * (unitLevel - 1));
		damage = baseDamage + damageGrowth * (unitLevel - 1) * (additionalDamageOffset + multiplierDamageOffset * (unitLevel - 1));
		attackRange = baseAttackRange;
		attackSpeed = baseAttackSpeed;
		mass = unitMass;
		colliderScale = collisionScale;
		delay = 0.0;
		target = UINT_MAX;
		unitType = WALL;
		unitFaction = unitFact;
		originUnit = UINT_MAX;
		targetUnit = UINT_MAX;
		FlowFieldCost = 500;
		StandingGridCost = 0;
		nextGrid = glm::vec2(-1, -1);
		velocity = glm::vec3(0, 0, 0);
		resourcesgenerated = 0.f;
		timeforgeneration = 0.f;
		generationdelay = 0;
	}

	~UWall() {}
};

class UNexus : public Unit
{
public:
	UNexus() {}

	UNexus(int unitLevel, UnitFaction unitFact)
	{
		std::string unitName = "Nexus";

		float baseHealth = 10000;
		float healthGrowth = 100;
		float additionalHealthOffset = 0.7025;
		float multiplierHealthOffset = 0.0175;

		float baseDefense = 0;
		float defenseGrowth = 0;
		float additionalDefenseOffset = 0.7025;
		float multiplierDefenseOffset = 0.0175;

		float baseDamage = 0;
		float damageGrowth = 0;
		float additionalDamageOffset = 0.7025;
		float multiplierDamageOffset = 0.0175;

		float baseAttackSpeed = 1.0;
		float baseAttackRange = 1.0;
		float unitMass = -1;
		glm::vec3 collisionScale = glm::vec3(33, 23, 33);

		name = unitName;
		level = unitLevel;
		health = baseHealth + healthGrowth * (unitLevel - 1) * (additionalHealthOffset + multiplierHealthOffset * (unitLevel - 1));
		defense = baseDefense + defenseGrowth * (unitLevel - 1) * (additionalDefenseOffset + multiplierDefenseOffset * (unitLevel - 1));
		damage = baseDamage + damageGrowth * (unitLevel - 1) * (additionalDamageOffset + multiplierDamageOffset * (unitLevel - 1));
		attackRange = baseAttackRange;
		attackSpeed = baseAttackSpeed;
		mass = unitMass;
		colliderScale = collisionScale;
		delay = 0.0;
		target = UINT_MAX;
		unitType = NEXUS;
		unitFaction = unitFact;
		originUnit = UINT_MAX;
		targetUnit = UINT_MAX;
		FlowFieldCost = 500;
		StandingGridCost = 0;
		nextGrid = glm::vec2(-1, -1);
		velocity = glm::vec3(0, 0, 0);
		resourcesgenerated = 0.f;
		timeforgeneration = 0.f;
		generationdelay = 0;
	}

	~UNexus() {}
};

class UGenerator1 : public Unit
{
public:
	UGenerator1() {}

	UGenerator1(int unitLevel, UnitFaction unitFact)
	{
		std::string unitName = "Generator1";

		float baseHealth = 500;
		float healthGrowth = 100;
		float additionalHealthOffset = 0.7025;
		float multiplierHealthOffset = 0.0175;

		float baseDefense = 0;
		float defenseGrowth = 0;
		float additionalDefenseOffset = 0.7025;
		float multiplierDefenseOffset = 0.0175;

		float baseDamage = 0;
		float damageGrowth = 0;
		float additionalDamageOffset = 0.7025;
		float multiplierDamageOffset = 0.0175;

		float baseAttackSpeed = 1.0;
		float baseAttackRange = 1.0;
		float unitMass = -1;
		glm::vec3 collisionScale = glm::vec3(21, 24, 21);

		name = unitName;
		level = unitLevel;
		health = baseHealth + healthGrowth * (unitLevel - 1) * (additionalHealthOffset + multiplierHealthOffset * (unitLevel - 1));
		defense = baseDefense + defenseGrowth * (unitLevel - 1) * (additionalDefenseOffset + multiplierDefenseOffset * (unitLevel - 1));
		damage = baseDamage + damageGrowth * (unitLevel - 1) * (additionalDamageOffset + multiplierDamageOffset * (unitLevel - 1));
		attackRange = baseAttackRange;
		attackSpeed = baseAttackSpeed;
		mass = unitMass;
		colliderScale = collisionScale;
		delay = 0.0;
		target = UINT_MAX;
		unitType = GENERATOR1;
		unitFaction = unitFact;
		originUnit = UINT_MAX;
		targetUnit = UINT_MAX;
		FlowFieldCost = 500;
		StandingGridCost = 0;
		nextGrid = glm::vec2(-1, -1);
		velocity = glm::vec3(0, 0, 0);
		resourcesgenerated = 0.f;
		timeforgeneration = 10.f;
		generationdelay = 0;
	}

	~UGenerator1() {}
};

class UGenerator2 : public Unit
{
public:
	UGenerator2() {}

	UGenerator2(int unitLevel, UnitFaction unitFact)
	{
		std::string unitName = "Generator2";

		float baseHealth = 500;
		float healthGrowth = 100;
		float additionalHealthOffset = 0.7025;
		float multiplierHealthOffset = 0.0175;

		float baseDefense = 0;
		float defenseGrowth = 0;
		float additionalDefenseOffset = 0.7025;
		float multiplierDefenseOffset = 0.0175;

		float baseDamage = 0;
		float damageGrowth = 0;
		float additionalDamageOffset = 0.7025;
		float multiplierDamageOffset = 0.0175;

		float baseAttackSpeed = 1.0;
		float baseAttackRange = 1.0;
		float unitMass = -1;
		glm::vec3 collisionScale = glm::vec3(21, 24, 21);

		name = unitName;
		level = unitLevel;
		health = baseHealth + healthGrowth * (unitLevel - 1) * (additionalHealthOffset + multiplierHealthOffset * (unitLevel - 1));
		defense = baseDefense + defenseGrowth * (unitLevel - 1) * (additionalDefenseOffset + multiplierDefenseOffset * (unitLevel - 1));
		damage = baseDamage + damageGrowth * (unitLevel - 1) * (additionalDamageOffset + multiplierDamageOffset * (unitLevel - 1));
		attackRange = baseAttackRange;
		attackSpeed = baseAttackSpeed;
		mass = unitMass;
		colliderScale = collisionScale;
		delay = 0.0;
		target = UINT_MAX;
		unitType = GENERATOR2;
		unitFaction = unitFact;
		originUnit = UINT_MAX;
		targetUnit = UINT_MAX;
		FlowFieldCost = 500;
		StandingGridCost = 0;
		nextGrid = glm::vec2(-1, -1);
		velocity = glm::vec3(0, 0, 0);
		resourcesgenerated = 0.f;
		timeforgeneration = 10.f;
		generationdelay = 0;
	}

	~UGenerator2() {}
};

class ULab : public Unit
{
public:
	ULab() {}

	ULab(int unitLevel, UnitFaction unitFact)
	{
		std::string unitName = "Lab";

		float baseHealth = 500;
		float healthGrowth = 100;
		float additionalHealthOffset = 0.7025;
		float multiplierHealthOffset = 0.0175;

		float baseDefense = 0;
		float defenseGrowth = 0;
		float additionalDefenseOffset = 0.7025;
		float multiplierDefenseOffset = 0.0175;

		float baseDamage = 0;
		float damageGrowth = 0;
		float additionalDamageOffset = 0.7025;
		float multiplierDamageOffset = 0.0175;

		float baseAttackSpeed = 1.0;
		float baseAttackRange = 1.0;
		float unitMass = -1;
		glm::vec3 collisionScale = glm::vec3(19, 24, 19);

		name = unitName;
		level = unitLevel;
		health = baseHealth + healthGrowth * (unitLevel - 1) * (additionalHealthOffset + multiplierHealthOffset * (unitLevel - 1));
		defense = baseDefense + defenseGrowth * (unitLevel - 1) * (additionalDefenseOffset + multiplierDefenseOffset * (unitLevel - 1));
		damage = baseDamage + damageGrowth * (unitLevel - 1) * (additionalDamageOffset + multiplierDamageOffset * (unitLevel - 1));
		attackRange = baseAttackRange;
		attackSpeed = baseAttackSpeed;
		delay = 0.0;
		mass = unitMass;
		colliderScale = collisionScale;
		target = UINT_MAX;
		unitType = LAB;
		unitFaction = unitFact;
		originUnit = UINT_MAX;
		targetUnit = UINT_MAX;
		FlowFieldCost = 500;
		StandingGridCost = 0;
		nextGrid = glm::vec2(-1, -1);
		velocity = glm::vec3(0, 0, 0);
		resourcesgenerated = 0.f;
		timeforgeneration = 0.f;
		generationdelay = 0;
	}

	~ULab() {}
};

class UProjectile : public Unit
{
public:
	UProjectile() {}

	UProjectile(Entity attacking, Entity targeted)
	{
		std::string unitName = "Projectile";

		float baseHealth = 100.0f;

		float baseDefense = 0.0f;

		float baseDamage = 0.0f;

		float baseAttackSpeed = 0.0;
		float baseAttackRange = 1.0;
		float unitMass = -1;

		glm::vec3 collisionScale = glm::vec3(5, 5, 5);

		name = unitName;
		level = 1;
		health = baseHealth;
		defense = baseDefense;
		damage = baseDamage;
		attackRange = baseAttackRange;
		attackSpeed = baseAttackSpeed;
		delay = 0.0;
		mass = unitMass;
		colliderScale = collisionScale;
		target = UINT_MAX;
		unitType = PROJECTILE;
		unitFaction = UNDEFINED;
		originUnit = attacking;
		targetUnit = targeted;
		FlowFieldCost = 500;
		StandingGridCost = 0;
		nextGrid = glm::vec2(-1, -1);
		velocity = glm::vec3(0, 0, 0);
		resourcesgenerated = 0.f;
		timeforgeneration = 0.f;
		generationdelay = 0;
	}

	~UProjectile() {}
};

class UMeleeProjectile : public Unit
{
public:
	UMeleeProjectile() {}

	UMeleeProjectile(Entity attacking, Entity targeted)
	{
		std::string unitName = "Melee Projectile";

		float baseHealth = 1000.0f;

		float baseDefense = 0.0f;

		float baseDamage = 0.0f;

		float baseAttackSpeed = 0.0;
		float baseAttackRange = 1.0;
		float unitMass = -1;

		glm::vec3 collisionScale = glm::vec3(0, 0, 0);

		name = unitName;
		level = 1;
		health = baseHealth;
		defense = baseDefense;
		damage = baseDamage;
		attackRange = baseAttackRange;
		attackSpeed = baseAttackSpeed;
		delay = 0.0;
		mass = unitMass;
		colliderScale = collisionScale;
		target = UINT_MAX;
		unitType = MELEE_PROJECTILE;
		unitFaction = UNDEFINED;
		originUnit = attacking;
		targetUnit = targeted;
		FlowFieldCost = 500;
		StandingGridCost = 0;
		nextGrid = glm::vec2(-1, -1);
		velocity = glm::vec3(0, 0, 0);
		resourcesgenerated = 0.f;
		timeforgeneration = 0.f;
		generationdelay = 0;
	}

	~UMeleeProjectile() {}
};