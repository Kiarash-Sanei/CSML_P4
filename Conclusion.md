# Project Structure
- `ASM/`
    + `C.s`: The Assembly function for calculation of the curve path
    + `EA.s`: The Assembly function for calculation in drawing the details of ball
    + `EX.s`: The Assembly function for calculation in drawing the details of ball
    + `EY.s`: The Assembly function for calculation in drawing the details of ball
    + `G.s`: The Assembly function for calculation of the gradient
    + `R.s`: The Assembly function for calculation of the regular path
    + `S.s`: The Assembly function for calculation of the sinusodial path
    + `SA.s`: The Assembly function for calculation in drawing the details of ball
    + `SE.s`: The Assembly function for calculation in drawing the details of ball
- `CPP/`
    + `class.cpp`: The file that contains all the classes
    + `function.cpp`: The file that contains main functions
    + `game.cpp`: The main game file
    + `kgh.h`: The header file
- `.gitignore`: The git ignore file
- `Conclusion.md`: The main report
- `game.sh`: The bash file to run the game
- `log.old.txt`: The log of the games that have been executed
- `log.txt`: The log for new games
- `README.md`: Read Me file

# Tools
- `C++`
- `Assembly` (x86)
- `Raylib`

# The game
The game have single and multiplayer mode.
It also have 3 different path choise for the ball
It has 3 difficulty level.
You can choose how the hot parts are handled, too.

# Why are we using Assembly?
There are some hot parts in game which are occurring every time that the window is rendered. So, we want to convert hot parts to Assembly so that they become faster!

# Where did we use Assembly?
We found the hot parts of the code and write the functions in that hot part in Assembly.
There are __9__ hot parts that are replaced by Assembly functions.  

# How did we use Assembly?
We extern some functions in header. `extern "C" ...` is the part for externing. The `"C"` is for forcing function to use `C` calling convention.

# Compiling & Running
`-O0` flag makes the compiler not to optimize the code in any aspect. The compilers is still programming better in most of the cases, but hot parts are taking time for calculations, so we can use Assembly and improve the calculation speed.
When use run `game.sh` the Assembly codes are assembled to object files. Then the object files and the main code in C++ are integrated and linked (using linker). The game is executed. The hot parts, besides the main ball and gradient in game, are always in assembly. When you close the window, the log of your game consisting of how long have you executed the game, how long have you played, and how long have the calculations taken along with some metadatas, is saved in `log.txt`. 

# The results
## Regular Path
As you can see in log.old.txt, in regular path using Assembly significantly improve our speed. So, in this case we were successfully achieve the purpose of our project.

## Sinusodial Path
Furthermore in sinusodial path using Assembly takes much less time. As we know the is a part for some special arithmatics in CPU and the `fsin` in `S.s` use that part and improve the speed.

## Curve Path
At the end in Curve pass we can see that using Assembly actually improve our code. In the curve pass we have the more calculations than Regular path and we don't have a special unit to do them (unlike the sinusodial path).

## Conclusion
It's not always optimal to use Assembly for every day tasks and codings but in some cases that we have some calculations that are occurring so much and are sophisticated enough, we can use Assembly and improve our speed and make better user experience (FPS).
