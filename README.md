# Game Simulation README

This program is a simplified game simulation that involves characters, teams, and their interactions. It provides a basic framework for creating different types of characters, organizing them into teams, and simulating gameplay scenarios.

## Program Logic

The program follows the logic of a game simulation where characters can belong to different teams and interact with each other. The main components of the program's logic are:

1. **Characters**: The program defines a base `Character` class, which serves as a foundation for different types of characters in the game. The `Character` class provides common attributes and behaviors such as name, location, health points, and damage calculation. It also includes methods to check if a character is alive, retrieve character information, and interact with other characters.

2. **Teams**: The program introduces a `Team` class that represents a group of characters. The `Team` class allows for creating teams, adding members to a team, performing team-based attacks, and retrieving information about the team and its members.

3. **Character Types**: The program includes specific character types derived from the `Character` class, such as `Cowboy` and Derived classes of `Ninja`. These derived classes add unique attributes and behaviors specific to each character type. For example, a `Cowboy` class introduces the concept of ammunition and shooting enemies, while a `Ninja` class focuses on movement and slashing enemies.

4. **Class Interactions**: The program facilitates interactions between characters and teams by providing methods to calculate distances, track damage dealt, find the closest character from a group, and perform attacks. These interactions allow for simulating gameplay scenarios and evaluating the outcome of character interactions.

## Class Overview

The program consists of the following classes:

 1. **Point**: Represents a two-dimensional point on a coordinate plane and provides methods for manipulating and querying points.

2. **Character**: Serves as the base class for different character types. It defines common attributes and behaviors for characters, such as health points, location, and interaction methods.

3. **Cowboy**: A derived class of `Character` that represents a cowboy character type. It adds the concept of ammunition and shooting enemies.

4. **Ninja**: A derived class of `Character` that represents a ninja character type. It introduces additional attributes and behaviors specific to ninjas, such as speed and slashing enemies.

5. **YoungNinja, TrainedNinja, OldNinja**: Derived classes of `Ninja` that represent different subclasses of ninjas with varying characteristics. These classes demonstrate inheritance and allow for customization of ninja types.

6. **Team**: Represents a team of characters. It allows for creating teams, adding members, performing team-based attacks, and retrieving information about the team and its members. While in `Team` object all the cowboys will shoot before any ninja will act, in `Team2` the attacking order is depends on the inseration order. On the other hand, `SmartTeam` provide a uniqe way to attack, by adapting a new strategy each round, featuring focusing in low health enemies and strong types of characters. 

## Usage

To use the program, you can create instances of different characters, organize them into teams, and simulate gameplay scenarios. Each class provides specific methods and attributes to interact with and manipulate characters and teams.

Example usage:

1. Create instances of characters, such as cowboys and ninjas, by instantiating the respective classes.

2. Create teams using the `Team` class and add characters to the teams.

3. Simulate interactions between characters and teams by calling the appropriate methods, such as attacking enemies or moving characters.

4. Retrieve information about characters, teams, and their attributes to analyze the game state and make decisions.

Please refer to the code documentation and class definitions for detailed information on available methods, attributes, and their usage. My recommendation:

    while(team_A.stillAlive() > 0 && team_B.stillAlive() > 0){
        team_A.attack(&team_B);
        team_B.attack(&team_A);
        // team_A.print();
        // team_B.print();
    }

## Contributing

If you wish to contribute to this program, you can follow the standard procedures for code contribution. Fork the repository, make your changes, and submit a

## Analysis

I conducted an analysis to determine which character type dealt the most damage in a single round. To achieve this, I created 400 random teams of 10 characters, with a distribution of:

* 40% Cowboys
* 20% YoungNinjas
* 20% TrainedNinjas
* 20% OldNinjas

I recorded the winner team of each round, and calculated the amount of damage dealt by each character, categorized by their class character types. This enabled me to calculate the average damage each type does in each game with good probability:

    Cowboy:  202.74
    Young:   748.37
    Trained: 742.22
    Old:     848.90

![image](https://github.com/AlonMesh/Cowboy_vs_ninja_B/assets/97172662/73239954-eb02-4a95-8f1b-cc554b53e7fe)

The average damage divided by the character's HP amount:

(Which means: For each 1 HP of a character, it deals this amount of damage)

    Cowboy:  1.8431
    Young:   7.4837
    Trained: 6.1852
    Old:     5.6593
    
![image](https://github.com/AlonMesh/Cowboy_vs_ninja_B/assets/97172662/a4906266-be9e-4c45-b1f0-c9b295f267a1)

You can see the full data in data.csv.
