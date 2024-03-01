
#include "VariablesAndLibraries.h"
#include "FunctionPrototypes.h"


int main() {

	StartScreen();
	InsertQuestionsAndAnswers();
	Play();
	EndScreen();
	
	return 0;
}

void StartScreen() {

	std::string game_name {"CROSSWORD PUZZLE GAME"};

	std::cout << std::setfill('=') << std::setw(width) << "" << std::setfill(' ');

	std::cout << std::endl;
	std::cout << std::setw((game_name.size()) + ((width - game_name.size()) / 2)) << game_name << std::endl;  /* Display header in the middle of the width */

	std::cout << std::setfill('=') << std::setw(width) << "" << std::setfill(' ');
		

	std::cout << std::endl << std::endl;
	std::cout << std::left << std::setw((width / 2) - 10) << "" << "N - New Game\n\n" /* Display (width/2)-10 spaces before instructions, setfill(' ') as default */ 
						   << std::setw((width / 2) - 10) << "" << "Q - Display Questions\n\n"
						   << std::setw((width / 2) - 10) << "" << "B - Display Board\n\n"
						   << std::setw((width / 2) - 10) << "" << "E - Exit Game" << std::endl;
}

int InsertQuestionsAndAnswers(int game) {

	std::string Question, Answer, AnswerNumber;
	std::ifstream QuestionsFile, AnswersFile;
	
	if (game == 1 || game == 9999) {                                         /* open files */
		QuestionsFile.open("DarkSoulsQuestions.txt");						  
		AnswersFile.open("DarkSoulsAnswers.txt");
	}
	else if (game == 2) {
		QuestionsFile.open("TheWitcherQuestions.txt");						   
		AnswersFile.open("TheWitcherAnswers.txt");
	}
	else {
		std::cout << std::setw((width / 2) - 10) << "" << "SELECT YOUR GAME\n" << std::endl
				  << std::setw((width / 2) - 10) << "" << "1.Dark Souls Series" << std::endl
			      << std::setw((width / 2) - 10) << "" << "2.The Witcher Series" << std::endl;
		std::cin >> game;
		InsertQuestionsAndAnswers(game);
	}
		
	if (!QuestionsFile || !AnswersFile) {
		std::cerr << "Open File Error! Be sure that the .exe and .txt files are in the same folder" << std::endl;
		return 1;
	}
	else {
		while (std::getline(QuestionsFile, Question)) {            /* Read every (line) from Questions.txt and Question = line */
			Questions.push_back(Question);                         /* Add (line) to Questions vector */ 
		}
		while (AnswersFile >> AnswerNumber >> Answer) {            /* Read word by word and AnswerNumber = first word of the line
																							Answer = second word of the line */
			Answers.insert(std::make_pair(AnswerNumber, Answer));  /* Make first and second words pair and add it to Answers map */
		}
	}
	QuestionsFile.close();										   /* don't forget to close files */
	AnswersFile.close();
	return 0;
}

inline void DisplayInstructions() {

	std::cout << std::setw((width / 2) - 10) << "" << "N - New Game\n\n"
			  << std::setw((width / 2) - 10) << "" << "C - Continue Game\n\n"
			  << std::setw((width / 2) - 10) << "" << "Q - Display Questions\n\n"
			  << std::setw((width / 2) - 10) << "" << "B - Display Board\n\n"
			  << std::setw((width / 2) - 10) << "" << "E - Exit Game" << std::endl;
}

void menu() {

	switch (_getch()) {													
	case 'n': 
	case 'N':
		StartTime = std::chrono::system_clock::now();                        /* get system_clock as soon as the user presses N */
		ElapsedTimeInPause = StartTime - StartTime;							 /* reset duration */
		system("CLS");
		Questions.clear();
		Answers.clear();
		RightAnswers.clear();
		InsertQuestionsAndAnswers(3);
		break;
	case 'c':  
	case 'C':
		ElapsedTimeInPause += std::chrono::system_clock::now() - PauseTime;  /* calculate the sum of the time elapsed in the menu */
		system("CLS");
		break;
	case 'q':
	case 'Q':
		system("CLS");
		DisplayQuestions();
		InvalidKey();
		break;
	case 'b': 
	case 'B':
		system("CLS");
		DisplayBoard();
		InvalidKey();
		break;
	case 'e':
	case 'E':
		system("CLS");
		std::cout << "Thank You For Playing" << std::endl;
		exit(1);
		break;
	default:
		std::cout << "Invalid Option" << std::endl;
		menu();
	}
}

