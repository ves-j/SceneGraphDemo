# SceneGraphDemo
A basic scene graph for the OpenGL rendering engine using ImGui. The basic idea is to create bunch of root/parent "Nodes". These nodes will have their own properties and a vector of children nodes that will be added after the parent node is initialized. Then they are visualized in ImGui.

P.S I created the scene graph before creating an ECS, that is something that should be avoided in real life application.

P.S 2 I played around a little bit and realised that something was missing, it lacked the function that supports an arbitrary number of levels of recursion. I'll update the code. So the next update should be something like this:

    |_ Parent

      |_ child
         
        |_ grandchild
                 
          |_ great grandchild
                              
            |_ ...



![scene](https://user-images.githubusercontent.com/69974236/228007582-7067c967-824f-4088-9452-ef2520fc206c.gif)
