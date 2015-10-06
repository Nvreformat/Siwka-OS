#ifndef GRIDLIST_H
#define GRIDLIST_H

#define NAME_POS 2
#define DESC_POS 63
#define SIZE_POS 108

struct GridListItem
{
	char* Name;
	char* Description;
	int ProgramSize;
};

class GridList
{
	char SizeBuffer[16];
	int SelectedItem;
	int ItemCount;
	GridListItem GridListItems[64];
	
	public:
	GridList();
	int GetSelectedItem();
	void SetSelectedItem(int Item);
	void AddItem(char* Name, char* Description, int ProgramSize);
	void MoveDown();
	void MoveUp();
};

#endif