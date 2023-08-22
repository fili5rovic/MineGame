# MineBlast: Interactive Graph-based Mine Detonation Simulator

**MineBlast** is a C program that allows users to create a graph of interconnected nodes, simulate mine detonation efficiency, and find the most efficient mine placement for maximum impact. This program is designed to provide insights into the potential effects of mine detonation within a given area.

> This project was developed as part of a university assignment. Please refer to the [instructions.pdf](instructions.pdf) file for detailed assignment instructions.
>
> Through the GraphMine Detonator project, I appreciate gaining a practical understanding of BFS - its significance and implementation in graph traversal - making my learning journey insightful and enjoyable.


## Table of Contents
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Usage](#usage)
- [File Format](#file-format)

## Features
- Create a graph by adding nodes with coordinates (x, y) and radius.
- Establish links between nodes to represent relationships.
- Visualize the graph structure and relationships in a tabular format.
- Calculate detonation efficiency using the Breadth-First Search (BFS) algorithm.
- Find the mine with the maximum detonation efficiency.
- Simulate the detonation area by getting user input
- Import graph information from a text file.
- Interactive command-line interface for user input.
- Calculation of affected area based on detonation radius (**Monte Carlo simulation**).
- Detection of overlapping nodes and automatic link establishment.
- User-friendly outputs with colored messages.

## Getting Started

### Prerequisites

To compile and run the GraphMine Detonation Simulation, you need to have a C compiler such as GCC installed on your system.

### Usage
Follow the on-screen instructions to create nodes, establish links, perform other operations on the graph and much more. 

**Make sure to use an output console which supports ANSI Escape Sequences for colored output, such as a Windows 10 console. Otherwise, weird characters will appear.**

## File format
When importing graph information from a file, the format should be as follows:
```
<number_of_nodes>
<x1> <y1> <radius1>
<x2> <y2> <radius2>
...
```
This project includes 3 examples, filenames `input1.csv`, `input2.csv` and `myTest.txt`.

