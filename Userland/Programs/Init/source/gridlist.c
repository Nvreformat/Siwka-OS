#include <gridlist.h>
#include <Stdlib/string.h>
#include <Siwka/graphics.h>

GridList::GridList()
{
	SelectedItem = 0;
	ItemCount = 0;
	
	Graphics::PutString("------------------------------------------------------------------------------------------------------------------------", 0, 8, 0);
	Graphics::PutString("|        Name        |                                    Description                                     |    Size    |", 0, 9, 0);
	Graphics::PutString("|----------------------------------------------------------------------------------------------------------------------|", 0, 10, 0);
	for (int I = 11; I < 37; ++I)
	{
		Graphics::PutString("|                    |                                                                                    |            |", 0, I, 0);
	}
	Graphics::PutString("------------------------------------------------------------------------------------------------------------------------", 0, 37, 0);
}
	
int GridList::GetSelectedItem()
{
	return SelectedItem;
}

void GridList::SetSelectedItem(int Item)
{
	Graphics::SetTextColors(0, 0, 0, 255, 255, 255);
	Graphics::PutString("|                    |                                                                                    |            |", 0, 11 + SelectedItem, 0);
	Graphics::PutString((char*) GridListItems[SelectedItem].Name, NAME_POS, 11 + SelectedItem, 0);
	Graphics::PutString("Que se yo, soy una descripcion random", DESC_POS, 11 + SelectedItem, 2);
	Graphics::PutString(StringFormat(SizeBuffer, "%u", GridListItems[SelectedItem].ProgramSize), SIZE_POS, 11 + SelectedItem, 0);

	Graphics::SetTextColors(200, 200, 200, 0, 0, 0);
	Graphics::PutString("|                    |                                                                                    |            |", 0, 11 + Item, 0);
	Graphics::PutString((char*) GridListItems[Item].Name, NAME_POS, 11 + Item, 0);
	Graphics::PutString("Que se yo, soy una descripcion random", DESC_POS, 11 + Item, 2);
	Graphics::PutString(StringFormat(SizeBuffer, "%u", GridListItems[Item].ProgramSize), SIZE_POS, 11 + Item, 0);

	SelectedItem = Item;
}

void GridList::AddItem(char* Name, char* Description, int ProgramSize)
{
	GridListItems[ItemCount].Name = Name;
	GridListItems[ItemCount].Description = Description;
	GridListItems[ItemCount].ProgramSize = ProgramSize;

	Graphics::PutString("|                    |                                                                                    |            |", 0, 11 + ItemCount, 0);

	Graphics::PutString((char*) GridListItems[ItemCount].Name, NAME_POS, 11 + ItemCount, 0);
	Graphics::PutString("Que se yo, soy una descripcion random", DESC_POS, 11 + ItemCount, 2);
	Graphics::PutString(StringFormat(SizeBuffer, "%u", GridListItems[ItemCount].ProgramSize), SIZE_POS, 11 + ItemCount, 0);

	ItemCount++;

	Graphics::PutString("|----------------------------------------------------------------------------------------------------------------------|", 0, 11 + ItemCount, 0);
}

void GridList::MoveDown()
{
	SetSelectedItem(SelectedItem == (ItemCount - 1) ? 0 : SelectedItem + 1);
}

void GridList::MoveUp()
{
	SetSelectedItem(SelectedItem == 0 ? ItemCount - 1 : SelectedItem - 1);
}