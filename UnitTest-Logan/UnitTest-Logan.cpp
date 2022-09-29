#include "pch.h"
#include "CppUnitTest.h"
#include "../King.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KingTest
{
	TEST_CLASS(KingTest)
	{
	public:
		
		TEST_METHOD(TestKing)
		{
			TestCastlingKing();
			TestCastlingKing();
			TestKingMovement();
			TestKingBlocked();
			TestKingCapturing();
		}

	private:

		/*   
			0 1 2 3 4 5 6 7
		 0 r . . . k p . r 0
		 1 . . . p p p . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		*/
		TEST_METHOD(TestCastlingQueen) 
		{
			// setup
			
			// exercise
			getPossibleMove();
			// verify
			// takedown
		}

		/*
			0 1 2 3 4 5 6 7
		 0 r . . p k . . r 0
		 1 . . . p p p . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		*/
		TEST_METHOD(TestCastlingKing) 
		{
			// setup
			// exercise
			// verify
			// takedown
		}

		/*
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . k . . . . . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		*/
		TEST_METHOD(TestKingMovement) 
		{
			// setup
			// exercise
			// verify
			// takedown
		}

		/*
			0 1 2 3 4 5 6 7
		 0 . . . p p p . . 0
		 1 . . . p k p . . 1
		 2 . . . p p p . . 2
		 3 . . . . . . . . 3
		 4 . . . . . . . . 4
		 5 . . . . . . . . 5
		 6 . . . . . . . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		*/
		TEST_METHOD(TestKingBlocked) 
		{
			// setup
			// exercise
			// verify
			// takedown
		}

		/*
			0 1 2 3 4 5 6 7
		 0 . . . . . . . . 0
		 1 . . . . . . . . 1
		 2 . . . . . . . . 2
		 3 . . . . . . . . 3
		 4 . . . P P P . . 4
		 5 . . . P k P . . 5
		 6 . . . P P P . . 6
		 7 . . . . . . . . 7
			0 1 2 3 4 5 6 7
		*/
		TEST_METHOD(TestKingCapturing) 
		{
			// setup
			// exercise
			// verify
			// takedown
		}
	};

	
}
