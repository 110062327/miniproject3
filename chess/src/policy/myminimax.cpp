#include <cstdlib>

#include "../state/state.hpp"
#include "./myminimax.hpp"
/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
int heuristicvalue(State mystate){
    Board b=mystate.board;
    int white=0;
    for(int i=0;i<6;i++){
      for(int j=0;j<5;j++){
        if(b.board[0][i][j]==1){
          white+=2;
        }
        if(b.board[0][i][j]==2){
          white+=6;
        }
        if(b.board[0][i][j]==3){
          white+=7;
        }
        if(b.board[0][i][j]==4){
          white+=8;
        }
        if(b.board[0][i][j]==5){
          white+=20;
        }
        if(b.board[0][i][j]==6){
          white+=100;
        }
      }
    }
    int black=0;
    for(int i=0;i<6;i++){
      for(int j=0;j<5;j++){
        if(b.board[1][i][j]==1){
          black+=2;
        }
        if(b.board[1][i][j]==2){
          black+=6;
        }
        if(b.board[1][i][j]==3){
          black+=7;
        }
        if(b.board[1][i][j]==4){
          black+=8;
        }
        if(b.board[1][i][j]==5){
          black+=20;
        }
        if(b.board[1][i][j]==6){
          black+=100;
        }
      }
    }
    return white-black;
}
/*
function minimax(node, depth, maximizingPlayer) is
    if depth = 0 or node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, minimax(child, depth − 1, FALSE))
        return value
    else (* minimizing player *)
        value := +∞
        for each child of node do
            value := min(value, minimax(child, depth − 1, TRUE))
        return value

*/
int minimax(State& node, int depth, bool maximizingPlayer){
  if(depth==0||std::abs(heuristicvalue(node))>=50){
    return heuristicvalue(node);
  }
  if(maximizingPlayer){
    int value=-1e9;
    node.get_legal_actions();
    for(auto child:node.legal_actions){
      State* next_move=node.next_state(child);
      value = std::max(value, minimax(*next_move, depth-1, false));
    }
    return value;
  }else{
    int value=1e9;
    node.get_legal_actions();
    for(auto child:node.legal_actions){
      State* next_move=node.next_state(child);
      value = std::min(value, minimax(*next_move, depth-1, true));
    }
    return value;
  }
}

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move myclass::get_move(State *state, int depth){

  if(!state->legal_actions.size())
    state->get_legal_actions();
  Move ans;
  if(state->player==0){//white
    int value=-1e9;
    for(auto child:state->legal_actions){
      State* next_state=state->next_state(child);
      int tmp=minimax(*next_state, depth, true);
      if(tmp>value){
        value=tmp;
        ans=child;
      }
    }
  }else{
    int value=1e9;
    for(auto child:state->legal_actions){
      State* next_state=state->next_state(child);
      int tmp=minimax(*next_state, depth, true);
      if(tmp<value){
        value=tmp;
        ans=child;
      }
    }
  }
  return ans;
  
}
