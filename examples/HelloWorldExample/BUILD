cc_binary(
    name="helloWorld",
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
        "test.jpg",
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


cc_library(
    name = "stb_image",
    hdrs = ["@stb_image//file"],
    visibility = ["//visibility:public"],
    strip_include_prefix = "/external/stb_image/file",
    include_prefix = "",
    linkstatic=True
)