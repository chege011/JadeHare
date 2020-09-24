//
// Created by 1129 on 2020/9/24.
//

#include <geometry.h>

namespace vulkanPBR
{

    Ray::Ray() : tMax(Infinity), time(0.f) {}

    Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction, float tMax, float time) : origin(origin),
                                                                                            direction(direction),
                                                                                            tMax(tMax), time(time) {}

    RayDifferential::RayDifferential() { hasDifferentials = false; }


    RayDifferential::RayDifferential(const glm::vec3 &origin, const glm::vec3 &direction, float tMax,
                                     float time)
            : Ray(origin, direction, tMax, time) {}

    void RayDifferential::ScaleDifferentials(float s)
    {
        rxOrigin = origin + (rxOrigin - origin) * s;
        ryOrigin = origin + (ryOrigin - origin) * s;
        rxDirection = direction + (rxDirection - direction) * s;
        ryDirection = direction + (ryDirection - direction) * s;
    }

    RayDifferential::RayDifferential(const Ray &ray) : Ray(ray) { hasDifferentials = false; }
}

