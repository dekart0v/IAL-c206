
/* ******************************* c206.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c206 - Dvousměrně vázaný lineární seznam                            */
/*  Návrh a referenční implementace: Bohuslav Křena, říjen 2001               */
/*  Vytvořil: Martin Tuček, říjen 2004                                        */
/*  Upravil: Kamil Jeřábek, září 2020                                         */
/*           Daniel Dolejška, září 2021                                       */
/* ************************************************************************** */
/*
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int. Seznam bude jako datová
** abstrakce reprezentován proměnnou typu DLList (DL znamená Doubly-Linked
** a slouží pro odlišení jmen konstant, typů a funkcí od jmen u jednosměrně
** vázaného lineárního seznamu). Definici konstant a typů naleznete
** v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ obousměrně
** vázaný lineární seznam:
**
**      DLL_Init ........... inicializace seznamu před prvním použitím,     #DONE
**      DLL_Dispose ........ zrušení všech prvků seznamu,                   #
**      DLL_InsertFirst .... vložení prvku na začátek seznamu,              #DONE
**      DLL_InsertLast ..... vložení prvku na konec seznamu,                #DONE
**      DLL_First .......... nastavení aktivity na první prvek,             #DONE
**      DLL_Last ........... nastavení aktivity na poslední prvek,          #DONE
**      DLL_GetFirst ....... vrací hodnotu prvního prvku,                   #DONE
**      DLL_GetLast ........ vrací hodnotu posledního prvku,                #DONE
**      DLL_DeleteFirst .... zruší první prvek seznamu,                     #DONE
**      DLL_DeleteLast ..... zruší poslední prvek seznamu,                  #DONE
**      DLL_DeleteAfter .... ruší prvek za aktivním prvkem,                 #DONE
**      DLL_DeleteBefore ... ruší prvek před aktivním prvkem,               #
**      DLL_InsertAfter .... vloží nový prvek za aktivní prvek seznamu,     #
**      DLL_InsertBefore ... vloží nový prvek před aktivní prvek seznamu,   #
**      DLL_GetValue ....... vrací hodnotu aktivního prvku,                 #DONE
**      DLL_SetValue ....... přepíše obsah aktivního prvku novou hodnotou,  #DONE
**      DLL_Previous ....... posune aktivitu na předchozí prvek seznamu,    #DONE
**      DLL_Next ........... posune aktivitu na další prvek seznamu,        #DONE
**      DLL_IsActive ....... zjišťuje aktivitu seznamu.                     #DONE
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce explicitně
 * uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c206.h"

int error_flag;
int solved;

/**
 * Vytiskne upozornění na to, že došlo k chybě.
 * Tato funkce bude volána z některých dále implementovaných operací.
 */
void DLL_Error() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = TRUE;
}

/**
 * Provede inicializaci seznamu list před jeho prvním použitím (tzn. žádná
 * z následujících funkcí nebude volána nad neinicializovaným seznamem).
 * Tato inicializace se nikdy nebude provádět nad již inicializovaným seznamem,
 * a proto tuto možnost neošetřujte.
 * Vždy předpokládejte, že neinicializované proměnné mají nedefinovanou hodnotu.
 *
 * @param list Ukazatel na strukturu dvousměrně vázaného seznamu
 */
