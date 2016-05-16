%            Maria-Piotr        Ewa-Adam
%            -----------        --------
%              /  |  \          /  |  \
%             /   |   \        /   |   \
%            /  Marek  \      /  Joanna \
% Robert-Agata         Jan-Anna         Krzysztof-Agnieszka
% ------------         --------         -------------------
%     /  \               /  \                   /  \
%    /    \             /    \                 /    \
%   /      \           /      \               /      \
% Radek   Beata      Darek   Tomek         Jacek    Iwona

parent(maria,agata).
parent(maria,marek).
parent(maria,jan).
parent(piotr,agata).
parent(piotr,marek).
parent(piotr,jan).
parent(ewa,anna).
parent(ewa,joanna).
parent(ewa,krzysztof).
parent(adam,anna).
parent(adam,joanna).
parent(adam,krzysztof).
parent(robert,radek).
parent(robert,beata).
parent(agata,radek).
parent(agata,beata).
parent(jan,darek).
parent(jan,tomek).
parent(anna,darek).
parent(anna,tomek).
parent(krzysztof,jacek).
parent(krzysztof,iwona).
parent(agnieszka,jacek).
parent(agnieszka,iwona).

marriage(maria,piotr).
marriage(ewa,adam).
marriage(robert,agata).
marriage(jan,anna).
marriage(krzysztof,agnieszka).

female(maria).
female(ewa).
female(agata).
female(anna).
female(joanna).
female(agnieszka).
female(beata).
female(iwona).
male(piotr).
male(adam).
male(robert).
male(marek).
male(jan).
male(krzysztof).
male(radek).
male(darek).
male(tomek).
male(jacek).

mother(X,Y):-female(X),parent(X,Y),X\=Y.
father(X,Y):-male(X),parent(X,Y),X\=Y.
sister(X,Y):-female(X),parent(Z,X),parent(Z,Y),X\=Y.
brother(X,Y):-male(X),parent(Z,X),parent(Z,Y),X\=Y.
grandmother(X,Y):-female(X),parent(X,Z),parent(Z,Y),X\=Y.
grandfather(X,Y):-male(X),parent(X,Z),parent(Z,Y),X\=Y.
uncles(X,Y):-brother(X,Z),female(Z),parent(Z,Y),X\=Y.
uncleb(X,Y):-brother(X,Z),male(Z),parent(Z,Y),X\=Y.
wife(X,Y):-female(X),marriage(X,Y).
wife(X,Y):-female(X),marriage(Y,X).
husband(X,Y):-male(X),marriage(X,Y).
husband(X,Y):-male(X),marriage(Y,X.










