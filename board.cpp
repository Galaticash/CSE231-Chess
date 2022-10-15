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

	// If the Move if From and To different positions on the Board, and the current Piece is the current Team
	if (!(pieceCurrentPos == pieceDestination) && (this->currentIsWhite() == piecesBoard[pieceCurrentPos.getRow()][pieceCurrentPos.getCol()]->getIsWhite()))
	{
		Piece* movePiece = piecesBoard[pieceCurrentPos.getRow()][pieceCurrentPos.getCol()];
		Piece* destinationPiece = piecesBoard[pieceDestination.getRow()][pieceDestination.getCol()];

		// Get the current position of the Moving Piece, to be replaced with a Space
		RC prevPosition = movePiece->getCurrentPosition();

		// Update the Piece's currentPosition, and hasMoved
		movePiece->setPosition(pieceDestination);

		// Delete the old Piece/Space, and put in the new one
		this->insertPiece(movePiece);

		// Replace the previous position with an empty space
		this->insertPiece(new Space(prevPosition));

		if (currentMove.getPromotion())
		{
			// Replace the Pawn with a Queen
			Piece* promotedPawn = new Queen(RC(movePiece->getCurrentPosition().getRow(), movePiece->getCurrentPosition().getCol()), movePiece->getIsWhite());
			this->insertPiece(promotedPawn);
		}
		else if (currentMove.getEnPassant())
		{
			// Remove the Pawn that was captured
			// Get the direction the current Pawn traveled,
			int direction = currentMove.getDelta().getRow();

			// Insert an empty Space at the captured Pawns' position (1 row behind the moved Pawn)
			Space* newEmpty = new Space(RC(movePiece->getCurrentPosition().getRow() + direction, movePiece->getCurrentPosition().getCol()));
			this->insertPiece(newEmpty);
		}
		else if (currentMove.getCastlingK())
		{
			// Move Rook (K side)
			move(Move(RC(pieceDestination.getRow(), 7), RC(pieceDestination.getRow(), 5)));
			// Change current Team to the opposite (two Moves were performed, single turn)
			this->currentTeam = (this->currentTeam) ? 0 : 1;
		}
		else if (currentMove.getCastlingQ())
		{
			// Move Rook (Q side)
			move(Move(RC(pieceDestination.getRow(), 0), RC(pieceDestination.getRow(), 3)));
			// Change current Team to the opposite (two Moves were performed, single turn)
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