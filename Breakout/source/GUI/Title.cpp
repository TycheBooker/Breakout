#include "Title.h"

Title::Title(std::string text) :
	TextElement(text)
{
	marginBottom = 100.f;
	setCharacterSize(50);
	centerText();
}


Title::~Title()
{
}