void InvalidKey() {

	if (_getch() && (GetKeyState(VK_ESCAPE) & 0x8000)) {                    /* Hold the instructions screen until user presses esc */
		system("CLS");
		DisplayInstructions();
		Play();
	}
	else {
		std::cout << "\nInvalid key! Press ESC" << std::endl;
		InvalidKey();
	}
}

void DisplayQuestions() {
	for (auto s : Questions)												/* range-base loop */
		std::cout << s << std::endl;
}

inline void DispNumber(int colour, int number, int defaultcolour) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
	std::cout << ((number == 10 || number == 11) ? " " : "  ") << number << " ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultcolour);
}

void DisplayBoard(std::string QuestionNumber) {
				
	static constexpr int max_Row {20};              
	static constexpr int max_Column {16};

	RightAnswers.insert(std::make_pair(QuestionNumber, Answers[QuestionNumber]));  /* If the question is answered right, the answer will be placed in rightanswers container */

	std::cout << std::right << std::setw(13 + ((max_Column * 4 - 13) / 2)) << "ANSWERS BOARD" << std::endl;  
	
	int k {1};
	while (k <= max_Column) { std::cout << "  - "; k++; }
	std::cout << std::endl;

	for (int row {1}; row < max_Row; row++) {                       /* The Answers Board is displayed row by row */
		std::cout << "|   ";

		for (int column {1}; column <= max_Column; column++) {      /* .count(QuestionNumber) returns 1 or 0 according to whether the answer is in RightAnswers or not */
			
			if (row == 1 && column == 8) {
				DispNumber(4, 2, 7);
				column += max_Column;

			}                         

			else if (row == 2 && column == 2) {
				DispNumber(4, 7, 7);
				if (RightAnswers.count("7-") && !RightAnswers.count("2-")) {
					for (auto c : RightAnswers["7-"]) {
						std::cout << "- " << c << " ";
					}
					column += max_Column;
				}
				else if (RightAnswers.count("2-") && !RightAnswers.count("7-")) {
					std::cout << std::setw(20) << "" << "- " << RightAnswers["2-"].at(0) << " " << std::endl << "|"
						<< std::setw(31) << "" << "| " << RightAnswers["2-"].at(1) << " |" << std::endl << "|"
						<< std::setw(31) << "" << "| " << RightAnswers["2-"].at(2) << " |";
					row += 2;
					column += max_Column;
				}
				else if (RightAnswers.count("7-") && RightAnswers.count("2-")) {
					for (auto c : RightAnswers["7-"]) {
						std::cout << "- " << c << " ";
					}
					std::cout << std::endl << "|" << std::setw(31) << "" << "| " << RightAnswers["2-"].at(1) << " |"
						<< std::endl << "|" << std::setw(31) << "" << "| " << RightAnswers["2-"].at(2) << " |";
					row += 2;
					column += max_Column;
				}

			}

			else if (row == 5 && column == 4) {
				DispNumber(4, 1, 7);
				if (RightAnswers.count("1-") || (RightAnswers.count("1-") && RightAnswers.count("2-"))) {
					for (auto c : RightAnswers["1-"]) {
						std::cout << "- " << c << " ";
					}
					column += max_Column;
				}
				else if (!RightAnswers.count("1-") && RightAnswers.count("2-")) {
					std::cout << std::setw(12) << "" << "- " << RightAnswers["2-"].at(3) << " ";
					column += max_Column;
				}
			}

			else if (row == 6 && column == 3) {
				DispNumber(4, 4, 7);
				if (RightAnswers.count("2-"))
					std::cout << std::setw(16) << "" << "| " << RightAnswers["2-"].at(4) << " |";
				column += max_Column;
			}

			else if (row == 7) {

				if (RightAnswers.count("4-") && column == 3) {
					std::cout << "| " << RightAnswers["4-"].at(0) << " |   ";
					column++;
				}
				else if (RightAnswers.count("2-") && column == 8) {
					std::cout << "| " << RightAnswers["2-"].at(5) << " |   ";
					column++;
				}
				else if (column == 13) {
					DispNumber(4, 8, 7);
				}
				else if (column == 15) {
					DispNumber(4, 9, 7);
					column += max_Column;
				}
				else {
					std::cout << "    ";
				}
			}

			else if (row == 8) {

				if (column == 1) {
					DispNumber(4, 3, 7);
					column++;
				}
				if (RightAnswers.count("3-")) {
					if (column == 2) {
						for (auto c : RightAnswers["3-"]) {
							std::cout << "- " << c << " ";
							column++;
						}
						column--;
					}
					else if (RightAnswers.count("8-") && column == 13) {
						std::cout << "| " << RightAnswers["8-"].at(0) << " |   ";
						column++;
					}
					else if (RightAnswers.count("9-") && column == 15) {
						std::cout << "| " << RightAnswers["9-"].at(0) << " |";
						column += max_Column;
					}
					else {
						std::cout << "    ";
					}
				}

				else if (!RightAnswers.count("3-")) {
					if (RightAnswers.count("4-") && column == 3) {
						std::cout << "- " << RightAnswers["4-"].at(1) << " ";
					}
					else if (RightAnswers.count("2-") && column == 8) {
						std::cout << "- " << RightAnswers["2-"].at(6) << " ";
					}
					else if (RightAnswers.count("8-") && column == 13) {
						std::cout << "| " << RightAnswers["8-"].at(0) << " |   ";
						column++;
					}
					else if (RightAnswers.count("9-") && column == 15) {
						std::cout << "| " << RightAnswers["9-"].at(0) << " |";
						column += max_Column;
					}
					else {
						std::cout << "    ";
					}
				}
			}

			else if (row == 9) {

				if (RightAnswers.count("4-") && column == 3) {
					std::cout << "| " << RightAnswers["4-"].at(2) << " |   ";
					column++;
				}
				else if (RightAnswers.count("2-") && column == 8) {
					std::cout << "| " << RightAnswers["2-"].at(7) << " |   ";
					column++;
				}
				else if (RightAnswers.count("8-") && column == 13) {
					std::cout << "| " << RightAnswers["8-"].at(1) << " |   ";
					column++;
				}
				else if (RightAnswers.count("9-") && column == 15) {
					std::cout << "| " << RightAnswers["9-"].at(1) << " |";
					column += max_Column;
				}
				else {
					std::cout << "    ";
				}
			}

			else if (row == 10) {

				if (RightAnswers.count("4-") && column == 3) {
					std::cout << "| " << RightAnswers["4-"].at(3) << " |   ";
					column++;
				}
				else if (RightAnswers.count("2-") && column == 8) {
					std::cout << "| " << RightAnswers["2-"].at(8) << " |   ";
					column++;
				}
				else if (RightAnswers.count("8-") && column == 13) {
					std::cout << "| " << RightAnswers["8-"].at(2) << " |   ";
					column++;
				}
				else if (RightAnswers.count("9-") && column == 15) {
					std::cout << "| " << RightAnswers["9-"].at(2) << " |";
					column += max_Column;
				}
				else {
					std::cout << "    ";
				}

			}

			else if (row == 11) {

				if (RightAnswers.count("4-") && column == 3) {
					std::cout << "| " << RightAnswers["4-"].at(4) << " |   ";
					column++;
				}
				else if (RightAnswers.count("2-") && column == 8) {
					std::cout << "| " << RightAnswers["2-"].at(9) << " |   ";
					column++;
				}
				else if (column == 11) {
					DispNumber(4, 11, 7);
				}
				else if (RightAnswers.count("8-") && column == 13) {
					std::cout << "| " << RightAnswers["8-"].at(3) << " |   ";
					column++;
				}
				else if (RightAnswers.count("9-") && column == 15) {
					std::cout << "| " << RightAnswers["9-"].at(3) << " |";
					column += max_Column;
				}
				else {
					std::cout << "    ";
				}

			}

			else if (row == 12) {

				if (RightAnswers.count("4-") && column == 3) {
					std::cout << "| " << RightAnswers["4-"].at(5) << " |   ";
					column++;
				}
				else if (column == 6) {
					DispNumber(4, 5, 7);
				}
				else if (RightAnswers.count("5-") && column == 7) {
					for (auto c : RightAnswers["5-"]) {
						std::cout << "- " << c << " ";
					}
					column += max_Column;
				}
				else if (!RightAnswers.count("5-")) {
					if (RightAnswers.count("2-") && column == 8) {
						std::cout << "- " << RightAnswers["2-"].at(10) << " ";
					}
					else if (RightAnswers.count("11-") && column == 11) {
						std::cout << "- " << RightAnswers["11-"].at(0) << " ";
					}
					else if (RightAnswers.count("8-") && column == 13) {
						std::cout << "- " << RightAnswers["8-"].at(4) << " ";
					}
					else if (RightAnswers.count("9-") && column == 15) {
						std::cout << "- " << RightAnswers["9-"].at(4) << " ";
						column += max_Column;
					}
					else {
						std::cout << "    ";
					}
				}
				else {
					std::cout << "    ";
				}
			}

			else if (row == 13) {

				if (RightAnswers.count("4-") && column == 3) {
					std::cout << "| " << RightAnswers["4-"].at(6) << " |   ";
					column++;
				}
				else if (RightAnswers.count("11-") && column == 11) {
					std::cout << "| " << RightAnswers["11-"].at(1) << " |   ";
					column++;
				}
				else if (RightAnswers.count("8-") && column == 13) {
					std::cout << "| " << RightAnswers["8-"].at(5) << " |   ";
					column++;
				}
				else if (RightAnswers.count("9-") && column == 15) {
					std::cout << "| " << RightAnswers["9-"].at(5) << " |";
					column += max_Column;
				}
				else {
					std::cout << "    ";
				}
			}

			else if (row == 14) {

				if (RightAnswers.count("4-") && column == 3) {
					std::cout << "| " << RightAnswers["4-"].at(7) << " |   ";
					column++;
				}
				else if (RightAnswers.count("11-") && column == 11) {
					std::cout << "| " << RightAnswers["11-"].at(2) << " |   ";
					column++;
				}
				else if (RightAnswers.count("8-") && column == 13) {
					std::cout << "| " << RightAnswers["8-"].at(6) << " |   ";
					column++;
				}
				else if (RightAnswers.count("9-") && column == 15) {
					std::cout << "| " << RightAnswers["9-"].at(6) << " |";
					column += max_Column;
				}
				else {
					std::cout << "    ";
				}
			}

			else if (row == 15) {

				if (column == 2) {
					DispNumber(4, 6, 7);
				}
				else if (RightAnswers.count("6-") && column == 3) {
					for (auto c : RightAnswers["6-"]) {
						std::cout << "- " << c << " ";
						column++;
					}
					column--;
				}
				else if (!RightAnswers.count("6-")) {

					if (RightAnswers.count("4-") && column == 3) {
						std::cout << "- " << RightAnswers["4-"].at(8) << " ";
					}
					else if (RightAnswers.count("11-") && column == 11) {
						std::cout << "- " << RightAnswers["11-"].at(3) << " ";
					}
					else if (RightAnswers.count("8-") && column == 13) {
						std::cout << "- " << RightAnswers["8-"].at(7) << " ";
					}
					else if (RightAnswers.count("9-") && column == 15) {
						std::cout << "| " << RightAnswers["9-"].at(7) << " |";
						column += max_Column;
					}
					else {
						std::cout << "    ";
					}
				}
				else if (RightAnswers.count("9-") && column == 15) {
					std::cout << "| " << RightAnswers["9-"].at(7) << " |";
					column += max_Column;
				}
				else {
					std::cout << "    ";
				}
			}

			else if (row == 16) {

				if (RightAnswers.count("4-") && column == 3) {
					std::cout << "| " << RightAnswers["4-"].at(9) << " |   ";
					column++;
				}
				else if (RightAnswers.count("11-") && column == 11) {
					std::cout << "| " << RightAnswers["11-"].at(4) << " |   ";
					column++;
				}
				else if (RightAnswers.count("8-") && column == 13) {
					std::cout << "| " << RightAnswers["8-"].at(8) << " |   ";
					column++;
				}
				else if (RightAnswers.count("9-") && column == 15) {
					std::cout << "| " << RightAnswers["9-"].at(8) << " |";
					column += max_Column;
				}
				else {
					std::cout << "    ";
				}
			}

			else if (row == 17) {

				if (RightAnswers.count("4-") && column == 3) {
					std::cout << "| " << RightAnswers["4-"].at(10) << " |   ";
					column++;
				}
				else if (RightAnswers.count("11-") && column == 11) {
					std::cout << "| " << RightAnswers["11-"].at(5) << " |   ";
					column++;
				}
				else if (RightAnswers.count("8-") && column == 13) {
					std::cout << "| " << RightAnswers["8-"].at(9) << " |   ";
					column++;
				}
				else if (RightAnswers.count("9-") && column == 15) {
					std::cout << "| " << RightAnswers["9-"].at(9) << " |";
					column += max_Column;
				}
				else {
					std::cout << "    ";
				}
			}

			else if (row == 18) {

				if (column == 1) {
					DispNumber(4, 10, 7);
				}
				else if (RightAnswers.count("10-") && column == 2) {
					for (auto c : RightAnswers["10-"]) {
						std::cout << "- " << c << " ";
						column++;
					}
					column--;
				}
				else if (!RightAnswers.count("10-") && RightAnswers.count("4-") && column == 3) {
					std::cout << "- " << RightAnswers["4-"].at(11) << " ";
				}
				else if (RightAnswers.count("9-") && column == 15) {
					std::cout << "| " << RightAnswers["9-"].at(10) << " |";
					column += max_Column;
				}
				else {
					std::cout << "    ";
				}
			}

			else if (row == 19 && RightAnswers.count("4-") && column == 3) {

				std::cout << "| " << RightAnswers["4-"].at(12) << " |" << std::endl << "|"
					<< std::setw(11) << "" << "| " << RightAnswers["4-"].at(13) << " |";
				column += max_Column;
			}

			else {
				std::cout << "    ";
			}

		}

		std::cout << std::endl;
	}

	k = 1;
	while (k <= max_Column) { std::cout << "  - "; k++; }

}

