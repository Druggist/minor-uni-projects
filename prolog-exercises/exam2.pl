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
/*
Sortowanie wedlug sredniej z list pomiedzy min i max
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

maxelement([X],X).
maxelement([H1,H2|T],X):-
	H1 >= H2,
	maxelement([H1|T],X), !.
maxelement([_,H2|T],X):-
	maxelement([H2|T],X).

minelement([X],X).
minelement([H1,H2|T],X):-
	H1 =< H2,
	minelement([H1|T],X), !.
minelement([_,H2|T],X):-
	minelement([H2|T],X).

ostatni([X],X).
ostatni([_|T],X):-
	ostatni(T,X).

usunostatni([_],[]).
usunostatni([H|T],[H|X]):-
	usunostatni(T,X).

usunzlewej(X,[X|T],T):- !.
usunzlewej(X,[_|T],Lwy):-
	usunzlewej(X,T,Lwy).

usunzprawej(X,L,L1):-
	ostatni(L,Y),
	X =:= Y, 
	usunostatni(L,L1), !.
usunzprawej(X,Lwe,Lwy):-
	usunostatni(Lwe,L),
	usunzprawej(X,L,Lwy).

rezultat(Lwe,Lwy):-
	minelement(Lwe,Min),
	maxelement(Lwe,Max),
	usunzlewej(Min,Lwe,L),
	usunzprawej(Max,L,Lwy).

klucz(Lwe,K):-
	rezultat(Lwe,Lwy),
	srednia(Lwy,K), !.

zamien([X],[X]).
zamien([H1,H2|T],[H2,H1|T]):-
	klucz(H1,Y),
	klucz(H2,X),
	X < Y, !.
zamien([H1,H2|T],[H1|Lwy]):-
	zamien([H2|T],Lwy).

sortuj(Lwe,Lwy):-
	zamien(Lwe,Lwy),
	Lwe = Lwy, !.
sortuj(Lwe,Lwy):-
	zamien(Lwe,Lwy1),
	sortuj(Lwy1,Lwy).
*/
/*
Sortowanie liczb wedlug ich binarnej reprezentacji z usuniętymi powtorzeniami
*/
/*
nakoniec(X,[],[X]).
nakoniec(X,[H|T],[H|Lwy]):-
	nakoniec(X,T,Lwy).

ostatni([X],X).
ostatni([_|T],X):-
	ostatni(T,X).

usunostatni([_],[]).
usunostatni([H|T],[H|Wy]):-
	usunostatni(T,Wy).

dec2bin(0,[]).
dec2bin(Dec,Bin):-
	Bit is Dec mod 2,
	Rest is Dec // 2,
	dec2bin(Rest,Bin1),
	nakoniec(Bit,Bin1,Bin).

bin2dec([],0).
bin2dec(Bin,Dec):-
	ostatni(Bin,Bit),
	usunostatni(Bin,Rest),
	bin2dec(Rest,Dec1),
	Dec is Dec1 * 2 + Bit.

usunpowtorzenia([H],[H]).
usunpowtorzenia([H1,H2|T],[H1|Lwy]):-
	H1 =\= H2,
	usunpowtorzenia([H2|T],Lwy), !.
usunpowtorzenia([_,H2|T],Lwy):-
	usunpowtorzenia([H2|T],Lwy).

klucz(X,K):-
	dec2bin(X,Bin),
	usunpowtorzenia(Bin,Bin1),
	bin2dec(Bin1,K), !.

doposort(X,[],[X]).
doposort(X,[H|T],[X,H|T]):-
	klucz(X,K1),
	klucz(H,K2),
	K1 =< K2, !.
doposort(X,[H|T],[H|L]):-
	doposort(X,T,L).

sortuj([],[]).
sortuj([H|T],Lwy):-
	sortuj(T,L),
	doposort(H,L,Lwy).
*/
/*
Sortuj liczby wedlug ich reprezentacji szesnastkowej z usunietymi literami
*/
/*
nakoniec(X,[],[X]):-
	X < 10, !.
nakoniec(_,[],[]).
nakoniec(X,[H|T],[H|Lwy]):-
	X < 10,
	nakoniec(X,T,Lwy), !.
nakoniec(_,L,L).

ostatni([X],X).
ostatni([_|T],X):-
	ostatni(T,X).

usunostatni([_],[]).
usunostatni([H|T],[H|Wy]):-
	usunostatni(T,Wy).

dec2hex(0,[]).
dec2hex(Dec,Hex):-
	Bit is Dec mod 16,
	Rest is Dec // 16,
	dec2hex(Rest,Hex1),
	nakoniec(Bit,Hex1,Hex).

hex2dec([],0).
hex2dec(Hex,Dec):-
	ostatni(Hex,Bit),
	usunostatni(Hex,Rest),
	hex2dec(Rest,Dec1),
	Dec is Dec1 * 16 + Bit.

klucz(X,K):-
	dec2hex(X,Hex),
	hex2dec(Hex,K), !.

zamien([X],[X]).
zamien([H1,H2|T],[H2,H1|T]):-
	klucz(H1,K1),
	klucz(H2,K2),
	K1 > K2, !.
zamien([H1,H2|T],[H1|Lwy]):-
	zamien([H2|T],Lwy).

sortuj(Lwe, Lwy):-
	zamien(Lwe,Lwy),
	Lwe = Lwy, !.
sortuj(Lwe, Lwy):-
	zamien(Lwe,Lwy1),
	sortuj(Lwy1,Lwy).
	*/

/*
Sortowanie liczb wedlug ich sredniej z unikalnych czynnikow pierwszych.
*/

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

czynnikipierwsze(X,Cz):-
	czynnikipierwsze(X,2,Cz).
czynnikipierwsze(X,Dzielnik,[Dzielnik]):-
	X =:= Dzielnik.
czynnikipierwsze(X,Dzielnik,[Dzielnik|Cz]):-
	X mod Dzielnik =:= 0,
	X1 is X / Dzielnik,
	czynnikipierwsze(X1,2,Cz), !.
czynnikipierwsze(X,Dz,Cz):-
	Dz1 is Dz + 1,
	czynnikipierwsze(X,Dz1,Cz).

usuntesame(_,[],[]).
usuntesame(X,[H|T],Lwy):-
	X =:= H,
	usuntesame(X,T,Lwy), !.
usuntesame(X,[H|T],[H|Lwy]):-
	usuntesame(X,T,Lwy).

unikalne([],[]).
unikalne([H|T],Lwy):-
	member(H,T),
	usuntesame(H,T,Lwy1),
	unikalne(Lwy1,Lwy), !.
unikalne([H|T],[H|Lwy]):-
	unikalne(T,Lwy).

klucz(X,K):-
	czynnikipierwsze(X,C),
	unikalne(C,Y),
	srednia(Y,K), !.

doposort(X,[],[X]).
doposort(X,[H|T],[X,H|T]):-
	klucz(X,K1),
	klucz(H,K2),
	K1 =< K2, !.
doposort(X,[H|T],[H|L]):-
	doposort(X,T,L).

sortuj([],[]).
sortuj([H|T],Lwy):-
 	sortuj(T,L),
 	doposort(H,L,Lwy).