/***********************************************************************
 * Header File:
 *    Piece: 
 * Author:
 *    
 * Summary:
 *    
 ************************************************************************/

#pragma once

using namespace std;



class Piece {
public:
   RC[] getPossibleMoves();
   bool getHasMoved() { return false; };
   bool move() { return false; }

protected:
   bool hasMoved;
   bool isWhite;

private:
   
};