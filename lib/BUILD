cc_library(
  name = "PumpkinSpice",
  srcs = [
    "AbstractComponent.cpp",
    "PumpkinSpice.cpp",
  ],
  hdrs = [
    "AbstractComponent.h",
    "ButtonComponent.h",
    "CommonTypes.h",
    "CommonUtils.h",
    "InputComponent.h",
    "Input.h",
    "PumpkinFactory.h",
    "PumpkinSpiceComponentObject.h",
    "PumpkinSpiceObject.h",
    "PumpkinSpice.h",
    "Style.h",
    "SpiceFactory.h",
    "Texture.h",
  ],
  deps = [
    "@rapidxml//:rapidxml",
    "@json//:json",
    "@nothings//:stb_truetype",
    "@nothings//:stb_image"
  ],
  data = [
    "pumpkin.xsd",
  ],
  visibility = ["//visibility:public"]
)

