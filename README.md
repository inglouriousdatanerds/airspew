# airspew

## Video

This readme is a supplement to the instructional video found at: https://youtu.be/oemmYHsJMOQ. Please see the video in addition to reading this document.

## Components

### Control Module
Has an exterior of sturdy, USA manufactured plastic.  The removable front panel has three control switches, described below.  External wiring connections exist for a photoresistor, leaflet dropper and audio output.  Within the control module are an Arduino UNO, an Adafruit Music Maker Sound Shield and an Adafruit FM radio transmitter.  A powerful 9V battery and a microSD card are replaceable components.

### Photoresistor
An integrated component complete with a potentiometer for sensitivity adjustment. The sensitivity can be adjusted by removing the control module’s front panel and rotating the potentiometer with a screwdriver. The photoresistor is extended from the component board with a wire so that it can be attached to the drone’s controllable LED. The output of the photoresistor component board conveniently reads two discrete voltage levels to the Arduino, representing a 1 or a 0.

### Leaflet Dropper
Scaled down to handle index card sized leaflets, this component is made out of fragile balsa wood, plastic hinges, and superglue.  It also features rubberbands and bent paper clips.  Be careful with it; two hinges once fell off when Tim gave it a mean look. Load leaflets by lifting the top lid, which is secured with Velcro (tm).

### Altec Speaker
A powerful, battery-operated waterproof speaker, it was selected primarily because the orange-red color was not selling well at Best Buy and I got a discount.  Please fully charge it before use.

### Landing Gear
This is a manifold of wire, originally designed for caging rabbits.  The edges covered with a duct tape, with a layer of paper towel beneath, are the surfaces on which the drone lands.

### Duct Tape
What project designed by veterans would be complete without a roll of duct tape?  This component is critical for attaching the photoresistor and making the rotor arm opaque to sunlight.

### Zip Ties
A ziploc bag of zipties is used to attach components to the DJI 4 Phantom.

## Installation
There is a video with installation instructions. Please find the video at https://youtu.be/oemmYHsJMOQ. This text is to augment the video.  The drone is designed to carry either the speaker or the leaflet dropper.  One component must be removed before the adding the other.  The fm radio transmitter and wire antenna are permanently stored in the control module.

1. Landing Gear. 
Center drone landing skids on wire landing gear.  The landing gear should be oriented such that it entends port and starboard, **not** fore and aft.  Use 4 of the small red zip ties to secure the landing gear to the drone landing skids.
1. Control Module. 
Attach to the drone aft of the camera.  Make sure control panel switches are facing aft.  Connect using two zipties; there are holes in the control module for this purpose.
1. Photo Resistor. 
As demonstrated in the video, take the photoresistor and center it on one of the controllable LEDs. Use opaque tape to secure the photoresistor against the LED. Use enough tape to completely block out all light so that the control module can be signaled with the LED.
1. Speaker. 
Hold the power button on the speaker until it turn on.  There should be a recorded voice telling you "Powering On".  Press the + button multiple times for maximum output volume.  Attach the 3.5 mm audo jack to the speaker.  Center the speaker beneath the landing gear, so that the speaker is pointed downwards.  Use the two larger, clear zipties to secure the speaker.  Run one of the zipties through the speaker's carrying loop. 
1. Leaflet Dropper. 
**Load the leaflet dropper prior to installation!**  Installation will require some dexterity and finesse.  The dropper is held in place with bent paperclips, whihc in turn are held onto the dropper with rubberbands.  Note there are "studs" in the balsa wood to prevent rubberband slippage.  Center the lid of the leaflet dropper under the drone landing skids.  This placement increases the lift of the drone (decreases it the least actually).  Push the hooked paperclips up through the square holes in the rabbit fencing and position the hooks so the dropper hangs from them.  Connnect the leaflet dropper to the control module with appropriate connector.  The blue wire on the control module connector should be attached to the ground (black) wire on the leaflet dropper.


## Operation

Before turning on the control module, the drone must be powered on, and the LEDs must be placed in the ON state. The control module is signaled when the LEDs are turned off. This means that, depending on the selected mode, when the LEDs are turned off, the Dropper will drop the leaflets, the audio will be turned on, or the radio will start broacasting. Therefore, to reiterate, the LED must be in the ON state before the Control Module is turned on.

### The controls

* Left 3-position switch
  * Radio
  * Leaflet
  * Speaker
* Center 2-position switch
  * ON
  * OFF
* Right 2-position switch
  * Speaker
  * Radio

The left 3-position switch determines the mode. When the mode is changed, the Control Module must be power-cycled. The right 2-position switch determines where the audio is routed. 

### Operating the Loudspeaker

To use the loudspeaker, ensure it is turned on. It will turn itself off if the Control Module is off for an extended period of time. Place the left 3-position switch in the "Audio/Speaker" mode. Place the right 2-position switch in the "Speaker" position. The audio is turned on by turning off the drone's LEDs using the controller.

### Operating the Leaflet Dropper

To use the leaflet dropper, place the left 3-position switch in the "Leaflet" mode.  The leaflets are dropped by turning off the drone's LEDs using the controller.

**Caution:** The 'bomb bay door' of the leaflet dropper can jam shut if it is placed on a flat surface and any weight/force is put on it.  If this happens the leaflet dropper will not open.  This can be repaired by gently (gently!) prying open the bomb bay door.  There should be a slight gap between the door and side of the dropper.


### Operating the FM Radio
Place the left 3-position switch in radio mode, and the right 2-position switch to the "Radio" position. The radio will start transmitting when the drone's LEDs are turned off. Tune in to frequency 91.3 MHz to hear audio message.  Hopefully, this will be "Welcome to the Jungle" by GNR.

