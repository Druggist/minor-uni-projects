/*
Suma parzystych elementow listy
*/

sumujparzyste([_],0).
sumujparzyste([_,X],X).
sumujparzyste([_,H|T],X):-
	sumujparzyste(T,Y),
	X is H + Y.

/*
Suma nieparzystych elementow listy
*/

sumujnieparzyste([X],X).
sumujnieparzyste([X,_],X).
sumujnieparzyste([H,_|T],X):-
	sumujnieparzyste(T,Y),
	X is H + Y.

/*
Sprawdza czy lista jest parzysta
*/

checkeven([]).
checkeven([_]):- fail.
checkeven([_,_]).
checkeven([_,_|T]):-
	checkeven(T).

/*
Usuwa powtorzenia w liscie
*/
deleterepetitions([],[]).
deleterepetitions([X],[X]).
deleterepetitions([H|T],X):-
	member(H,T),
	deleterepetitions(T,X).
deleterepetitions([H|T],[H|X]):-
	not(member(H,T)),
	deleterepetitions(T,X).

/*
Generuje ciag arytmetyczny o podanej dlugosci i przeskoku
*/

generatesequence(0,_,[]).
generatesequence(L,A,X):-
	L1 is L - 1,
	El is L * A,
	generatesequence(L1,A,X1),
	append(X1,[El],X).

/*
Usuwa co trzeci element listy
*/

deleteeverythird([],[]).
deleteeverythird([H1],[H1]).
deleteeverythird([H1,H2],[H1,H2]).
deleteeverythird([H1,H2,_|T],[H1,H2|X]):-
	deleteeverythird(T,X).

/*
laczy dwie listy w jedna
*/

concatlists([],Y,Y).
concatlists([H|T],X,[H|Out]):-
	concatlists(T,X,Out).

/*
Podzielenie listy na dwie czesci i wziecie srodkowych elementów
*/

splitlist([],[],[],[]).
splitlist([X],[],[],[X]).
splitlist([X,Y],[],[],[X,Y]).
splitlist([H|T],[H|X],Y,Center):-
append(T1,[L],T),
splitlist(T1,X,Y1,Center),
append(Y1,[L],Y).