# RC_Car
The Arduino (MEGA board) code for the UTTS's club RC bluetooth controlled car through an available android app.

The code was built around an RC car (Version 1) designed for the UTTS (University of Toronto Technical Specialists) club as our first major design project. The car is designed using generative design, and functions with the bare minimum (movements, turning and speed control). 

Future versions of the car will incorporate more sophisticated sensors and upgrades. 

This code supports the movement in all 8 directions, as well as speed control using the HC-05 Bluetooth Chip, two L298N Motor boards with regular DC motors, 4 battery packs (to supply 12V each to the Arduino MEGA and the chip, as well as the two boards)

Schematics of the RC_Car can be found here: 

The design of the car can be found here: 

This version of the code uses the following Android App: https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller&hl=en&gl=US that runs at 115200 baud.

The App's documentation can be found here: https://sites.google.com/site/bluetoothrccar/home/4PuttingItAllTogetherAndTheAndroidApplication

With the following signals (characters) being received from the app:

Forward------------------> F                                                                                                                   
Back---------------------> B                                                                                                                   
Left---------------------> L                                                                                                                   
Right--------------------> R                                                                                                                   
Forward Left-------------> G                                                                                                                   
Forward Right------------> I                                                                                                                   
Back Left----------------> H                                                                                                                   
Back Right---------------> J                                                                                                                   
Stop---------------------> S                                                                                                                   
Speed 0------------------> 0                                                                                                                   
Speed 10-----------------> 1                                                                                                                   
Speed 20-----------------> 2                                                                                                                    
Speed 30-----------------> 3                                                                                                                  
Speed 40-----------------> 4                                                                                                                   
Speed 50-----------------> 5                                                                                                                  
Speed 60-----------------> 6                                                                                                                   
Speed 70-----------------> 7                                                                                                                   
Speed 80-----------------> 8                                                                                                                   
Speed 90-----------------> 9                                                                                                                   
Speed 100----------------> q                                                                                                                   
Everything OFF-----------> D                                                                                                                   
