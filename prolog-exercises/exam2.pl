/*
FOR PROPER USE UNCOMMENT ONLY ONE EXERCISE
*/

/*
Sortowanie list wedlug sredniej odleglosci takich samych elementów
*/
/*
suma([],0).
suma([H|T],X):-
	suma(T,X1),
	X is H + X1.

dlugosc([],0).
dlugosc([_|T],X):-
	dlugosc(T,X1),
	X is X1 + 1.

srednia([],0).
srednia(Lwe,X):-
	suma(Lwe,Suma),
	dlugosc(Lwe,Dlugosc),
	X is Suma / Dlugosc.

sublist(X,[X|T],[X|T]):- !.
sublist(El,[_|T],Sublist):-
	sublist(El,T,Sublist).

dystans([X,X|_],1):- !.
dystans([X,_|T],L):-
	dystans([X|T],L1),
	L is L1 + 1.

usunduplikaty([],[]):- !.
usunduplikaty([H|T],Wy):-
	member(H,T),
	usunduplikaty(T,Wy), !.
usunduplikaty([H|T],[H|Wy]):-
	usunduplikaty(T,Wy).
  
rezultat(Lwe,Lwy):-
	usunduplikaty(Lwe,Lel),
	rezultat(Lwe,Lel,Lwy).
rezultat(_,[],[]).
rezultat(Lwe,[H|T],[X|Lwy]):-
	sublist(H,Lwe,L),
	dystans(L,X),
	rezultat(Lwe,T,Lwy).

klucz(L,X):-
	rezultat(L,Lwy),
	srednia(Lwy,X), !.

zamien([H],[H]).
zamien([H1,H2|T],[H2,H1|T]):-
	klucz(H1,R1),
	klucz(H2,R2),
	R1 > R2, !.
zamien([H1,H2|T],[H1|Lnew]):-
	zamien([H2|T],Lnew).

sortuj(Lwe,Lwy):-
	zamien(Lwe,Lwy),
	Lwe = Lwy, !.
sortuj(Lwe,Lwy):-
	zamien(Lwe,Lwy1),
	sortuj(Lwy1,Lwy).
*/
/*
	Wyszukaj max element, wycentruj go usuwając elementy z prawej i lewej strony, zrob srednia z nowej listy i posortuj wedlug tego klucza
*/
/*
suma([],0).
suma([H|T],X):-
	suma(T,X1),
	X is H + X1.

dlugosc([],0).
dlugosc([_|T],X):-
	dlugosc(T,X1),
	X is X1 + 1.

srednia([],0).
srednia(Lwe,X):-
	suma(Lwe,Suma),
	dlugosc(Lwe,Dlugosc),
	X is Suma / Dlugosc.

usunostatni([_],[]).
usunostatni([H|T],[H|Wy]):-
	usunostatni(T,Wy).

maxelement([X],X).
maxelement([H1,H2|T],X):-
	H1 >= H2,
	maxelement([H1|T],X), !.
maxelement([_,H2|T],X):-
	maxelement([H2|T],X).

odlewej(X,[X|_],0):- !.
odlewej(X,[_|T],Y):-
	odlewej(X,T,Y1),
	Y is Y1 + 1.

odprawej(X,Lwe,Y):-
	odlewej(X,Lwe,L),
	dlugosc(Lwe,D),
	Y is D - 1 - L.


rezultat(Lwe,Lwe):-
	maxelement(Lwe,X),
	odlewej(X,Lwe,L),
	odprawej(X,Lwe,P),
	P =:= L, !.
rezultat([H|T],Lwy):-
	maxelement([H|T],X),
	odlewej(X,[H|T],L),
	odprawej(X,[H|T],P),
	P < L,
	rezultat(T,Lwy), !.
rezultat(Lwe,Lwy):-
	usunostatni(Lwe,T),
	rezultat(T,Lwy).

klucz(Lwe,K):-
	rezultat(Lwe,L),
	srednia(L,K), !.

doposort(X,[],[X]).
doposort(X,[H|T],[X,H|T]):-
	klucz(X,K1),
	klucz(H,K2),
	K1 =< K2, !.
doposort(X,[H|T],[H|Lwy]):-
	doposort(X,T,Lwy).

sortuj([],[]).
sortuj([H|T],Lwy):-
	sortuj(T,L),
	doposort(H,L,Lwy).
*/