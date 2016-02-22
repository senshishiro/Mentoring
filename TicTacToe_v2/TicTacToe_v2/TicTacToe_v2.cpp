// TicTacToe_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "model.h"
#include "controller.h"
#include "view.h"
#include <iostream>




int TicTacToe(drawUI UI, bool &bEndGame)
{

	GridController gControl;
	PlayerController player;
	compController comp;
	turnModel activePlayer;
	
	bool bWin = false;
	bool bQuit = false;
	bool bTest = false;
	bool bPlayerTurn = true;
	bool bPlayAgain = false;
	string winMessage = "";

	// Ask if player want to go first
	bPlayerTurn = player.turnOrder();

	//Ask if player wants to be X or O
	player.setXO(comp);

	//Don't draw grid if the comp is going first
	if (bPlayerTurn)
	{
		gControl.drawGrid();
	}
	

	do 
	{	
		//Player's Turn
		if (bPlayerTurn)
		{
			//Draw header
			UI.draw(UI.game_playerTurn);

			//Get move
			player.getMove(gControl, bQuit);

			//Update grid and set the active player and winMessage
			gControl.updateGrid(gControl.gridInfo, player.playerInfo);		
			activePlayer = player.playerInfo;
			winMessage = player.playerInfo.winMessage;
			bPlayerTurn = false;
		}
		//Comp Turn
		else
		{
			//Draw header
			UI.draw(UI.game_compTurn);
			
			if (player.playerInfo.prevTurnExists())
			{
				//Check for potential wins
				if (comp.compBlockWins(gControl, comp.compInfo))
				{
					comp.compInfo.OverrideMove();
					//comp.compInfo.SetRow(comp.bestMove[0]);
					//comp.compInfo.SetCol(comp.bestMove[1]);
					//gControl.updateGrid(gControl.gridInfo, comp.compInfo);
				}
				// Block player wins
				else if (comp.compBlockWins(gControl, player.playerInfo))
				{
					comp.compInfo.OverrideMove();
					//comp.compInfo.row = comp.bestMove[0];
					//comp.compInfo.col = comp.bestMove[1];
					//gControl.updateGrid(gControl.gridInfo, comp.compInfo);
					
				}
				//Random move if there are no good moves
				else
				{
					comp.compRandomTurn(gControl);
				}
			}
			else
			{
				comp.compRandomTurn(gControl);
			}

			gControl.updateGrid(gControl.gridInfo, comp.compInfo);
			activePlayer = comp.compInfo;
			//winMessage = comp.compInfo.winMessage;
			bPlayerTurn = true;
		}

		
		// Continue if player does not want to quit
		if (!bQuit)
		{
			gControl.drawGrid();
			bWin = gControl.checkWins(gControl.gridInfo, activePlayer);
			UI.drawLine();

			//player or comp win 
			if (bWin)
			{
				UI.draw(activePlayer.getWinMessage());
				bEndGame = player.playAgain();
				bQuit = true;
			}
			//draw
			else if (!bWin && gControl.isFull())
			{
				UI.draw(UI.game_draw);
				bEndGame = player.playAgain();
				bQuit = true;
			}
		}
		else if (bQuit)
		{
			bEndGame = true;
		}

	} while (!bQuit);

    return 0;
}


int main()
{
	drawUI UI;
	bool bEndGame = false;
	
	UI.drawIntro();

	do
	{
		TicTacToe(UI, bEndGame);

	} while (!bEndGame);

	UI.drawLine();
	UI.draw(UI.game_end);
	return 0;
}
