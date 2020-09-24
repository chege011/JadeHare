//
// Created by 1129 on 2020/9/24.
//

#ifndef VULKANPBR_GEOMETRY_H
#define VULKANPBR_GEOMETRY_H

#include <glm/glm.hpp>

#define Infinity std::numeric_limits<float>::infinity()

#define Vector3 glm::vec3
#define Vector4 glm::vec4
#define Point3 glm::vec3
#define Point2 glm::vec2
#define Normal3 glm::vec3

namespace vulkanPBR
{
    class Ray
    {
    public:
        // Ray Public Methods
        Ray();

        Ray(const glm::vec3 &origin, const glm::vec3 &direction, float tMax = Infinity, float time = 0.f);

        Vector3 operator()(float t) const { return origin + direction * t; }

        // Ray Public Data
        Point3 origin;
        Vector3 direction;
        mutable float tMax;
        float time;
        // TODO: const Medium *medium;
    };

    class RayDifferential : public Ray
    {
    public:
        // RayDifferential Public Method
        RayDifferential();

        RayDifferential(const glm::vec3 &origin, const glm::vec3 &direction, float tMax = Infinity, float time = 0.f);

        explicit RayDifferential(const Ray &ray);

        void ScaleDifferentials(float s);

        // RayDifferential Public Data
        bool hasDifferentials;
        Point3 rxOrigin, ryOrigin;
        Vector3 rxDirection, ryDirection;
    };
}

#endif //VULKANPBR_VECTOR_H
