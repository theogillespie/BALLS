// BALLS.cpp : Defines the entry point for the application.
//

#include "BALLS.h"
#include "core/core.h"

int main()
{
	Projectile* projectile = Simulation::run();
	Console::print("Done:");
	Console::print(projectile->position.toString());
}
