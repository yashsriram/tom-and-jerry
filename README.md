## What?
* Carrom Chase is a strike and pocket tabletop game.
* It is similar to the classic Carrom game but with an touch of action.

## How to install? [Ubuntu]
* Install dependencies
    * `sudo apt-get install libx11-dev`
* Open terminal in this directory
    * `make` to compile code [creates an executable **carromchase**]
    * `make play` or `./carromchase` to start playing

## How to play?
* The game is on a carrom board
* But unlike the classic game, there are just two carroms, one runner & one chaser
* You can place runner (anywhere inside the placing circle) and strike it
    * After you place the runner, few aiming circles appear
    * You can click inside the circles to strike it
    * You can control the force with which you strike by changing the distance of click from center
* Your job is to strike the runner into pocket
* The chaser however will try to catch the runner while it is moving
    * The chaser will move in the same direction as that of runner
    * The chaser gets faster as time progresses
    * If chaser catches runner the game ends
* There is friction and both of them will stop after a while
    * If the runner stops on the board without falling in pocket the game ends
* If the runner goes into a pocket you get a point
* Place, Strike, Score and repeat!
