# Task Manager - C Project

A command-line task management application built in C.

## Project Structure

```
TaskManager/
├── include/
│   ├── task.h       - Task structure and function declarations
│   ├── file_io.h    - File I/O function declarations
│   └── ui.h         - User interface function declarations
├── src/
│   ├── main.c       - Main entry point
│   ├── task.c       - Task management implementation
│   ├── file_io.c    - File I/O implementation
│   └── ui.c         - User interface implementation
├── data/
│   └── tasks.dat    - Persistent storage for tasks
└── Makefile         - Build configuration
```

## Features to Implement

- [x] Project structure
- [ ] Dynamic task list creation and management
- [ ] Add new tasks with priority and due date
- [ ] Display all tasks
- [ ] Mark tasks as complete/incomplete
- [ ] Delete tasks
- [ ] Search tasks by keyword
- [ ] Sort tasks by priority or due date
- [ ] Save tasks to file (binary format)
- [ ] Load tasks from file
- [ ] Interactive menu system

## Compilation

```bash
make          # Build the project
make run      # Build and run
make clean    # Remove build artifacts
```

## Implementation Order

1. **task.c** - Implement core task management functions
2. **file_io.c** - Implement file save/load functionality
3. **ui.c** - Implement the interactive menu
4. **main.c** - Wire everything together
