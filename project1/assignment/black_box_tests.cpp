//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     ALEXANDRA SLEZAKOVA <xsleza20@stud.fit.vutbr.cz>
// $Date:       $2020-02-11
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author ALEXANDRA SLEZAKOVA
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

TEST(EmptyTree, DeleteNode) {
    BinaryTree *tree = new BinaryTree();
    /* zmazanie uzla s hodnotou 1 */
    bool deleted = tree->DeleteNode(1);
    EXPECT_FALSE(deleted);
    /* zmazanie uzla s hodnotou 2 */
    deleted = tree->DeleteNode(2);
    EXPECT_FALSE(deleted);

    delete tree;
}

TEST(EmptyTree, InsertNode) {
    BinaryTree *tree = new BinaryTree();
    /* vlozenie hodnoty 1 */
    std::pair<bool, Node_t *> node1 = tree->InsertNode(1);
    EXPECT_TRUE(node1.first);
    /* nema rodica */
    EXPECT_FALSE(node1.second->pParent);
    EXPECT_EQ(node1.second->key, 1);
    /* cierna farba uzlu node1 */
    EXPECT_EQ(node1.second->color, ::Color_t::BLACK);
    /* pravy list nema potomka */
    Node_t *right1 = node1.second->pRight;
    EXPECT_FALSE(right1->pRight);
    EXPECT_EQ(right1->color, node1.second->color);
    /* list ma rodica */
    EXPECT_TRUE(right1->pParent);

    /* lavy list nema potomka */
    Node_t *left1 = node1.second->pLeft;
    /* lavy list nema potomka */
    EXPECT_FALSE(left1->pRight);
    EXPECT_EQ(left1->color, node1.second->color);
    /* list ma rodica */
    EXPECT_TRUE(left1->pParent);

    /* vlozenie hodnoty 2 */
    std::pair<bool, Node_t *> node2 = tree->InsertNode(2);
    EXPECT_TRUE(node2.first);
    EXPECT_EQ(node2.second->key, 2);
    /* cervena farba uzlu node2 */
    EXPECT_EQ(node2.second->color, ::Color_t::RED);
    /* rodic je node1 */
    EXPECT_TRUE(node2.second->pParent->key == node1.second->key);

    /* vlozenie hodnoty 5 */
    std::pair<bool, Node_t *> node5 = tree->InsertNode(5);
    /* node2 sa stava rodicom */
    EXPECT_TRUE(node2.second->pParent == nullptr);
    /* node2 ma ciernu farba */
    EXPECT_EQ(node2.second->color, ::Color_t::BLACK);
    /* node5 a node1 maju cervenu farbu */
    EXPECT_EQ(node1.second->color, ::Color_t::RED);
    EXPECT_EQ(node5.second->color, ::Color_t::RED);

    delete tree;
}

TEST(EmptyTree, FindNode) {
    BinaryTree *tree = new BinaryTree();
    int values[7] = {1, 2, 5, 8, 10, 3, 6};

   for (int value : values) {
       EXPECT_TRUE(tree->FindNode(value) == nullptr);
   }

    delete tree;
}


TEST(NonEmptyTree, InsertNode) {
    BinaryTree *tree = new BinaryTree();
    int values[7] = {1, 2, 5, 8, 10, 3, 6};

    for (int value : values) {
            tree->InsertNode(value);
    }

    /* vlozenie hodnoty 11 */
    std::pair<bool, Node_t *> node11 = tree->InsertNode(11);
    EXPECT_TRUE(node11.first);
    /* uzol s hodnotou 10 sa stava rodicom a ma ciernu farbu */
    EXPECT_TRUE(node11.second->pParent->key == 10);
    EXPECT_EQ(node11.second->pParent->color, ::Color_t::BLACK);
    /* node11 ma cervenu farbu */
    EXPECT_EQ(node11.second->color, ::Color_t::RED);
    EXPECT_TRUE(node11.second->pLeft->pRight == nullptr);
    EXPECT_TRUE(node11.second->pLeft->pLeft == nullptr);
    EXPECT_TRUE(node11.second->pRight->pRight == nullptr);
    EXPECT_TRUE(node11.second->pRight->pLeft == nullptr);

    /* znovu vlozenie hodnoty 5 */
    std::pair<bool, Node_t *> node5 = tree->InsertNode(5);
    EXPECT_FALSE(node5.first);
    EXPECT_EQ(node5.second->color, ::Color_t::BLACK);

    delete tree;
}

