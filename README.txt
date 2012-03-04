********************************************************
*		CpSc 870: Object Oriented Programming   *
*	      				                *
*                                              		*
*							*
*	By,						*
*	  Nikhil Bendre	                                *
*         nbendre@clemson.edu		                *
*********************************************************/

Story Background
*********************************************************/


Game Motivation
*********************************************************/
In todays world, when we are so short of time, we are always 
in need of a small refreshing break. I have designed a game
which is time based game where a user needs to shoot maximum 
number of ghosts in just 30 seconds. The black colored ghosts
damage the users health and shooting the white ghost will earn 
you more points. 

Game Controls
*********************************************************/
ESC - Game Pause/Menu
F1 - Help 
Left Arrow - Direction Left
Right Arrow - Direction Right
Up Arrow - Direction Up
Down Arrow - Direction Down
r - Shoot the ghosts

Game Design
*********************************************************/

The game designed has been designed using the following 
design patterns,

1. Factory Pattern: 
	Factory is used for creation of sprites, here the 
white and black color ghosts. This is useful since we just
create only 1 frame and then reuse the same frame. 

2. Singleton Pattern:
	It is used to read the constants from XML files.

3. Multiframe Sprite:
	The hero of the game, the ghost buster, is created 
using the multiframe sprite. I have also used the Multiframe
factory method here for the creation of this multisprite. 

4. Shooting
	The multiframe sprite shoots fire at the ghosts thus
destroying them. I have used the Bullet class to achieve this 
and then I have accessed these bullets from Orbs class. 

5. Explosions
	There are two types of explosions here in the game. 
a). When the ghost buster (multiframe sprite) shoots the white 
ghost and destroys them. The user scores points as he busts more
ghost in the game. 
b). When the black ghost strikes the ghost buster, the health 
of the ghost buster reduces and the black ghost explodes. 

6. Health GFX 
	I am using the health bars to maintain the following, 
a) Time left to finish the game. The user needs to score as many
 points as possible in that given time frame. 
b) Health of the ghost buster. If too many black ghost attack the 
ghost buster, then the ghost buster loses health and then the
game comes to an end. 

7. Parallelex Scrolling 
	Two different sprite sheets were used to achieve 
parallelex scrolling. 

8. Sound
	The background music is played using the SDL_SOUND library. 
I tried giving some sound for explosion but I am running into some problem. 
I think that it supports the *.WAV files only although the SDL_SOUND
documentation says otherwise. I did try playing a mp3 format file but it wont
load so had to convert it to WAV file.

9. Game Menu
	The game menu consist of two options 1) New game and 2) Exit. 

10. F1 Keys
	F1 key gives information about the how to play the game. 

11. Force Quit (Q) 
	The game will be forced to quit if anyone presses Q key. 

********************************************************************************/

	       


