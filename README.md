# multithreading socket programm for linux


This is a multithreaded socket program for Linux consisting of two programs that interact with each other using sockets.

Program #1
The program should have two threads and one shared buffer. The first thread accepts a string from the user and checks if it consists only of digits and does not exceed 64 characters. If the string passes the check, it is sorted in descending order and all even elements are replaced with the letters "KB". The resulting string is then placed in the shared buffer, and the thread waits for more input from the user. The second thread processes the data in the shared buffer, displays it on the screen, calculates the total sum of all numerical values, and sends the sum to Program #2. The threads must be synchronized, and the synchronization mechanism should not be a global variable. The program should be independent of the status of Program #2, and a sudden shutdown of Program #2 should not cause immediate input problems for the user.

Program #2
The program expects data from Program #1 and performs an analysis to determine the number of characters in the transmitted value. If the value has more than two characters and is a multiple of 32, the program displays a message about the received data. Otherwise, an error message is displayed. The program should be independent of the status of Program #1, and a sudden shutdown of Program #1 should not cause immediate display problems. When the connection between the programs is lost, Program #2 should expect the reconnection of Program #1.
