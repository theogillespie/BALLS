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

	
	Projectile proj = Projectile::fromFile("/workspace/BALLS/BALLS/io/ConfigTest.txt");
	cout << proj.name;
	return 0;
}
