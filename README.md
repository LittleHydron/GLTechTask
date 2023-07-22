This is a program, that searches for a file in your filesystem.


To build it, you have to execute following commands from 'build' directory:

  "cmake .."
  
  "cmake --build ."


Then, you can run it using this commands:

  "cd app"
  
  "sudo ./App"


How does it work:

First, the processRoot() method from app/main.cpp is called. It creates threads for every subdirectory of root folder ('/' for Linux) using a ThreadPool object.

Then, inside of each thread, findFileOrDirectory() method uses DFS-like approach to traverse through your filesystem and find targetFile.

If targetFile is found, all the threads will be stopped and full path to the file will be printed out.

If file was not found, "File not found!" phrase will appear.
