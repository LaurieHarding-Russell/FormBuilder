cc_binary(
    name = "test",
    srcs = [
      "examples/Test.cpp",
      "examples/TestComponent/TestComponent.h",
    ],
    deps = [
      "@system_include_x86_64_linux//:x11",
      "@glew//:glew",
      # "//lib:abstractComponent",
      "//lib:initShader",  
    ],
    includes	= [
      "//lib/shaders:shaders",
    ],
    linkopts = ["-lX11", "-lGL", "-lGLU"],
    defines = ["DEBUG", "GL_GLEXT_PROTOTYPES"]
)
