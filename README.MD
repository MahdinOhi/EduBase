Skip to content
Files
Commands
Search
#ifndef core_lib
#define core_lib

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 3
#define MIN_KEYS (MAX_KEYS / 2)

typedef struct CoreNode {
  bool is_leaf;
  int num_keys;
  int keys[MAX_KEYS];
  struct CoreNode *children[MAX_KEYS + 1];
  struct CoreNode *next;
} CoreNode;

// B+ Tree structure
typedef struct {
  CoreNode *root;
} Core;

Core *create_bplus_tree(void);
void insert_bplus_tree(Core *tree, int key);
CoreNode *search_bplus_tree(Core *tree, int key);
void delete_bplus_tree(Core *tree, int key);
void print_bplus_tree(Core *tree);

#endif
🎓 EduBase
Welcome to EduBase! This is a student-level project designed to create a simple lightweight Database Management System (DBMS) for managing student portal data. Built entirely in C and powered by B+ Trees, EduBase ensures fast and efficient data storage and retrieval. 🌟

🚀 Project Overview
EduBase is a practical implementation of a simple DBMS designed for educational purposes. It focuses on managing:

📁 Student records
📄 Course information
🔍 Efficient data access using B+ Tree indexing
🛠️ Features
📂 CRUD Operations: Easily create, read, update, and delete records
⚡ High Performance: Utilizes B+ Trees for fast data access
🎯 Educational Focus: Simple and beginner-friendly design
🔍 Modular Code: Organized for better readability and maintainability
💻 Tech Stack
Programming Language: C
📋 How to Run
Clone the repository:

git clone https://github.com/YourUsername/EduBase.git
Navigate to the project directory:

cd EduBase
Compile the code:

gcc main.c -o EduBase
Run the program:

./EduBase
📚 Learning Objectives
Implement and understand B+ Tree indexing
Learn the basics of building a DBMS from scratch
Collaborate effectively using project management techniques
🤝 Contributing
We’d love to have your contributions! To contribute:

Fork the repository
Create a new branch (git checkout -b feature-name)
Commit your changes (git commit -m "Add a cool feature")
Push your branch (git push origin feature-name)
Open a Pull Request
📧 Contact
For questions or feedback, reach out at:
📩 mahdinislamohi@gmail.com

🌟 EduBase is built by students, for students, as a learning project. Happy coding! 🎉

🔥 Let us know if you'd like further tweaks!

- Replit