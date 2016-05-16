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