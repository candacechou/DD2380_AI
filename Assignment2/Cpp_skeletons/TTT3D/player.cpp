#include "player.hpp"
#include <cstdlib>

namespace TICTACTOE3D
{
int Player::evaluation(const GameState &pState){
    int h = 0;
    int countMax = 0;
    int countMin = 0;
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
    else  if(pState.isDraw()) return 0;
    // // check row in 4 plains
    // for(int t = 0; t<4;t++){
    //     countMax = 0;
    //     countMin = 0;
    //     for(int i = 0; i<4;i++){
    //         for(int j = 0; j<4;j++){
    //             if(pState.at(t*16+i*4+j) == maxPlayer){
    //                 countMax++;
    //             }
    //             if(pState.at(t*16+i*4+j) == minPlayer) {
    //                 countMin++;
    //             }
    //         }
    //         h = h + Heuristic[countMax][countMin];
    //     } 
    // }
    // // check col in 4 plians
    // for(int t = 0;t<4;t++){
    //     countMax = 0;
    //     countMin = 0;
    //     for(int i = 0;i<4;i++){
    //         for(int j = 0; j<4;j++){
    //             if(pState.at(t*16+j*4+i)==maxPlayer){
    //                 countMax++;
    //             }
    //             if(pState.at(t*16+j*4+i)==minPlayer){
    //                 countMin++;
    //             }
    //         }
    //         h = h + Heuristic[countMax][countMin];
    //     }
    // }
    // // check for diagonal in 4 plains
    // for(int t = 0; t<4;t++){
    //     countMax = 0;
    //     countMin = 0;
    //     for(int i = 0; i<4;i++){
    //         if(pState.at(16*t +4*i + i)== maxPlayer){
    //             countMax++;
    //         }
    //         if(pState.at(16*t +4*i + i)== minPlayer){
    //             countMin++;
    //         }
    //     }
    //     h = h + Heuristic[countMax][countMin];
    // }
    // // check for of diagonal in 4 plains
    // for(int t = 0; t<4;t++){
    //     countMax = 0;
    //     countMin = 0;
    //     for(int i = 0; i<4;i++){
    //         if(pState.at(16*t +4*i +3-i)== maxPlayer){
    //             countMax++;
    //         }
    //         if(pState.at(16*t +4*i +3-i)== minPlayer){
    //             countMin++;
    //         }
    //     }
    //     h = h + Heuristic[countMax][countMin];
    // }
    // //check for the vertically down
    // for(int t = 0 ; t<16;t++){
    //     countMax = 0;
    //     countMin = 0;
    //     for(int i = 0; i<3;i++){
    //         if(pState.at(t+16*i) == maxPlayer){
    //             countMax++;
    //         }
    //         if(pState.at(t+16*i) == minPlayer){
    //             countMin++;
    //         }
    //     }
    //     h = h + Heuristic[countMax][countMin];

    // }
    // // check for the diagonal facing to us
    // for(int t = 0 ;t <4;t++){//row
    //     countMax = 0;
    //     countMin = 0;
    //     for(int i = 0; i<4;i++){// layer
    //         if(pState.at(4 * t + 17 * i) == maxPlayer){
    //             countMax++;
    //         }
    //         if(pState.at(4 * t + 17 * i) == minPlayer){
    //             countMin++;
    //         }
    //     }
    //     h = h + Heuristic[countMax][countMin];
    // }
    // // check for the off diagonal facing to us
    // for(int i = 0; i<4;i++){
    //     countMax = 0;
    //     countMin = 0;
    //     for(int t = 0; t<4;t++){
    //         if(pState.at(i * 4 + 3 + 15 * t) == maxPlayer){
    //             countMax++;
    //         }
    //         if(pState.at(i * 4 + 3 + 15 * t) == minPlayer){
    //             countMin++;
    //         }
    //     }
    //     h = h + Heuristic[countMax][countMin];
    // }
    // // check for the diagonal point to the environment
    // for(int t = 0 ; t<4 ; t++){
    //     countMax = 0;
    //     countMin = 0;
    //     for(int i = 0; i<4;i++){
    //         if(pState.at(t + 20 * i) == maxPlayer){
    //             countMax++;
    //         }
    //         if(pState.at(t + 20 * i) == minPlayer){
    //             countMin++;
    //         }
    //     }
    //     h = h + Heuristic[countMax][countMin];
    // }
    // // check for the off diagonal point to the environment
    // for(int t = 0; t<4;t++){
    //     countMax = 0;
    //     countMin = 0;
    //     for(int i = 0; i<4;i++){
    //         if(pState.at(12 + t + 12 * i) == maxPlayer){
    //             countMax++;
    //         }
    //         if(pState.at(12 + t + 12 * i) == minPlayer){
    //             countMin++;
    //         }
    //     }
    //     h = h + Heuristic[countMax][countMin];
    // }
    // // the big diagonals - (0,21,42,63)
    // countMax = 0;
    // countMin = 0;
    // for(int i = 0; i<4;i++){
    //     if(pState.at(21*i) == maxPlayer){
    //             countMax++;
    //         }
    //         if(pState.at(21*i) == minPlayer){
    //             countMin++;
    //         }
    // }
    // h = h + Heuristic[countMax][countMin];
    // // the big diagonals -(3,22,41,60)
    // countMax = 0;
    // countMin = 0;
    // for(int i = 0; i<4;i++){
    //     if(pState.at(3 + 19 * i) == maxPlayer){
    //             countMax++;
    //         }
    //         if(pState.at(3 + 19 * i) == minPlayer){
    //             countMin++;
    //         }
    // }
    // h = h + Heuristic[countMax][countMin];
    // // the big diagonals -(12,25,38,51)
    // countMax = 0;
    // countMin = 0;
    // for(int i = 0; i<4;i++){
    //     if(pState.at(12+13*i) == maxPlayer){
    //             countMax++;
    //         }
    //         if(pState.at(12+13*i) == minPlayer){
    //             countMin++;
    //         }
    // }
    // h = h + Heuristic[countMax][countMin];
    // // the big diagonals - (15,26,37,48)
    // countMax = 0;
    // countMin = 0;
    // for(int i = 0; i<4;i++){
    //     if(pState.at(15+11*i) == maxPlayer){
    //             countMax++;
    //         }
    //         if(pState.at(15+11*i) == minPlayer){
    //             countMin++;
    //         }
    // }
    // h = h + Heuristic[countMax][countMin];
    for(int t = 0; t<76;t++){
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

/*namespace TICTACTOE3D*/ }
