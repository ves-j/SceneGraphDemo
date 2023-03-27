# SceneGraphDemo
A basic scene graph for the OpenGL rendering engine using ImGui. The basic idea is to create bunch of root/parent "Nodes". These nodes will have their own properties and a vector of children nodes that will be added after the parent node is initialized. Then they are visualized in ImGui.

P.S I created the scene graph before creating an ECS, that is something that should be avoided in real life application (cuz it's a pain).


![Capture1](https://user-images.githubusercontent.com/69974236/227809822-b37e191e-e014-4f58-b528-a9f9f46b1de5.PNG)