TEST(NonEmptyTree, FindNode) {
    BinaryTree *tree = new BinaryTree();
    int values[7] = {1, 2, 5, 8, 10, 3, 6};

    for (int value : values) {
        tree->InsertNode(value);
    }

    /* najdenie uzla s danou hodnotou*/
    Node_t *node;
    for (int value : values) {
        node = tree->FindNode(value);
        EXPECT_TRUE(node);
    }

    /* najdenie neexistujuceho uzla */
    node = tree->FindNode(9);
    EXPECT_TRUE(node == nullptr);
    delete tree;
}

TEST(NonEmptyTree, DeleteNode) {
    BinaryTree *tree = new BinaryTree();
    int values[7] = {1, 2, 5, 8, 10, 3, 6};

    for (int value : values) {
        tree->InsertNode(value);
    }

    EXPECT_TRUE(tree->DeleteNode(1));
    EXPECT_TRUE(tree->DeleteNode(10));
    EXPECT_FALSE(tree->DeleteNode(-5));

    delete tree;
}

TEST(TreeAxioms, Axiom1) {
    BinaryTree *tree = new BinaryTree();
    int values[7] = {1, 2, 5, 8, 10, 3, 6};

    for (int value : values) {
        tree->InsertNode(value);
    }

    std::vector<Node_t *> outLeafNodes;
    tree->GetLeafNodes(outLeafNodes);

    for (Node_t *outLeafNode : outLeafNodes) {
        EXPECT_EQ(outLeafNode->color, ::Color_t::BLACK);
    }

    delete tree;
}

TEST(TreeAxioms, Axiom2) {
    BinaryTree *tree = new BinaryTree();
    int values[7] = {1, 2, 5, 8, 10, 3, 6};

    for (int value : values) {
        tree->InsertNode(value);
    }

    std::vector<Node_t *> outAllNodes;
    tree->GetAllNodes(outAllNodes);

    for (Node_t *outAllNode : outAllNodes) {
        if (outAllNode->color == ::Color_t::RED) {
            EXPECT_EQ(outAllNode->pRight->color, ::Color_t::BLACK);
            EXPECT_EQ(outAllNode->pLeft->color, ::Color_t::BLACK);
        }
    }

    delete tree;
}

TEST(TreeAxioms, Axiom3) {
    BinaryTree *tree = new BinaryTree();
    int values[7] = {1, 2, 5, 8, 10, 3, 6};

    for (int value : values) {
        tree->InsertNode(value);
    }

    std::vector<Node_t *> outLeafNodes;
    tree->GetLeafNodes(outLeafNodes);

    Node_t *root = tree->GetRoot();
    Node_t *parent;
    int count = 0;
    int oldCount = 0;

    for (Node_t *outLeafNode : outLeafNodes) {
        parent = outLeafNode->pParent;
        if (outLeafNode->color == ::Color_t::BLACK)
            count++;

        while (parent != nullptr && root->key != parent->key) {
            if (parent->color == ::Color_t::BLACK) {
                count++;
            }
            /* novy rodic */
            parent = parent->pParent;
        }

        if (oldCount != 0) {
            EXPECT_EQ(count, oldCount);
        }

        oldCount = count;
        count = 0;
    }

    delete tree;
}



/*** Konec souboru black_box_tests.cpp ***/
