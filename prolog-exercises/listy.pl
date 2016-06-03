ostatni([O], O).
ostatni([_|X], O) :- 
	ostatni(X, O).

przedostatni([P,_], P).
przedostatni([_|X], P) :- 
	przedostatni(X, P).

nakoniec(X, [], [X]).
nakoniec(X, [A|B], [A|C]) :- 
	nakoniec(X, B, C).

napoczatek(X, Ld, Lw) :- 
	Lw = [X|Ld].

wszedzie(X, [], [X]).
wszedzie(X, [A|B], [X|C]) :- 
	C = [A|B].
wszedzie(X, [A|B], [A|C]) :- 
	wszedzie(X, B, C).

usunostatni([_], []).
usunostatni([A|B], [A|C]) :- 
	usunostatni(B, C).

usunpierwszy([_|B], Lw) :- 
	Lw = B.

usunkazdy([_|X], X).
usunkazdy([A|B], [A|C]) :- 
	usunkazdy(B, C).

odwroc([], []).
odwroc([A|B], L) :- 
	odwroc(B, T),append(T, [A], L).

permutacja([], []).
permutacja([A|B], Lw) :- 
	permutacja(B, Lt), 
	wszedzie(A, Lt, Lw).

sklej(A, [], A).
sklej(A, [B|C], D) :- 
	nakoniec(B, A, W), 
	sklej(W, C, D).

dlugosc([], 0).
dlugosc([_|B], D) :- 
	dlugosc(B, Dn), 
	D is Dn + 1.

nalezy(X, [X|_]).
nalezy(X, [_|A]) :- 
	nalezy(X,A).

odwroc([],[]).
odwroc([H|T], Rev) :-
	odwroc(T, RT),
	append(T,[H],Rev).

odwroc_niezgodnie([],[X|Rev2]).
odwroc_niezgodnie(List, Rev) :-
	append(List2,[X],List),
	odwroc_niezgodnie(List2, Rev2).

polowki([], [], []).
polowki([X|Lwe], Xout, Yout) :-
	append(L,[Y], Lwe),
	polowki(L, X1, Y1),
	Xout = [X|X1],
	append(Y1, [Y], Yout).

srodkowy([X],X).
srodkowy([_|Lwe], Wy) :-
	append(L,[_],Lwe),
	srodkowy(L,Wy).

palindrom([]).
palindrom([_]).
palindrom([X|Lwe]) :-
	append(L,[Y],Lwe),
	X == Y,
	palindrom(L).

sklejaj([],[]).
sklejaj([H],H).
sklejaj([H1,H2|T],Wy) :-
	sklejaj(T, X),
	append(H1,H2,L),
	append(L,X,Wy).

/*
append(WY1, WY2, WE), WY1=[_].  -dekompozycja listy, WY1 jednoelementowe
append(_,[X],L). ostatni
append(_,[X],L). 
*/

tesame([H1],[H1],[]).
tesame([H1,H2|T],[H1],[H2|T]) :-
	H1 \= H2.
tesame([H,H|T], [H|X], Y) :- 
	tesame([H|T], X, Y).

podzial([],[]).
podzial(We, [X1|X2]) :-
	tesame(We, X1, Y),
	podzial(Y, X2).


%PRZETWARZANIE NUMERYCZNE
sumuj([X],X).
sumuj([X|T],S) :-
	sumuj(T, S1),
	S is S1 + X.

rosnacy([_]).
rosnacy([X1,X2|T]) :-
	X1 < X2,
	rosnacy([X2|T]).

arytmetyczny([_]). 
arytmetyczny([_,_]). 
arytmetyczny([X1,X2,X3|T]) :-
	X1 - X2 =:= X2 - X3,
	arytmetyczny([X2,X3|T]).

maksio([X], X).
maksio([X1,X2|T], X) :-
	X1 >= X2,
	maksio([X1|T], X).
maksio([X1,X2|T], X) :-
	X1 < X2,
	maksio([X2|T], X).

faster_maksio(X, Y) :-
	max_list(X, Y).

nstart(Y,0,[],Y).
nstart([H|T],N,[H|X],Y) :-
	N1 is N - 1,
	nstart(T,N1,X,Y).

rozbijaj([],[],[]).
rozbijaj(We,[N|T],[[X]|Wy]) :-
	nstart(We,N,X,Y),
	rozbijaj(Y,T,Wy).


silnia(1,1).
silnia(N,F) :-
	N1 is N - 1,
	silnia(N1, F1),
	F is F1 * N.

pnp([],[],[]).
pnp([H|T],[H|P],NP) :-
	H mod 2 =:= 0,
	pnp(T,P,NP).
pnp([H|T],P,[H|NP]) :-
	H mod 2 =:= 1,
	pnp(T,P,NP).

doposort(X,[],[X]).
doposort(X, [H|T], [X,H|T]) :-
	H >= X.
doposort(X, [H|T], [H|OUT]) :-
	H < X,
	doposort(X,T,OUT).

insertsort([],[]).
insertsort([H|T],Lsorted):-
	insertsort(T,Lwy),
	doposort(H,Lwy,Lsorted).

zamien([X],[X]).
zamien([H1,H2|T],[H1|Lnew]):-
	H1=<H2,
	zamien([H2|T],Lnew).
zamien([H1,H2|T],[H2,H1|T]):-
	H1 > H2.

babel(Lwe,Lwy):-
	zamien(Lwe,Lwy),
	Lwe = Lwy.

babel(Lwe,Lsorted):-
	zamien(Lwe,Lwy),
	Lwe \= Lwy,
	babel(Lwy,Lsorted).

zamienlen([X],[X]).
zamienlen([H1,H2|T],[H1|Lnew]):-
	length(H1,X),
	length(H2,Y),
	X=<Y,
	zamienlen([H2|T],Lnew).
zamienlen([H1,H2|T],[H2,H1|T]):-
	length(H1,X),
	length(H2,Y),
	X>Y.

sortlen(X,Y):-
	zamienlen(X,Y),
	X=Y.
sortlen(X,Lsorted):-
	zamienlen(X,Y),
	X \= Y,
	sortlen(Y,Lsorted).

setdiff([],_,[]).
setdiff([H1|T1],S2,W):-
	member(H1,S2),
	setdiff(T1,S2,W).
setdiff([H1|T1],S2,[H1|W]):-
	not(member(H1,S2)),
	setdiff(T1,S2,W).

unikalne(S,[],S).
unikalne(S,[H|T],W):-
	setdiff(S,H,X),
	unikalne(X,T,W).

/*
sortuniq(ListaList,Lsorted)
Posortowac liste zbiorow po liczbie elementow unikalnych (wzgledem pozostalych zbiorow)
*/

czynniki(Liczba,Listaczynnikow):-
	czynniki(Liczba,2,Listaczynnikow).
czynniki(Liczba,Dzielnik,[Liczba]):-
	Liczba =:= Dzielnik.
czynniki(Liczba,Dzielnik,[Dzielnik|Listaczynnikow]):-
	Liczba mod Dzielnik =:= 0,
	Liczba1 is Liczba // Dzielnik,
	czynniki(Liczba1,2,Listaczynnikow).
czynniki(Liczba,Dzielnik,Listaczynnikow):-
	Liczba mod Dzielnik =\= 0,
	Dzielnik1 is Dzielnik+1,
	czynniki(Liczba,Dzielnik1,Listaczynnikow).





