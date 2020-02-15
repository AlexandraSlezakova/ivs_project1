//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     ALEXANDRA SLEZAKOVA <xsleza20@stud.fit.vutbr.cz>
// $Date:       $2020-02-15
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author ALEXANDRA SLEZAKOVA
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    root = nullptr;
}

PriorityQueue::~PriorityQueue()
{
    struct Element_t *firstElement = GetHead();
    struct Element_t *tmp;

    while (firstElement != nullptr) {
        tmp = firstElement;
        firstElement = tmp->pNext;
        delete tmp;
    }
}

void PriorityQueue::Insert(int value)
{
    struct Element_t *element = GetHead();

    /* nastavenie korena na zaciatok */
    if (element == nullptr) {
        root = (struct Element_t *)malloc(sizeof(struct Element_t *));
        root->pNext = nullptr;
        root->pPrev = nullptr;
        root->value = value;
    }
    else {
        auto *newElement = (struct Element_t *)malloc(sizeof(struct Element_t *));
        struct Element_t *currentElement;

        while (element != nullptr) {
            currentElement = element;

            if (currentElement->value < value) {
                /* posun na dalsi prvok */
                element = currentElement->pNext;

                /* vlozenie prvku, ak ma najvacsiu hodnotu */
                if (element == nullptr) {
                    newElement->pPrev = currentElement;
                    newElement->pNext = nullptr;
                    newElement->value = value;
                    currentElement->pNext = newElement;
                }
            } else if (currentElement->value >= value){
                /* vlozenie prvku do prostriedku */
                newElement->pPrev = currentElement->pPrev;
                newElement->pNext = currentElement;
                newElement->value = value;

                /* vlozenie noveho prvku za prvok, ktory bol povodne pred aktualnym prvkom */
                if (currentElement->pPrev != nullptr) {
                    currentElement->pPrev->pNext = newElement;
                } /* vkladanie na zaciatok */
                else {
                    root = newElement;
                }
                /* nastavenie noveho prvku ako predchadzajuci prvok aktualneho prvku */
                currentElement->pPrev = newElement;
                break;
            }
        }
    }
}

bool PriorityQueue::Remove(int value)
{
    struct Element_t *firstElement = GetHead();
    struct Element_t *currentElement;

    while (firstElement != nullptr) {
        currentElement = firstElement;
        if (firstElement->value == value) {

            if (firstElement->pPrev != nullptr) {
                firstElement->pPrev->pNext = firstElement->pNext;
            } else {
                root = firstElement->pNext;

                /* ak nedoslo k zmazaniu celeho zoznamu */
                if (root != nullptr) {
                    root->pPrev = nullptr;
                }
            }

            if (firstElement->pNext != nullptr) {
                firstElement->pNext->pPrev = firstElement->pPrev;
            }

            delete currentElement;

            return true;
        }
        firstElement = currentElement->pNext;

    }
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    struct Element_t *currentElement = GetHead();

    while (currentElement != nullptr) {
        if (currentElement->value == value) {
            return currentElement;
        }
        currentElement = currentElement->pNext;

    }
    return nullptr;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return root;
}

/*** Konec souboru tdd_code.cpp ***/
