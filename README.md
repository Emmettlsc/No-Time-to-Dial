# No-Time-to-Dial
To flash gesture identification code onto Arduino, upload Arduino/IMUClassify.ino

## Messages
Seperate all gestures with a 2s pause.
1. Activation: clockwise wrist turn, clockwise wrist turn  
    Clockwise wrist turn followed by any action that is not a clockwise wrist turn will restart the activation process
2. Messages:
    Single Gesture:
        Clockwise wrist turn: omw
        Counter-clockwise wrist turn: driving
    2 Gestures:
        Up-Down Shaking + clockwise wrist-turn: busy
        Up-Down Shaking + counter-clockwise wrist-turn: omw 5 min
        Up-Down Shaking + up-down shaking: omw 15 min
        Up-Down Shaking + left-right shaking: omw 30 min

        Left-Right Shaking + clockwise wrist-turn: yes
        Left-Right Shaking + counter-clockwise wrist-turn: no
        Left-Right Shaking + up-down shaking: brb
        Left-Right Shaking + left-right shaking: I love ECEM119
