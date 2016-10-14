#include <iostream>
#include <list>
#include <initializer_list>

using namespace std;

void function(initializer_list<initializer_list<char>> const & symbols)
{
	for (auto it = symbols.begin(); it != symbols.end(); ++it)
	{
		// for (auto it2 = it->begin(); it2 != it->end(); ++it2)
		auto i = it->end();
		--i;
			cout << *i << ' ';

		cout << endl;
	}
	
}


int main(void)
{
	function({ {'1','2','3','4','5'},{'a','f'},{'a','z'} });

	system("PAUSE");
	return EXIT_SUCCESS;
}