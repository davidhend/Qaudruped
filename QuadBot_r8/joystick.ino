void parse_and_convert_data(){
    // parse data
    int first_start = data.indexOf('l_ud:');
    int first_end = data.indexOf('!', first_start+1);
    String left_ud = data.substring(first_start+1, first_end);
    
    int second_start = data.indexOf('l_lr:', first_end+1);
    int second_end = data.indexOf('!', second_start+1);
    String left_lr = data.substring(second_start+1, second_end);    
    
    int third_start = data.indexOf('r_ud:', second_end+1);
    int third_end = data.indexOf('!', third_start+1);
    String right_ud = data.substring(third_start+1, third_end); 
  
    int fourth_start = data.indexOf('r_lr:', third_end+1);
    int fourth_end = data.indexOf('!', fourth_start+1);
    String right_lr = data.substring(fourth_start+1, fourth_end);  
   
    int fifth_start = data.indexOf('mode:', fourth_end+1);
    int fifth_end = data.indexOf('!', fifth_start+1);
    String remote_mode = data.substring(fifth_start+1, fifth_end);
    
    // convert strings to ints
    left_ud_int = left_ud.toInt();
    left_lr_int = left_lr.toInt();
    right_ud_int = right_ud.toInt();
    right_lr_int = right_lr.toInt();
    remote_mode_int = remote_mode.toInt();
    
    /*
    //display data
    Serial.print("Left UD: ");
    Serial.print(left_ud_int);
    Serial.print("  ");
    Serial.print("Left LR: ");
    Serial.print(left_lr_int);
    Serial.print("  ");
    Serial.print("Right UD: ");
    Serial.print(right_ud_int);
    Serial.print("  ");
    Serial.print("Right LR: ");
    Serial.print(right_lr_int);
    Serial.print("    Mode : ");
    Serial.println(remote_mode_int);
    */
    
}
