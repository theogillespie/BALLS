// BALLS.cpp : Defines the entry point for the application.
//

#include "BALLS.h"
#include "core/Quaternion.h"
#include "core/Vector3.h"
#include "core/Projectile.h"

#include "io/ConfigReader.h"
#include "io/LoadingBar.h"
#include "io/ProjectileLoader.h"

#include <stdio.h>

int main()
{

	
	// technically executes, but values are not correct... probably a pointer issue;
	Projectile proj = Projectile::fromFile("C:\\Users\\icat7\\OneDrive\\Documents\\BALLS\\BALLS\\io\\ConfigTest.txt");
	cout << proj.mass;
	return 0;
}
