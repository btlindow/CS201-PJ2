# CS201-PJ2

//  Created by Benjamin Lindow on 9/15/16.
//  Copyright © 2016 Benjamin Lindow. All rights reserved.
//
//  Project2 Driver File
//
//  A program for building Binary Search Trees and AVL Balanced Trees.
//  Each tree construction supports insert, delete, report statistics,
//  and show tree functions.
//
//
//
//  Program Execution
//  -----------------
//                                                          |
//  tree [TREE TYPE] [CORPUS FILE] [INSTRUCTION FILE]       |
//                                                          |
//  [TREE TYPE] = "-a" -> AVL Tree Construction             |
//              = "-b" -> BST Tree Construction             |
//                                                          |
//  [CORUPUS FILE] = "words.txt"                            |
//                                                          |
//  [INSTRUCTION FILE] = "instructions.txt"                 |
//                                                          |
//  *********************************************************
//                                                          |
//                                                          |
//  Sample Call                                             |
//  -----------                                             |
//                                                          |
//  tree -a avltext.txt avlinstructions.txt                 |
//  tree -b bsttext.txt bstinstructions.txt                 |
//                                                          |
//  *********************************************************
//                                                          |
//  Instructions File Codes                                 |
//  -----------------------                                 |
//                                                          |
//  i = insert word                                         |
//  d = delete word                                         |
//  f = report frequency of word                            |
//  r = report statistics of tree                           |
//  s = show tree                                           |
//                                                          |
//  ---------------------------------------------------------
