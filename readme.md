# Engine Exercise 001
A fixed size window that updates 60 time a second, has multiple game states and
cleanly exits. 

## Compilation Requirements
- SDL2 2.0.8+ library https://www.libsdl.org/download-2.0.php
- C++17


## Purpose
This is a very basic test of a simple game loops with an event handler and game
state that uses a finite state machine approach. In this case the states are:

Initial -> Idle -> Quit

## Game States

### Initial
- Render a red screen for a given time period.
- Ignore all events.
- When the time period has elapsed, change the game state to Idle.

### Idle 
- Render a screen with a colour that changes.
- Colour cycles from black to white over 10 seconds, repeating indefinately.
- If a quit event is detected, change the state to Quit.

### Quit 
- Render a blue screen for a given time period.
- Ignore all events.
- When the time period has elapsed, cleanly end the application.
