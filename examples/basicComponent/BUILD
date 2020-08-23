cc_binary(
    name="basicComponent",
    srcs = [
        "main.cpp",
        "ShaderLoader.h",
        "basicComponent/BasicComponent.h"
    ],
    deps = [
        "//lib:PumpkinSpice",
        "@glew//:glew",
        "@glut//freeglut/freeglut:glut",
    ],
    data = [
        "base.spice",
        "base.pumpkin",
        # FIXME, having this in a folder isn't working. 
        "basic.spice",
        "basic.pumpkin",
        "@font//:Bangers",
        "//examples/shaders:shaders",
    ],
    linkopts = [
        "-lGL",
    ],
    defines = [ 
        "DEBUG",
        "GL_GLEXT_PROTOTYPES"
    ],
    copts = [
        "-Wno-unused",
        "-Wno-unused-function",
    ],
)