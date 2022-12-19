#pragma once

#include "algebraLinear.h"

class Camera {

public:

	Vetor* eye = nullptr;
	Vetor* at = nullptr;
	Vetor* up = nullptr;

    AlgebraLinear al;

	Vetor mundoParaCamera(Vetor world);

	Camera(Vetor* eye, Vetor* at, Vetor* up);

};
