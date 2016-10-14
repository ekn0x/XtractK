//! \file MatchListRangesSymbols.h
//!
//! \brief Définition de la classe MatchListRangeSymbols.
//!
//! \version 1.0
//!
//! \author Alexandre H. Lamarche\n
//! \author	Guillaume Whittom\n
//!		Étudiants
//!		Département de génie de production automatisée\n
//!		École de technologie supérieure\n
//!

#ifndef MATCH_LIST_RANGES_SYMBOLS_H
#define MATCH_LIST_RANGES_SYMBOLS_H

#include <list>
#include <initializer_list>

class Range;

using namespace std;

class MatchListRangeSymbols
{
public:
	MatchListRangeSymbols() = delete;

	MatchListRangeSymbols(initializer_list<Range> const & listRange);

	~MatchListRangeSymbols() = default;

	bool isMatching(symbol_t const & symbol);

private:
	list<Range>  mListRange;
};

#endif
