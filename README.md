# PizzaBOT
CyBot pizza delivery project for CprE 288.

High-level mission goals:
The Cy-Bots purpose will be to accurately be able to navigate through a simulated traffic and deliver the pizza to the the destination in a timely manner

- Cybot Communication	-  Offering manual control of the PizzaBOT for when extra granularity is needed, along with fulfillment information.
- Cybot Movement  -	Safely deliver pizza
- Object Detection	-  Identify on going traffic, potholes, and objects.
- Object Avoidance	-  By stopping and waiting for traffic to pass by, avoiding potholes, and avoid bumping objects.
- Boundary Adherence	-  Avoid leaving the “Road”/damaging property
- Arrival at Destination	-  Slowing down to avoid damaging pizza
- User Interface	-  Potential UI with a progress bar, worst case a terminal.
- Base Station Control	-  Movement, horn button, information about delivery location.
- Other Application Specific Functionality -	Celebrate pizza arrival! Little tune/victory spin

LIST OF ALL FEATURES:

  Test Field
  - Grid system (Coordinates for destination)
  - Potholes - different colored strips
  - Vechicles - Other cyBots
  - Pedestrians - Skinny Tubes
  - Delivery - Big Tube
  - Buildings - Cardboard or Tape??

  puTTY
  - Get progress reports (at every block)
      * direction
      * objects at intersection
      * What road is open
      * Coordinates
      * Tells Driver when its finished
  - Handle movement and any other input
  - Speed
  - Make UI instead of puTTY??

  Movement / Interface
  - wasd for for movement with puTTY, each control will move one block
  - Reset Button for movement || collision
  - Scan button
  - Horn button
  - Victory Song Button
  - Needs to keep track of coordinates on field
  - Slowing Down (Pulls into driveway)

  Ping Sensor || IR Sensor
  - Calculate distace from IR with Ping sensor (Lab 08)
  - Scan for object (Cars && Pedestrians)
  - Differentiate between different objects
  - Detect which side of intersection objects are located at

  Below Sensor 
  - Detect Potholes
  
  Bump Detection
  - Stops when lightly taps house door

  Music
  - Play Horn
  - Play Victory Tune
  - Yell at Pedistrian??

  LCD
  - Cost
  - Speedometer
  
