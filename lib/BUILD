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



load("@rules_flex//flex:flex.bzl", "flex_cc_library")
flex_cc_library(
  name = "pumpkinSpiceFlex",
  src = "style.l",
  visibility = ["//visibility:public"]
)


load("@rules_bison//bison:bison.bzl", "bison_cc_library")
bison_cc_library(
    name = "pumpkinSpiceBison",
    src = "style.y",
)

# cc_binary(
#     name = "hello_bin",
#     deps = [":hello"],
# )