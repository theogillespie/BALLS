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

	Vector3 vec(90, 0, 0);

	cout << "input euler angles (deg): " << vec.toString() << endl;
	Quaternion q = Quaternion::fromEuler(vec);
	cout << "as quat: " << q.toString() << endl;
	cout << "converted back to euler (deg): " << q.toEulerAngles().toString();

	return 0;
}
