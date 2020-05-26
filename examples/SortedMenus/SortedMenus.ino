#include <M5ez.h>

// A selection of sorting functions.
// If you just add a single string in menu.addItem(), the first set is fast and simple.
// Padding is not stripped from the from of a name when sorted.
// If you specify both a Name and a Caption, as in menu.addItem("This is the Name | This is the Caption which is displayed"),
// use the second group of functions so that the menu is ordered as the user sees it.

// For sorting by Names as quickly as possible
bool ascendingNameCaseSensitive   (const char* s1, const char* s2) { return 0 >     strcmp(s1, s2); }
bool ascendingNameCaseInsensitive (const char* s1, const char* s2) { return 0 > strcasecmp(s1, s2); }
bool descendingNameCaseSensitive  (const char* s1, const char* s2) { return 0 <     strcmp(s1, s2); }
bool descendingNameCaseInsensitive(const char* s1, const char* s2) { return 0 < strcasecmp(s1, s2); }

// For sorting by Caption if there is one, falling back to sorting by Name if no Caption is provided (all purpose)
const char* captionHelper(const char* nameAndCaption) {
	char* sub = strchr(nameAndCaption, '|');	// Find the divider
	if(nullptr == sub) return nameAndCaption;	// If none, return the entire string
	sub++;                          			// move past the divider
	while(isspace(sub[0])) sub++;				// trim whitespace
	return sub;
}
bool ascendingCaptionCaseSensitive   (const char* s1, const char* s2) { return 0 >     strcmp(captionHelper(s1), captionHelper(s2)); }
bool ascendingCaptionCaseInsensitive (const char* s1, const char* s2) { return 0 > strcasecmp(captionHelper(s1), captionHelper(s2)); }
bool descendingCaptionCaseSensitive  (const char* s1, const char* s2) { return 0 <     strcmp(captionHelper(s1), captionHelper(s2)); }
bool descendingCaptionCaseInsensitive(const char* s1, const char* s2) { return 0 < strcasecmp(captionHelper(s1), captionHelper(s2)); }


void setup() {
	ez.begin();
}

void loop() {
	ezMenu menu("Menu Sorting Demo");
	menu.txtSmall();
	// You can simply call setSortFunction once here, and the menu will always stay sorted.
	// menu.setSortFunction(yourSortingFunction);
	menu.buttons("asc # Asc # dsc # Dsc # Unsorted #");
	menu.addItem("Just a few");
	menu.addItem("words of");
	menu.addItem("random text in");
	menu.addItem("No Particular Order.");
	menu.addItem("Press buttons");
	menu.addItem("to re-sort");
	menu.addItem("NAME IS IGNORED! Value is sorted. | as you like.");

	// Or, you can call setSortFunction any time to re-sort the menu.
	// Once set, additional insertions are made in sorted order as well.
	// No need to call setSortFunction again unless you want to change to a different order.
	while(true) {
		menu.runOnce();
		String result = menu.pickButton();
		if     (result == "asc")      menu.setSortFunction(ascendingCaptionCaseSensitive);
		else if(result == "Asc")      menu.setSortFunction(ascendingCaptionCaseInsensitive);
		else if(result == "dsc")      menu.setSortFunction(descendingCaptionCaseSensitive);
		else if(result == "Dsc")      menu.setSortFunction(descendingCaptionCaseInsensitive);
		else if(result == "Unsorted") menu.setSortFunction(nullptr);
	}
}
