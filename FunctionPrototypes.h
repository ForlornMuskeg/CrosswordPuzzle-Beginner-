#pragma once

void StartScreen(void); 
/* Display game header and instructions */

int InsertQuestionsAndAnswers(int game = 9999);
/* Read questions and answers from outer txt files and insert them into containers */

void DisplayInstructions(void);
/* Display instructions */

void menu(void);
/* Make every instruction works */

void InvalidKey(void);
/* In case that user presses a undefined key, display instructions again and prompt another choice */

void DisplayQuestions(void);
/* Display elements of questions vector  */

void DispNumber(int colour, int number, int defaultcolour);
/* Change display colour(red), display numbers and turn it to defaultcolour(white) */

void DisplayBoard(std::string QuestionNumber = "0");
/* Display answers board with user answers */

std::string FixLetters(std::string& UserAnswer);
/* Make all letters of user answers uppercase to be able to compare real answers */

int Play(void);
/* Main gameplay function */

void EndScreen(void);
/* Once all questions are answered, display the end message */













;