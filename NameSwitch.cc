// Elizabeth Soechting
// Take first and last name, switch and separate with a comma

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string reverse(string fName, string lName) {
	return lName + "," + fName;
}


int main()
{

	string Name = "Ellie King";

	string revName;

	string names[] = { "", "", "", "", "" };

	stringstream stream(Name);
	int i = 0;
	while (getline(stream, revName, ' '))
	{
		names[i] = revName;
		i++;
	}
	cout << names[1] << "," << names[0] << endl;

		


	/*
	string fName;	// First name
	string lName; // Last name

	// Prompt user to input thier first name and read it in
	cout << "Input first name: ";
	cin >> fName;

	// Prompt user to ebnter their last name and read it in
	cout << "Input last name ";
	cin >> lName;

	// Print out user's last and first name separated by a comma
	cout << lName << "," << fName << endl;

	cout << reverse("Mary", "Smith") << endl;
	*/
}
