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

/*
Na wejsciu lista list, posortowac ja po srednich z liczb ktorych wartosc we wzorze X = (Max-Min)/(MaxPos-MinPos) jest mniejsza niż pierwsza wartosc z tego wzoru. 
*/

suma([],0).
suma([H|T],X):-
	suma(T,X1),
	X is X1 + H.

dlugosc([],0).
dlugosc([_|T],X):-
	dlugosc(T,X1),
	X is X1 + 1.

srednia([],0).
srednia(Lwe,X):-
	suma(Lwe,Suma),
	dlugosc(Lwe,Dlugosc),
	X is Suma / Dlugosc.

pozycja([Num],Num,1).
pozycja([Num|_],Num,1).
pozycja([_|T],Num,X):-
	pozycja(T,Num,X1),
	X is X1 + 1.

ostatni([X],X).
ostatni([_|T],X):-
	ostatni(T,X).

wzor(Lwe,Min,Max,X):-
	pozycja(Lwe,Min,MinPos),
	pozycja(Lwe,Max,MaxPos),
	X is (Max - Min)/(MaxPos - MinPos).

rezultat([_],[]).
rezultat([H|T],Lwy):-
	ostatni([H|T],Max),
	wzor([H|T],H,Max,Base),
	rezultat(T,Base,Lwy).
rezultat([],_,[]).
rezultat([_],_,[]).
rezultat([H1,H2|T],Base,[H1|Lwy]):-
	ostatni([H1,H2|T],Max),
	wzor([H1,H2|T],H1,Max,New),
	New < Base,
	rezultat([H2|T],Base,Lwy).
rezultat([H1,H2|T],Base,Lwy):-
	ostatni([H1,H2|T],Max),
	wzor([H1,H2|T],H1,Max,New),
	New >= Base,
	rezultat([H2|T],Base,Lwy).

klucz(Lwe,X):-
	rezultat(Lwe,Lwy),
	srednia(Lwy,X), !.

zamien([X],[X]).
zamien([H1,H2|T],[H2,H1|T]):-
	klucz(H1,Y1),
	klucz(H2,Y2),
	Y1 > Y2.
zamien([H1,H2|T],[H1|Lwy]):-
	zamien([H2|T],Lwy), !.

sortuj(Lwe,Lwy):-
	zamien(Lwe,Lwy),
	Lwy = Lwe, !.

sortuj(Lwe,Lwy):-
	zamien(Lwe,Lwy1),
	Lwe \= Lwy1,
	sortuj(Lwy1,Lwy).

