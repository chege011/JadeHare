#include <iostream>
#include <cxxopts.hpp>
#include <glm/glm.hpp>
#include <entt/entt.hpp>
#include "util/vecmath.h"

int main(int argc, const char *argv[])
{
    cxxopts::Options options("pbrt", "Physically Base Rendering");
    // Default options
    options.add_options()
            ("h,help", "Print this help text.");

    // Rendering options
    options.add_options("Rendering options")
            ("cropwindow", "Specify an image crop window.", cxxopts::value<std::vector<float>>(), "x0,x1,y0,y1")
            ("j,nthreads", "Use specified number of threads for rendering.", cxxopts::value<int>()->default_value("1"))
            ("o,outfile", "Write the final image to the given filename.", cxxopts::value<std::string>())
            ("quick", "Automatically reduce a number of quality settings to render more quickly.",
             cxxopts::value<bool>()->default_value("false")->implicit_value("true"))
            ("quiet", "Suppress all text output other than error messages.",
             cxxopts::value<bool>()->default_value("false")->implicit_value("true"));

    // Logging options
    options.add_options("Logging options")
            ("logdir", "Specify directory that log files should be written to.\n "
                       "Default: system temp directory (e.g. $TMPDIR or /tmp).",
             cxxopts::value<std::string>()->default_value("tmp"))
            ("logtostderr", "Print all logging messages to stderr.",
             cxxopts::value<bool>()->default_value("false")->implicit_value("true"))
            ("minloglevel", "Log messages at or above this level (0 -> INFO, 1 -> WARNING, 2 -> ERROR, 3-> FATAL).",
             cxxopts::value<uint8_t>()->default_value("0"))
            ("v,verbosity", "Set VLOG verbosity.", cxxopts::value<int>());

    // Reformatting options
    options.add_options("Reformatting options")
            ("cat", "Print a reformatted version of the input file(s) to standard output. Does not render an image.",
             cxxopts::value<bool>()->default_value("false")->implicit_value("true"))
            ("toply",
             "Print a reformatted version of the input file(s) to standard output and convert all triangle meshes to PLY files. Does not render an image.",
             cxxopts::value<bool>()->default_value("false")->implicit_value("true"));

    options.help({"", "Rendering options", "Logging options", "Reformatting options"});

    auto result = options.parse(argc, argv);

//    if (argc <= 1 || result.count("help"))
//    {
//        std::cout << options.help() << std::endl;
//        exit(0);
//    }

    entt::registry registry;

    jadehare::Vector3f vector3;

    glm::vec2 vew23 {1.3, 3.6};
    glm::vec3 ve222;
    glm::vec3 wqe;
    jadehare::Vector3f vector3F;
    jadehare::Vector3f ve231(1.0f, 1.0f, 1.0f);
    vector3 += vector3F + vector3;

    auto xx = ve231 * 3;
    xx /= 2;

    ve231[2] = 12;
    vector3 = ve231;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}