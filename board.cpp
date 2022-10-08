/***********************************************************************
 * Source File:
 *    Board:
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#include "board.h"

/// <summary>
/// Inserts a Piece into the Board's 2D Piece pointers array, deleting the previous piece
/// </summary>
/// <param name="insertPiece">The pointer of the new Piece to insert</param>
void Board::insertPiece(Piece* insertPiece)
{
	// Get the row/column position of the Piece
	int row = insertPiece->getCurrentPosition().getRow();
	int col = insertPiece->getCurrentPosition().getCol();

	// Delete the previous Piece at that position (in most cases, a Space)
	// What. Errors stopped when previous Piece is NOT deleted
	if (false)
	{
		delete& (piecesBoard[row][col]);
	}

	// Assign the position on the board the Piece*
	this->piecesBoard[row][col] = insertPiece;
}

/// <summary>
/// Performs the given move
/// </summary>
/// <param name="currentMove">Move to be performed</param>
/// <returns></returns>
Move Board::move(Move currentMove)
{
	// Get the To and From positions of the Move
	RC pieceCurrentPos = currentMove.getPositionFrom();
	RC pieceDestination = currentMove.getPositionTo();
	// TODO: Assert RC positions are on the board (return lastMove if this Move cannot be completed)
	// Assert RC positions are not the same (no actual movement done)

	// If the Move if From and To different positions on the Board,
	if (!(pieceCurrentPos == pieceDestination))
	{
		Piece* movePiece = piecesBoard[pieceCurrentPos.getRow()][pieceCurrentPos.getCol()];
		Piece* destinationPiece = piecesBoard[pieceDestination.getRow()][pieceDestination.getCol()];

		// Delete the old Piece/Space, and put in the new one
		this->insertPiece(movePiece);

		// Update the Piece's currentPosition, and hasMoved
		movePiece->setPosition(pieceDestination);

		// Replace the previous position with an empty space
		this->insertPiece(new Space(RC(pieceCurrentPos.getRow(), pieceCurrentPos.getCol())));

		// TODO: Change to rely on Smith's notation for Castling, EnPassant, etc

		//if(currentMove.isEnpassant)
		// if (currentMove.isCastlingQ/isCastlingK
		// if currentMove.isPromotion -> Then (not in this case, 

		/*

		// PAWN PROMOTION
		if (movePiece->getType() == "PAWN" && (movePiece->getCurrentPosition().getRow() == 8 || movePiece->getCurrentPosition().getRow() == 0)) {

			// Replace the Pawn with a Queen
			insertPiece(new Queen(movePiece->getCurrentPosition(), movePiece->getIsWhite()));
		}
		*/
		// CASTLING (King side/Queen side)
		// EN-PASSANT

		return currentMove;
	}

	// The given Move could not be completed
	return this->lastMove;
}