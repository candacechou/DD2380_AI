#ifndef _CHECKERS_PLAYER_HPP_
#define _CHECKERS_PLAYER_HPP_

#include "constants.hpp"
#include "deadline.hpp"
#include "move.hpp"
#include "gamestate.hpp"
#include <vector>

namespace checkers
{

class Player
{
public:
  const int side[14] = {0,1,2,3,11,19,27,31,30,28,20,12,4,29};
  const int lRow[9] = {5,6,7,13,14,15,21,22,23};
  const int rRow[9] = {8,9,10,16,17,18,24,25,26};
  const int MaxDepth = 8;
  uint8_t maxPlayer;
  uint8_t minPlayer;
  int alphabeta(const GameState &pState,int depth,int alphas,int betas, uint8_t player,uint8_t me);
  int evaluation(const GameState &pState,uint8_t me);
  uint8_t Other(uint8_t me);
  int protectedCheck(const GameState &pState,uint8_t me);
  int sideCheck(const GameState &pState,uint8_t me);
  int endeval(const GameState &pState,uint8_t me);
  int JumpCheck(const GameState &pState,uint8_t me);


    ///perform a move
    ///\param pState the current state of the board
    ///\param pDue time before which we must have returned
    ///\return the next state the board is in after our move
    GameState play(const GameState &pState, const Deadline &pDue);
};

/*namespace checkers*/ }

#endif
