/***********************************************************************
 * Header File:
 *    Move: 
 * Author:
 *
 * Summary:
 *
 ************************************************************************/

#pragma once
#include "RC.h"

class Move {
public:
	Move()
	{
		position = RC(1, 1);
	};

private:
	RC position;
};