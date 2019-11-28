#include "Player.hpp"
#include <cstdlib>
#include <iostream>
#include "HMM.hpp"
namespace ducks
{
    struct SpeciesModel{
        
        int ID;
        HMM Model;

    };
    int Oldround = -1;
    int Newround = 0;
    int timestep = 0;
    float shootThreshold = 0.65;
    int Species_Check[6] = {0,0,0,0,0,0}; // checking if we already have species models
    std::vector<ESpecies> lGuesses;
    std::vector<SpeciesModel> SPECIES_MODELS;
    int GuessCorrect = 0; // guess correct
    int GuessWrong = 0; // guess wrongly
    int GuessNSure = 0;
    int tryhit = 0;
    int HitCorrect = 0;
    int tryguess = 0;
    int TotalGuess = 0;
    
Player::Player()
{
}
int Player::birdID(Bird bird){
    float MaxmaxProb = -1;
    float TempProb = 0;
    float MaxmaxID = -1;
    int tempID = -1;
    
    for(auto element: SPECIES_MODELS ){
        TempProb = element.Model.Prob_sequence(bird);
         if(TempProb > MaxmaxProb){
             MaxmaxProb = TempProb;
             MaxmaxID = element.ID;
         }
    }
    //std::cerr<<"prob: "<< MaxmaxProb<<std::endl;
    // if(MaxmaxProb<0.01){
    //     if(Newround <2){
    //         return 0;
    //     }
    //     else{
    //         return -1;
    //     }
    // }
    return MaxmaxID;
}
    
Action Player::shoot(const GameState &pState, const Deadline &pDue)
{   //return cDontShoot;
    int maxID = -1;
    int nextMove = 0;
    float maxProb = 0;
    float sum = 0;
    int i = 0;
    int GuessSpecies;
    int preshoot = 60;
    if(pState.getNumPlayers()>1) preshoot = 20;
    //std::cerr<<"hello!"<<std::endl;
    Newround = pState.getRound();
    if(Newround != Oldround){
        timestep = 1;
    }
    if(Newround < 2){
        return cDontShoot;
    }
    else{
        if(timestep == 1){
        timestep ++;
        Oldround = Newround;
        return cDontShoot;
    }
        if(timestep < preshoot && timestep > 1){
            timestep ++;
            Oldround = Newround;
            return cDontShoot;
        }
        else{
            while(pDue.remainingMs() > 400 && i < pState.getNumBirds()){
                if(pState.getBird(i).isAlive()){
                    HMM tmpM;
                    tmpM.Initialization(pState.getBird(i));
                    tmpM.Build_HMM();
                    tmpM.firstBuild = 1;
                    //std::cerr<< Birdmodel[i].Probnobservation<<std::endl;
                    if(tmpM.converge){
                        tmpM.Prediction(pState.getBird(i));
                        //std::cerr<<"here"<<std::endl;
                        //std::cerr<<Birdmodel[i].Probnobservation<<std::endl;
                        sum += tmpM.Probnobservation;
                        GuessSpecies = birdID(pState.getBird(i));
                        // if(tmpM.Probnobservation > shootThreshold  && GuessSpecies !=5 && GuessSpecies != -1 ){
                        //     tryhit++;
                        //     return Action(i,EMovement(tmpM.nobservation));
                        // }
                        if(maxProb < tmpM.Probnobservation && GuessSpecies !=5){
                            maxID = i;
                            maxProb = tmpM.Probnobservation;
                            nextMove = tmpM.nobservation;

                        }
                    }
                }
                i++;
            }   
        // for(int i = 0; i<pState.getNumBirds();i++){
            
        // }

        timestep ++;
        Oldround = Newround; 
        //return cDontShoot;
    //std::cerr<<"sum "<<sum<<std::endl;
    //std::cerr<<maxProb<<std::endl;
    if(sum == 0){
        return cDontShoot;
    }
    else{
        //maxProb = maxProb / sum;
        std::cerr<<"------------------------------"<<std::endl;
        std::cerr<<" current round: "<< Newround <<std::endl;
        std::cerr<<" current timestep: "<< timestep << std::endl;
        std::cerr<<" max Prob: "<< maxProb << " ID: "<< maxID << " MOVE: "<< nextMove << std::endl;
        if(maxProb > shootThreshold){
            //std::cerr<<"hit!"<<std::endl;
            tryhit++;
            return Action(maxID,EMovement(nextMove));
        }
        else return cDontShoot;
    }
}


    }
    






    
    // This line choose not to shoot
    //return cDontShoot;

    //This line would predict that bird 0 will move right and shoot at it
    //return Action(0, MOVE_RIGHT);
}

std::vector<ESpecies> Player::guess(const GameState &pState, const Deadline &pDue)
{
    /*
     * Here you should write your clever algorithms to guess the species of each bird.
     * This skeleton makes no guesses, better safe than sorry!
     */
    //std::cerr<<"guess"<<std::endl;
    lGuesses.clear();
    lGuesses.assign(pState.getNumBirds(), SPECIES_UNKNOWN);
    if(pState.getRound() < 1){
        for(int i = 0; i<pState.getNumBirds();i++){
            TotalGuess++;
            lGuesses[i] = SPECIES_PIGEON;
        }
    }
    else{
        
        for(int i = 0; i < pState.getNumBirds();i++){
            TotalGuess++;
            //std::cerr<<birdID(pState.getBird(i));
            lGuesses[i] = ESpecies(birdID(pState.getBird(i)));
        }
    }
    
    //std::vector<ESpecies> lGuesses(pState.getNumBirds(), SPECIES_UNKNOWN);
    
    return lGuesses;
}

void Player::hit(const GameState &pState, int pBird, const Deadline &pDue)
{
    /*
     * If you hit the bird you are trying to shoot, you will be notified through this function.
     */
    HitCorrect++;
    
    std::cerr<<"we try to hit: "<< tryhit<<std::endl;
    std::cerr<<"hit correctly: "<< HitCorrect<<std::endl;
    
    std::cerr << "HIT BIRD!!!" << std::endl;
    

}

void Player::reveal(const GameState &pState, const std::vector<ESpecies> &pSpecies, const Deadline &pDue)
{
    /*
     * If you made any guesses, you will find out the true species of those birds in this function.
     */
    // if round = 0 , we simply add the models 
    
    
    if(pState.getRound() < 1){
        for(int i = 0; i<pState.getNumBirds();++i){
            SpeciesModel tempModel;
            tempModel.ID = pSpecies[i];
            tempModel.Model.Initialization(pState.getBird(i));
            tempModel.Model.Build_HMM();
            tempModel.Model.firstBuild = 1;
            if(tempModel.Model.converge == 1){
                SPECIES_MODELS.push_back(tempModel);
                Species_Check[pSpecies[i]]++;
                //std::cerr<<"reveal"<<std::endl;
            }
        }
    }
    else{
        for(int i = 0; i<pState.getNumBirds();++i){
            if(pSpecies[i]!=-1){
                SpeciesModel tempModel;
                tempModel.ID = pSpecies[i];
                tempModel.Model.Initialization(pState.getBird(i));
                tempModel.Model.Build_HMM();
                tempModel.Model.firstBuild = 1;
                if(tempModel.Model.converge == 1){
                    SPECIES_MODELS.push_back(tempModel);
                    Species_Check[pSpecies[i]]++;
                }

            }
        }
    }
    for(int i = 0 ;i<pState.getNumBirds();++i){
        
        if(pSpecies[i]==lGuesses[i] && pSpecies[i]!=-1){
            GuessCorrect++;
        }
        else if (pSpecies[i]!=lGuesses[i] && pSpecies[i]!=-1){
            GuessWrong++;
        }
        else{
            GuessNSure++;

        }
    }
    // checking
    for(int i = 0 ;i<6;i++){
        std::cerr<< Species_Check[i]<<" ";
    }
    std::cerr<<std::endl;
    std::cerr<<"guess correct: "<< GuessCorrect << std::endl;
    std::cerr<<"guess incorrect: "<< GuessWrong << std::endl;
    std::cerr<<"guess Nsure: "<< GuessNSure << std::endl;
    std::cerr<<"total Guess: "<< TotalGuess<<std::endl;
    
}


} /*namespace ducks*/

