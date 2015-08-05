ReadMe:

1) The compile.bat is present in the folder OODProj3 file.

2) There are seperate run.bat files for sender and receiver. 
         - The run.bat for the sender is there in the path 
             " OODProj3\Sender\Sender". 
         - The run.bat for the for the receiver is there in the path 
             " OODProj3\Receiver"

3) If any test files are to be added should be added in this path " OODProj3\Sender\Sender". 

4) After sending the files from the sender, the files that are uploaded in to the receiver will be 
   in the path  " OODProj3\Receiver"

5)The receiver takes the argument, port number
            To run this:start ..\Debug\Receiver.exe "#portnumber" 

6) The sender takes the arguments ListenerPort,IPAdresstosend, ReceiverPort, Command(text/ file), Contentto send. Arguments should be provided only in this order.
        "8080" "127.0.0.1" "40004" "file" "text.txt"-------> if it is a file, then file name is given as message content.
        "8080" "127.0.0.1" "40004" "text" "sampleMessage to send"-------> if it is a text, then text content is sent as MessageContent.

7) Receiver accepts both text and binary files.

8) The Code Available in the below stated link is used as an reference:
        http://ecs.syr.edu/faculty/fawcett/handouts/CSE687/code/Project3HelpS14/
         
                