.. author: Samuel Gaehwiler (klangfreund.com)

HiReSam - Closed issues
=======================


Set a minimal size to the plugin window
---------------------------------------

Estimated: 1800s
Measured: 

Include the pitch detector into the spectrum classes
----------------------------------------------------

Estimated: 5200s
Measured:

Split the Spectroscope into a processing and a component unit
-------------------------------------------------------------

Estimated: 7200s
Measured: 13100s


Buffer the gradient to fill the spectroscope in an image
--------------------------------------------------------

Hint: Search for setGradientFill in the JuceDemo

Estimated: 3600s
Measured:  1380s


Display the frequency in the balloon when the mouse is over the Spectroscope
----------------------------------------------------------------------------

Estimated: 1h
Measured: 3005s


Draw a vertical line when the mouse is over the Spectroscope
------------------------------------------------------------

Estimate: 1800
Measured: 3578

I tried to add it to the Spectroscope, but strangely, mouseMove
is never called. S.t. in its base class drow::GraphicalComponent
might prevent this call.
-> Ask Dave.
It is now implemented in the PitchDetectorComponent.


Move the pitch detector label to the bubble.
--------------------------------------------

Estimated: 2700s
Measured: 3948s


Add the picture of me and a balloon with text
---------------------------------------------

Estimated: 3h


Address the JUCE_CHECK_COORDS_ARE_VALID assertion
-------------------------------------------------

Estimate: 1800s
Measured: 2684s


Add the name of the plugin on top of its interface
--------------------------------------------------

Estimate: 40m


Value pattern
-------------

Change the pattern according to http://www.juce.com/forum/topic/value

estimate: 20m
needed: 17.75


Make the FrequencyCaption a subclass of the Spectroscope.
---------------------------------------------------------

estimate: 30m
needed: 55m



About
=====

A list of closed (i.e. implemented or fixed) issues.
In reversed chronological order.
