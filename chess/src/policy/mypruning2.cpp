#include <cstdlib>

#include "../state/state.hpp"
#include "./mypruning2.hpp"
/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
int _heuristicvalue2(State mystate){
    Board b=mystate.board;
    int white=0;
    for(int i=0;i<6;i++){
      for(int j=0;j<5;j++){
        if(b.board[0][i][j]==0){
          continue;
        }
        if(b.board[0][i][j]==1){
          white+=2;
        }
        else if(b.board[0][i][j]==2){
          white+=6;
        }
        else if(b.board[0][i][j]==3){
          white+=7;
        }
        else if(b.board[0][i][j]==4){
          white+=8;
        }
        else if(b.board[0][i][j]==5){
          white+=20;
        }
        else if(b.board[0][i][j]==6){
          white+=1000;
        }
      }
    }
    int black=0;
    for(int i=0;i<6;i++){
      for(int j=0;j<5;j++){
        if(b.board[1][i][j]==0){
          continue;
        }
        if(b.board[1][i][j]==1){
          black+=2;
        }
        else if(b.board[1][i][j]==2){
          black+=6;
        }
        else if(b.board[1][i][j]==3){
          black+=7;
        }
        else if(b.board[1][i][j]==4){
          black+=8;
        }
        else if(b.board[1][i][j]==5){
          black+=20;
        }
        else if(b.board[1][i][j]==6){
          black+=1000;
        }
      }
    }
    return white-black;
}
/*
function alphabeta(node, depth, α, β, maximizingPlayer) is
    if depth == 0 or node is terminal then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, alphabeta(child, depth − 1, α, β, FALSE))
            α := max(α, value)
            if value ≥ β then
                break (* β cutoff *)
        return value
    else
        value := +∞
        for each child of node do
            value := min(value, alphabeta(child, depth − 1, α, β, TRUE))
            β := min(β, value)
            if value ≤ α then
                break (* α cutoff *)
        return value
*/
class MoveAndValue:Move {
  public:
    Move movedata;
    int value;
    MoveAndValue(Move m, int v){
      movedata=m;
      value=v;
    }
};
Move lastmove;
MoveAndValue alphabeta2(State& node, int depth,int a,int b, bool maximizingPlayer){
  if(depth==0||node.game_state == WIN){//std::abs(_heuristicvalue(node))>=500
    return MoveAndValue(lastmove,_heuristicvalue2(node));
  }
  if(maximizingPlayer){
    int value=-1e9;
    Move returnmove;
    for(auto child:node.legal_actions){
      State* next_move=node.next_state(child);
      lastmove=child;
      int oldvalue=value;
      value = std::max(value, alphabeta2(*next_move, depth-1,a,b, false).value);
      if(oldvalue!=value){
        returnmove=child;
      }
      a=std::max(a,value);
      if(value>b){
        break;
      }
    }
    return MoveAndValue(returnmove,value);
  }else{
    int value=1e9;
    Move returnmove;
    for(auto child:node.legal_actions){
      State* next_move=node.next_state(child);
      lastmove=child;
      int oldvalue=value;
      value = std::min(value, alphabeta2(*next_move, depth-1,a,b, true).value);
      if(oldvalue!=value){
        returnmove=child;
      }
      b=std::min(b,value);
      if(value<a){
        break;
      }
    }
    return MoveAndValue(returnmove,value);
  }
}

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move _myclass2::get_move(State *state, int depth){

  if(!state->legal_actions.size())
    state->get_legal_actions();
  Move ans;
  if(state->player==0){//white
    return alphabeta2(*state,depth,-1e9,1e9,true).movedata;
    int value=-1e9;
    for(auto child:state->legal_actions){
      State* next_state=state->next_state(child);
      int tmp=alphabeta2(*next_state, depth,-1e9,1e9, true).value;
      if(tmp>value){
        value=tmp;
        ans=child;
      }
    }
  }else{
    int value=1e9;
    for(auto child:state->legal_actions){
      State* next_state=state->next_state(child);
      int tmp=alphabeta2(*next_state, depth,-1e9,1e9, true).value;
      if(tmp<value){
        value=tmp;
        ans=child;
      }
    }
  }
  return ans;
  //return alphabeta(*state,depth,-1e9,1e9,true).movedata;
}
