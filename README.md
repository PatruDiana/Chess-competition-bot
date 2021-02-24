# Chess-competition-bot
Proiect PA - etapa 3 -> Cocoru Emilia-Iuliana, Patru Diana-Georgiana, Tabirca Natalia-Mihaela

Structura proiect:
    -> Proiectul este realizat in C++
    -> Conține fișierul main.cpp și fișiere de tip header *.h în care sunt implementate
    funcționalitățile
    -> Makefile cu regulile make all, make run și make clean

Implementare:

-> fișierul PieceClasses :
    Am modificat structura tablei interne, astfel încât aceasta este formată din elemente de tip piesă.
    Fișierul piece.h conține implementarea acestei clase, iar fișierele Bishop.h, King.h, Knight.h,
    Pawn.h, Queen.h, Rook.h o moștenesc, reprezentând tipul de piese ce alcătuiesc jocul.

-> fișierul MovePieces : conține implementarea mișcărilor specifice pentru fiecare piesă în parte,
fiind analizate mișcările de atac și basic pe care le poate face la un anumit moment dat.Funcția
get_all_moves are rolul de a extrage toate mișcările posibile pentru o piesă într-un vector
(atacurile apărând la inceputul acestuia). De asemenea, strategy_moves.h conține o serie de tabele
ce oferă anumite bonusuri și penalizări pentru fiecare piesă în funcție de cum avansează în joc
(lucru folosit în funcția de evaluarea din Minimax).

-> board.h : (în plus) conține clasa Board al cărui contructor și funcție setBoardConfig au rolul de
inițializare a tablei de joc (modificatate și ele pentru noua reprezentare internă), funcția apply prin
care se realizează o mișcare propriu zisă, actualizându-se coordonatele pieselor(realizată cu ajutorului
funcțiilor update_attack, place_back_pieces) și cea de undo care face fix opusul.
De asemenea, funcția de strategy_points are rolul de a oferi bonusul de poziție pentru o anumită piesă.

-> check_checkMate.h conține o serie de funcții ce au rolul de a afla dacă există o situație de checkmate
(funcția is_attacked verifică dacă o piesă este atacată de una de culoare opusă, getKing returnează regele
de o anumită culoare căutat, reply_to_check returnează o serie de mișcări posibile ce pot scoate jocul din starea de check)

->MiniMax.h : conține minimax-ul, format din funcția de maxi, mini și cea de evaluarea. Evaluarea este calculată
ca diferentă dintre suma punctelor piesele engine-ul nostru și cele ale adversarului. De asemenea se adaugă și
bonusul de poziție menționat anterior. În jocul nostru punctajele sunt astfel:
			- Pawn   100
			- Knight 320
			- Bishop 330
			- King   20000
			- Queen  900
			- Rook	 500

-> main.cpp : comunicare cu Xboard, apel funcții
-> reply.h  : răspunsul pe care îl primește în urma apelării minimax-ului


Colaborare:
	Asemănător cu prima etapă, toți membri echipei au contribuit la toate părțile codului
    și la rezolvarea bug-urilor.
