#pragma once

#include "MatrixStack.h"

struct Collider
{
   glm::vec3 scale;
   float mass;

   Collider()
       : scale(1, 1, 1)
       , mass(1)
    {
    }

    Collider(glm::vec3 scale, float mass)
        : scale(scale)
        , mass(mass)
    {
    }

};
