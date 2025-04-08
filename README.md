# Graph-Based City Distance Calculator

## Overview

This project implements a graph-based system for managing and analyzing distances between cities. It is written in C and follows structured programming practices, using file input/output to build and operate on a city network graph. The program reads city connection data from an input file, constructs an internal graph representation, and computes useful results such as shortest paths or connectivity information.

## Project Structure

- **Source Files**
  - `main.c`: Contains the main logic for loading data, constructing the graph, and performing operations such as distance calculations.
  
- **Data Files**
  - `cities.txt`: Input file listing city-to-city connections and distances in a structured format.
  - `shortest_distance.txt`: Output file for results such as shortest distances between cities.

- **Build Files**
  - May include IDE project files (e.g., `.cbp`, `.layout`, `.depend`) for Code::Blocks or similar C development environments.
  - Binary and object files generated during compilation may be stored in `/bin/Debug/` and `/obj/Debug/`.

## Features

- Loads city data and distances from an external file.
- Constructs an adjacency matrix or list to represent the graph.
- Supports computing and writing results such as shortest paths to an output file.
- Implements efficient search algorithms suitable for small- to medium-scale graphs.

## Compilation and Execution

### Requirements

- GCC compiler or any standard-compliant C compiler
- (Optional) Code::Blocks or another C IDE for easier management

### Steps

1. Ensure all source and data files are in the same directory.
2. Compile using:
   ```bash
   gcc main.c -o city_graph
   ```
3. Run the executable:
   ```bash
   ./city_graph
   ```

## Input Format

The `cities.txt` file should follow a format similar to:

```
CityA CityB 15km
CityB CityC 30km
...
```

Each line represents a direct connection between two cities with a specified distance.

## Output

Results, such as computed shortest distances, are saved in a file named `shortest_distance.txt`. The format and content of this output depend on the specific algorithm implemented (e.g., Dijkstra’s, Floyd-Warshall).

## Coding Standards

- Modular and structured code organization
- Use of `struct` for data abstraction (e.g., `City`, `Edge`)
- Defined constants and clear variable naming
- Graceful handling of file operations and memory management
- Use of comments and logical code segmentation for clarity

## License

This project is for academic and educational use. Please credit the original authors when reusing or extending this code.
