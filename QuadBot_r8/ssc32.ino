/* This function sends the constructed command to the SSC32.
Then delays to give the servos time to move before we send
another command.  It also clears the String command so we
are free to build another command.
*/
void execute_command(){

    // write string to SSC-32
    Serial1.println(command);
    // clear command buffer string
    command = "";

}

/* This function accepts a servo number, 
a position to move to, and the time it 
has to move there and formats it for 
the SSC-32.  Offsets are applied here
also.*/
void make_command(int servo, int position, int time) {
    //Apply offsets
    switch (servo) {
     default:   
        break;
    }
  
    //Form command
    command += "#";
    command += (servo);
    command += " P";
    command += (position);
    command += " T";
    command += (time);
    command += " ";

}

