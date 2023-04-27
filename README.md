# SceneGraphDemo
A basic scene graph for the OpenGL rendering engine using ImGui. The basic idea is to create bunch of root/parent "Nodes". These nodes will have their own properties and a vector of children nodes that will be added after the parent node is initialized. Then they are visualized in ImGui.

P.S I created the scene graph before creating an ECS, obviously that is something that should be avoided in real life application.

P.S 2 I played around a little bit and realised that something was missing, it lacked the function that supports an arbitrary number of levels of recursion. I'll update the code. So the next update lets you create a complex tree structure, something like this:

    |_ Parent

      |_ child
         
        |_ grandchild
                 
          |_ great grandchild
                              
            |_ ...


And each node will have their properties inside them.

UPDATE: I got it working, but there are two problems. First, because it's a recursive function, each node creates another one of itself (first as a child of the previous node, and then as a parent). Second, grandchildren shapes are only drawn when their nodes are open. The later can be fixed by having a general vector that stores all nodes (parents and children) in order and then draw them all.

![scene](https://user-images.githubusercontent.com/69974236/228007582-7067c967-824f-4088-9452-ef2520fc206c.gif)
