# Autonomous-Vehicle
A autonomous vehicle with adaptive cruise control, collision avoidance, traffic light detection/reaction, and turning.

This project utilized an Adafruit vl53l0x lidar sensor and a Pixy2 camera to implement semi-autonomy. The vehicle was able to dynamically modify its cruise control speed
based on the distance of the vehicle in front of it, with the use of the lidar sensor. It included the Pixy2 to read the color and distance of a trafflic light, and based
on the output of that traffic light it would pull up to the trafflic light (Red, Yellow) or continue through (Green). 

(Do note that the collision avoidance overrides this subroutine so that the car will not collide with another vehicle if the light is green) 

Collision avoidance in this project was orignally to be based on acceleration of objects detected by the lidar. However, due to collaboration with the professor, this
was beyond the scope of the project (Hence why acceleration is found but unused), and was instead substituted for braking at a distance of 120 mm.

The Professor was impressed with the project and I recieved an 4.0. 
