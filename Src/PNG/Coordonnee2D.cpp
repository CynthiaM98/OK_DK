#include "Coordonnee2D.h"

Coordonnee2D::Coordonnee2D(float x, float y) {
	this->x = x;
	this->y = y;
}

Coordonnee2D::Coordonnee2D() {
	this->x = 0.0;
	this->y = 0.0;
}


float Coordonnee2D::getX() {
	return this->x;
}

float Coordonnee2D::getY() { 
	return this->y;
}

void Coordonnee2D::setX(float x) {
	this->x = x;
}

void Coordonnee2D::setY(float y) {
	this->y = y;
}