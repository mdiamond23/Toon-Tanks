# Toon-Tanks  
A short action game made in Unreal Engine using C++. Made by Matthew Diamond, using Udemy Assets.  

Here is a link to where you can play the game!  
[**Toon Tanks On Itch**](https://mdiamond23.itch.io/toon-tanks-demo ) 

I've attached code examples that were integral to the project. The code was written in 2024

**`BasePawn.cpp/.h`**: Defines the base functionality for both **tanks** and **towers**. Manages core features like movement, turret rotation, firing projectiles, and handling destruction. Includes visual and audio effects on destruction, such as particle systems, sound cues, and camera shake.

**`HealthComponent.cpp/.h`**: Manages the **health system** for all damageable actors. Tracks current health, applies damage, and communicates death events to the game mode. Supports dynamic health initialization and damage event binding.

**`Projectile.cpp/.h`**: Handles projectile behavior, including **movement**, collision detection, and applying damage upon impact. Supports effects like hit particles, sounds, and camera shake upon collision.

**`Tank.cpp/.h`**: Implements **player-controlled tank behavior**, including movement, rotation, turret aiming, and firing mechanics. Supports enhanced input mapping for precise controls and integrates with the **BasePawn** class for shared functionality.

**`ToonTanksGameModeBase.cpp/.h`**: Manages the **overall game flow**, including starting conditions, win/loss states, and tracking active actors like tanks and towers. Listens for actor deaths to trigger endgame conditions.

**`ToonTanksPlayerController.cpp/.h`**: Controls **player input state**, enabling and disabling player controls based on game events. Used to restrict input during transitions, like cutscenes or game over screens.

**`Tower.cpp/.h`**: Implements **enemy tower behavior**, including automated targeting, turret rotation, and firing at the player tank. Checks firing range and handles destruction effects.

