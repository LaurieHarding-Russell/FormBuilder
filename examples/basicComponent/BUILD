cc_binary(
    name="basic",
    srcs = [
        "main.cpp",
        "ShaderLoader.h",
    ],
    deps = [
        "//lib:PumpkinSpice",
        "@glew//:glew",
        "@glut//freeglut/freeglut:glut",
        "//examples/basicComponent/basicComponent:basicComponent"
    ],
    data = [
        "base.spice",
        "base.pumpkin",
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