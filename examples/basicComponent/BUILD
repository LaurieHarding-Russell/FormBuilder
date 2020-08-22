cc_binary(
    name="basicComponent",
    srcs = [
        "main.cpp",
        "ShaderLoader.h",
    ],
    deps = [
        "//lib:PumpkinSpice",
        "@glew//:glew",
        "@glut//freeglut/freeglut:glut",
    ],
    data = [
        "style.spice",
        "test.xml",
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