#ifndef NPC_BASE_H
#define NPC_BASE_H

#include "Behaviour.hpp"
#include "GameObject.hpp"

// for: movement, player detection, behaviour with enviroment
#define BEHAVIOUR_COUNT 2 /* 2 for now, TODO: expand to 3 */

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
};



#endif // !ENEMY_H



