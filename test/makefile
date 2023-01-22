#chemins
CLIB = ../src
CLIBINC = ../inc
DSRC = src
DINC = inc
OBJOUT = obj
DEXE = bin

DDATA = data

EXEN = lorenz

#flags
FLAGS = -I$(DINC) -I$(CLIBINC) -Wall -ansi

all: $(DEXE)/$(EXEN)

#commandes
CCL = gcc -lm -o
CC = gcc $(FLAGS) -g -c

#dependances
OBJETS = $(OBJOUT)/rk4.o $(OBJOUT)/vect.o $(OBJOUT)/step.o $(OBJOUT)/algos.o $(OBJOUT)/lorenz.o $(OBJOUT)/euler.o
$(DEXE)/$(EXEN) : $(OBJETS)
	$(CCL) $@ $(OBJETS)


#Une 'meta-regle' permettant de compiler tout fichier source "C".
$(OBJOUT)/%.o:$(DSRC)/%.c
	$(CC) -o $@ $<


$(OBJOUT)/%.o:$(CLIB)/%.c
	$(CC) -o $@ $<


#on vire tout
clean:
	rm $(OBJOUT)/*.o
	rm $(DEXE)/$(EXEN)

#lancement du programme
run:
	cd $(DEXE);\
	./lorenz
	
#vire les donnees de sortie
cleandata:
	rm $(DDATA)/*.out

#deplace les fichiers sauvegarde
cleansave:
	rm */*~* 
