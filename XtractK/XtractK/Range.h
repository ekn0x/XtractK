


#include "Symbol.h"

class Range
{
public:
	Range() = delete; // ne peut pas prendre le constructeur par defaut
	Range(symbol_t f, symbol_t l);

	bool isInRange(symbol_t const & symbol);
	bool isNotInRange(symbol_t const & symbol);

private:
	symbol_t mFirst;
	symbol_t mLast;
};