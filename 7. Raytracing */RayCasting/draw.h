#pragma once

#include "Libraries.h"

void RayCasting();

int randomgen(int min, int max);

Vector get_true_color(int x, int y, const Vector viewPos, const Vector materialColor, const Vector lightColor,
					  const Vector ambientColor, const Vector lightPosition, int R, int smooth,
					  const Vector ambientPosition);

Vector AmbientLightning(const Vector& p, const Vector& N, const Vector& V,
	const Vector& lightPos, const Vector& lightColor,
	const Vector& materialColor);

Vector collision(const Vector& p, double r, int smooth);