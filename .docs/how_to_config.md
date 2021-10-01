# Customising Newb Shader

> **Warning**: Making wrong changes to the files may cause shader to fail

1) Make sure you are using "External Storage" in Minecraft settings.
2) Using a file manager, navigate to this folder:
`/storage/games/com.mojang/resource_packs/NewbShader/shaders/glsl/config_utilities`  
All the configuration files can be found here as a `.h` file.
3) Open the required config file using a text editor and after making your changes, save the file.
4) Open Minecraft to see changes. You can launch Minecraft from recents/background without having to restart it completely.

> Note: Some files have parts of code after
 configuration section. Don't mess with the
 code section unless you understand what you are doing.
 
# Making changes

> #### Toggle options
> Add `//` before `#define` to turn it OFF.
>
> `#define EXAMPLE` will enable EXAMPLE  
> `//#define EXAMPLE` will disable EXAMPLE  

> #### Value options
> Values must be in decimal format. eg: `1.7`,`0.1`,`0.0`.  
> Don't toggle unless specified "Toggle + Value".  
>
>        #define example <your value here>

> #### Color options
> Colors are in RGB format (range 0.0-1.0 for most options)
>
>        const vec3 example = vec3(<red>,<green>,<blue>);`
>
> Some color examples:  
> `vec3(0.0,0.0,0.0)` - black  
> `vec3(1.0,1.0,1.0)` - white  
> `vec3(1.0,0.0,0.0)` - red  
> `vec3(1.0,0.0,1.0)` - magenta  

> #### Type options
> 0,1,2,3... (choose between types using numbers)
>
>        // <read this>
>        #define EXAMPLE_TYPE 2
