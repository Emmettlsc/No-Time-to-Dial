To run GestureClassification.ipynb:
1. upload Arduino/ImuSerial.ino to Arduino
2. change the 2nd cell of GestureClassification.ipynb to the port that Arduino is connected to
3. run the rest of the cells

Current Set of Gestures
-----------------------
'clockwise_wrist_turn': like tightening a screw
- I'm thinking we can do this 2x as an activation gesture
'counterclockwise_wrist_turn': like untightening a screw
- and this 2x as a deactivation gesture

'palm_down_neutral': palm facing down, parallel to the ground, perpendicular to your body
- default state, not a word. The other 4 below are messages
'palm_down_left_swipe': palm facing down, parallel to the ground, perpendicular to your body, move hand left to -45 deg then back to neutral
'palm_down_right_swipe': palm facing down, parallel to the ground, perpendicular to your body, move hand up to 45 deg then back down
'palm_down_up': palm facing down, parallel to the ground, perpendicular to your body, move hand right to 45 deg then back down
'palm_down_down': palm facing down, parallel to the ground, perpendicular to your body, move hand down to -45 deg then back up

'palm_left_neutral': palm facing left like you're about to shake hands, perpendicular to your body
- another default state, not a word. The other 4 below are messages
'palm_left_classic_slap': above postion, move hand to -45 deg then back
'palm_left_backhand_slap': move hand from neutral to 45 deg then back
'palm_left_up_chop': move hand from neutral up to 45 deg then back down
'palm_left_down_chop': move hand from neutral down to -45 deg then back up

- 12 words total. 2 for de/activation, 2 for neutral modes, 8 for actual messages
- I tried stuff like making a circle motion and it didnt work. It may require using a larger window length to train on