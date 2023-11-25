#ifndef NPC_BASE_H
#define NPC_BASE_H

#include "Behaviour.hpp"
#include "GameObject.hpp"

// for: movement, player detection, behaviour with enviroment
#define BEHAVIOUR_COUNT 2 /* 2 for now, TODO: expand to 3 */
#define NPC_CHANCE RAND_MAX / 2 /* usage: rand() < CHANCE */
#define NPC_MULTIPLIER_PER_ROOM 10

class NonPlayableCharacter : public GameObject
{
public:
	NonPlayableCharacter();
	NonPlayableCharacter(Behaviour** behaviours);
	NonPlayableCharacter(Behaviour** behaviours, Point position);

	~NonPlayableCharacter();

	void FirstUpdate() override;
	int Update() override;
	void LastUpdate() override;

	void SetUpdateDelay(int delay);

private:
	int updateDelay;
	Behaviour** behaviourStates;
	MainCharacter* mainCharacter;
protected:
	virtual void Init() override;
};



#endif // !ENEMY_H



