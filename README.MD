## How to get started:
1. Install bazel.
2. Run `bazel run //examples/HelloWorldExample:helloWorld`

## How to run tests
`bazel test ...`

## How to inlcude it into your project
Include the following in your WORKSPACE file and depend on `pumpkinSpice`.
```
http_archive(
    name = "pumpkinSpice",
    urls = ["https://github.com/LaurieHarding-Russell/FormBuilder/archive/e85f7c69c38db7a903ebcc7f9732f8646f782565.zip"],
    strip_prefix = "FormBuilder-e85f7c69c38db7a903ebcc7f9732f8646f782565",
)
load('@formLib//toolchain:pumpkinSpiceDependencies.bzl', 'load_pumpkin_spice_deps')
load_pumpkin_spice_deps()
```

## What is this?
This is a library for creating form components in C++. It is heavily influenced by html, css, and the Angular Framework.

## WHY?
For fun? Also, seperating concerns like html and css allows for easier developement of more complex UX. Lets be honest, Web developers make better looking buttons/inputs then any other flavor of programmer. 

That being said we can do better. CSS has to be backward compatable. This has lead to quirks/complexity in the language. (What's up with css stacking order?) I don't need to worry about the world. You can run with whichever version of this library you want. When things start getting quirky I can fix them withought worrying about breaking users.

Am I being pretentious? Yup. Will anyone ever use this library? Probably not. Would I recommend it to a friend? Only if they want to contribute and make it a lot better!
