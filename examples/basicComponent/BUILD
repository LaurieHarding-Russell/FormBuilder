cc_binary(
    name="basic",
    srcs = [
        "main.cpp",
        "ShaderLoader.h",
    ],
    deps = [
        "//lib:PumpkinSpice",
        "@glew//:glew",
        "@glfw//:glfw",
        "//examples/basicComponent/basicComponent:basicComponent"
    ],
    data = [
        "base.spice",
        "base.pumpkin",
        "@font//:Bangers",
        "//examples/shaders:shaders",
    ],
    linkopts = select({
        "@bazel_tools//src/conditions:linux_x86_64": [
            "-lX11",
            "-ldl",
            "-lpthread",
            "-lGL"
        ],
        "@bazel_tools//src/conditions:darwin_x86_64": [
            "-lX11",
            "-ldl",
            "-lpthread",
            "-lGL"
        ]
    }),
    defines = [ 
        "DEBUG",
        "GL_GLEXT_PROTOTYPES"
    ],
    copts = [
        "-Wno-unused",
        "-Wno-unused-function",
    ],
)