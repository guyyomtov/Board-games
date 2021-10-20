#include "menu.h"
#include "chess.h"
#include "amazonas.h"
#include "checkers.h"
menu::menu() :gameStart(false), curGame(nullptr), exit(false)
{
}
menu::~menu()
{}
void menu::start_Game()
{
	gameStart = true;
	exit = false;
}
void menu::choseGame()
{
	system("cls");
	const int sizeOfCheckersBoard = 8;
	const int sizeOfAmazonasBoard = 10;
	const int sizeOfChessBoard = 8;

	cout << "Please chose one of the following options: \n";
	cout << " 1. Checkers.\n 2. Game Of The Amazonas.\n 3. Chess.\n";
	int userSelection;
	cin >> userSelection;
	bool validChose = false;
	game* newGame = nullptr;
	while (!validChose)
	{
		switch (userSelection)
		{
		case 1:
			newGame = new checkers(typeGame::CHECKERS, sizeOfCheckersBoard);
			validChose = true;
			break;
		case 2:
			newGame = new amazonas(typeGame::GAME_OF_AMAZONAS, sizeOfAmazonasBoard);
			validChose = true;
			break;
		case 3:
			newGame = new chess(typeGame::CHESS, sizeOfChessBoard);
			validChose = true;
			break;

		default:
			cout << "Please chose one of the options!\n";
			cin >> userSelection;
			break;
		}

	}
	curGame = newGame;
	listGames.insertDataToEndList(newGame);
	system("cls");
}
game* menu::getDetailOnGameAndAllocate(ifstream& inFile)
{
	typeGame type;
	inFile.read(rcastc(&type), sizeof(type));
	winner currWinner;
	inFile.read(rcastc(&currWinner), sizeof(currWinner));
	statusGame currStatus;
	inFile.read(rcastc(&currStatus), sizeof(currStatus));
	currTurn turn;
	inFile.read(rcastc(&turn), sizeof(turn));
	if (!inFile.good())
		throw invalid_argument("The load failed.");
	switch (type)
	{
	case typeGame::CHECKERS:
		return new checkers(type, currWinner, currStatus, turn, inFile);
		break;
	case typeGame::GAME_OF_AMAZONAS:
		return new amazonas(type, currWinner, currStatus, turn, inFile);
		break;
	case typeGame::CHESS:
		return new chess(type, currWinner, currStatus, turn, inFile);
		break;
	default:
		throw bad_alloc();
		return nullptr;
		break;
	}

}
bool menu::checkOpeningFile(ifstream& file)
{
	if (!file)
	{
		cout << "the opening of the file faild\n";
		return false;
	}
	return true;
}
bool menu::checkOpeningFile(ofstream& inFile)
{
	if (!inFile)
	{
		cout << "the opening of the file faild\n";
		return false;
	}
	return true;
}
void menu::printMenu()
{
	if (gameStart)
	{
		cout << "*************************** ";
		curGame->printName();
		cout << " ***************************\n";
	}
	else
		cout << "************************************************************\n";
	cout << "Please chose one of the option:\n";
	cout << "1. Start New Game.\n";
	cout << "2. Go to the next Game.\n";
	cout << "3. Delete Game.\n";
	cout << "4. Get details on the current game.\n";
	cout << "5. See list of possible moves.\n";
	cout << "6. See list of possible risks.\n";
	cout << "7. Make Move.\n";
	cout << "8. Exit.\n";
	cout << "9. Save game.\n"; 
	cout << "10. Load game.\n";
	cin >> userSelection;
}
void menu::afterUserSelect()
{
	int fromX, fromY, toX, toY;
	switch (userSelection)
	{
	case 1:
		system("cls");
		choseGame();
		start_Game();
		break;
	case 2:
		system("cls");
		if (checkIfGameIsOn())
			curGame = listGames.goToTheNextValue(); // maybe to do return beacuse its private ask almog shoaf
		break;
	case 3:
		system("cls");
		if (checkIfGameIsOn())
			curGame = listGames.deleteValue(); // to update the currGane
		if(curGame == nullptr) // if the list is empty!
			gameStart = false; // there is no game
		break;
	case 4:
		system("cls");
		if (checkIfGameIsOn())
			curGame->printBoardAndDetailsOnTheGame(); // to do ostrem

		break;
	case 5:

		if (checkIfGameIsOn() && !theGameIsOver())
		{
			getInput(fromX, fromY);
			try
			{
				curGame->checkValidMoveOfSoldier(fromX, fromY);
				cout << "The valid moves are:\n";
				curGame->printValidMove(); // to free the list an to print beautiful
				curGame->freeListOfValidMove();
			}
			catch (const invalid_argument& error)
			{
				cout << error.what() << endl;
			}
		}

		break;
	case 6:

		if (checkIfGameIsOn() && !theGameIsOver()) // if the user press 1
		{
			getInput(fromX, fromY);
			try
			{ 
				curGame->checkRisks(fromX, fromY);
				cout << "The risks are:\n";
				curGame->printRisks();
				curGame->freeListOfRisks(); // for using later
			}
			catch (const invalid_argument& error)
			{
				cout << error.what() << endl;
			}
		}
		break;

	case 7:
		if (checkIfGameIsOn() && !theGameIsOver())
		{
			bool inputIsGood = false;
			getInput(fromX, fromY);
			cout << "please enter where to move:(y,x)\n";
			cin >> toX >> toY;
			try
			{
				curGame->gamePlay(fromX, fromY, toX, toY, true);
				if (typeid(*curGame).name() == typeid(amazonas).name())
					getWhereToDart(toX, toY);		
			}
			catch (const invalid_argument& error)
			{
				cout << error.what() << endl;
			}
			
		}
		break;
	case 8:
		exit = true;
		break;
	case 9:
	{
		if (checkIfGameIsOn())
		{
			cout << "please enter file's name:\n";
			string fileName;
			cin >> fileName;
			ofstream outFile(fileName, ios::binary); // to check open file
			if (!checkOpeningFile(outFile))
				break;
			try
			{
				curGame->save(outFile);
				outFile.close();
			}
			catch (const invalid_argument& error)
			{
				outFile.close();
				cout << error.what() << endl;
			}
		}
		break;
	}
	case 10:
	{
		cout << "please enter file's name:\n";
		string fileName;
		cin >> fileName;
		ifstream inFile(fileName, ios::binary);
		if (!checkOpeningFile(inFile))
			break;
		game* newGame = getDetailOnGameAndAllocate(inFile);
		listGames.insertDataToEndList(newGame);
		curGame = newGame;
		gameStart = true;
		inFile.close();
	}
		break;
	default:
		system("cls");
		cout << "Please enter one of the possible selction.\n";
		break;
	}
}
//----------------------------------------------------------------------------------------------------------------//
void menu::getWhereToDart(int toX, int toY)
{
	bool inputIsGood = false;
	while (!inputIsGood)
	{
		int dartX, dartY;
		cout << "please enter where to Dart:(y,x)" << endl;
		cin >> dartX >> dartY;
		try
		{
			curGame->gamePlay(toX, toY, dartX, dartY, false);
			inputIsGood = true;
		}
		catch (const string& str)
		{
			cout << str << endl;
		}
	}
}
bool menu::checkIfGameIsOn()
{
	if (gameStart == false)
	{
		cout << "To start a new game, press 1.\n";
		return false;
	}
	return true;
}
//----------------------------------------------------------------------------------------------------------------//
void menu::startGame()
{
	while (!exit)
	{
		printMenu();
		afterUserSelect();
	}

}
//----------------------------------------------------------------------------------------------------------------//
void menu::getInput(int& x, int& y)
{
	cin.ignore();
	cout << "please enter location of square : (y, x)\n";
	cin >> x >> y;
}
//----------------------------------------------------------------------------------------------------------------//
bool menu::theGameIsOver()
{
	if (curGame->getStatusOfGame() == statusGame::OVER)
	{
		system("cls");
		cout << "The game is over!\n";
		return true;
	}
	return false;
}



