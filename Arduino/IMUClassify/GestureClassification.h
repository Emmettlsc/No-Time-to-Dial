int buf_idx = 0;
const int N = 4;
int buffer[N];
int curr_target = -1;
int prev_target = -1;
int prev_prev_target = -1;

enum actions {
  error = -1,
  neutral,
  clockwise,
  counterclockwise,
  horizontal_shake,
  vertical_shake
};

enum states {
  wait1,
  wait2,
  wait3,
  msg_1,
  msg_2,
  msg_3,
  msg_4
};
const int n_actions = vertical_shake+1;
const int n_states = msg_4+1;
int target_hist[n_states];
String target_map[n_actions] = {"neutral", "clockwise", "counterclockwise", "horizontal_shake", "vertical_shake"};
String state_map[n_states] = {"wait1", "wait2", "wait3", "omw", "omw 5 min", "omw 15 min", "omw 30 min"};


int map_prediction(String prediction) {
  int target;
  if(prediction == "neutral")
    target = neutral;
  else if(prediction == "clockwise")
    target = clockwise;
  else if(prediction == "counterclockwise")
    target = counterclockwise;
  else if(prediction == "horizontal_shake") // this isnt a typo, I accidentially switched the lables while training
    target = vertical_shake;
  else if(prediction == "vertical_shake")
    target = horizontal_shake;
  else
    target = error;

  return target;
}

int state = wait1;
int s0 = -1, s1 = -1, s2 = -1;

int detect_gesture(int target) {
  buffer[buf_idx%N] = target;

  if(buf_idx >= N) {
    // use the most frequently detected target in
    // a window of N elements
    memset(target_hist, 0, sizeof(int)*n_actions);
    for(int i=0; i<N; i++)
      target_hist[buffer[(buf_idx-i)%N]]++;
    int max_state_count = -1;
    prev_target = curr_target;
    for(int i=0; i<n_actions; i++) {
      if(target_hist[i] > max_state_count) {
        max_state_count = target_hist[i];
        curr_target = i;
      }
    }
    Serial.println(target_map[curr_target]);

    // All state transition changes require neutral-[some non-neutral state]-neutral
    if(state == msg_1 || state == msg_2 || state == msg_3 || state == msg_4)
      state = wait1;
    if(curr_target != prev_target) {
      s0 = s1;
      s1 = prev_target;
      s2 = curr_target;
      Serial.print(s0);
      Serial.print(s1);
      Serial.println(s2);

      if(state == wait1) {
        if(s0 == neutral && s1 == clockwise && s2 == neutral)
          state = wait2;
      }
      else if(state == wait2) {
        if(s0 == neutral && s1 == clockwise && s2 == neutral)
          state = wait3;
        else if(s2 != neutral && s2 != clockwise) // TODO havent thought this out properly
          state = wait1;
      }
      else if(state == wait3) {
        if(s0 == neutral && s1 != neutral && s2 == neutral) {
          if(s1 == clockwise) state = msg_1;
          else if(s1 == counterclockwise) state = msg_2;
          else if(s1 == vertical_shake) state = msg_3;
          else if(s1 == horizontal_shake) state = msg_4;
        }
      }
    }
    Serial.println(state_map[state]);
  }

  buf_idx++;
  
  return state;
}

bool state_is_message(int state) {
  return state == msg_1 || state == msg_2 || state == msg_3 || state == msg_4;
}