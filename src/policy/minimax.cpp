#include <cstdlib>
#include <climits>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  auto actions = state->legal_actions;
  int best_value = INT_MIN;
  Move best;

  for(size_t i = 0; i < actions.size(); i++){
    State* next = state->next_state(actions[i]);
    int value = minimax_value(next, depth-1, false);
    if(value > best_value){
        best_value = value;
        best = actions[i];
    }
  }

  return best;
}

int Minimax::minimax_value(State *state, int depth, bool player){
  auto actions = state->legal_actions;
  if(depth == 0){
    if(state->player == player) return state->evaluate();
    else return -state->evaluate();
  }
  if(player){
    int value = INT_MIN;
    for(size_t i = 0; i < actions.size(); i++){
        State* child = state->next_state(actions[i]);
        value = std::max(value, minimax_value(child, depth-1, false));
    }
    return value;
  }
  else{
    int value = INT_MAX;
    for(size_t i = 0; i < actions.size(); i++){
        State* child = state->next_state(actions[i]);
        value = std::min(value, minimax_value(child, depth-1, true));
    }
    return value;
  }
}