# How to contribute (in code)

### Prerequisite
- Basic understanding of GLSL
- Understand the codes of Newb Shader

### Instruction
> For Termux git client (terminal)  

Download and install Termux  
https://f-droid.org/en/packages/com.termux/

Install git in Termux
```
pkg install git
```

Cd to `development_resource_packs` directory
```
cd storage/shared/games/com.mojang/development_resource_packs/
```

Clone the github repository there  
```
git clone https://github.com/devendrn/newb-shader-mcbe
``` 

Cd to your git folder
```
cd newb-shader-mcbe
```

Create your branch and switch to it
```
git checkout -b <your branch name>
```

Edit the shader files/codes as you normally would

Make a git commit
```
git commit -a -m "<your commit message>"
```

Push the commit (Upload the commit)
```
git push orgin <your branch name>
```

Send a pull request for your branch through the github page citing the changes made
> Note: The instructions may have some mistakes. Please refer other sources

### Things you could do
- Add new feature
- Improve an existing feature
- Fix a bug
- Optimize the code
