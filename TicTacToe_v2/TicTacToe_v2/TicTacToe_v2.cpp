// TicTacToe_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "model.h"
#include "controller.h"
#include "view.h"
#include <iostream>



class GameController
{
public:
	GridController gControl;
	PlayerController player;
	compController comp;
	turnModel activePlayer;
	gameModel gameInfo;
	/*
	bool bWin = false;
	bool bQuit = false;
	bool bPlayerTurn = true;
	bool bPlayAgain = false;
	*/

	void game(drawUI UI, bool &bEndGame)
	{


		//Get input from player. First turn and X/O.
		gameInfo.bPlayerTurn = player.playerSetup(comp);

		//Don't draw grid if the comp is going first
		if (gameInfo.bPlayerTurn)
		{
			gControl.drawGrid();
		}
	
		do 
		{	
			//Player's Turn
			if (gameInfo.bPlayerTurn)
			{
				//Draw header
				UI.draw(UI.game_playerTurn);
				player.playerTurn(activePlayer, gControl, gameInfo.bQuit);
				gameInfo.bPlayerTurn = false;
			}
			//Comp Turn
			else
			{
				//Draw header
				UI.draw(UI.game_compTurn);
				comp.compTurn(activePlayer, gControl, player.playerInfo, gameInfo.bQuit);
				gameInfo.bPlayerTurn = true;
			}

		
			// Continue if player does not want to quit
			if (!gameInfo.bQuit)
			{
				gControl.drawGrid();
				gameInfo.bWin = gControl.checkWins(gControl.gridInfo, activePlayer);
				UI.drawLine();

				//player or comp win 
				if (gameInfo.bWin)
				{
					UI.draw(activePlayer.getWinMessage());
					bEndGame = player.playAgain();
					gameInfo.bQuit = true;

					if (!bEndGame)
						gControl.gridInfo.gridReset();
				}
				//draw
				else if (!gameInfo.bWin && gControl.isFull())
				{
					UI.draw(UI.game_draw);
					bEndGame = player.playAgain();
					gameInfo.bQuit = true;

					if (!bEndGame)
						gControl.gridInfo.gridReset();
				}


			}
			else if (gameInfo.bQuit)
			{
				bEndGame = true;
			}

		} while (!gameInfo.bQuit);

	}
};


int main()
{
	drawUI UI;
	bool bEndGame = false;
	GameController TicTacToe;
	UI.drawIntro();

	do
	{
		TicTacToe.game(UI, bEndGame);

	} while (!bEndGame);

	UI.drawLine();
	UI.draw(UI.game_end);
	return 0;
}
