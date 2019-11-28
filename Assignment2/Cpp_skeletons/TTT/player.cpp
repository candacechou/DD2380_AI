#include "player.hpp"
#include <cstdlib>
#include <limits>
namespace TICTACTOE
{
  int Player::evaluation(const GameState &pState){
    int h = 0;
    int countMax = 0;
    int countMin = 0;
    // // check row
    // for(int i = 0;i < 4;i++){ // each row
    //   countMax = 0;
    //   countMin = 0;
    //   for(int j = 0;j< 4;j++){ // each column
    //     if(pState.at(i,j) == maxPlayer){
    //       countMax++;
    //     }
    //     else if(pState.at(i,j) == minPlayer){
    //       countMin++;
    //     }
    //   }
    //   h = h + 2*Heuristic[countMax][countMin];
    // }
    // // check column
    // for(int i = 0;i < 4;i++){
    //   countMax = 0;
    //   countMin = 0;
    //   for(int j = 0;j < 4;j++){
    //     if(pState.at(j,i)== maxPlayer){
    //       countMax++;
    //     }
    //     else if(pState.at(j,i)== minPlayer){
    //       countMin++;
    //     }
    //   }
    //   h = h + 2*Heuristic[countMax][countMin];
    // }
    // //check diagonals
    // countMax = 0;
    // countMin = 0;
    // for(int i = 0; i < 4;i++){
    //   if(pState.at(i,i)== maxPlayer){
    //     countMax++;
    //   }
    //   else if(pState.at(i,i)== minPlayer){
    //     countMin++;
    //   }
    //   h = h + Heuristic[countMax][countMin];
    // }


    // //check off-diagonals
    // countMax = 0;
    // countMin = 0;
    // for(int i = 0;i < 4;i++){
    //   if(pState.at(i,3-i)== maxPlayer){
    //     countMax++;
    //   }
    //   else if(pState.at(i,3-i)== minPlayer){
    //     countMin++;
    //   }
    //   h = h + Heuristic[countMax][countMin];
    // }
    if(pState.isXWin()&& maxPlayer==CELL_X){
      return 10000000;

    }
    else if(pState.isOWin()&& maxPlayer==CELL_O){
      return 10000000;
    }
    else if(pState.isXWin()&& maxPlayer==CELL_O){
      return -10000000;
    }
    else if(pState.isOWin()&& maxPlayer==CELL_X){
      return -10000000;
    }

    for(int t = 0; t<10;t++){
        countMax = 0;
        countMin = 0;
        for(int i = 0; i<4;i++){
            if(pState.at(WinDeal[t][i])==maxPlayer){
                countMax++;
            }
            if(pState.at(WinDeal[t][i])== minPlayer){
                countMin++;
            }
        }
        h = h + Heuristic[countMax][countMin];
    }
    return h;
}
/* minmax algorithm with alpha and beta pruning*/
int Player::alphabeta(GameState &pState,int depth,int alphas,int betas,uint8_t player){
  // alphas : the current best value achievable by A
  // betas : the current best value achievable by B
  //player : the current Player
  // returns the minmax value of the state
  std::vector<GameState> child;
  pState.findPossibleMoves(child);
  int v = 0;
  int vtemp = 0;
  if (depth == 0 || pState.isEOG() == 1){
    // terminal states
    v = evaluation(pState);
  }
  else if(player == maxPlayer){
    v = -std::numeric_limits<int>::max();
    for(int i = 0; i < child.size();i++){
      vtemp = alphabeta(child[i],depth-1,alphas,betas,minPlayer);
      if(vtemp > v){
        v = vtemp;
      } // find max between alphabeta and v
      if(alphas < v){
        alphas = v;
      } //assign new alphas
      if(betas <= alphas){
        break;
      }// beta pruning
    }
  }

  else if(player == minPlayer){
    v = std::numeric_limits<int>::max();
    for(int i = 0; i<child.size();i++){
      vtemp = alphabeta(child[i],depth-1,alphas,betas,maxPlayer);
      if(vtemp < v){
        v = vtemp;
      } // find min between alphabeta and v
      if(betas > v){
        betas = v;
      }// betas = min(betas,v)
      if(betas <= alphas){
        break;
      }// alpha pruning
    }
  }

  /* return v */
  return v;
}

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::endl;
    int alphas;
    int betas;
    int maxv = 0;
    int maxID = 0;
    int v;
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    int lChild = lNextStates.size();
    // Determine max and min
    maxPlayer = pState.getNextPlayer();
    minPlayer = (maxPlayer == CELL_X) ? CELL_O:CELL_X;
    if (lNextStates.size() == 0) return GameState(pState, Move());
    if (lNextStates.size() == 1) return lNextStates[0]; // there is only one move left

    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */

     for(int i = 0; i< lChild;i++){
       alphas = -std::numeric_limits<int>::max();
       betas  = std::numeric_limits<int>::max();
       v = alphabeta(lNextStates[i],maxDepth,alphas,betas,maxPlayer);
       if(v > maxv){
         maxv = v;
         maxID = i;
       }
     }
    return lNextStates[maxID];
}

/*namespace TICTACTOE*/ }