void DLL_Init( DLList *list ) {
    list->activeElement = NULL;
    list->firstElement = NULL;
    list->lastElement = NULL;
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Zruší všechny prvky seznamu list a uvede seznam do stavu, v jakém se nacházel
 * po inicializaci.
 * Rušené prvky seznamu budou korektně uvolněny voláním operace free.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Dispose( DLList *list ) {

    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Vloží nový prvek na začátek seznamu list.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na začátek seznamu
 */
void DLL_InsertFirst( DLList *list, int data ) {
    DLLElementPtr element = malloc(sizeof(struct DLLElement));
    if (!element) DLL_Error();

    element->data = data; //
    element->nextElement = list->firstElement; // creating element to store it somewhere
    element->previousElement = NULL; //

    if(list->firstElement) { // does this if list has some data already (when list->firstElement != NULL)
		list->firstElement->previousElement = element; // с нулевой позиции двигаем на первую и вставляем на место нулевое чето
    }	
	else { // ?????????
		list->lastElement = element;
	}
	list->firstElement = element; // if list is empty
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Vloží nový prvek na konec seznamu list (symetrická operace k DLL_InsertFirst).
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na konec seznamu
 */
void DLL_InsertLast( DLList *list, int data ) {
    DLLElementPtr element = malloc(sizeof(struct DLLElement));
    if (!element) DLL_Error();

    element->data = data; // the same as in DLL_InsertFirst() but inverted
    element->nextElement = NULL;
    element->previousElement = list->lastElement;

    if(list->lastElement) { // does this if list has some data already (when list->firstElement != NULL)
        list->lastElement->nextElement = element;
    }
    else { // ???????????
        list->firstElement = element;
    }
    list->lastElement = element; //if list is empty
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Nastaví první prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz (nepočítáme-li return),
 * aniž byste testovali, zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_First( DLList *list ) { // simply assign smth to activeElement
    list->activeElement = list->firstElement;
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Nastaví poslední prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz (nepočítáme-li return),
 * aniž byste testovali, zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Last( DLList *list ) { // same as in DLL_First but inverted
    list->activeElement = list->lastElement;
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu prvního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetFirst( DLList *list, int *dataPtr ) {
    if(!list->firstElement) {
        DLL_Error();
        return;
    }
    *dataPtr = list->firstElement->data;
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu posledního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetLast( DLList *list, int *dataPtr ) {
    if(!list->lastElement) {
        DLL_Error();
        return;
    }
    *dataPtr = list->lastElement->data;
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Zruší první prvek seznamu list.
 * Pokud byl první prvek aktivní, aktivita se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteFirst( DLList *list ) {
    if(!list) return;
    else if (list->firstElement == list->activeElement) return;

    DLLElementPtr x = list->firstElement; // pointer to 1st element
    free(x); // delete the pointer to the first element
    list->firstElement = list->firstElement->nextElement; // make the next(2nd) element the first
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Zruší poslední prvek seznamu list.
 * Pokud byl poslední prvek aktivní, aktivita seznamu se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteLast( DLList *list ) {
    if(!list) return;		
	if(list->lastElement == list->activeElement) return;

	DLLElementPtr x = list->lastElement; // pointer to last element
	list->lastElement = list->lastElement->previousElement; // make the previous element last element 
	free(x); // delete the pointer to the last element
	
	if(!list->lastElement) { // if list is empty
		return;
	}
    else { //if contains smth make the last element the last element (no links to the next node)
		list->lastElement->nextElement = NULL;
    }
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Zruší prvek seznamu list za aktivním prvkem.
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * posledním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteAfter( DLList *list ) {
    if(!list) return;
    if(list->activeElement == list->lastElement) return;

    DLLElementPtr x = list->activeElement->nextElement;

    if(x->nextElement) { // if we have smth after after activeElement
        list->activeElement->nextElement = x->nextElement;
        x = list->activeElement;
    }
    else { // end of list
        list->activeElement->nextElement = NULL;
        list->lastElement = list->activeElement;
    }

    free(x);
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Zruší prvek před aktivním prvkem seznamu list .
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * prvním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteBefore( DLList *list ) {

    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Vloží prvek za aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu za právě aktivní prvek
 */
void DLL_InsertAfter( DLList *list, int data ) {
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/** 
 * Vloží prvek před aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu před právě aktivní prvek
 */
void DLL_InsertBefore( DLList *list, int data ) {

    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, volá funkci DLL_Error ().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetValue( DLList *list, int *dataPtr ) {
    if(!list->activeElement || !list) {
        DLL_Error();
        return; // added so compilator won't say "illegal operation" #TODO
    }
    *dataPtr = list->activeElement->data;
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Přepíše obsah aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, nedělá nic.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Nová hodnota právě aktivního prvku
 */
void DLL_SetValue( DLList *list, int data ) {
    if(!list->activeElement) return;
    list->activeElement->data = data;
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Posune aktivitu na následující prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Next( DLList *list ) {
    if(!list) return;
    list->activeElement = list->activeElement->nextElement;
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}


/**
 * Posune aktivitu na předchozí prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Previous( DLList *list ) {
    if(!list) return;
    list->activeElement = list->activeElement->previousElement;
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/**
 * Je-li seznam list aktivní, vrací nenulovou hodnotu, jinak vrací 0.
 * Funkci je vhodné implementovat jedním příkazem return.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 * @returns Nenulovou hodnotu v případě aktivity prvku seznamu, jinak nulu
 */
int DLL_IsActive( DLList *list ) {
    return (list->activeElement) ? 1 : 0;
    //solved = FALSE; /* V případě řešení, smažte tento řádek! */
}

/* Konec c206.c */
