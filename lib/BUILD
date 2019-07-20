cc_library(
  name = "abstractComponent",
  srcs = ["AbstractComponent.cpp"],
  hdrs = ["AbstractComponent.h"],
  linkopts = ["-lGL", "-lGLU"],
  deps = [
    "@system_include_x86_64_linux//:GL",
    "@rapidxml//:rapidxml",
    # "@json//:json"
  ],
  visibility = ["//visibility:public"]
)