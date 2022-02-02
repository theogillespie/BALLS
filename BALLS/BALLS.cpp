// BALLS.cpp : Defines the entry point for the application.
//

#include "BALLS.h"
#include "core/Quaternion.h"
#include "core/Vector3.h"
#include "core/Projectile.h"

#include "io/ConfigReader.h"

#include <stdio.h>

int main()
{

	/* un comment to test quaternion conversion (broken)W
	Vector3 vec(90, 90, 90);
	vec.toRad();
	Quaternion a = Quaternion::fromEuler(vec);
	std::cout << a.toString() << std::endl;
	std::cout << a.toEulerAngles().toDeg()->toString();
	*/

	ConfigReader cf("C:\\Users\\icat7\\OneDrive\\Documents\\BALLS\\BALLS\\io\\ConfigTest.txt");
	cf.parse();

	cout << cf.elements[0].getString() << endl;
	cout << cf.elements[1].getString() << endl;

	printf("hi!");
	return 0;
}
