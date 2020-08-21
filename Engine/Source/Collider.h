#pragma once

#include "MatrixStack.h"
#include "glm.hpp"

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
