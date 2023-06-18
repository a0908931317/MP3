#include <cstdlib>
#include <climits>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Alphabeta::get_move(State *state, int depth){
  auto actions = state->legal_actions;
  int best_value = INT_MIN;
  Move best = actions[0];

  for(size_t i = 0; i < actions.size(); i++){
    State* next = state->next_state(actions[i]);
    int value = alphabeta_value(next, depth-1, INT_MIN, INT_MAX, 1-state->player);
    if(value > best_value){
        best_value = value;
        best = actions[i];
    }
  }

  return best;
}

int Alphabeta::alphabeta_value(State *state, int depth, int alpha, int beta, int player){
  auto actions = state->legal_actions;
  if(depth == 0) return state->evaluate();
  if(depth % 2 == 0){
    int value = INT_MIN;
    for(size_t i = 0; i < actions.size(); i++){
        State* child = state->next_state(actions[i]);
        alpha = value = std::max(value, alphabeta_value(child, depth-1, alpha, beta, 1-player));
        if(alpha >= beta) break;
    }
    return value;
  }
  else{
    int value = INT_MAX;
    for(size_t i = 0; i < actions.size(); i++){
        State* child = state->next_state(actions[i]);
        beta = value = std::min(value, alphabeta_value(child, depth-1, alpha, beta, 1-player));
        if(beta <= alpha) break;
    }
    return value;
  }
}