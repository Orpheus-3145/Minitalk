# Minitalk
Basic setup client-server communication


# Overview
First, the communication relies on the two signals: SIGUSR1 and SIGUSR2; a string (received in input) is sent from the client to the server, after the process is ended the message will be printed from the server, also the client aknowledges the end of the task. First the server must be executed, it will print its PID; then we can run the client giving it two arguments:
    - the server PID
    - the message to send (double quotes for multiple words)

It is possible to send multiple messages in differente call with stopping the server


# Structure
- **include/**   -->  header files
- **objects/**   -->  deposit for object files
- **sources/**   -->  source files:
                          - client.c
                          - server.c
- **libft/**     -->  libft directory with auxiliary functions
- **test_read/** -->  some test to stress the client-server


# Execute
- command `make` creates the two executables: server and client
- `server` must be executed first, 
- `client` follows with the arguments
- other make commands: `re`, `clean`, `fclean`


# Info
    1) the server does not print the full message after the last symbol 
    is gained, instead it prints a character every time 8 bits are received: so it can be
    interrepted due to crashes on client-side, but still can send something before 
    the communication goes down
    2) it is possible to use both ASCII and UTF-8 characters


# References
- 42 project: [minitalk](https://cdn.intra.42.fr/pdf/pdf/68781/en.subject.pdf)
- by: Francesco Aru, francesco.aru25@gmail.com, intra42/slack nickname: @faru, Codam, Amsterdam
