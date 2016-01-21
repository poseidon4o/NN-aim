#pragma once
#include <SDL.h>
#include "Vec2.h"

//returns surface with radis * 2/ radius * 2 size with circle drew in it
SDL_Surface *  drawCircle(const float radius, const char red, const char green, const char blue);

bool intersectCircleTriangle(Vector2 center, float radius, Vector2 v[3]);
