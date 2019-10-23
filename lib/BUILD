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
  includes	= [
    ":defaultStyle",
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

exports_files(["default.style"])

load("@rules_flex//flex:flex.bzl", "flex_cc_library")
load("@rules_bison//bison:bison.bzl", "bison_cc_library")
flex_cc_library(
  name = "pumpkinSpiceFlex",
  src = "pumpkinSpice/style.l",
  deps = ["pumpkinSpiceBison"],
)

bison_cc_library(
    name = "pumpkinSpiceBison",
    src = "pumpkinSpice/style.y",
)



cc_test(
    name = "pumpkinSpiceTest",
    srcs = ["pumpkinSpice/pumpkinSpiceTest.cpp"],
    deps = [
      ":pumpkinSpiceFlex", 
      "@gtest//:gtest_main",
    ],
    data	= [
      ":default.style",
    ],
)