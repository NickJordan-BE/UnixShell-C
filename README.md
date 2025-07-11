🐚 Shelldon — A Custom Unix Shell in C
Shelldon is a minimalist Unix shell built from scratch in C, designed to provide hands-on experience with systems programming, including process control, input parsing, file redirection, and piping. It emulates core functionality found in popular shells like Bash and Dash, while maintaining a clean and extensible codebase.

🚀 Features
✅ Core Functionality
Interactive Shell Loop
Displays a prompt (dash>) and continuously accepts user commands.

Command Execution

Built-in commands (e.g., cd, exit, pwd, echo)

External commands via execvp() (e.g., ls, cat, wc)

I/O Redirection

Input (<)

Output (>)

Append (>>)

Piping Support

Multi-stage pipes supported (e.g., ls | grep .c | wc -l)

Command History

In-memory tracking of commands (e.g., history)

Displays recent commands from session

🧰 Built-In Commands
Command	Description	Example
cd	Change directory	cd ~/projects
exit	Exit the shell	exit
help	Show supported commands	help
pwd	Print current working directory	pwd
echo	Print to standard output	echo Hello World!
clear	Clear the terminal screen	clear
history	Show previously entered commands	history
sizeof	Print number of arguments passed	sizeof ls -la
grep	Search lines matching a pattern in file	grep main main.c

🧪 External Commands
Supported via execvp(), any valid system binary in your $PATH can be executed.

Examples: ls, cat, sort, head, tail, diff, wc, top, ps, etc.

🔧 Design Overview
Shelldon is split into modular components for clarity and ease of development:

main.c
Entry point that initializes the shell and launches the REPL loop.

shell.c
Implements the main interactive loop. Handles prompt display, reading input, and coordinating parsing + execution.

parser.c
Responsible for tokenizing user input, splitting by pipes or redirection symbols, and building structured argument lists.

commands.c
Implements built-in commands such as cd, exit, echo, pwd, etc.
Dispatches commands that must be handled within the current process.

external.c
Handles execution of external programs using fork(), execvp(), and waitpid().

redirection.c
Manages input (<), output (>), and append (>>) redirection.
Modifies file descriptors appropriately using dup2() before execution.

piping.c
Supports single and multi-stage pipes by creating and managing file descriptors.
Routes stdout/stdin between processes in a pipeline.

handler.c
Acts as a coordinator — decides if the command is built-in or external, and routes execution through the correct logic.

🧪 Example Commands to Try
bash
Copy code
ls -la | grep .c | wc -l
cat input.txt > output.txt
sort < unsorted.txt > sorted.txt
cd src
pwd
echo Hello World!
history
📚 Key Concepts Used
fork(), execvp(), waitpid()

pipe(), dup2()

chdir(), getcwd()

String parsing and tokenization

Dynamic memory allocation (malloc, free)

ANSI escape codes for terminal control

🔮 Possible Future Work
Background job execution (&)

jobs, fg, bg support

Persistent command history

Tab completion

Scripting support

🧑‍💻 Author
Nicholas Jordan
Computer Science @ University of Washington Tacoma
GitHub: NickJordan-BE

