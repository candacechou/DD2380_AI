#include "player.hpp"
#include <cstdlib>
# include <climits>
namespace checkers
{
int Player::JumpCheck(const GameState &pState,uint8_t player){
  Move pMove;
  int h = 0;
  pMove = pState.getMove();
  //int lmove = pMove.length();
  if(pMove.isJump()){
    if(pState.at(pMove[pMove.length()-1]) & player){
      h += pMove.length()-1;
      // Maxplayer jumps
    }
    else{
      h -= pMove.length()-1;
      // minplayer jumps
    }
  }
    return h;
}
int Player::endeval(const GameState &pState, uint8_t me){
  if(pState.isRedWin() && me == CELL_RED){
    return 2000;
  }
  else if(pState.isWhiteWin() && me == CELL_RED){
    return -2000;
  }
  else if(pState.isWhiteWin() && me == CELL_WHITE){
    return 2000;
  }
  else if(pState.isRedWin() && me == CELL_WHITE){
    return -2000;
  }
  else if(pState.isDraw()){
    return -1000;
  }
  else{
    return 0;
  }
}
int Player::sideCheck(const GameState &pState,uint8_t me){
  int h = 0;
  for(auto i :side){
    if(pState.at(i) & me){
      --h;
    }
    else if(pState.at(i) & Other(me)){
      --h;
    }
  }
  return h;
}
int Player::protectedCheck(const GameState &pState,uint8_t me){
  int Redh = 0;
  int Whiteh = 0;
  for(auto i :lRow){
    if(pState.at(i) & CELL_RED){
      if((pState.at(i-4)& CELL_RED) || (pState.at(i-5)& CELL_RED)){
        ++Redh;
      }
    }
    else if(pState.at(i) & CELL_WHITE){
      if((pState.at(i+4)& CELL_WHITE) || (pState.at(i+3)& CELL_WHITE)){
        ++Whiteh;
      }
    }
  }
  for( auto i : rRow){
    if(pState.at(i)& CELL_RED){
      if((pState.at(i-4)& CELL_RED) || (pState.at(i-3)& CELL_RED)){
        ++Redh;
      }
    }
      else if((pState.at(i)& CELL_WHITE)){
        if((pState.at(i+4)& CELL_WHITE) || (pState.at(i+5) & CELL_WHITE)){
          ++Whiteh;
        }
      }
  }




  if(me ==CELL_RED){
    return (Whiteh - Redh);
  }
  else{
    return (Redh - Whiteh);
  }
}
uint8_t Player::Other(uint8_t me){
  if(me == CELL_RED){
    return CELL_WHITE;
  }
  else return CELL_RED;
}
int Player::evaluation(const GameState &pState,uint8_t me){
  int h = 0;
  int countMinPawn = 0;
  int countMaxPawn = 0;
  int countMinKing = 0;
  int countMaxKing = 0;
  for(int i = 0;i<pState.cSquares;++i){
    if(pState.at(i) & me){
      ++countMaxPawn;
      if(pState.at(i) & CELL_KING){
        ++countMaxKing;
        countMaxPawn--;
      }
    }
    else if(pState.at(i) & Other(me)){
      ++countMinPawn;
      if(pState.at(i) & CELL_KING){
        ++countMinKing;
        countMaxPawn--;
      }
    }
  }
  h = 904*(countMaxPawn - countMinPawn) + 1692*(countMaxKing-countMinKing);
  // h -= 100 * countMinKing;
  // h += JumpCheck(pState,me);
   h += endeval(pState,me);
  // h += sideCheck(pState,me);
  //h += protectedCheck(pState,me);
  return h;
}
int Player::alphabeta(const GameState &pState,int depth,int alphas,int betas, uint8_t player,uint8_t me){
  std::vector <GameState> lNextStates;
  pState.findPossibleMoves(lNextStates);
  int v =0;
  int vtemp = 0;
  if(depth == 0 || lNextStates.size()==0){
    v = evaluation(pState,me);
  }
  else{
    if(player == me){
      v = INT_MIN;
      for(int i = 0; i<lNextStates.size();i++){
        vtemp = alphabeta(lNextStates[i],depth-1,alphas,betas,Other(player),me);
        if(vtemp > v){
          v = vtemp;
        }
        if(alphas < v){
          alphas = v;
        }
        if(betas <= alphas){
          break;
        }
      }
    }
    else if(player!=me){
      v = INT_MAX;
      for(int i = 0; i<lNextStates.size();i++){
        vtemp = alphabeta(lNextStates[i],depth-1,alphas,betas,Other(player),me);
        if(vtemp < v){
          v = vtemp;
        }
        if(betas > v){
          betas = v;
        }
        if(betas <= alphas){
          break;
        }
    }
  }
}
  return v;
}
GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::endl;
    int v = 0;
    int vtemp = 0;
    int maxv = INT_MIN;
    int maxID = 0;
    int alphas = INT_MIN;
    int betas = INT_MAX;
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    maxPlayer = pState.getNextPlayer();
    minPlayer = Other(maxPlayer);
    if (lNextStates.size() == 0) return GameState(pState, Move());
    if (lNextStates.size() == 1) return lNextStates[0];
    for(int i = 0; i< lNextStates.size();i++){
      if(pDue.now() > pDue-0.1){
        break;
      }
      v = alphabeta(lNextStates[i],MaxDepth,alphas,betas,minPlayer, maxPlayer);
      if(v > maxv){
        maxv = v;
        maxID = i;
      }
    }
    return lNextStates[maxID];
    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */

}

/*namespace checkers*/ }
