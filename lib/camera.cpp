#include "../include/camera.h"
#include "../include/algebraLinear.h"

Vetor Camera::worldToCamera(Vetor world) {

	Vetor k = al.vetorSubVetor(*eye, *at);
	Vetor normalK = al.vetorDivEscalar(k, al.norma(k));

	Vetor ViewUp = al.vetorSubVetor(*up, *at);

	Vetor i = al.produtoVetorial(ViewUp, normalK);
	Vetor normalI = al.vetorDivEscalar(i, al.norma(i));

	Vetor normalJ = al.produtoVetorial(normalK, normalI);

	double x = (
        (normalI.x * world.x) + 
        (normalI.y * world.y) + 
        (normalI.z * world.z) + 
        (-al.produtoEscalar(normalI, *eye) * 1)
    );

	double y = (
        (normalJ.x * world.x) + 
        (normalJ.y * world.y) + 
        (normalJ.z * world.z) + 
        (-al.produtoEscalar(normalJ, *eye) * 1)
    );

	double z = (
        (normalK.x * world.x) + 
        (normalK.y * world.y) + 
        (normalK.z * world.z) + 
        (-al.produtoEscalar(normalK, *eye) * 1));

	return Vetor(x, y, z, 0);
}


Camera::Camera(Vetor* eye, Vetor* at, Vetor* up) {
	this->eye = eye;
	this->at = at;
	this->up = up;
}

