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
  src = "pumpkinSpice/spice.l",
  deps = ["pumpkinSpiceBison"],
)

bison_cc_library(
    name = "pumpkinSpiceBison",
    src = "pumpkinSpice/spice.y",
    deps = [
        "@openGL_x86_64_linux//:GL",
    #   ":pumpkinSpice",
    ],
)

cc_library(
  name = "pumpkinSpice",
  hdrs = ["pumpkinSpice/pumpkinSpice.h"],
  linkopts = ["-lGL", "-lGLU"],
  deps = [
    "@openGL_x86_64_linux//:GL",
  ],
)


cc_test(
    name = "pumpkinSpiceTest",
    srcs = [
      "pumpkinSpice/pumpkinSpiceTest.cpp",
    ],
    deps = [
      ":pumpkinSpiceFlex", 
      "@gtest//:gtest_main",
      "@openGL_x86_64_linux//:GL",
    ],
    linkopts = ["-lGL", "-lGLU"],
    data	= [
      ":default.style",
    ],
)