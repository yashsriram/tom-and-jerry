# tom-and-jerry

## description
- Tom and Jerry is a simple cat and mouse game.

## code
- The code is written in `C++`.
- All the src is written in `src/`.
- [Simplecpp](https://www.cse.iitb.ac.in/~ranade/simplecpp/) is used for rendering.
- `include` & `lib` contains headers and implementation of simplecpp.

## documentation
- The documentation for the code is itself.

## usage

### how to install?
- Make sure X11 and X11-dev are installed.
    - For ubutnu `apt install libx11-6 libx11-dev`.
- Open terminal in the root directory.
    - Make a build directory using `mkdir build && cd build`.
    - Create a makefile using `cmake ..`
    - Compile code using `make`. This creates an executable named `tomandjerry`.
    - Use `./tomandjerry` to start playing.

### how to play?
- The game is played on a board.
- There are two agents, Tom (the adversery) & Jerry (the player).
- Tom is the big mean circle and Jerry is small witty circle.
- Jerry is placed on the board automatically and you can control it.
    - For controlling Jerry, a few concentric circles are provided.
    - A click inside them makes Jerry running in that direction.
    - Farther click from Jerry equals more speed, but you cannot click outside the circles.
- The goal is to get Jerry safely into one of the holes.
- Tom will however try to catch Jerry while it is moving.
    - But we know a little bit about Tom's strategy.
    - Tom will move in the same initial direction as that of Jerry.
    - And Tom will get faster for hole you reach safely.
- Both of them get tired after some chasing and stop to catch a breath.
- If Tom catches Jerry the game ends!
- If Tom and Jerry stop on the board without Jerry reaching one of the holes safely, the game ends!
- Help Jerry escape, score and repeat!

## roadmap
- [x] Basic game.
- [ ] Refactor literal constants to const variables
- [ ] Use logical constraints to render layout