std::string FixLetters(std::string& UserAnswer) {
	std::string temp;
	int i = 0;
	while (i < UserAnswer.length()) {
		temp += std::toupper(UserAnswer.at(i));
		i++;
	}
	return temp;
}

int Play() {

	std::string QuestionNumber, UserAnswer;
	auto it = Questions.begin();                                       /* İterator declaration > hold the address of the first element */

	menu();

	while (Questions.size() != 3) {                                    /* At the beginning Question.size() = 14, When all questions are removed from the vector, the game is finished */

		system("CLS");
		DisplayBoard();
		std::cout << std::endl;
		DisplayQuestions();

		std::cout << "\nChoose a question to answer:";
		std::cin >> QuestionNumber;
		QuestionNumber += "-";

		if (!Answers.count(QuestionNumber)) {
			continue;
		}

		for (auto s : Questions) {														   /* Clear the screen and display the chosen question */
			if (s.substr(0, 3) == QuestionNumber || s.substr(0, 2) == QuestionNumber) {    /* to clip string > substr(starting index, length) */
				system("CLS");
				std::cout << s << std::endl;
				it = std::find(Questions.begin(), Questions.end(), s);					  /* Find the address of the chosen question, std::find(start, end, find this element)  */
			}
		}

		std::cout << "\nEnter your answer without spaces: ";
		std::cin >> UserAnswer;
		UserAnswer = FixLetters(UserAnswer); 

																		
		if (UserAnswer == Answers[QuestionNumber]) {                                     
			
			static const std::string Messages[5]{ "VICTORY ACHIEVED!",
												  "ENEMY FELLED",
												  "YOU DEFEATED",
												  "HEIR OF FIRE DESTROYED",
												  "LORD OF CINDER FALLEN" };

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			std::cout << "\n" << Messages[rand() % 5] << std::endl << std::endl;          /* Display one message randomly */
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			DisplayBoard(QuestionNumber);

			Questions.erase(it);                                                          /* Remove from the question from the questions vector */
			Answers.erase(QuestionNumber);                                                /* Remove from the answer from the answers map */
		}
		else {                      

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			std::cout << "\nYOU DIED!" << std::endl << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

		std::cout << "\nPress Any Key to continue" << std::endl;
		std::cout << "Press Escape to return menu" << std::endl;

		if (_getch() && (GetKeyState(VK_ESCAPE) & 0x8000)) {                              /* Allow the user to pause the game */
			PauseTime = std::chrono::system_clock::now();
			system("CLS");
			DisplayInstructions();
			Play();
		}

	}

	return 0;
}

void EndScreen() {

	EndTime = std::chrono::system_clock::now();
	RealPlayTime = EndTime - StartTime - ElapsedTimeInPause;

	system("CLS");
	DisplayBoard();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

	std::cout << "\nCongratulations, THE GREAT ENEMY FELLED!" << std::endl;

	std::cout << "Your Time: " << static_cast<int>(RealPlayTime.count()) / 60 << " : "       /* static_cast<int>: convert to int */
		<< static_cast<int>(RealPlayTime.count()) % 60 << " : "
		<< static_cast<int>((RealPlayTime.count() - static_cast<int>(RealPlayTime.count())) * 1000) << std::endl; 

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	Sleep(1000000);
}
