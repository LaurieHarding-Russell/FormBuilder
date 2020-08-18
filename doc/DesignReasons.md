## Desing Goals:
1. Seperation of concerns: Having logic, structure and style mixed up seems to decreases readability of code in forms. Its easiest to keep structure, style, and logic defined in there own domains.
2. Modularity: If I decide to rewrite how structure code is generated it should be relatively easy to do without a rewrite of the styling or logic code.
3. Ease of use: this library should be easy to use. The average developer should be able to use it and create a quick form in a day.
4. Portable. This should work with openGL, vulkan, directX or your own custom hardware/software product. Glut sdl whatever it should work.
5. Reasonably small. The library does forms and thats it.

## Decisions

### Why JSON for styleing?
Its a quick standard way of defining information.

### Why xml for structure?
XML has been shown to be very readable way to define a form as seen by html.

### Will X change?
Possibly everything should be built/designed in a reasonably modular way.

### Why not X element?
I want pumpking (the strucural element in pumpkin spice) to be simple. I may add more element if they can increase the readability of the form.

### Why no video element and all that other html5 fanciness?
Complex elements should be done outside of this library. We want to keep the library light weight.

