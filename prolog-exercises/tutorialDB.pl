%FACTS & RULES
loves(romeo, juliet).

loves(X, Y) :- loves(Y, X). 

happy(albert).
happy(alice).
happy(bob).
happy(bill).
with_albert(alice).

runs(albert) :- 
	happy(albert).

dances(alice) :-
	happy(alice),
	with_albert(alice).

does_alice_dance :- dances(alice),
	write('When Alice is happy and with Albert she dances').

swims(bill) :-
	happy(bill).

swims(bill) :-
	near_water(bill).

%VARIABLES
male(albert).
male(bob).
male(bill).
male(carl).
male(charlie).
male(dan).
male(edward).

female(alice).
female(betsy).
female(diana).

parent(albert, bob).
parent(albert, betsy).
parent(albert, bill).

parent(alice, bob).
parent(alice, betsy).
parent(alice, bill).

parent(bob, carl).
parent(bob, charlie).

grandparent(X, Y) :-
	parent(Z, Y),
	parent(X, Z).

grandson(X) :-
	parent(X, Y),
	parent(Y, Z),
	male(Z).

granddaughter(X) :-
	parent(X, Y),
	parent(Y, Z),
	female(Z).

stab(tybalt, mercutio, sword).
hates(romeo, X) :- stab(X, mercutio, sword).

%IF STATEMENT
what_grade(5) :-
	write('Go to kindergarten').

what_grade(6) :-
	write('Go to 1st Grade').

what_grade(Other) :-
	Grade is Other - 5,
	format('Go to grade ~w', [Grade]).

%TERMS & STRUCTURES
owns(albert, pet(cat, olive)).

customer(tom, smith, 20.55).
customer(sally, smith, 120.55).

get_cust_bal(FName, LName) :-
	customer(FName, LName, Bal),
	write(FName), tab(1),
	format('~w owes us $~2f ~n', [LName, Bal]).

vertical(line(point(X, Y), point(X, Y2))).
horizontal(line(point(X, Y), point(X2, Y))).

%TRACE - console command showing processing steps
warm_blooded(penguin).
warm_blooded(human).

produce_milk(penguin).
produce_milk(human).

have_feathers(penguin).
have_hair(human).

mammal(X) :-
	warm_blooded(X),
	produce_milk(X),
	have_hair(X).

%RECURSION - using facts from VARIABLES
related(X, Y) :-
	parent(X, Y).

related(X, Y) :-
	parent(X, Z),
	related(Z, Y).

%MATH
/*
=:= - equality
=/= - inequality
; - or
mod(7, 1) - modulo
random(start, end, Store) - randomize
between(start, end, Store) - all between 
succ(val, Store) - increments
abs(num) - absolute
max(nums), min(nums)
round(num), truncate(num), floor(num), ceiling(num)
** - power
// - integer division
sqrt, log, log10, exp, pi, e, sin, cos, tan, asin, acos, sinh, asinh
*/

%READ-WRITE
/*
write(TEXT).
nl. - new line
writeq(TEXT) - write with quotes
read(X). - string
get(X). - one char
format(TEXT + ~w, [LIST]).
put(X) - show single char
*/

write_to_file(File, Text) :-
	open(File, write, Stream),
	write(Stream, Text), nl,
	close(Stream).

read_from_file(File) :-
	open(File, read, Stream),
	get_char(Stream, Char1),
	process_stream(Char1, Stream),
	close(Stream).

process_stream(end_of_file, _) :- !.

process_stream(Char, Stream) :-
	write(Char),
	get_char(Stream, Char2),
	process_stream(Char2, Stream).

%LOOPING
count_to_10(10) :- 
	write(10), nl.

count_to_10(X) :- 
	write(X), nl,
	Y is X + 1,
	count_to_10(Y).

count_down(Low, High) :-
	between(Low, High, Y),
	Z is High - Y,
	write(Z), nl.

count_up(Low, High) :-
	between(Low, High, Y),
	Z is Low + Y,
	write(Z), nl.

guess_num :- loop(start).

loop(15) :- 
	write('You guessed it').

loop(X) :-
	X\= 15,
	write('Guess Number '),
	read(Guess),
	write(Guess),
	write(' is not the number'), nl,
	loop(Guess).

%CHANGING DATABASE

/*
define at the begining:
*/
:- dynamic(father/2).
:- dynamic(likes/2).
:- dynamic(friend/2).
:- dynamic(stabs/3).

father(lord_montague, romeo).
father(lord_capulet, juliet).

likes(mercutio, dancing).
likes(benvolio, dancing).
likes(romeo, dancing).
likes(romeo, juliet).
likes(juliet, romeo).
likes(juliet, dancing).

friend(romeo, mercutio).
friend(romeo, benvolio).

stabs(tybalt, mercutio, sword).
stabs(romeo, tybalt, sword).
/*
assertz(friend(benvolio, mercutio)). - adds to the end
asserta(friend(benvolio, mercutio)). - adds to the begining
retract(likes(mercutio, dancing)). - deletes
retractall(father(_, _)). - deletes all
retractall(likes(_, dancing)). - deletes all

*/

%LISTS
/*
write([albert|[alice, bob]]), nl. - adds albert to the begining of the list
length([1, 2, 3], X)
[H|T] 
member(a, LIST) - checks if a is inside LIST
member(X, LIST) - get all distinct
reverse(LIST, X) - reverses list
append(LIST1, LIST2, X) - concats lists
*/

write_list([]).

write_list([Head|Tail]) :-
	write(Head), nl,
	write_list(Tail).

%STRINGS
/*
name(STRING, X) - converts string to ascii
name(X, ASCII) - converts ascii to string
nth0(0, List, FChar), put(FChar). - prints first character
atom_length(STRING, X) - string length
*/
join_str(Str1, Str2, Str3) :-
	name(Str1, StrList1),
	name(Str2, StrList2),
	append(StrList1, StrList2, StrList3),
	name(Str3, StrList3).