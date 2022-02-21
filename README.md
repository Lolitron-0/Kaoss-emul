
# Abandoned here
# Now on https://gitlab.com/Lolitron/Kaoss-emul
-
-
-
-
-
-
-
-
-
-
# Kaoss-emul

%project_name% is a set of software to process music in real time using only a plug-in in your DAW and a smartphone app. It is a solution to many problems of hardware instruments (such as price, inability to try out the device, amount of needed space, additional equipment and connections). And it's wireless! 

### Idea and goal

The idea was to create an instrument to help beginners (and not only) orient in a world of musical live hardware instruments without buing them. As found out, it is going to be not only test suitable solution.
The wireless connection latency appeared to be acceptably small and it already has a bunch of usable (and useful) effects and a huge space to improve.
In general, it allows you to control your mix on live perfomance using a smartphone and a plugin by applying, recording and managing a set of effects using XY-panel. 

### Software solutions

* Sound processing (plugin) -- mainly JUCE framework (C++)
* Mobile app -- QT application deployed on Android (C++)
* Mobile sockets -- QT UdpSender implementation
* Plugin sockets -- WinSock2 (C++ (basically C))


### Communication

Theese two pieces communicate using sockets on local network (it means they should be connected to one Wi-Fi or hotspot).
Protocol used is obviously UDP due to it's low latency and "real-timeness". (TCP delievers packages in any case which creates additional response time)

### Processing 

Processing part includes many algorithms (however many of them are out-of-the-box).
By now i've created theese effects:
*   LOOPER
*   REV LOOPER
*   DELAY
*   1DELAY
*   TAPE ECHO
*   REVERB
*   CHORUS
*   DECIMATOR
*   PHASER
*   PAN
*   COMP
*   HPF
*   LPF
*   BPF
*   TEMPO
*   PITCH
*   RATE
 
Their physics and logics i'll describe in another file soon.

This list will grow and improve (i mean i'm open for suggestions ;) )
