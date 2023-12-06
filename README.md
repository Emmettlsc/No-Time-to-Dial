# No-Time-to-Dial
To flash gesture identification code onto Arduino, upload Arduino/IMUClassify.ino

## Messages
Seperate all gestures with a 2s pause.
1. Activation: clockwise wrist turn, clockwise wrist turn  
    Clockwise wrist turn followed by any action that is not a clockwise wrist turn will restart the activation process
2. Messages:
    Single Gesture:
        msg1: Clockwise wrist turn: omw
        msg2: Counter-clockwise wrist turn: driving
    2 Gestures:
        msg3: Up-Down Shaking + clockwise wrist-turn: busy
        msg4: p-Down Shaking + counter-clockwise wrist-turn: omw 5 min
        msg5: Up-Down Shaking + up-down shaking: omw 15 min
        msg6: Up-Down Shaking + left-right shaking: omw 30 min

        msg7: Left-Right Shaking + clockwise wrist-turn: yes
        msg8: Left-Right Shaking + counter-clockwise wrist-turn: no
        msg9: Left-Right Shaking + up-down shaking: brb
        msg10: Left-Right Shaking + left-right shaking: I love ECEM119

## State Diagram
cw = clockwise, ccw = counter-clockwise, ud = up-down, lr = left-right

      cw         cw
wait1 ---> wait2 ---> wait3
/\                      |
|                    cw |
--------------- msg1----|
|                    ccw|
--------------- msg2----|
|                       |
|       cw              |
|<--msg3---|            |
|       ccw|         ud |
|<--msg4---|<--wait4----|
|       ud |            |
|<--msg5---|            |
|       lr |            |
|<--msg6---|            |
                        |
                        |
                    lr  |
   same as     wait5----|
above block
for msg7-10