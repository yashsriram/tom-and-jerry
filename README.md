## What?
* Carrom Chase is a strike and pocket tabletop game.
* It is similar to the classic Carrom game but with an touch of action.

## How to install? [Ubuntu]
* Install dependencies
    * `sudo apt-get install libx11-6 libx11-dev`
* Open terminal in this directory
    * `mkdir build && cd build`
    * `cmake ..`
    * `make` to compile code [creates an executable **carromchase**]
    * `./carromchase` to start playing

## How to play?
* The game is on a carrom board
* But unlike the classic game, there are just two carroms, one runner & one chaser
* The runner is placed for you and you can strike it
    * For striking, a few aiming circles are provided
    * A click inside the circles directs it
    * You can control the force of the strike by clicking away or towards the center of circles
* Your job is to strike the runner into pocket and score points
* The chaser however will try to catch the runner while it is moving
    * The chaser will move in the same initial direction as that of runner
    * It gets faster for every pocket you score
    * If the chaser catches runner the game ends!
* But remember, there is friction and both of them will stop after a while
    * If the runner stops on the board without falling in pocket again, the game ends!
* Place, Strike, Score and repeat!
