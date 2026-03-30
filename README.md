# Task Processing System

## Program Overview
This program is used to manage tasks using three data structures:
- Queue for normal tasks (FIFO)
- Deque for priority tasks
- Stack for undo

Users can add tasks, process tasks, undo last action, and display all tasks.

## Features
- Add normal task
- Add priority task
- Process task
- Undo last action
- Show all tasks

## How to Run
```bash
gcc main.c -o task
./task
```

## Sample Execution

Input:
1 → Task A  
1 → Task B  
2 → Task X  
5  

Output:
--- Priority Tasks (Deque) ---
- Task X

--- Normal Tasks (Queue) ---
- Task A  
- Task B  

## Input to Output
User input is checked:
- Normal → goes to queue  
- Priority → goes to deque  

When processing:
- Priority tasks are processed first  
- Then normal tasks  

Undo uses stack to remove the last action.
