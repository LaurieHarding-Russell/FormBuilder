cc_library(
  name = "abstractComponent",
  srcs = ["AbstractComponent.cpp"],
  hdrs = ["AbstractComponent.h"],
  linkopts = ["-lGL", "-lGLU"],
  deps = [
    "@openGL_x86_64_linux//:GL",
    "@rapidxml//:rapidxml",
    # "@json//:json"
  ],
  visibility = ["//visibility:public"]
)

cc_library(
  name = "initShader",
  hdrs = ["initShader.h"],
  linkopts = ["-lGL", "-lGLU"],
    deps = [
    "@openGL_x86_64_linux//:GL",
  ],
  visibility = ["//visibility:public"]
)
