cc_binary(
    name = "test",
    srcs = [
      "examples/Test.cpp",
      "examples/TestComponent/TestComponent.h",
    ],
    deps = [
        "@system_include_x86_64_linux//:x11",
        "//lib:abstractComponent",
        
    ],
    linkopts = ["-lX11", "-lGL", "-lGLU"]
)
