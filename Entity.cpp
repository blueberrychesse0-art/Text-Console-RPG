#include "Entity.h"
#include <string>

using namespace std;


string Entity::GetName()const
{
	return name;
}
int Entity::GetHealth()const
{
	return health;
}
int Entity::GetAttack()const
{
	return attack;
}