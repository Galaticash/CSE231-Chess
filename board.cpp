/***********************************************************************
* Source File:
*      Board
* Author:
*      Ashley DeMott
* Summary:
*      Stores a collection of Piece pointers and moves Pieces to
*      new positions on the Board. Also keeps track of the state of
*      the Chess game (lastMove and currentTeam)
************************************************************************/

#include "board.h"

/***************************************
* INSERT PIECE
* Replaces the current Piece with a the insertPiece
********************************************/
void Board::insertPiece(Piece* insertPiece)
{
	// Get the row/column position of the Piece
	int row = insertPiece->getCurrentPosition().getRow();
	int col = insertPiece->getCurrentPosition().getCol();

	// Delete the previous Piece at that position (in most cases, a Space)
	// WARNING: Previous Pieces should be deleted, but errors 
	//			stopped when previous Piece is NOT deleted
	if (false)
	{
		delete& (piecesBoard[row][col]);
	}

	// Assign the position on the board the Piece pointer
	this->piecesBoard[row][col] = insertPiece;
}

 /***************************************************
 * MOVE
 * Performs the given Move. 
 * currentMove: Move to be performed
 *		 Returns: The last Move succesfully performed
 ****************************************************/
Move Board::move(Move currentMove)
{
	// Get the To and From positions of the Move
	RC pieceCurrentPos = currentMove.getPositionFrom();
	RC pieceDestination = currentMove.getPositionTo();

	// If the two locations are on the board, and they are not the same, and the current Piece is on the current Team
	if (isValidPosition(pieceCurrentPos) && isValidPosition(pieceDestination) && !(pieceCurrentPos == pieceDestination) 
		&& (this->getCurrentTeam() == piecesBoard[pieceCurrentPos.getRow()][pieceCurrentPos.getCol()]->getIsWhite()))
	{
		Piece* movePiece = piecesBoard[pieceCurrentPos.getRow()][pieceCurrentPos.getCol()];
		Piece* destinationPiece = piecesBoard[pieceDestination.getRow()][pieceDestination.getCol()];

		// Get the current position of the Moving Piece, to be replaced with a Space
		RC prevPosition = movePiece->getCurrentPosition();

		// Update the Piece's currentPosition, and hasMoved
		movePiece->setPosition(pieceDestination);

		// Delete the old Piece/Space, and put in the new one
		this->insertPiece(movePiece);

		// Replace the previous position on the Board with an empty space
		this->insertPiece(new Space(prevPosition));

		// Check for special cases
		// If a Pawn is being promoted,
		if (currentMove.getPromotion() != ' ')
		{
			Piece* promotedPawn;

			// Based on which Piece the Pawn is promoting to,
			switch (currentMove.getPromotion())
			{
			case 'Q':
				// Replace the Pawn with a Queen
				promotedPawn = new Queen(RC(movePiece->getCurrentPosition().getRow(), movePiece->getCurrentPosition().getCol()), movePiece->getIsWhite());
			case 'B':
				// Replace the Pawn with a Bishop
				promotedPawn = new Bishop(RC(movePiece->getCurrentPosition().getRow(), movePiece->getCurrentPosition().getCol()), movePiece->getIsWhite());
			case 'N':
				// Replace the Pawn with a Knight
				promotedPawn = new Knight(RC(movePiece->getCurrentPosition().getRow(), movePiece->getCurrentPosition().getCol()), movePiece->getIsWhite());
			case 'R':
				// Replace the Pawn with a Rook
				promotedPawn = new Rook(RC(movePiece->getCurrentPosition().getRow(), movePiece->getCurrentPosition().getCol()), movePiece->getIsWhite());

			default:
				// Default to Queen
				promotedPawn = new Queen(RC(movePiece->getCurrentPosition().getRow(), movePiece->getCurrentPosition().getCol()), movePiece->getIsWhite());
			}
			
			// Insert the promoted Piece into the Board
			this->insertPiece(promotedPawn);
		}
		// If a Pawn captured another Pawn enPassant,
		else if (currentMove.getEnPassant())
		{
			// Remove the Pawn that was captured
			// Get the direction the current Pawn traveled,
			int direction = currentMove.getDelta().getRow();

			// Insert an empty Space at the captured Pawns' position (1 row behind the moved Pawn)
			Space* newEmpty = new Space(RC(movePiece->getCurrentPosition().getRow() + direction, movePiece->getCurrentPosition().getCol()));
			this->insertPiece(newEmpty);
		}
		// If the King is castling (King side)
		else if (currentMove.getCastlingK())
		{
			// Move Rook (K side)
			move(Move(RC(pieceDestination.getRow(), 7), RC(pieceDestination.getRow(), 5)));
			// Change current Team back to the current (two Moves were performed, single turn)
			this->currentTeam = (this->currentTeam) ? 0 : 1;
		}
		// If the King is castling (Queen side)
		else if (currentMove.getCastlingQ())
		{
			// Move Rook (Q side)
			move(Move(RC(pieceDestination.getRow(), 0), RC(pieceDestination.getRow(), 3)));
			// Change current Team back to the current (two Moves were performed, single turn)
			this->currentTeam = (this->currentTeam) ? 0 : 1;
		}

		// Update the last performed Move
		this->lastMove = currentMove;
		// Change current Team to the opposite
		this->currentTeam = (this->currentTeam) ? 0 : 1;
	}

	// Return the last Move
	return this->lastMove;
}

