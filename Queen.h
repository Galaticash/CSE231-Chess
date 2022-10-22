/***********************************************************************
* Header File:
*    Queen
* Author:
*		Ashley DeMott, Logan Huston
* Summary:
*		A queen in chess. This file contains info on drawing a queen.
************************************************************************/

#pragma once
#ifndef PIECE_CLASS
#define PIECE_CLASS
#include "Piece.h"
#endif

class Queen : public Piece
{
public:
	// Call Piece's constructor
	Queen(RC position, bool isWhite) : Piece(position, isWhite)
   {
      this->type = 'q';   // Queen type
      this->rectangles = {
      { 8,8,   5,8,   5,5,   8,5 },     // right crown jewel
      {-8,8,  -5,8,  -5,5,  -8,5 },     // left crown jewel
      { 2,8,  -2,8,  -2,5,   2,5 },     // center crown jewel
      { 7,5,   5,5,   1,0,   5,0 },     // right crown holder
      {-7,5,  -5,5,  -1,0,  -5,0 },     // left crown holder
      { 1,5,   1,0,  -1,0,  -1,5 },     // center crown holder
      { 4,0,  -4,0,  -4,-2,  4,-2},     // upper base
      { 6,-3, -6,-3, -6,-5,  6,-5},     // middle base
      { 8,-6, -8,-6, -8,-8,  8,-8}      // base
      };
   };
   set <Move> getPossibleMoves(Board* board);
};